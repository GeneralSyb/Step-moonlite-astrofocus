# Step-moonlite-astrofocus
A simple focuser program made for the ESP32-S2 which uses a step/dir based stepper motor controller, in my case the EasyDrive.
It uses a modified version of hansastro's moonlite library: https://github.com/Hansastro/Focuser


## Setup

1. Drop the ```Moonlite```(inside libraries) folder into your ```.\Documents\Arduino\libraries\``` folder.
2. Drop the ```focuser``` folder into your ```.\Documents\Arduino\``` folder and open it using the Arduino IDE.
3. Setup the stp, dir, MS1, MS2 in accordance with your own pinout.
4. Upload the sketch by following the upload procedure required for your board.
