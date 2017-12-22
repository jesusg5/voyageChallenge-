# Mechatronics Challenge

## Goal
Design a prototype can output GPS coordinates and accelerometer data via serial USB.

## Instructions
1. Fork this repo
2. Put your deliverables for **Part 1** in `electrical` and `src` folders and **Part 2** in the `mechanical` folder.
3. Once you've completed the challenge, please send an e-mail to alan@voyage.auto with the link to your forked Github repo.

### Part 1: Electrical/Coding
At Voyage, we are always trying to improve sensor data quality.  The objective of this challenge is to build a module that can output GPS coordinates and accelerometer data.  Assume clean 5V, 3A power source is available.     

#### Electrical:
- The carloop-gps is designed to stack up over a particle photon when using the carloop-basic module. Thus, the pin
mapping between the photon is very simple. Each pin on the photon is wired to the corresponding pin on the carloop
GPS. The GPS communicates via RX/TX lines and the accelerometer uses SPI. I omitted the sd/data logger connections since
we are not using them

- On my schematic I added a 5V power supply as per the assumption in the instructions. However, since we are planning to
collect data over USB serial, the photon can be powered via the USB cable. I designed my mechanical enclosure with this in
mind. However, it would be simple to modify the enclosure to accommodate another power source
Using a Particle Photon microcontroller

#### Coding
- The src/lib directory contains all of the libraries I used for my code. Carloop.h and TinyGPS++.h come from the
carloop library repo. Is use the LIS3DH library created by rickkas7 (https://github.com/rickkas7/LIS3DH) to retrieve
data from the accelerometer via SPI.


 [https://docs.particle.io/datasheets/photon-(wifi)/photon-datasheet/#pin-and-button-definition](https://docs.particle.io/datasheets/photon-(wifi)/photon-datasheet/#pin-and-button-definition) and a Carloop GPS [https://store.carloop.io/products/carloop-gps?variant=4846877966372](https://store.carloop.io/products/carloop-gps?variant=4846877966372)

### Part 2: Mechanical
- The mechanical enclosure is designed using solidworks 2017

- The enclosure is built around an adafruit proto-board (https://www.adafruit.com/product/1609?gclid=CjwKCAiAsejRBRB3EiwAZft7sNjUHxHuLhG8LI3ev9jRYw6MQxkIKKRCxM6PgQqXnvu7dj3k1xFY1BoCYRUQAvD_BwE)

- I would expect to solder stacking headers (https://www.sparkfun.com/products/14322) to the proto-board
and then mount the photon and carloop GPS on those. These should allow enough clearance to accomodate the
mounting screw on the proto-board. In my CAD model I offset the photon by 1cm from the proto-board. This is the
height of the stacking headers.

- I could not find exact dimension for the carloop gps but the overall form factor and pin positions are similar to
a photon. I use a second photon to illustrate where the carloop gps goes.

- I use 3mm nylon screws, nuts and aluminum standoffs for fastening on my case:
6mm M3 Screw: https://www.mcmaster.com/#92492a716/=1arhwsr
8mm M3 Screw: https://www.mcmaster.com/#92492a717/=1arhwkk
M3 Standoff:  https://www.mcmaster.com/#95947a002/=1arhy35
M3 Nut:       https://www.mcmaster.com/#93800a400/=1arhyl5
- The case is designed with rapid-prototyping in mind. I would 3D print the case and lid in either
ABS or PLA plastic, which are both inexpensive and should not cause conductivity issues. The tolerences will
vary depending on the machine used to print. Iteration or light post processing may be necessary to
correct issues that may arise.

- I added flanges with dummy mounting holes to the case. These can easily be modified to accomodate
different mounting scenarios/needs
