#include "CFA_634_Serial.h"

CFA_634_Serial::CFA_634_Serial(uint8_t txPin, long baudRate, bool inverted)
    : _txPin(txPin), _baudRate(baudRate), _inverted(inverted) {
    _lcdSerial = new SoftwareSerial(-1, txPin, _inverted);  // Only TX, no RX
}

//####################################################################################################
//####################################################################################################
//#                                    CREATION AND MAIN FUNCTIONS                                    
//####################################################################################################
//####################################################################################################
void CFA_634_Serial::begin() {
    // Opens the serial port at the predefined comm speed
    // The delay is included because these displays show a splash screen, and need a moment to be ready
    // to accept commands
    _lcdSerial->begin(_baudRate);
    delay( 2500 );
}

void CFA_634_Serial::center(byte row, const String &message) {
    // Prints centered text on the specified row
    unsigned int lpad = ( 20 - message.length() ) / 2;
    cursorPosition( row, lpad );
    _lcdSerial->print(message);
}

void CFA_634_Serial::rprint(byte row, const String &message) {
    // Prints right-justified text on the specified row
    unsigned int lpad = ( 20 - message.length() );
    cursorPosition( row, lpad );
    _lcdSerial->print(message);
}

void CFA_634_Serial::print(const String &message) {
    // Prints left-aligned text starting at the current cursor position
    _lcdSerial->print(message);
}

void CFA_634_Serial::print(byte row, const String &message) {
    // Prints left-aligned text starting on the specified row and column 0
    cursorPosition( row, 0 );
    _lcdSerial->print(message);
}

void CFA_634_Serial::print(byte row, byte col, const String &message) {
    // Prints left-aligned text starting at the specified row and column position
    cursorPosition( row, col );
    _lcdSerial->print(message);
}

void CFA_634_Serial::write(byte message) {
    // Sends a byte value to the LCD.  LCD commands all start with a byte value
    _lcdSerial->write(message);
}

void CFA_634_Serial::clear() {
    // Clears the display and returns cursor to Home position (0, 0). All data is erased.
    _lcdSerial->write(0x0c);
}

void CFA_634_Serial::reboot() {
    // This reboots the display and returns all settings to defaults
    // The first nine characters are needed in case another command is active
    for ( int i = 0; i < 9; i++ ){  
        write( 0x20 );  
    }
    _lcdSerial->write( 0x1a );
    _lcdSerial->write( 0x1a );
    delay( 2500 );
}

void CFA_634_Serial::initialize( byte bklt = 30, byte contr = 50 ){
    // This sets the LCD to my preferred operating mode.  
    displayShow();
    cursorHide();
    backlight( bklt );
    contrast( contr );
    scrollOff();
    wrapOff();
    formFeed();
    delay( 2000 );
}

void CFA_634_Serial::initialize( byte bklt ){
    initialize( bklt, 50 );
}

void CFA_634_Serial::initialize() {
    initialize( 30, 50 );
}

//####################################################################################################
//####################################################################################################
//#                                          CURSOR CONTROLS                                          
//####################################################################################################
//####################################################################################################
void CFA_634_Serial::cursorPosition( byte Row, byte Col ) {
    // Moves the cursor to the specified location.  The CFA634 LCD is 4 rows by 20 columns, specified
    // as row 0 through 3 and column 0 through 19.
    _lcdSerial->write( 0x11 );
    _lcdSerial->write( Col );
    _lcdSerial->write( Row );
}

void CFA_634_Serial::cursorHome() {
    // Moves cursor to the top left character position. No data is changed.
    _lcdSerial->write( 0x01 );
}

void CFA_634_Serial::cursorHide() {
    // Cursor is not shown; nothing else is changed.
    _lcdSerial->write( 0x04 );
}

void CFA_634_Serial::cursorBlock() {
    // Sets cursor to blinking block underscore.
    _lcdSerial->write( 6 );
}

void CFA_634_Serial::cursorUnderline() {
    // Sets cursor to nonblinking underscore.
    _lcdSerial->write( 0x05 );
}

void CFA_634_Serial::cursorStyle( CursorStyle setting ) {
    _lcdSerial->write( setting );
}

void CFA_634_Serial::backspace() {
    // Moves the cursor back one space and erases the character in that space. Will wrap from the left-most
    // column to the right-most column of the line above. Will wrap from the left-most column of the top row
    // to the right-most column of the bottom row. Ignores wrap.
    _lcdSerial->write( 0x08 );
}

void CFA_634_Serial::arrow( Arrows dir ) {
    // Moves the cursor up, down, left or right.
    _lcdSerial->write( 0x1b );
    _lcdSerial->write( 0x5b );
    _lcdSerial->write( dir );
}

void CFA_634_Serial::lineFeed() {
    // Moves the cursor down one row. If SCROLL is on and the cursor is at the bottom row, the display will
    // scroll up one row and the bottom row will be cleared.
    _lcdSerial->write( 0x0a );
}

void CFA_634_Serial::formFeed() {
    // Clears the display and returns cursor to Home position (upper left). All data is erased.
    _lcdSerial->write( 0x0c );
}

void CFA_634_Serial::carriageReturn() {
    // Moves cursor to the left-most column of the current row.
    _lcdSerial->write( 0x0d );
}

//####################################################################################################
//####################################################################################################
//#                                          DISPLAY CONTROLS                                         
//####################################################################################################
//####################################################################################################
void CFA_634_Serial::displayHide(){
    // Display is blanked; no data is changed.
    _lcdSerial->write( 0x02 );
}

void CFA_634_Serial::displayShow(){
    // Restores blanked display; nothing else is changed.
    _lcdSerial->write( 0x03 );
}

void CFA_634_Serial::displayVisible( bool setting ){
    if ( setting == true ){  displayShow();
        } else {  displayHide();  }
}

void CFA_634_Serial::saveDisplayConfig(){
    // This command allows the current state of the module to be stored in the display's EEPROM, recalling
    // of the EEPROM contents to the display, and controlling the boot behavior.
    _lcdSerial->write( 0x09 );
    delay( 5000 );
}

//####################################################################################################
//####################################################################################################
//#                                        VISIBILITY CONTROLS                                        
//####################################################################################################
//####################################################################################################
void CFA_634_Serial::backlight( byte setting ){
    // Specify the backlight intensity as 0 to 100
    if ( setting > 100 )  setting = 100;
    _lcdSerial->write( 0x0e );
    _lcdSerial->write( setting );    
}

void CFA_634_Serial::contrast( byte setting ){
    // Specify the contrast as 0 to 100
    if ( setting > 100 )  setting = 100;
    _lcdSerial->write( 0x0f );
    _lcdSerial->write( setting );    
}

void CFA_634_Serial::scrollOn(){
    // Turns scroll feature on. Then a Line Feed command from the bottom row will scroll the
    // display up by one row, independent of Wrap. If Wrap is also on, a wrap occurring on the
    // bottom row will cause the display to scroll up one row. Scroll is on by default.
    scrollMode(SCROLL_ON);
}

void CFA_634_Serial::scrollOff(){
    // Turns scroll feature off. Then a Line Feed command from the bottom row will move the
    // cursor to the top row of the same column, independent of wrap.  If wrap is on, a wrap 
    // occurring on the bottom row will also wrap vertically to the top row. Please note 
    // that Scroll is on by default at power-up.
    scrollMode(SCROLL_OFF);    
}

void CFA_634_Serial::scrollMode( ScrollMode setting ){
    _lcdSerial->write( setting );
}

void CFA_634_Serial::wrapOn(){
    // Turns wrap feature on. When wrap is on, a printable character received when the cursor is at the
    // right-most column will cause the cursor to move down one row to the left-most column. If the cursor is
    // already at the right-most column of the bottom row, it will wrap to the top row if Scroll is off, or the
    // display will scroll up one row if Scroll is on.
    wrapMode(WRAP_ON);
}

void CFA_634_Serial::wrapOff(){
    // Turns wrap feature off. When wrap is off, a printable character received when the cursor is at the
    // right-most column will cause the cursor to disappear as it will be off the right edge of the screen. Any
    // subsequent characters will be ignored until some other command moves the cursor back onto the
    // display. This function is independent of Scroll.
    wrapMode(WRAP_OFF);
}

void CFA_634_Serial::wrapMode( WrapMode setting){
    _lcdSerial->write( setting );
} 

//####################################################################################################
//####################################################################################################
//#                                         SPECIAL FUNCTIONS                                         
//####################################################################################################
//####################################################################################################
void CFA_634_Serial::bargraph( BargraphIndex charindex, byte bitpattern, byte startcol, byte endcol, int length, byte row ){
    // This displays a horizontal bargraph.
    // The bitpattern displays vertically and occupies two custom character slots (specified by charindex).
    // Startcol, endcol and row define the area available for the bargraph.  Length specifies how many pixels
    // will be displayed (5 pixels per character column)
    // This uses two custom characters, and should not be used with any other custom characters or block numbers
    // Negative values can be calculated as 256 minus the display value.  It will extend the bargraph from 
    // the right of the defined area.
    _lcdSerial->write( 0x12 );
    _lcdSerial->write( charindex );
    _lcdSerial->write( bitpattern );
    _lcdSerial->write( startcol );
    _lcdSerial->write( endcollength );
    _lcdSerial->write( row  );
}

void CFA_634_Serial::setCustomBmp( CustomChar charnum, byte data0, byte data1, byte data2, byte data3, 
    byte data4, byte data5, byte data6, byte data7){
    // The custom characters are mapped at \128 through \135 corresponding to character 0 to character 7.
    // Each byte represents one row of pixels in the character.  Byte 0 is the top row, and Byte 7 is the
    // bottom.  Only the first five bits are displayed, and the last three must be set to 0.
    // DO NOT display a custom character and block numbers or bargraph at the same time.
    _lcdSerial->write( 0x19 );
} 

void CFA_634_Serial::blockNumber( BlockNumStyle style, byte col, int number){
    // This displays large (3x4 or 4x4) numbers on the display.  DO NOT use at the same time as displaying
    // custom characters or bargraphs.
    _lcdSerial->write( 0x1c );
    _lcdSerial->write( style );
    _lcdSerial->write( col );
    _lcdSerial->write( number );    
}

void CFA_634_Serial::controllerComm( ControllerAddr loc, byte data){
    // This command executes a low-level write directly to the controller. 
    // USE THIS COMMAND AT YOUR OWN RISK – this command can disable or damage the display module.
    // Rebooting the display will recover from most mistakes. 
    _lcdSerial->write( 0x1e );
    _lcdSerial->write( loc );
    _lcdSerial->write( data );    
} 

void CFA_634_Serial::showInfoScreen(){
    // This function displays the communication mode and speed of the display
    _lcdSerial->write( 0x1f );
} 
