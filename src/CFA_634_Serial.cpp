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
    _lcdSerial->begin(_baudRate);
    delay( 2500 );
    //initialize();
}

void CFA_634_Serial::center(byte row, const String &message) {
    unsigned int lpad = ( 20 - message.length() ) / 2;
    cursorPosition( row, lpad );
    _lcdSerial->print(message);
}

void CFA_634_Serial::rprint(byte row, const String &message) {
    unsigned int lpad = ( 20 - message.length() );
    cursorPosition( row, lpad );
    _lcdSerial->print(message);
}

void CFA_634_Serial::print(const String &message) {
    _lcdSerial->print(message);
}

void CFA_634_Serial::print(byte row, const String &message) {
    cursorPosition( row, 0 );
    _lcdSerial->print(message);
}

void CFA_634_Serial::print(byte row, byte col, const String &message) {
    cursorPosition( row, col );
    _lcdSerial->print(message);
}

void CFA_634_Serial::write(byte message) {
    _lcdSerial->write(message);
}

void CFA_634_Serial::clear() {
    _lcdSerial->write(0x0c);
}

void CFA_634_Serial::reboot() {
    // The first nine characters are needed in case another command is active
    for ( int i = 0; i < 9; i++ ){  
        write( 0x20 );  
    }
    _lcdSerial->write( 0x1a );
    _lcdSerial->write( 0x1a );
    delay( 2500 );
}

void CFA_634_Serial::initialize( byte bklt, byte contr ){
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
    _lcdSerial->write( 0x11 );
    _lcdSerial->write( Col );
    _lcdSerial->write( Row );
}

void CFA_634_Serial::cursorHome() {
    _lcdSerial->write( 0x01 );
}

void CFA_634_Serial::cursorHide() {
    _lcdSerial->write( 0x04 );
}

void CFA_634_Serial::cursorBlock() {
    _lcdSerial->write( 6 );
    //_lcdSerial->write( 0x06 );
}

void CFA_634_Serial::cursorUnderline() {
    _lcdSerial->write( 0x05 );
}

void CFA_634_Serial::cursorStyle( CursorStyle setting ) {
    _lcdSerial->write( setting );
}

void CFA_634_Serial::backspace() {
    _lcdSerial->write( 0x08 );
}

void CFA_634_Serial::arrow( Arrows dir ) {
    _lcdSerial->write( 0x1b );
    _lcdSerial->write( 0x5b );
    _lcdSerial->write( dir );
}

void CFA_634_Serial::formFeed() {
    _lcdSerial->write( 0x0c );
}

void CFA_634_Serial::carriageReturn() {
    _lcdSerial->write( 0x0d );
}


//####################################################################################################
//####################################################################################################
//#                                          DISPLAY CONTROLS                                         
//####################################################################################################
//####################################################################################################
void CFA_634_Serial::displayHide(){
    _lcdSerial->write( 0x02 );
}

void CFA_634_Serial::displayShow(){
    _lcdSerial->write( 0x03 );
}

void CFA_634_Serial::displayVisible( bool setting ){
    if ( setting == true ){  displayShow();
        } else {  displayHide();  }
}

void CFA_634_Serial::saveDisplayConfig(){
    _lcdSerial->write( 0x09 );
    delay( 5000 );
}

//####################################################################################################
//####################################################################################################
//#                                        VISIBILITY CONTROLS                                        
//####################################################################################################
//####################################################################################################
void CFA_634_Serial::backlight( byte setting ){
    if ( setting > 100 )  setting = 100;
    _lcdSerial->write( 0x0e );
    _lcdSerial->write( setting );    
}

void CFA_634_Serial::contrast( byte setting ){
    if ( setting > 100 )  setting = 100;
    _lcdSerial->write( 0x0f );
    _lcdSerial->write( setting );    
}

void CFA_634_Serial::scrollOn(){
    scrollMode(SCROLL_ON);
}

void CFA_634_Serial::scrollOff(){
    scrollMode(SCROLL_OFF);    
}

void CFA_634_Serial::scrollMode( ScrollMode setting ){
    _lcdSerial->write( setting );
}

void CFA_634_Serial::wrapOn(){
    wrapMode(WRAP_ON);
}

void CFA_634_Serial::wrapOff(){
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
void CFA_634_Serial::bargraph(){
    _lcdSerial->write( 0x12 );
    
} // 0x12

void CFA_634_Serial::setCustomBmp( CustomChar charnum, byte data0, byte data1, byte data2, byte data3, 
    byte data4, byte data5, byte data6, byte data7){
    _lcdSerial->write( 0x19 );
    
} // 0x19

void CFA_634_Serial::blockNumber( BlockNumStyle style, byte col, int number){
    _lcdSerial->write( 0x1c );
    _lcdSerial->write( style );
    _lcdSerial->write( col );
    _lcdSerial->write( number );    
}

void CFA_634_Serial::controllerComm( ControllerAddr loc, byte data){
    _lcdSerial->write( 0x1e );
    _lcdSerial->write( loc );
    _lcdSerial->write( data );    
} // 0x1e

void CFA_634_Serial::showInfoScreen(){
    _lcdSerial->write( 0x1f );
} // 0x1f


