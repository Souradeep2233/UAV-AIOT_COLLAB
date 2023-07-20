# UAV-AIOT_COLLAB

Our research team has created this brilliant repository, over their research on UAVs ( Unmanned Aerial Vehicles) and their application in agricultural science, Load transport, weather prediction, and pollution index  from various sensors and edge computations to cloud architecture for visualization and further analysis with machine learning. Together we have made a complete system basic but compatible with UAV surveillance and exploration  in weather science and forecasting.
## Glimpses

![9931112 fig 007](https://github.com/Souradeep2233/UAV-AIOT_COLLAB/assets/94059815/39795825-9793-4aa6-bd09-edef0153b666)

## Sensors Used

- DHT11: Measures temperature and humidity
- BMP180: Measures atmospheric pressure
- MQ7: Measures carbon monoxide (CO) concentration
- MQ135: Measures NH3 and SOx concentration

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

## Modified Kalman Filter Description for noise reduction in data collection and transmission
The Kalman filter is a recursive mathematical algorithm used for estimating the state of a dynamic system in the presence of uncertain and noisy measurements. It was developed by Rudolf Kalman in the early 1960s and has since found numerous applications in various fields, including control systems, robotics, navigation, computer vision, and signal processing.

Algorithm :

1. Initialization: The Kalman filter is initialized with the necessary parameters, including the state transition matrix (A), input matrix (B), measurement matrix (H), process noise covariance matrix (Q), measurement noise covariance matrix (R), initial state estimate (x0), and initial covariance matrix (P0). These parameters define the system dynamics and measurement characteristics, as well as the initial assumptions about the state and uncertainty.

2. Reading and Filtering Sensor Data: Once the Kalman filter is set up with the proper parameters, it is used to read and filter the sensor data in a loop. For each sensor data point acquired from the IoT sensors on the UAV, the Kalman filter performs the prediction and update steps.

3. Predict Step: The predict() method is called to forecast the upcoming state estimate and covariance using the state transition matrix (A) and the process noise covariance matrix (Q). This step predicts the UAV's state based on its previous state, system dynamics, and any external inputs (if applicable).

4. Update Step: The update() method is called to update the state estimate and covariance using the measurement matrix (H), measurement noise covariance matrix (R), and the actual sensor measurement (y). The Kalman filter calculates the Kalman gain (K) to correct the predicted state estimate based on the sensor measurement.

5. Repeat: The process of reading the sensor data, predicting the state estimate, updating the state estimate with measurements, and repeating this loop for all sensor data points allows the Kalman filter to iteratively refine its estimates of the UAV's true state.

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

## Contributions

Contributions to this project are welcome. If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](LICENSE).
