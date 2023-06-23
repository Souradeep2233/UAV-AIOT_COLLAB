# UAV-AIOT_COLLAB

This repository contains code for an environmental monitoring system that collects data from various sensors and uploads it to ThingSpeak for visualization and analysis. The system uses an ESP32 microcontroller to read sensor data and establish a Wi-Fi connection for data transmission.

## Sensors Used

- DHT11: Measures temperature and humidity
- BMP180: Measures atmospheric pressure
- MQ7: Measures carbon monoxide (CO) concentration
- MQ135: Measures air quality and detects multiple gases

## Hardware Requirements

- ESP32 microcontroller
- DHT11 sensor
- BMP180 sensor
- MQ7 sensor
- MQ135 sensor
- Wi-Fi network for data transmission

## Installation and Setup

1. Clone the repository: `git clone https://github.com/UdaySMukherjee/UAV-AIOT_COLLAB.git`
2. Set up the necessary libraries and dependencies by following the instructions provided by the sensor manufacturers.
3. Modify the `secrets.h` file to include your Wi-Fi credentials and ThingSpeak API key.
4. Upload the code to your ESP32 microcontroller using the Arduino IDE or platform of your choice.
5. Connect the sensors to the appropriate pins on the ESP32 board.
6. Power on the system and ensure that the sensors are working correctly.

## Usage

1. The ESP32 will attempt to connect to the specified Wi-Fi network.
2. Once connected, the sensors will start collecting data at regular intervals.
3. The data will be uploaded to the specified ThingSpeak channel for visualization and analysis.
4. You can access the ThingSpeak channel to view the collected data and perform further analysis.

## Contributing

Contributions to this project are welcome. If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).
