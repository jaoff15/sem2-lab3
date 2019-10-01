/*
 * Keypad.cpp
 *
 *  Created on: Sep 24, 2019
 *      Author: jacoboffersen
 */

#include "Keypad.h"

Keypad::Keypad() {
	initialized_ = false;
	width_ = 4;
	height_ = 4;
	last_keys_pressed = "";

}

Keypad::~Keypad() {

}
void Keypad::init() {
// Init all buttons in col. Coloums are initialized as outputs with default value of high.
	for (u8 pin = 1; pin <= KEYPAD_PIN_COL_LEN; pin++) {
		const int pin_number = KEYPAD_PIN_COL_LEN - pin;
		std::string pin_id = std::to_string(KEYPAD_PIN_COL_BASE + pin - 1);
		column_[pin_number].setPinNumber(pin_id);
		column_[pin_number].setDirection(out);
		column_[pin_number].setValue(true);
//		std::cout << column_[pin_number].getPin() << std::endl;
	}
// Init all buttons in row. The rows are initialized as inputs.
	for (u8 pin = 1; pin <= KEYPAD_PIN_ROW_LEN; pin++) {
		const int pin_number = KEYPAD_PIN_ROW_LEN - pin;
		std::string pin_id = std::to_string(KEYPAD_PIN_ROW_BASE + pin - 1);
		row_[pin_number].setPinNumber(pin_id);
		row_[pin_number].setDirection(in);
//		std::cout << row_[pin_number].getPin() << std::endl;
	}
	initialized_ = true;

}

std::string Keypad::NumpadDriver() {
	if (!initialized_) {
		return "";
	}
	std::string keys_pressed = "";
	for (u8 col = 0; col < width_; col++) {
		for (u8 row = 0; row < height_; row++) {
			if (!getValue(col, row)) {
				keys_pressed += keys_[row][col];
			}
		}
	}
	if (keys_pressed == last_keys_pressed) {
		return "";
	}
	last_keys_pressed = keys_pressed;
	return keys_pressed;
}

bool Keypad::getValue(const u8 col, const u8 row) {
	/* Set column low
	 * Read row
	 * Set column high
	 * Return pin value
	 * */
	column_[col].setValue(false);
	bool pin_value;
	row_[row].getValue(&pin_value);
	column_[col].setValue(true);
	return pin_value;

}
