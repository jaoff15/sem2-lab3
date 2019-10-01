/*
 * Keypad.h
 *
 *  Created on: Sep 24, 2019
 *      Author: jacoboffersen
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "types.hpp"
#include <string>
#include <iostream>

#include "Gpio.h"

#define KEYPAD_PIN_COL_BASE 992
#define KEYPAD_PIN_COL_LEN 4
#define KEYPAD_PIN_ROW_BASE 996
#define KEYPAD_PIN_ROW_LEN 4

const std::string keys_[4][4] = { { "1", "2", "3", "A" }, { "4", "5", "6", "B" }, { "7", "8", "9", "C" }, { "0", "F", "E", "D" } };

class Keypad {
public:
	Keypad();
	virtual ~Keypad();

	void init();
	std::string NumpadDriver();

private:
	bool initialized_;

	u8 width_;
	u8 height_;

	Gpio column_[4];
	Gpio row_[4];

	std::string last_keys_pressed;

//	std::string keys_[4][4];

	bool getValue(const u8 col, const u8 row);
};

#endif /* KEYPAD_H_ */
