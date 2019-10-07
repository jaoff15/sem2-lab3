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
	std::cout << "Init GPIO" << std::endl;
	initGpios();
	std::cout << "Init Display" << std::endl;
	initDisplay();
}

void Display::print(std::string str) {
	std::cout << "Print " << std::endl;
	clear();  										// Clear display
	home();
	for (int j = 0; j < DISPLAY_HEIGHT; j++) {  	// For each row
		for (int i = 0; i < DISPLAY_WIDTH; i++) {  	// For each character in row
			unsigned int character_id = j * DISPLAY_WIDTH + i;
			if (character_id < str.length()) {
				sendData(str[character_id]);		// Send data character to display
				std::cout << character_id << " ";
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
	std::cout << "Power On" << std::endl;
// Wait 20ms
	sleep.millisecond(20);
//	sleep.millisecond(50);

// Set function
	setFunction();

// Wait 37us
	sleep.microsecond(37);
//	sleep.microsecond(60);

// Display On/Off Control
	displayOnOffFunction();

// Wait 37us
	sleep.microsecond(37);
//	sleep.microsecond(60);

// Display clear
	clear();

// Wait 1.52ms
	sleep.microsecond(1520);
//	sleep.millisecond(2);

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

void Display::sendCommand(const std::bitset<10> command) {

	std::cout << "Command ";
	register_select_.setValue(command[command.size() - 1]);  	// Low for instruction transfer
	read_write_.setValue(command[command.size() - 2]);  	// Set to write mode
//	std::cout << "(RS)" << command[0] << " (RW)" << command[1] << " ";
	std::cout << command[0] << command[1];
//	for (unsigned int i = BYTE; i > 0; --i) {
	for (unsigned int i = 0; i < BYTE; i++) {
		const int id = i;
//		std::cout << " " << id << ":";
		data_bit_[id].setValue(command[id]);
//		std::cout << "(" << data_bit_[id].getPin() << ")";
		if (command[id]) {
			std::cout << "1";
		} else
			std::cout << "0";
	}
	std::cout << std::endl;
	pulseEnableSignal();
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
	std::cout << "Set Function";
	sendCommand((std::bitset<10>) "0000110000");
	// Bit 4: 1 = 8 bit data length
	// Bit 3: 1 = 2 active display lines
	// Bit 2: 0 = Font 5x8 bits
}

void Display::displayOnOffFunction() {
	// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	// 0   0   0   0   0   0   1   D   C   B
	std::cout << "Display on/off ";
	sendCommand((std::bitset<10>) "0000001111");
}

void Display::home() {
	// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	// 0   0   0   0   0   0   0   0   1   X
	std::cout << "Home ";
	sendCommand((std::bitset<10>) "0000000010");
}

void Display::clear() {
// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0   0   0   0   0   0   0   0   0   1
	std::cout << "Clear ";
	sendCommand((std::bitset<10>) "0000000001");
}

void Display::setEntryMode() {
	// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	// 0   0   0   0   0   0   0   1   1   1
	std::cout << "Set Entry Mode ";
	sendCommand((std::bitset<10>) "0000000110");
}

void Display::setEntryAddress() {
	// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	// 0   0   0   0   0   0   0   0   0   0
	std::cout << "Set Entry Address ";
	sendCommand((std::bitset<10>) "0010000000");
}
