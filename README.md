# Internet-of-Things-IoT---Smart-Home-System

# Project Overview:
This project builds a smart home model that automatically regulates internal temperature based on perceived Heat Index. It leverages an ESP8266 microcontroller, DHT11 sensor, servo motor (for window control), and cloud communication for data acquisition, processing, visualization, and prediction.

# Key Functionalities:
Heat Index Calculation: Calculates Heat Index based on temperature and humidity readings from the DHT11 sensor.
Window Automation: Controls window opening/closing using a servo motor, adjusting the degree of openness based on the calculated Heat Index levels.
Real-Time Monitoring: Continuously acquires sensor data and publishes it to a cloud broker (e.g., HiveMQ) for real-time visualization.
Heat Index Prediction: Analyzes and predicts past and future Heat Index trends using ARIMA models based on provided datasets.
User-Friendly Dashboard: Presents live sensor data, historical and predictive Heat Index trends on a Node-RED dashboard for comprehensive understanding.

# Technical Stack:
Hardware: NodeMCU ESP8266, DHT11 Sensor, SG90 Servo Motor
Software: Arduino IDE, DHT library, Node-RED, ARIMA Model
Communication: MQTT Protocol (cloud broker)

* Member Contribution:
Member 01: (Hardware Integration & Sensor Data Acquisition): Sets up the NodeMCU, integrates the DHT11 sensor, writes code to read sensor data periodically, ensures reliable readings.
Member 02: (Data Acquisition, Processing & Communication): Implements Heat Index calculation, maps Heat Index levels to servo positions, configures MQTT communication, publishes sensor data and calculated Heat Index to the cloud broker.
Member 03: (Node-RED Dashboard & Integration): Sets up Node-RED, creates a user-friendly dashboard to visualize real-time and predicted Heat Index data, integrates MQTT data for live updates.
Member 04: (Data Analysis & Prediction with Integration): Preprocesses datasets, builds ARIMA models for past and future Heat Index prediction, validates predictions, provides data for Node-RED visualization (optional: alarm system for extreme HI levels).
