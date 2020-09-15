# Derpy2D

A bare metal 2D game engine for a *currently non-existing* portable game console
using the Raspberry PI, together with a 128x160px 1.8'' ST7735 TFT LCD panel.

## Specs

### Hardware

 - Currently Raspberry Pi 3B+ *(Final target will likely be a Pi Zero though\*)*
 - ST7735 TFT LCD 128x160px
 - TBD: Speaker *(probably something like [this](https://www.adafruit.com/product/3885))*
 - TBD: Controller *(probably just tactile buttons with 3D printed caps)*
 - TBD: Custom designed 3D printable case
 - TBD: Power delivery *(something like [this](https://hackaday.io/project/164733-pisugar-battery-for-raspberry-pi-zero))*

*\* Depending on whether a single core at lower frequency can handle rendering & audio & input handling*


### Software

 - C++
 - [Circle](https://github.com/rsta2/circle)
 - [circle-stdlib](https://github.com/smuehlst/circle-stdlib)
 - 2D software texture rendering
 - Input event handling
 - SFX/Music output
 - TBD: Custom, domain specific programming language
 - TBD: Custom VM for easier development
 - TBD: ...
