🌱 Smart Irrigation System using ESP32

A beginner-friendly embedded systems project built using ESP32 (via Wokwi simulation) that waters plants automatically based on soil moisture and also supports manual pump control.

📌 Description

This project monitors soil moisture, temperature, and humidity in real time.
If the soil becomes dry, the pump turns ON automatically (Auto Mode).
The system also has Manual Mode, where the user can press a push-button to control the pump manually.

The OLED display shows:

Soil moisture value

Temperature and humidity

Current mode (AUTO / MANUAL)

Pump status (ON / OFF)

🧰 Components

ESP32 microcontroller

DHT22 temperature & humidity sensor

Soil moisture sensor (simulated with potentiometer)

SSD1306 OLED display

Push-button (for Manual Mode)

LED (simulating water pump)

Breadboard & jumper wires (for physical build)

📋 Code (main_code.ino)

See the code file in this repository.

🔗 Simulation Link

Test the smart irrigation system online using Wokwi:
https://wokwi.com/projects/448384460053331969

🚀 Future Improvements

Add Blynk or mobile app control

Add rain sensor and water-level sensor

Add solar panel or battery backup

Enable remote notifications when pump starts/stops
