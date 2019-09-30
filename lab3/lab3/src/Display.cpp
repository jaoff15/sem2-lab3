/*
 * Display.cpp
 *
 *  Created on: Sep 26, 2019
 *      Author: jacoboffersen
 */

#include "Display.h"

Display::Display() {

}

Display::~Display() {

}

void Display::init() {
	initGpios();
	initDisplay();
}

void Display::print(std::string str) {
	clear();  										// Clear display
	setDataBits((std::bitset<8>) "00000010");  		// Return home

	for (int j = 0; j < DISPLAY_HEIGHT; j++) {  	// For each row
		for (int i = 0; i < DISPLAY_WIDTH; i++) {  	// For each character in row
			unsigned int character_id = j * DISPLAY_WIDTH + i;
			if (character_id < str.length()) {
				sendData(str[character_id]);		// Send data character to display
			} else {
				break;								// If the string is empty. Break the loop
			}
		}
	}
	register_select_.setValue(false);
}

void Display::clear() {
// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0   0   0   0   0   0   0   0   0   1
	setDataBits((std::bitset<8>) "00000001");
}

void Display::initGpios() {
// Configure register select pin
	register_select_.setPinNumber(std::to_string(DISPLAY_RS_PIN));
	register_select_.setDirection(out);

// Configure read/write pin
	read_write_.setPinNumber(std::to_string(DISPLAY_RW_PIN));
	read_write_.setDirection(out);

// Configure enable pin
	enable_.setPinNumber(std::to_string(DISPLAY_ENABLE_PIN));
	enable_.setDirection(out);

// Configure all the data pins
	for (int i = DISPLAY_DATA_BASE; i < DISPLAY_DATA_BASE + DISPLAY_DATA_LEN; i++) {
		data_bit_[i].setPinNumber(std::to_string(i));
		data_bit_[i].setDirection(out);
	}
}
int Display::initDisplay() {
// Power on

// Wait 20ms
	sleep.sleepMillisecond(20);

// Set function
// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0   0   0   0   1  DL   N   F   X   X
	register_select_.setValue(false);
	read_write_.setValue(false);
	setDataBits((std::bitset<8>) "00110000");
// Bit 4: 1 = 8 bit data length
// Bit 3: 1 = 2 active display lines
// Bit 2: 0 = Font 5x8 bits

// Wait 37us
	sleep.sleepMicrosecond(37);

// Display On/Off Control
// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0   0   0   0   0   0   1   D   C   B
	setDataBits((std::bitset<8>) "00001001");

// Wait 37us
	sleep.sleepMicrosecond(37);

// Display clear
// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0   0   0   0   0   0   0   0   0   1
	clear();

// Wait 1.52ms
	sleep.sleepMicrosecond(1520);

// OK
	return 0;
}

void Display::setDataBits(const std::string str) {
	char character = str[0];
	for (int i = 0; i < BYTE; i++) {
		bool bit = (character >> i) & 1;
		data_bit_[i].setValue(bit);
	}
}

void Display::setDataBits(const std::bitset<DISPLAY_DATA_LEN> bit) {
	for (int i = 0; i < BYTE; i++) {
		data_bit_[i].setValue(bit[i]);
	}
}

void Display::pulseEnableSignal() {
	enable_.setValue(false);
	sleep.sleepMicrosecond(500);
	enable_.setValue(true);
}

void Display::sendCommand(const std::string command) {
	register_select_.setValue(false);  	// Register Select 	= true
	read_write_.setValue(false);		// Read/write 		= false
//	enable_.setValue(true);				// Enable 			= true
	setDataBits(command);  				// Set data bit
//	enable_.setValue(false);			// Enable 			= false;
	pulseEnableSignal();				// Pulse enable signal to send data
}

void Display::sendData(const std::string data) {
	sleep.sleepMillisecond(2);
	register_select_.setValue(true);  	// Register Select 	= true
	read_write_.setValue(false);		// Read/write 		= false
//	enable_.setValue(true);				// Enable 			= true
	setDataBits(data);  				// Set data bit
//	enable_.setValue(false);			// Enable 			= false;
	pulseEnableSignal();				// Pulse enable signal to send data
}

void Display::sendData(const char data) {
	sleep.sleepMillisecond(2);
	register_select_.setValue(true);  	// Register Select 	= true
	read_write_.setValue(false);		// Read/write 		= false
//	enable_.setValue(true);				// Enable 			= true
	setDataBits(data);  				// Set data bit
//	enable_.setValue(false);			// Enable 			= false;
	pulseEnableSignal();				// Pulse enable signal to send data
}
