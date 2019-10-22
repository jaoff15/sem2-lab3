/*
 * Display.cpp
 *
 *  Created on: Sep 26, 2019
 *      Author: jacoboffersen
 */

#include "display.h"

Display::Display() {
	data_bit_[DISPLAY_DATA_LEN] = { };
}

Display::~Display() {

}

void Display::init() {
	initGpios();
	initDisplay();
}

void Display::print(std::string line1, std::string line2) {
	clear();  										// Clear display
//	home();
	for (unsigned int j = 0; j < DISPLAY_HEIGHT; j++) {  	// For each row
		setEntryAddress(j);
//		sleep.microsecond(60);
		sleep.microsecond(1000);
		std::string str = (j == 0 ? line1 : line2);
//		std::cout << "j: " << j << "  " << str << std::endl;
		for (unsigned int i = 0; i < DISPLAY_WIDTH; i++) {  	// For each character in row
			if (i < str.length()) {
				sendData(str[i]);		// Send data character to display
			} else {
				//			break;								// If the string is empty. Break the loop
			}
		}
		std::cout << std::endl;
//		break;

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
	sleep.millisecond(1000);

// Set function
	setFunction();

// Wait 37us
	sleep.microsecond(1000);

// Display On/Off Control
	displayOnOffFunction();

// Wait 37us
	sleep.microsecond(1000);

// Display clear
	clear();

// Wait 1.52ms
	sleep.millisecond(2);

	setEntryMode();
	sleep.microsecond(500);

// OK
	return 0;
}

void Display::setDataBits(const std::string str) {
	register_select_.setValue(true);
	read_write_.setValue(false);
	char const character = str[0];
	for (int i = 0; i < BYTE; i++) {
		bool bit = (character >> i) & 1;
		data_bit_[i].setValue(bit);
	}
	pulseEnableSignal();
}

void Display::pulseEnableSignal() {
	enable_.setValue(false);
	sleep.millisecond(1);
	enable_.setValue(true);
}

void Display::sendCommand(const std::bitset<10> command) {
	register_select_.setValue(command[command.size() - 1]);  	// Low for instruction transfer
	read_write_.setValue(command[command.size() - 2]);  		// Set to write mode
	for (unsigned int i = 0; i < BYTE; i++) {
		data_bit_[i].setValue(command[i]);
	}
	pulseEnableSignal();
}

void Display::sendData(const char data) {
	std::string data_string;
	data_string += data;
	sendData(data_string);
}

void Display::sendData(const std::string data) {
	sleep.millisecond(1);
	register_select_.setValue(true);  	// High for data
	read_write_.setValue(false);		// Set to write mode
	setDataBits(data);  				// Set data bit
}

void Display::setFunction() {
	// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	// 0   0   0   0   1  DL   N   F   X   X
	// Set interface data length DL ('1' for 8 bit)
	// Number of display lines N ('1' for 2 lines)
	// Font F ('0' for 5×8 dots)
	sendCommand((std::bitset<10>) "0000110000");
	sleep.millisecond(1000);
	sendCommand((std::bitset<10>) "0000111000");
}

void Display::displayOnOffFunction() {
	// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	// 0   0   0   0   0   0   1   D   C   B
	sendCommand((std::bitset<10>) "0000001100");
	sleep.millisecond(1000);
}

void Display::home() {
	// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	// 0   0   0   0   0   0   0   0   1   X
	sendCommand((std::bitset<10>) "0000000010");
}

void Display::clear() {
// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0   0   0   0   0   0   0   0   0   1
	sendCommand((std::bitset<10>) "0000000001");
}

void Display::setEntryMode() {
	// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	// 0   0   0   0   0   0   0   1   1   1
	sendCommand((std::bitset<10>) "0000000110");
}

void Display::setEntryAddress(const int line_number) {
	// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
	// 0   0   1   x  0   0   0   0   0   0
	// x = 1 for line 1 otherwise x = 0
	sendCommand((std::bitset<10>) (line_number != 1 ? "0010000000" : "0011000000"));
}
