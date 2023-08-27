# Step-moonlite-astrofocus
A simple focuser program made for use on multiple different microcontrollers and stepper motors drivers with STP/DIR inputs.
It uses a modified version of hansastro's moonlite library: https://github.com/Hansastro/Focuser


## Setup

1. Drop the ```Moonlite```(inside libraries) folder into your ```.\Documents\Arduino\libraries\``` folder.
2. Drop the ```focuser``` folder into your ```.\Documents\Arduino\``` folder and open it using the Arduino IDE.
3. Setup the stp, dir, MS1, MS2 in accordance with your own pinout. The led pin is used as a debug led, you can set it to an unused pin on your microcontroller. If you have more or less microstepping pins, add or remove the pins at the top of the document. Also add or remove the pin setup in the setup() function, as well as the microstepping setting in the ML_SF and ML_SH case statement (in my case I set it to 8th and 16th step for the A4988). In some cases you might also have to set up Enable, Sleep and Reset pins. Again, if your situation differs from mine add or remove the pins from the top of the document and add or remove the pin setup in the setup() function.
(optional) you can set a sleep mode near the bottom of the document, this can be helpfull to reduce heat buildup or to save power. There is an if else statement which checks if a variable called 'allowed' is true. Basically as long as the motor is supposed to run, it will not be sleeping.
4. Upload the sketch by following the upload procedure required for your board.

## To be implemented

- Temperature compensation.

## Known Issues

- ~~NINA will give an error when you try to move larger steps.~~ (fixed) the microcontroller was always reporting that the motor was stopped, which the driver didn't seem to like.
