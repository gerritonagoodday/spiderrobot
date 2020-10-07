# Overview

This is based on the design and code in https://github.com/G6EJD and includes a display control class 
WhitePaperDisplay for use by the robot display, that has been C-plussified from the original C code.

The demonstration in main.cpp uses the WhitePaperDisplay class but still does what the original does:
* Connects to t'Internet
* Gets weather details
* Displays them

Tre trick with this type of display is to generate all the screen display content before issuing 
the "display" command, and then it takes a few seconds or so to fully appear on the screen. 
This makes if good for displaying the current status and trends, but not so good for displaying 
fast-scrolling log files.

# Usage

Create a class instance of WhitePaperDisplay. Use the member functions to generate display 
content and issue the "display" command to update the entire display.

# Example

See main.cpp:

Here we create an instance of WhitePaperDisplay, and then do a whole lot of wierd stuff to display
and then regularly update the display. 

![Breadboard layout](/fritzing/whitepaperdisplay.png)