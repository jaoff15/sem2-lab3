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
	clear();								  // Clear display
	setDataBits((std::bitset<8>) "00000010"); // Return home

	for (int j = 0; j < DISPLAY_HEIGHT; j++) {			// For both rows
		for (int i = 0; i < DISPLAY_WIDTH; i++) {	// For each character

			unsigned int character_id = j * DISPLAY_WIDTH + i;
			std::string character = "";
			if (character_id < str.length()) {
				character = str[character_id];
			}
			setDataBits(character);
		}
	}
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
	for (int i = DISPLAY_DATA_BASE; i < DISPLAY_DATA_BASE + DISPLAY_DATA_LEN;
			i++) {
		data_bit_[i].setPinNumber(std::to_string(i));
		data_bit_[i].setDirection(out);
	}
}
int Display::initDisplay() {
// Power on

// Wait 20ms
	std::this_thread::sleep_for(std::chrono::milliseconds(20));

// Set function
// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0   0   0   0   1  DL   N   F   X   X
	register_select_.setValue(false);
	read_write_.setValue(false);
	setDataBits((std::bitset<8>) "00110000");
// Bit 4: 1 = 8 bit data length
// Bit 3: 1 = 2 active display lines
// Bit 2: 0 = Font 5x8 bots

// Wait 37us
	std::this_thread::sleep_for(std::chrono::microseconds(37));

// Display On/Off Control
// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0   0   0   0   0   0   1   D   C   B
	setDataBits((std::bitset<8>) "00001001");

// Wait 37us
	std::this_thread::sleep_for(std::chrono::microseconds(37));

// Display clear
// RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0   0   0   0   0   0   0   0   0   1
	clear();

// Wait 1.52ms
	std::this_thread::sleep_for(std::chrono::microseconds(1520));

// OK
	return 0;
}

void Display::setDataBits(const std::string str) {
	// Switch nibbles
	// str     = 12345678
	// databit = 56781234
	char character = 0b00000000;
	character |= (str[0] & 0b00001111) << 4;
	character |= (str[0] & 0b11110000) >> 4;

	// Nibbles stay in place
	// str 	   = 12345678
	// databit = 12345678
	character = str[0];
	for (int i = 0; i < DISPLAY_DATA_LEN; i++) {
		data_bit_[i].setValue((bool) character[i]);
	}
}

void Display::setDataBits(const std::bitset<DISPLAY_DATA_LEN> bit) {
	for (int i = 0; i < DISPLAY_DATA_LEN; i++) {
		data_bit_[i].setValue(bit[i]);
	}
}

void Display::pulseEnableSignal() {
	enable_.setValue(false);
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	enable_.setValue(true);
}

void Display::sendCommand(const std::string command) {

}

void Display::sendData(const std::string data) {

}

void Display::sendData(const char data) {

}
