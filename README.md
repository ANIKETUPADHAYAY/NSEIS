# NeuralSense Environmental Intelligence System (NSEIS)

![Project Banner](https://drive.google.com/file/d/18EYG292KCIl6vR5p7rscMZPIUfQ3XR1-/view?usp=sharing)

<p align="center">
  <img src="YOUR_DRIVE_LINK_TO_PROTOTYPE_IMAGE_1" width="30%" alt="Prototype Side View">
  <img src="https://drive.google.com/file/d/1Q9Gj9WtWLV8TMrHCLqAZy4oBxy3G92ia/view?usp=sharing" width="30%" alt="ThingSpeak Dashboard">
  <img src="YOUR_DRIVE_LINK_TO_WIRING_IMAGE_3" width="30%" alt="Circuit Wiring">
</p>

**A compact, IoT-based system for real-time air quality and meteorological monitoring.** Using low-power sensors and cloud analytics, NeuralSense provides accurate pollutant and climate assessments for smart cities, homes, and environmental studies. It now features an advanced **Machine Learning Forecasting Engine** to predict future air quality trends.

---

## 📋 Table of Contents
* [Features](#-features)
* [Components Required](#-components-required)
* [Hardware Setup](#-hardware-setup)
* [Software & Libraries](#-software--libraries)
* [Cloud Setup (ThingSpeak)](#-cloud-setup-thingspeak)
* [Machine Learning Integration](#-machine-learning-integration)
* [Getting Started](#-getting-started)
* [Future Enhancements](#-future-enhancements)
* [Contributing](#-contributing)
* [License](#-license)

## ✨ Features
* **Real-Time Monitoring**: Measures Temperature, Humidity, and Air Quality (VOCs, smoke, CO2) simultaneously.
* **Wi-Fi Enabled**: Uses the ESP8266 NodeMCU to transmit data wirelessly.
* **Predictive Analytics**: Includes a Python-based Random Forest model to forecast air quality for up to 365 days.
* **Cloud Integration**: Seamlessly connects to **ThingSpeak** for instant data storage and visualization.
* **Zero-Config Dashboard**: Live graphs and historical data analysis are available immediately via the ThingSpeak platform.
* **Low Power & Compact**: Optimized code ensures efficient operation suitable for continuous monitoring.

## 🛠️ Components Required
| Component | Purpose | 
| :--- | :--- | 
| **NodeMCU ESP8266 V3** | Wi-Fi enabled microcontroller brain | 
| **MQ-135 Gas Sensor** | Detects air pollutants (VOCs, CO2, Smoke) | 
| **DHT11 Sensor** | Measures ambient temperature and humidity | 
| **Breadboard & Wires** | For prototyping and connections | 
| **Micro-USB Cable** | Power supply and programming interface | 

## 🔌 Hardware Setup

### Pin Connections
Connect the components according to the table below.

| Sensor | Sensor Pin | NodeMCU Pin | Notes |
| :--- | :--- | :--- | :--- |
| **DHT11** | VCC (+) | `3V3` | |
| | GND (-) | `GND` | |
| | DATA | `D2` (GPIO4) | |
| **MQ-135** | VCC | `3V3` | Needs warm-up time |
| | GND | `GND` | |
| | AOUT | `A0` | Analog reading |

## 💻 Software & Libraries

### Arduino Libraries
Install these via the Arduino Library Manager (`Sketch` > `Include Library` > `Manage Libraries...`):
1. **DHT sensor library** by Adafruit
2. **Adafruit Unified Sensor** by Adafruit
3. **ThingSpeak** by MathWorks
4. **MQ135** by GeorgK (Optional helper library)

## ☁️ Cloud Setup (ThingSpeak)

We selected **ThingSpeak** for this project because of its **ease of use**. Unlike other platforms that require complex database setup and frontend coding, ThingSpeak offers pre-built visualization tools and MATLAB integration out of the box.

**Steps to Configure:**
1.  **Create Account**: Sign up at [ThingSpeak.com](https://thingspeak.com/).
2.  **New Channel**:
    * Click **Channels** > **My Channels** > **New Channel**.
    * Name it: `NeuralSense Environment`.
    * Enable **Field 1**, **Field 2**, and **Field 3**.
    * Label them: `Temperature`, `Humidity`, `Air Quality`.
3.  **Get Credentials**:
    * Go to the **API Keys** tab.
    * Copy the **Write API Key**.
    * Copy the **Channel ID**.

## 🧠 Machine Learning Integration

NeuralSense is not just about monitoring; it's about **predicting**. We have included a Python-based Machine Learning module that uses historical data to forecast future environmental conditions.

### How it Works
* **Algorithm**: Random Forest Regressor (Ensemble Learning).
* **Features**: Uses Lag Features (1H, 24H), Rolling Averages, and Temporal Markers (Hour, Day, Month).
* **Capabilities**:
    * Analyzes historical trends (Yearly Average).
    * Trains on sensor data (Temperature, Humidity, Air Quality).
    * **Generates Forecasts**: 10-Day, 30-Day, or 365-Day predictions.
    * **Visualizes Data**: Plots historical vs. predicted values using Matplotlib.

### <details><summary><b>Click here to view the Python Forecasting Code</b></summary>

Use`model.ipynb` in your project folder. Ensure you have `jammu_data.csv` (or your sensor data CSV) in the same directory.

## 🚀 Getting Started

1.  **Setup Arduino IDE**:

      * Add ESP8266 URL to Preferences: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`
      * Install "ESP8266" via Boards Manager.
      * Select Board: `NodeMCU 1.0 (ESP-12E Module)`.

2.  **Configure Code**:

      * Open the project `.ino` file.
      * Edit the `CONFIGURATION` section at the top:

    <!-- end list -->

    ```cpp
    const char* WIFI_SSID = "YOUR_WIFI_NAME";
    const char* WIFI_PASSWORD = ""; // Leave empty for open networks

    unsigned long CHANNEL_ID = 1234567; // Your ThingSpeak Channel ID
    const char* WRITE_API_KEY = "XYZ123..."; // Your Write API Key
    ```

3.  **Upload**:

      * Connect NodeMCU via USB.
      * Select correct COM Port and click **Upload**.

4.  **Monitor**:

      * Open Serial Monitor at **115200 baud**.
      * Wait for the "WiFi Connected" and "ThingSpeak update successful" messages.

5.  **Run ML Forecast** (Optional):

      * Export your ThingSpeak data as a CSV file (e.g., `jammu_data.csv`).
      * Run the Python script: `python model.ipynb, by extracting py code`.

## 🔮 Future Enhancements

  * **TinyML Integration**: Implement on-device logic to categorize air quality ("Good", "Hazardous") before uploading.
  * **Mobile Alerts**: Use ThingSpeak's "React" feature to send tweets or emails if gas levels spike.
  * **OLED Display**: Add a 0.96" OLED screen to show real-time readings locally.

## 🤝 Contributing

Contributions are welcome\! Please fork the repository and submit a Pull Request.

## 📄 License

This project is licensed under the **MIT License**.


