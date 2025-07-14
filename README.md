# Smart Fish Tank Monitoring System
An IoT-based intelligent monitoring system for small to medium scale aquariums, designed to help users maintain ideal living conditions for aquatic life by tracking key environmental parameters in real time.

## Purpose
Aquarium owners and aquaculture professionals often struggle to manage multiple tanks efficiently due to limited resources and manual labor. This project offers a **cost-effective, automated solution** using **ESP32 microcontrollers** and various **sensors** to monitor essential water conditions, notify users, and help ensure healthy aquatic environments.

## Features

| Parameter                | Description                                                                                       |
| ------------------------ | ------------------------------------------------------------------------------------------------- |
| Temperature Monitoring   | Alerts the user if the water temperature goes out of the optimal range set by the user.           |
| Feeding Alerts           | Notifies the user to feed the fish based on a custom schedule.                                    |
| Water Level Monitoring   | Uses an ultrasonic sensor to detect low or high water levels, triggering alerts accordingly.      |
| Turbidity Detection      | Alerts the user when water becomes cloudy or dirty, indicating a need for filtration or cleaning. |

## System Overview

* Microcontroller: ESP32
* Sensors: Temperature sensor, ultrasonic sensor, turbidity sensor
* Connectivity: Wi-Fi (for cloud/database access)
* Data Storage: Sends data to an online database
* User Access: Mobile app or web app interface
* Alerts: Real-time notifications for parameter deviations

## Technologies Used

* Hardware: ESP32, sensors (DHT11/DS18B20, HC-SR04, turbidity sensor)
* Software: Arduino IDE, Firebase (or similar), Flutter/Web (for UI)
* Communication: Serial, Wi-Fi (MQTT or HTTP)

## User Interface

Users can access:
  * Live data from their fish tanks
  * Historical records of parameter readings
  * Alerts and reminders (push notifications, in-app, or email)

## Getting Started

### Requirements
  * ESP32 board
  * Required sensors connected to ESP32
  * Wi-Fi access
  * Firebase
  * web app connected to backend

## Future Enhancements / improvments

* Automated feeding module
* Water filtration automation
* Fish species-specific preset profiles
* AI-based health prediction (based on sensor data trends)

## Contributors

* IT23184558 - D B Y Binuwara
* IT23194830 - M.P. Cooray
* IT23442566 - M.V.M. Linash
* IT23283312 - P.W.K.W. Rupasinghe 
