Includes code for both Python and C++/?

# Explanation

The two 74HC138 are for row selection, and the two 74HC585 are for column selection for every line at a time. Keep the G input on LOW if you want to display the line, or HIGH to clear it entirely. For every row input sequence, the D, C, B and A pins select the line (they get value from 0x0000 for the first line and 0x1111 for the last), and for every clock signal, set the DI pin on LOW if you want it to be on, or HIGH if you want it off. After the 16 clock signals and the DI signals for the selected line, set the LAT (latch) pin on HIGH and after a short delay, set it on LOW, and redo the entire operation for the next line.

### Example:
If you want on the 3rd row to turn on the led 1, 3, 4, 5, 6, 7, 9, 10, 16, send the signals as shown below.
![Timing diagram](/timing.png)

# Schematic

![Schematic](/schematic.jpg)