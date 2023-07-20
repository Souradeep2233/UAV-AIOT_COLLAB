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

1. Clone the repository: `git clone https://github.com/Souradeep2233/UAV-AIOT_COLLAB.git`
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


## Machine Learning Technologies Implemented 

Classical Machine Learning algorithms have been used to predict weather components and the Pollution index.

However, to be noted Deep Learning technologies were also used to predict and classify the same :-> resulting in the depreciation of validation scores in this particular dataset collected.


Algorithms used:

For Classification over weather conditions(Cloudy, rainy & sunny): 

    1. SVC [Accuracy: 82.28 %, F1 Score = .8195 ] 
    2. XGBOOST [Accuracy: 90 %, F1 Score = .8667] 
    3. Naive Bayes[Accuracy: 91.25 %, F1 Score = .9117] 
    4. Random Forest [Accuracy: 93.67 %, F1 Score = .9369] 
    5. Softmax [Accuracy: 96.20 %, F1 Score = .9618]
Bootstrap sampling was used, from which the highest accuracy was observed via the Softmax algorithm.

To be noted: ANN implementation with Softmax activation only yielded 75% accuracy in Deep Learning.

For Regression over (Temperature, Humidity, and Precipitation):
    
    1. For Maximum temperature : [ R2 score = .9572, Lr] 
    2. For minimum temperature : [ R2 score = .9810, Pr] 
    3. For Humidity :[ R2 score = 1.0,Pr] 
    4. For precipitation chance :[R2 score = .9998,Pr]

Note :

'Lr' implies linear regression. & 'Pr' implies polynomial regression.

With validation experiments still being tested and optimized, live on UAV, models with their weights and biases are more or less kept the same throughout the flight experiments. Further modifications are to be tracked and updated.

## Contributing

Contributions to this project are welcome. If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).
