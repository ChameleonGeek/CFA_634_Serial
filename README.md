# CFA_634_Serial
This library creates an interface for CrystalFontz 634 Serial LCDs.  These LCDs ar 4 row x 20 column character (not graphical) displays.  They operate in inverted "basic UART" serial mode or in SPI mode.  SPI mode can be selected by bridging the JPA pads on the back of the LCD.

I have a handful of these LCDs, which I purchased as salvage for several projects I've wanted to create.  I will be updating this library as I am ready to implement other communications modes.  This version uses SoftwareSerial, as that was the best approach for my first project.  I will be updating the code so the user can select whether it should use Software or Hardware serial, or SPI.  Since these LCDs don't "talk back" to the host device, only the microcontroller Tx pin is specified in serial mode.

The LCD object is created by defining the microcontroller pin and baudrate.  
-  CFA_634_Serial LCD( LCD_RX_PIN, LCD_COMM_SPEED );

The simplest definition assumes inverted signal levels, but can be overridden.
-  CFA_634_Serial LCD( LCD_RX_PIN, LCD_COMM_SPEED, INVERT_BOOL );

To minimize pin count, this library specifies pin -1 as the LCD Tx pin.  This hasn't caused any problems in any of my testing.

Row and Columns are addressed as 0 through 3 and 0 through 19.

The print functions (print, rprint, center) currently only accept strings.  You will need to convert other data types to string before passing to the print functions.  I will be updating this as the conversion becomes more frustrating for me ;-)  All print functions will overwrite any text already on the screen.  You need to keep track of the data on the display if tracking it is important to you.
### Left-aligned print functions
-  print( byte row, byte col, const String &message );
-  print( byte row, const String &message ); ==>  Assumes column 0, and moves the cursor to the specified row
-  print( const String &message );  ==> Prints the text at the current cursor location
### Center-aligned print functions
-  center( byte row, const String &message );
### Right-aligned print functions
-  rprint( byte row, const String &message );

## Scroll and Wrap
The scroll and wrap settings will greatly define how the display behaves.  In my normal usage, I turn off scroll and wrap, and keep the data to be displayed in 20 character lengths.  Wrap controls what the display does when the entered text exceeds the display width, and Scroll controls when text is entered past the last column on the last row.
