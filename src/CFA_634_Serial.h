#ifndef CFA_634_Serial_H
#define CFA_634_Serial_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class CFA_634_Serial {
public:
    CFA_634_Serial(uint8_t txPin, long baudRate, bool inverted = true);

	enum Arrows {
		ARROW_UP    = 0x41,
		ARROW_DOWN  = 0x42,
		ARROW_LEFT  = 0x43,
		ARROW_RIGHT = 0x44
	};

	enum BlockNumStyle {
		BLOCK_3X4 = 0x00,
		BLOCK_4X4 = 0x01
	};

	enum ControllerAddr{
		CONTROLLER_REG = 0,
		CONTROLLER_MEM = 1
	};

	enum CustomChar {
		CUST_CHAR_0 = 128,
		CUST_CHAR_1 = 129,
		CUST_CHAR_2 = 130,
		CUST_CHAR_3 = 131,
		CUST_CHAR_4 = 132,
		CUST_CHAR_5 = 133,
		CUST_CHAR_6 = 134,
		CUST_CHAR_7 = 135
	};

	enum CursorStyle {
		CURSOR_BLOCK     = 0x06,
		CURSOR_HIDE      = 0x04,
		CURSOR_UNDERLINE = 0x05
	};

	enum ScrollMode {
		SCROLL_ON  = 0x13,
		SCROLL_OFF = 0x14
	};

	enum WrapMode {
		WRAP_ON  = 0x17,
    	WRAP_OFF = 0x18
	};

	//####################################################################################################
	//####################################################################################################
	//#                                    CREATION AND MAIN FUNCTIONS                                    
	//####################################################################################################
	//####################################################################################################
    void begin();
    void print( const String &message );
    void print( byte row, const String &message );
    void print( byte row, byte col, const String &message );
    void center( byte row, const String &message );
    void rprint( byte row, const String &message );
    void write( byte message );
    void clear(); // 0x0c
    void reboot(); // 0x1a
    void initialize( byte bklt, byte contr );
    void initialize( byte bklt );
    void initialize();

	//####################################################################################################
	//####################################################################################################
	//#                                          CURSOR CONTROLS                                          
	//####################################################################################################
	//####################################################################################################
    void cursorPosition( byte Row, byte Col ); // 0x11
    void cursorHome(); // 0x01
    void cursorHide(); // 0x04
    void cursorBlock(); // 0x06
    void cursorUnderline(); // 0x05
    void cursorStyle( CursorStyle setting );
    void backspace(); // 0x08
    void arrow( Arrows dir );
    void formFeed(); // 0x0c
    void carriageReturn(); // 0x0d


	//####################################################################################################
	//####################################################################################################
	//#                                          DISPLAY CONTROLS                                         
	//####################################################################################################
	//####################################################################################################
    void displayHide(); // 0x02
    void displayShow(); // 0x03
    void displayVisible( bool setting );
    void saveDisplayConfig(); // 0x09

	//####################################################################################################
	//####################################################################################################
	//#                                        VISIBILITY CONTROLS                                        
	//####################################################################################################
	//####################################################################################################
    void backlight( byte setting ); // 0x0e
    void contrast( byte setting ); // 0x0f
    void scrollOn(); // 0x13
    void scrollOff(); // 0x14
    void scrollMode( ScrollMode setting );
    void wrapOn(); // 0x17
    void wrapOff(); // 0x18
    void wrapMode( WrapMode setting); 

	//####################################################################################################
	//####################################################################################################
	//#                                         SPECIAL FUNCTIONS                                         
	//####################################################################################################
	//####################################################################################################
    void bargraph(); // 0x12
    void setCustomBmp( CustomChar charnum, byte data0, byte data1, byte data2, byte data3, 
    	byte data4, byte data5, byte data6, byte data7); // 0x19
    void blockNumber( BlockNumStyle style, byte col, int number); // 0x1c
    void controllerComm( ControllerAddr loc, byte data); // 0x1e
    void showInfoScreen(); // 0x1f


private:
    uint8_t _txPin;
    long _baudRate;
    bool _inverted;
    SoftwareSerial* _lcdSerial;
};

#endif // CFA_634_Serial_H
