# IoT-Based-Accident-Detection-and-Health-Monitoring-System-with-Emergency-Data-Transmission
# Introduction 
Two-wheeler riders are among the most vulnerable road users, primarily due to the lack of 
physical protection compared to four-wheeler occupants. In countries like India, the high rate of 
two-wheeler accidents often results in severe injuries or fatalities, many of which are linked to 
not wearing helmets, speeding, alcohol influence, and non-compliance with traffic rules. 
According to government data, thousands of lives could be saved each year through better safety 
practices and quicker emergency response. 
To address these challenges, modern technologies such as the Internet of Things (IoT) and 
machine learning (ML) offer powerful tools to enhance rider safety through smart, real-time 
monitoring systems. By combining sensors and connectivity, IoT enables continuous tracking of 
critical data like motion, location, and vital signs. Integrating machine learning further improves 
decision-making by accurately detecting abnormal conditions such as crashes. 
This project introduces a Smart Helmet system designed specifically for two-wheeler riders. It 
focuses on following core safety functions: 
1. Helmet Usage Enforcement 
a. An IR sensor is used to detect whether the rider is wearing the helmet. 
b. The ignition system is enabled only when the helmet is properly worn, ensuring 
mandatory helmet usage. 
2. Alcohol Detection 
a. The MQ3 gas sensor analyzes the rider’s breath to detect alcohol consumption. 
b. If alcohol levels exceed a defined threshold, the system disables ignition to 
prevent drunk driving. 
3. Accident Detection and Alerting 
a. An MPU6050 accelerometer and gyroscope module detects abnormal motion 
patterns such as sudden impacts or falls. 
b. In case of an accident, the system initiates an alert sequence automatically. 
4. Health Monitoring 
a. The MAX30100 pulse oximeter continuously monitors the rider’s heart rate 
(BPM) and blood oxygen level (SpO2) during the ride. 
b. These vitals are helpful in assessing the rider's condition after a crash. 
5. Location Tracking with GPS 
a. A NEO-6M GPS module provides real-time geographic coordinates. 
b. The location data is sent to the cloud and can be used for emergency response. 
6. Cloud Connectivity and Real-Time Monitoring 
a. The system uses an ESP8266 NodeMCU microcontroller to transmit data over 
Wi-Fi. 
b. All sensor data (vitals, location, motion) is displayed in real time on the Blynk 
IoT platform. 
7. Machine Learning Integration 
a. Sensor data from the MPU6050 is used to train a Random Forest Classifier. 
b. This model improves the accuracy of accident detection by distinguishing 
between normal and crash-like motion. 
8. False Alert Control 
a. A manual push button is included to cancel or override false accident alerts if 
triggered unintentionally. 
9. Efficient Sensor Management 
a. A PCA9548A I2C multiplexer is used to handle multiple I2C devices efficiently, 
allowing stable communication between sensors and the microcontroller. 
This integrated approach not only promotes safer riding habits but also reduces response time in 
emergencies, showcasing a practical and life-saving application of IoT and AI in personal 
protective equipment.

# implementation part
1.)Data Collection using MPU6050 Sensor 
To begin the machine learning process, data related to motion, and orientation was collected 
using the MPU6050 sensor, which combines a 3-axis accelerometer and a 3-axis gyroscope. The 
data includes six parameters: 
• Ax, Ay, Az (Acceleration in X, Y, Z directions) 
• Gx, Gy, Gz (Gyroscopic angular velocity in X, Y, Z directions) 
A Python script was used to collect this data via the Serial COM port from the ESP8266 
NodeMCU. The values were read continuously and stored in a CSV file along with timestamps.
2.)Data Preprocessing 
To prepare the sensor data for machine learning, the following preprocessing steps were applied 
using Python's pandas and NumPy libraries: 
• Unit Conversion: 
The gyroscope readings were converted from degrees per second to radians per second: 
• Magnitude Calculations: 
o Gyroscope magnitude (in radians/sec): 
gyro_mag_rad = √(𝐺𝑥2 + 𝐺𝑦2 +𝐺𝑧2)
 o Acceleration magnitude: 
Acceleration=  √(𝐴𝑥2 + 𝐴𝑦2 + 𝐴𝑧2)
 • Labeling: 
Each dataset was assigned a corresponding Outcome: 
o "Standing" 
o "Fall" 
o "Collision" 
3.) Model Training 
A supervised machine learning model was trained to classify the type of activity (Standing, Fall, 
Collision) based on sensor data. The RandomForestClassifier from scikit-learn was selected for 
its robustness and ability to handle nonlinear patterns in data. 
• Steps followed: 
o Encode labels using LabelEncoder. 
o Split the data into training and test sets. 
o Train the Random Forest classifier. 
o Evaluate model accuracy and performance. 
import pandas as pd 
from sklearn.ensemble import RandomForestClassifier
4.) Hardware Implementation 
This project integrates various sensors and electronic modules to enhance the safety of two
wheeler riders. The implementation involves real-time monitoring of physiological and 
environmental data, accident detection, and wireless communication using the ESP8266 
microcontroller. The hardware components and their roles in the system are detailed below: 
1. Microcontroller: ESP8266 NodeMCU 
• Purpose: Acts as the central control unit for reading sensor data, processing it, and 
transmitting it to the Blynk IoT cloud platform. 
• Features Used: 
o Wi-Fi for cloud communication. 
o GPIOs for sensor integration. 
o Serial communication for GPS and debugging. 
2. Helmet Detection (IR Sensor) 
• Pin Used: D5 (GPIO14) 
• Function: Detects whether the rider is wearing a helmet. 
• Logic: If the helmet is not worn, the ignition relay remains OFF to prevent vehicle 
starting. 
3. Alcohol Detection (MQ-3 Gas Sensor) 
• Pin Used: A0 
• Function: Detects alcohol in the rider’s breath. 
• Logic: 
o If the alcohol value exceeds a predefined threshold (>700), the system disables 
ignition. 
o Ensures that the rider is sober before starting the vehicle. 
4. Ignition Control (Relay Module) 
• Pin Used: D7 (GPIO13) 
• Function: Controls power to the ignition system. 
• Safety Enforcement: 
o Ignition is allowed only when the helmet is worn, and no alcohol is detected. 
o Otherwise, the relay remains off, blocking vehicle start. 
5. Accident Detection 
• Sensors: MPU6050 Accelerometer + Gyroscope 
• Pin Interface: I2C via PCA9548A multiplexer (channel 0) 
• Function: 
o Measures acceleration (ax, ay, az) and angular velocity (gx, gy, gz). 
o Computes total acceleration and gyroscopic magnitude. 
o Detects anomalies such as collisions or falls based on sudden changes in sensor 
values. 
• Detection Logic: 
o Collision: Large spike in acceleration difference and gyro magnitude. 
o Fall: Moderate but consistent movement in both sensors. 
6. Health Monitoring 
• Sensor: MAX30100 Pulse Oximeter 
• Pin Interface: I2C via multiplexer (channel 2) 
• Function: 
o Measures heart rate (BPM) and blood oxygen saturation (SpO2). 
o Updates the Blynk dashboard every second for real-time monitoring. 
7. Location Tracking 
• Sensor: GPS Module (TinyGPS++) 
• Interface: Serial communication 
• Function: 
o Captures latitude and longitude in real time. 
o Sends location data to Blynk during normal operation and especially in case of an 
accident. 
8. Emergency Manual Cancel (Push Button) 
• Pin Used: D6 (GPIO12) 
• Function: 
o Allows the user to manually cancel a false accident detection. 
o Resets accidentDetected flag and prevents unnecessary alerts. 
 
9. I2C Multiplexer (PCA9548A) 
• Address: 0x70 
• Function: 
o Enables multiple I2C devices with the same address to communicate with the 
ESP8266. 
o Handles switching between the MPU6050 (channel 0) and MAX30100 (channel 
2).

# final Hardware setup 
![final_setup](https://github.com/user-attachments/assets/4ded5c2b-925f-47b1-8765-7bd80008f0c0)
# Result on Blynk Iot Cloud
<img width="1920" height="1080" alt="Screenshot (259)" src="https://github.com/user-attachments/assets/4050d421-17f0-4577-bb7c-3f4f8da10738" />
when locating the co-ordinates on the google map, we get the location of the setup
<img width="1831" height="980" alt="Screenshot (266)" src="https://github.com/user-attachments/assets/397760e0-6f8a-4bf3-a709-9394adfebe3a" />

