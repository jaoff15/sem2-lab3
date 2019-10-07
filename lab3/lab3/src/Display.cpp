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
	initGpios();
	initDisplay();
}

void Display::print(std::string str) {
	std::cout << "Print " << std::endl;
	clear();  										// Clear display
	home();
	for (int j = 0; j < DISPLAY_HEIGHT; j++) {  	// For each row
		for (int i = 0; i < DISPLAY_WIDTH; i++) {  	// For each character in row
			unsigned int character_id = j * DISPLAY_WIDTH + i;
			std::cout << character_id << std::endl;
			if (character_id < str.length()) {
				sendData(str[character_id]);		// Send data character to display
			} else {
				break;								// If the string is empty. Break the loop
			}
		}
	}
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
//	sleep.millisecond(20);
	sleep.millisecond(50);

// Set function
	setFunction();

// Wait 37us
//	sleep.microsecond(37);
	sleep.microsecond(60);

// Display On/Off Control
	displayOnOffFunction();

// Wait 37us
//	sleep.microsecond(37);
	sleep.microsecond(60);

// Display clear
	clear();

// Wait 1.52ms
//	sleep.microsecond(1520);
	sleep.millisecond(2);

	setEntryMode();
	sleep.microsecond(60);
	setEntryAddress();
	sleep.microsecond(60);

// OK
	return 0;
}

void Display::setDataBits(const std::string str) {
	register_select_.setValue(true);
	read_write_.setValue(false);
	char const character = str[0];
	std::cout << "Character: " << character << " ";
	for (int i = 0; i < BYTE; i++) {
		bool bit = (character >> i) & 1;
		if (bit) {
			std::cout << "1";
		} else
			std::cout << "0";
		data_bit_[i].setValue(bit);
	}
	std::cout << std::endl;
	pulseEnableSignal();
}

void Display::setDataBits(const std::bitset<DISPLAY_DATA_LEN> bit) {
	register_select_.setValue(true);  	// High for data
	read_write_.setValue(false);		// Set to write mode
	std::cout << "Bitset ";
	for (int i = 1; i <= BYTE; i++) {
		if (bit[BYTE - i]) {
			std::cout << "1";
		} else
			std::cout << "0";
		std::cout << "(" << data_bit_[BYTE - i].getPin() << ") ";
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
	register_select_.setValue(false);  	// Low for instruction transfer
	read_write_.setValue(false);		// Set to write mode
	setDataBits(command);  				// Set data bit
}

void Display::sendData(const std::string data) {
	sleep.millisecond(1);
	register_select_.setValue(true);  	// High for data
	read_write_.setValue(false);		// Set to write mode
	setDataBits(data);  				// Set data bit
}

void Display::sendData(const char data) {

	std::string data_string;
	data_string += data;
	sleep.millisecond(1);
	register_select_.setValue(true);  	// High for data
	read_write_.setValue(false);		// Set to write mode
	setDataBits(data_string);  			// Set data bit
}

void Display::setFunction() {
	// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	// 0   0   0   0   1  DL   N   F   X   X
	register_select_.setValue(false);
	read_write_.setValue(false);
	std::cout << "Set Function ";
	setDataBits((std::bitset<8>) "00110000");
	pulseEnableSignal();
	// Bit 4: 1 = 8 bit data length
	// Bit 3: 1 = 2 active display lines
	// Bit 2: 0 = Font 5x8 bits
}
void Display::displayOnOffFunction() {
	// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	// 0   0   0   0   0   0   1   D   C   B
	register_select_.setValue(false);
	read_write_.setValue(false);
	std::cout << "Display on/off ";
	setDataBits((std::bitset<8>) "00001111");
	pulseEnableSignal();
}
void Display::home() {
	// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	// 0   0   0   0   0   0   0   0   1   X
	register_select_.setValue(false);
	read_write_.setValue(false);
	std::cout << "Home ";
	setDataBits((std::bitset<8>) "00000010");
	pulseEnableSignal();

}
void Display::clear() {
// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0   0   0   0   0   0   0   0   0   1
	register_select_.setValue(false);
	read_write_.setValue(false);
	std::cout << "Clear ";
	setDataBits((std::bitset<8>) "00000001");
}

void Display::setEntryMode() {
	// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	// 0   0   0   0   0   0   0   1   1   1
	register_select_.setValue(false);
	read_write_.setValue(false);
	std::cout << "Set Entry Mode ";
	setDataBits((std::bitset<8>) "00000111");
}

void Display::setEntryAddress() {
	// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	// 0   0   0   0   0   0   0   0   0   0
	register_select_.setValue(false);
	read_write_.setValue(false);
	std::cout << "Set Entry Address ";
	setDataBits((std::bitset<8>) "10000000");
}
