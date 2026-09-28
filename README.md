# ☀️ Smart Solar Panel Tracking + Protection

## 📌 Project Description

**Smart Solar Panel Tracking + Protection** is a low-cost, Arduino-based solar energy system that automatically adjusts the position of a solar panel according to the direction of maximum sunlight while providing basic environmental protection through rain detection.

The system uses *four LDR (Light Dependent Resistor) sensors* to detect differences in sunlight intensity from different directions. An *Arduino Mega 2560* processes these readings and controls a *servo motor* to adjust the solar panel toward the direction receiving greater sunlight.

A *raindrop sensor* is incorporated to detect rainfall and initiate the programmed protection response. An *OLED Display (128×64)* provides real-time information about the system status.

The complete system is initially developed and tested through **Wokwi simulation** before physical implementation.

<img width="1232" height="862" alt="image" src="https://github.com/user-attachments/assets/92306086-5bab-41aa-b824-8c591e4eb320" />

---

## 🎯 Objectives

- Automatically track the direction of maximum sunlight.
- Improve solar panel orientation throughout the day.
- Use multiple LDRs for adaptive sunlight detection.
- Automatically control the panel using a servo motor.
- Detect rainfall using a raindrop sensor.
- Provide a suitable protective response during rain.
- Display important system parameters in real time.
- Develop a simple, low-cost and practical solar tracking solution.

---

## ✨ Key Features

- 🌞 **Automatic Solar Tracking**
  - Uses four LDR sensors to detect the direction of stronger sunlight.

- 🔄 **Automatic Panel Positioning**
  - A servo motor adjusts the solar panel according to the detected sunlight direction.

- 💡 **Multi-Sensor Light Detection**
  - Four LDRs provide directional sunlight information for adaptive tracking.

- 🌧️ **Rain Detection**
  - Detects rainfall using a raindrop sensor.

- 💨 **Wind Detection**
  - Monitors wind conditions to help protect the solar panel during strong winds.

- 🛡️ **Environmental Protection**
  - Uses rain and wind conditions as inputs for the panel protection mechanism.

- 📟 **Real-Time OLED Monitoring**
  - Displays system information using an OLED Display (128×64).

- 💰 **Low-Cost Design**
  - Uses affordable and easily available components.

- 🧪 **Simulation-Based Development**
  - The system is designed and tested using Wokwi before physical implementation.

---
