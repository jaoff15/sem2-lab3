/*
 * Display.cpp
 *
 *  Created on: Sep 26, 2019
 *      Author: jacoboffersen
 */

#include "Display.h"

Display::Display() {
	data_bit_[DISPLAY_DATA_LEN] = { };
}

Display::~Display() {

}

void Display::init() {
//	std::cout << "Initializing Display GPIO" << std::endl;
	initGpios();
//	std::cout << "Running display startup sequence" << std::endl;
	initDisplay();
}

void Display::print(std::string str) {
	clear();  										// Clear display
//	setDataBits((std::bitset<8>) "00000010");  		// Return home
	std::cout << "Print ";
	setDataBits((std::bitset<8>) "00000010");
	pulseEnableSignal();

	for (int j = 0; j < DISPLAY_HEIGHT; j++) {  	// For each row
		for (int i = 0; i < DISPLAY_WIDTH; i++) {  	// For each character in row
			unsigned int character_id = j * DISPLAY_WIDTH + i;
			if (character_id < str.length()) {
//				std::cout << "print: " << std::to_string(character_id) << " " << str[character_id] << std::endl;
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
//	setDataBits((std::bitset<8>) "00000001");
	std::cout << "Clear ";
	setDataBits((std::bitset<8>) "00000001");
}

void Display::initGpios() {
// Configure register select pin
//	std::cout << "Init Register Select" << std::endl;
	register_select_.setPinNumber(std::to_string(DISPLAY_RS_PIN));
	register_select_.setDirection(out);

// Configure read/write pin
//	std::cout << "Init Read/Write" << std::endl;
	read_write_.setPinNumber(std::to_string(DISPLAY_RW_PIN));
	read_write_.setDirection(out);

// Configure enable pin
//	std::cout << "Init Enable" << std::endl;
	enable_.setPinNumber(std::to_string(DISPLAY_ENABLE_PIN));
	enable_.setDirection(out);

// Configure all the data pins
//	std::cout << "Init data pins" << std::endl;
	for (int i = 0; i < DISPLAY_DATA_LEN; i++) {
//		std::cout << "initGpio: " << std::to_string(DISPLAY_DATA_BASE + i) << std::endl;
		data_bit_[i].setPinNumber(std::to_string(DISPLAY_DATA_BASE + i));
		data_bit_[i].setDirection(out);
	}
}
int Display::initDisplay() {
// Power on

// Wait 20ms
	sleep.millisecond(20);

// Set function
// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0   0   0   0   1  DL   N   F   X   X
	register_select_.setValue(false);
	read_write_.setValue(false);
//	setDataBits((std::bitset<8>) "00110000");
	std::cout << "Set Function ";
	setDataBits((std::bitset<8>) "00110000");
// Bit 4: 1 = 8 bit data length
// Bit 3: 1 = 2 active display lines
// Bit 2: 0 = Font 5x8 bits

// Wait 37us
	sleep.microsecond(37);

// Display On/Off Control
// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0   0   0   0   0   0   1   D   C   B
//	setDataBits((std::bitset<8>) "00001001");
	std::cout << "Display on/off ";
	setDataBits((std::bitset<8>) "00001001");

// Wait 37us
	sleep.microsecond(37);

// Display clear
// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0   0   0   0   0   0   0   0   0   1
	clear();

// Wait 1.52ms
//	sleep.microsecond(1520);
	sleep.millisecond(2);

// OK
	return 0;
}

void Display::setDataBits(const std::string str) {
	char const character = str[0];
	std::cout << "Character: " << character << " ";
	for (int i = 0; i < BYTE; i++) {
//		std::cout << std::to_string((character >> i) & 1) << " ";
		bool bit = (character >> i) & 1;
		if (bit) {
			std::cout << "1";
		} else
			std::cout << "0";
//		std::cout << "setDataBits: " << std::to_string(i) << std::endl;
		data_bit_[i].setValue(bit);
	}
//	for (int i = BYTE - 1; i >= 0; i--) {
//		bool bit = (character >> i) & 1;
//	}
	std::cout << std::endl;
	pulseEnableSignal();
}

void Display::setDataBits(const std::bitset<DISPLAY_DATA_LEN> bit) {
	std::cout << "Bitset ";
	for (int i = 1; i <= BYTE; i++) {
		if (bit[BYTE - i]) {
			std::cout << "1";
		} else
			std::cout << "0";

		data_bit_[i].setValue(bit[BYTE - i]);
	}
	std::cout << std::endl;
	pulseEnableSignal();
}

void Display::pulseEnableSignal() {
	enable_.setValue(false);
	sleep.microsecond(500);
	enable_.setValue(true);
}

void Display::sendCommand(const std::string command) {
	register_select_.setValue(false);  	// Register Select 	= true
	read_write_.setValue(false);		// Read/write 		= false
//	enable_.setValue(true);				// Enable 			= true
	setDataBits(command);  				// Set data bit
//	enable_.setValue(false);			// Enable 			= false;
//	pulseEnableSignal();				// Pulse enable signal to send data
}

void Display::sendData(const std::string data) {
	sleep.millisecond(1);
	register_select_.setValue(true);  	// Register Select 	= true
	read_write_.setValue(false);		// Read/write 		= false
//	enable_.setValue(true);				// Enable 			= true
	setDataBits(data);  				// Set data bit
//	enable_.setValue(false);			// Enable 			= false;
//	pulseEnableSignal();				// Pulse enable signal to send data
}

void Display::sendData(const char data) {
	std::string data_string;
	data_string += data;
	sleep.millisecond(1);
	register_select_.setValue(true);  	// Register Select 	= true
	read_write_.setValue(false);		// Read/write 		= false
//	enable_.setValue(true);				// Enable 			= true
	setDataBits(data_string);  				// Set data bit
//	enable_.setValue(false);			// Enable 			= false;
//	pulseEnableSignal();				// Pulse enable signal to send data
}
