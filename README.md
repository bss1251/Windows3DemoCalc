# Windows3DemoCalc
### A very, very basic example windows program that will compile under Windows 3.0 (and probably later)

This program is a very basic, fixed-ish point, RPN calculator that was developed during the course of a video series called [Windows 3 Programming](https://www.youtube.com/watch?v=xJFn7tTQM1o&list=PLj0W_snzVsnOnIXf8tRgPZoOdJP4p3pYN). It is intended only as a demonstration of programming under Windows 3, and therefore lacks many features expected of calculators.

The base Windows APIs used in this code are still very similar today, and this project would probrably compile under Windows 10 with minimal (if any) changes.

## Building for Windows 3 using Microsoft C 6

*Copy all files into the same directory
*Compile the resource file `rc -r calc.rc`
*Build the project using the included makefile `nmake calc`
