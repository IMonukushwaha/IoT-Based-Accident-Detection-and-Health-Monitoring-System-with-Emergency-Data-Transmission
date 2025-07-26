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
