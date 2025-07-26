#define BLYNK_TEMPLATE_ID "TMPL5mOTYeXsR"
#define BLYNK_TEMPLATE_NAME "Smart Helmet"
#define BLYNK_AUTH_TOKEN "WtIgkYGmi8jecjWNdS05csI7V-Vrk7Gg"

const char* ssid = "8085";
const char* password = "1234@1234";

#define PCA9548A_ADDR 0x70

#define HELMET_PIN  14 // D5
#define RELAY_PIN   13 // D7
#define MQ3_PIN     A0
#define Push_button 12 // D6

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <MPU6050.h>
#include <MAX30100_PulseOximeter.h>

MPU6050 mpu;
PulseOximeter pox;
TinyGPSPlus gps;
BlynkTimer timer;

float BPM;
float SpO2;
bool accidentDetected = false;
bool alert_send = false;
float prev_acc = 0;
float current_acc = 0;
double lastLat = 0.0, lastLng = 0.0;
uint32_t tsLastReport = 0;

void selectMuxChannel(uint8_t channel) {
  if (channel > 7) return;
  Wire.beginTransmission(PCA9548A_ADDR);
  Wire.write(1 << channel);
  Wire.endTransmission();
}

void sendToBlynk() {
  if (accidentDetected && !alert_send) {
  Blynk.logEvent("accident", "⚠️ Accident Detected!");
  alert_send = true;
  }
  Blynk.virtualWrite(V1, BPM);
  Blynk.virtualWrite(V2, SpO2);
  Blynk.virtualWrite(V3, current_acc);
  Blynk.virtualWrite(V4, accidentDetected ? "Accident Detected" : "Safe");
  Blynk.virtualWrite(V5, lastLat);
  Blynk.virtualWrite(V6, lastLng);

  Serial.println("------ Blynk & Serial Report ------");
  Serial.print("Heart Rate: "); Serial.print(BPM); Serial.println(" BPM");
  Serial.print("SpO2: "); Serial.print(SpO2); Serial.println(" %");
  Serial.print("Acceleration: "); Serial.print(current_acc); Serial.println(" g");
  Serial.print("Status: "); Serial.println(accidentDetected ? "Accident Detected" : "Safe");
  Serial.print("Location: Lat "); Serial.print(lastLat, 6);
  Serial.print(", Lng "); Serial.println(lastLng, 6);
  Serial.println("-----------------------------------");
}

void setup() {
  Serial.begin(9600);   // GPS + debug on same line
  Wire.begin(4, 5);

  pinMode(HELMET_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(Push_button, INPUT_PULLUP);
  digitalWrite(RELAY_PIN, HIGH);

  selectMuxChannel(0);
  mpu.initialize();

  selectMuxChannel(2);
  pox.begin();
  pox.setIRLedCurrent(MAX30100_LED_CURR_27_1MA);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  timer.setInterval(1000L, sendToBlynk);

  Serial.println("System ready...");
}

void loop() {
  Blynk.run();
  timer.run();

  // Helmet & alcohol logic
  bool helmetWorn = digitalRead(HELMET_PIN);
  int alcoholValue = analogRead(MQ3_PIN);
  bool isDrunk = (alcoholValue > 700);
  if (!accidentDetected) {
    if (!helmetWorn && !isDrunk) {
      digitalWrite(RELAY_PIN, LOW);
      Serial.println("Helmet worn and not drunk");
    } else if (isDrunk) {
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println("Drunk");
    } else {
      digitalWrite(RELAY_PIN, HIGH);
      Serial.println("Helmet not worn");
    }
  }

selectMuxChannel(0);  // MPU channel

int16_t ax, ay, az;
mpu.getAcceleration(&ax, &ay, &az);

float ax_g = (float)ax / 16384.0;
float ay_g = (float)ay / 16384.0;
float az_g = (float)az / 16384.0;
current_acc = sqrt(ax_g * ax_g + ay_g * ay_g + az_g * az_g);  // current reading

// ----------- Get Gyroscope -------------
int16_t gx, gy, gz;
mpu.getRotation(&gx, &gy, &gz);
float gx_rad = (gx / 131.0) * (PI / 180.0);
float gy_rad = (gy / 131.0) * (PI / 180.0);
float gz_rad = (gz / 131.0) * (PI / 180.0);
float gyro_mag = sqrt(gx_rad * gx_rad + gy_rad * gy_rad + gz_rad * gz_rad);

// ----------- Compare with Previous Reading -------------
float acc_diff = abs(current_acc - prev_acc);

// ----------- Detect Event Based on Acceleration Difference -------------
if (acc_diff > 1.2 && gyro_mag >= 0.01) {
  Serial.println("Collision detected !");
  accidentDetected = true;
}
else if (acc_diff > 0.8 && gyro_mag >= 0.005 && gyro_mag <= 0.04) {
  Serial.println("fall detected !");
  accidentDetected = true;
}
else {
  Serial.println("Safe till now !");
}

  // MAX30100
  selectMuxChannel(2);
  pox.update();
  if (millis() - tsLastReport > 1000) {
    tsLastReport = millis();
    BPM = pox.getHeartRate();
    SpO2 = pox.getSpO2();
  }

  // GPS update directly on Serial
  while(Serial.available() > 0) {
    gps.encode(Serial.read());
    if (gps.location.isUpdated()) {
      lastLat = gps.location.lat();
      lastLng = gps.location.lng();
    }
  }

  // Manual cancel
  if (accidentDetected && digitalRead(Push_button) == LOW) {
    accidentDetected = false;
    alert_send = false;
    Serial.println("Button pressed. Accident cleared.");
  }
  prev_acc = current_acc;
}
