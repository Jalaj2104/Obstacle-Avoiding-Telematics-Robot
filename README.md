# Obstacle Avoiding Robot with Air Quality Monitoring 🚗🌫️

This is an Arduino-based robot that **automatically avoids obstacles** and **monitors air quality** using the MQ-135 gas sensor. Designed as a beginner-friendly embedded systems project, it combines real-time movement control with environmental sensing.

---

## 🔧 Features
- ✅ Obstacle detection using an ultrasonic sensor
- ✅ Smart directional turning using a servo motor
- ✅ Real-time air quality monitoring (in PPM) printed on the Serial Monitor
- ✅ Built using Adafruit Motor Shield and custom 2S2P battery pack

---

## 🧰 Components Used
- Tyres (x4)
- DC Motors (x4)
- MQ-135 Air Quality Sensor
- Ultrasonic Sensor (HC-SR04)
- Servo Motor
- Li-ion Batteries (2S2P setup, 3.7V each)
- Arduino Uno
- Adafruit Motor Shield
- Push Switch (used for powering robot manually)

---

## 📂 Files Included
- `obstacle_avoiding_air_quality.ino` – Main Arduino source code
- `images/` – Pictures of the final robot 
- `videos/` – Demo video link or embedded preview

---

## ⚙️ How It Works
1. **Obstacle Avoidance**  
   The ultrasonic sensor detects obstacles ahead. On detection, the servo rotates the sensor to scan both sides and the robot turns in the clearer direction before continuing forward.

2. **Air Quality Monitoring**  
   The MQ-135 gas sensor continuously reads air quality data and prints PPM values to the Serial Monitor, along with a simple interpretation like **Good**, **Moderate**, or **Poor**.

---

## ⚠️ Known Issues
- The motors work well **only for a few seconds** and then slow down or stop. This appears to be a **battery voltage issue** likely due to insufficient current output under load.
- Sensor readings (especially ultrasonic) may become unstable at low voltage.

> For demonstration and submission purposes, a short runtime video works reliably.

---

## 📸 Snapshots
https://github.com/Jalaj2104/Obstacle-Avoiding-Telematics-Robot/tree/main/videos
https://github.com/Jalaj2104/Obstacle-Avoiding-Telematics-Robot/tree/main/images
