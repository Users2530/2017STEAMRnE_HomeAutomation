# Changelog

For Korean-translated Changelog, see [here](Changelog_kr.md).

## Arduino Code

#### v1
##### New Features
+ First code.
+ Added code to display collected data (Pulse, Object,Ambient temp, Time) via OLED screen.
+ Added code to display collected data via serial monitor.

##### Known errors
+ Error with the RTC. Time isn't consistent.


#### v1.1
##### New Features
+ Added Real time data logging; While connected to a raspberry Pi, data is automatically saved to a MySQL Database.
+ Added code to control what is displayed on the OLED screen via potentiometer.

##### Known Errors
+ Time error: about 1 Hour.
+ Sensors intermittently stop recording.


#### v1.2
##### New Features
+ Fixed error where sensors randomly stop recording.
+ Edited code so that sensors log every 1 second.
+ Added code to see time or sensor value display via potentiometer.

##### Known Errors
Time error: about 1 second.


#### v2.0
##### New Features
+ Improved Time control features.

##### Known Errors
+ Clash between accelerometer and RTC.


#### v3.0
##### New Features
+ Bluetooth- Connection between Pi and arduino is now wireless.
+ Removed unstable Temp and pulse sensor.

##### Known Errors
+ Clash between accelerometer and RTC.


#### v3.1
##### New Features
+ Added functions within the arduino code that handles strings.
+ Added the ability to monitor progress via serial monitor.

##### Known Errors
+ Clash between accelerometer and RTC.


#### v3.2
##### New Features
+ Code Cleanup

##### Known Errors
+ Clash between accelerometer and RTC


#### v3.3
##### New Features
+ Dualization of code and hardware.
+ Solved RTC-Accelerometer clash problem.
+ Reciever Bluetooth module sends time data back to transmitter,and displays time.

##### Known Errors
+ Recieving time function is unstable.


#### v3.4
##### New Features
+ Removed unstable RTC module.
+ RE-Added Temp sensor to check if user is wearing the device.
+ Shortened display refresh time from 1 second to real-time.
+ fixed data transmission direction in order to make sure data doesn't get tangled.

##### Known Errors
+ Time error: 1~5 seconds for 600ish seconds. This is inevitable since the delay function within the arduino has a bit of inaccuracy.


## Raspberry Pi


#### v1
##### New Features
+ First code.
+ Added function that saves data recieved from the arduino serial monitor to a MySQL Database.
+ Added function that outputs collected data to a terminal.


#### v2
##### New Features
+ Added option to enter name
+ Added option to output logged data as a text(.txt) file.
