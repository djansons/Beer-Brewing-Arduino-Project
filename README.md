# Beer-Brewing-Arduino-Project

I made this project because I had no accurate way to keep my beer fermenter at a desired temperature. 

This is an Arduino sketch that controls the temperature of a beer fermenter. I connected a temperature sensor, LCD display and relay driver to the Arduino. An electric blanket was wrapped around the fermenter, which the Arduino then controlled. 
I have allowed a couple of degrees of hysteresis so that the controller does not start to heat immediately after dropping below setpoint. 
This project could have been improved with the addition of a couple of buttons on the controller to control the temperature setpoint. 

![Beer Brew Arduino](https://github.com/djansons/Beer-Brewing-Arduino-Project/blob/master/Picture%20of%20Arduino.jpg)
