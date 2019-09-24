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

class Keypad {
public:
	Keypad();
	virtual ~Keypad();

	std::string getKeyPressed();

private:
	bool initialized_ = false;

	const u8 width_ = 4;
	const u8 height_ = 4;

	Gpio column_[4];
	Gpio row_[4];

	const std::string keys_[4][4] = { { "1", "2", "3", "A" }, { "4", "5", "6",
			"B" }, { "7", "8", "9", "C" }, { "0", "F", "E", "D" } };

	void initializeButtons();

	bool getPinValue(const u8 col, const u8 row);
};

#endif /* KEYPAD_H_ */
