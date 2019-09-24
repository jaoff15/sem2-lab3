/*
 * Keypad.cpp
 *
 *  Created on: Sep 24, 2019
 *      Author: jacoboffersen
 */

#include "Keypad.h"

Keypad::Keypad() {

}

Keypad::~Keypad() {

}
void Keypad::initializeButtons() {
	// Init all buttons in col. Coloums are initialized as outputs with default value of high.
	for (u8 pin = 0; pin < KEYPAD_PIN_COL_LEN; pin++) {
		std::string pin_id = std::to_string(KEYPAD_PIN_COL_BASE + pin);
		column_[KEYPAD_PIN_COL_LEN - pin].initializePin(pin_id);
		column_[KEYPAD_PIN_COL_LEN - pin].setDirection(out);
		column_[KEYPAD_PIN_COL_LEN - pin].setValue(true);
	}
	// Init all buttons in row. The rows are initialized as inputs.
	for (u8 pin = 0; pin < KEYPAD_PIN_ROW_LEN; pin++) {
		std::string pin_id = std::to_string(KEYPAD_PIN_ROW_BASE + pin);
		row_[KEYPAD_PIN_ROW_LEN - pin].initializePin(pin_id);
		row_[KEYPAD_PIN_ROW_LEN - pin].setDirection(in);
	}
	initialized_ = true;
}

std::string Keypad::getKeyPressed() {
	if (!initialized_) {
		return "";
	}
	std::string keys_pressed = "";
	for (u8 col = 0; col < width_; col++) {
		for (u8 row = 0; row < height_; row++) {
			if (getPinValue(col, row)) {
				keys_pressed += keys_[col][row];
			}
		}
	}
	return keys_pressed;
}

bool Keypad::getPinValue(const u8 col, const u8 row) {
	/* Set column low
	 * Read row
	 * Set column high
	 * Return pin value
	 * */
	column_[col].setValue(false);
	bool pin_value = row_[row].getValue();
	column_[col].setValue(true);
	return pin_value;

//	if (col == 3 && row == 0) {
//		return true;
//	}
//	return false;
}
