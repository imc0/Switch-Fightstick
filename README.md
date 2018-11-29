## Switch-Fightstick
Proof-of-Concept Fightstick for the Nintendo Switch. Uses the LUFA library and reverse-engineering of the Pokken Tournament Pro Pad for the Wii U to enable custom fightsticks on the Switch System v3.0.0.

This is forked from progmem/Switch-Fightstick so please see there for documentation and rationale.

The objective of this fork is to turn the Switch-Fightstick code into a library
so that you can write your own apps without editing the Switch-Fightstick
source or including the LUFA build system in your project.

### Compiling the library

You need the AVR toolchain.  This is available in some current Linux distros
(look for packages called  gcc-avr and binutils-avr, or avr-gcc and
avr-binutils) and it also comes with the [Arduino IDE](https://www.arduino.cc/en/Main/Software).

You also need the [LUFA library](http://www.fourwalledcubicle.com/LUFA.php).
Download and unzip this (no need to build it).  The zipfile should have
contained a directory called LUFA.

Edit the makefile of this project so that LUFA_PATH points to the LUFA
directory mentioned above.  Check the other settings as well.

Hopefully you can now type `make` and end up with a file called libJoystick.a.

## Compiling the example applet

The `example.c` file documents how the library is used.  You can compile it
within the Switch-Fightstick project by just typing `make -f example.mk`.  This
should give you an `example.hex` file that you can load on to your Teensy.

By reading the source file and the makefile, hopefully you will get enough
information to be able to compile your own project.
