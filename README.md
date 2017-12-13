# Color-Wheel
Joystick-controlled color wheel powered by Arduino




## Introduction

This is a simple project for the Arduino Uno R3 but can probably be ported to other microcontrollers with ease.
Using a joystick, three 330-ohm resisters, and a common cathode RGB LED, the LED can change its color with respects
to the position of the joystick (similar to a color wheel). 




## How it works

It works by first taking the position of the joystick in cartesian coordiantes (x and y axis). The x and y axis
are in range [0,1024], however, so to center the coordinates to some origin, each value is the absolute value of
512 less than itself. E.g. (x'-512, y'-512) = (x,y), where x' and y' are the raw values from the joystick and x
and y are the final values to be used.

From the coordinates, simple trigonometry is used to find the angle of some line from the coordinate to the 
origin from the positive y-axis (positive clockwise). Using Arduino's atan2() function from math.h, one can find
this in [-pi,pi]. This is then converted to [0,2pi], then conveted to degrees (original output in radians). This
final value will be the hue angle. 

Using HSV coordinates, the saturation and value are fixed to 1 (for now). Thus, by following the formulas found 
[here](https://www.rapidtables.com/convert/color/hsv-to-rgb.html), the needed RGB values ca be calculated.

Afterwards, it's as simple as updating the colors via analogWrite();




## Future Updates
I plan to use the joystick to change the V value in HSV. The saturation can possibly changed as well but with
another module in addition to the joystick (e.g. a button).




## Video
[Watch here on Vimeo](https://vimeo.com/247068627/1ff394cbfa)




## Resources

Arduino.cc - [RGB LED hookup](https://playground.arduino.cc/Main/RGBLEDPWM) 

Arduino.cc - [Joystick hookup](https://www.arduino.cc/en/Tutorial/JoyStick)

AVR-libc - [Arduino documentation for math.h](http://www.nongnu.org/avr-libc/user-manual/group__avr__math.html)

RapidTables.com - [HSV to RGB conversion](https://www.rapidtables.com/convert/color/hsv-to-rgb.html)


