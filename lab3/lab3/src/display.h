/*
 * Display.h
 *
 *  Created on: Sep 26, 2019
 *      Author: jacoboffersen
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <iostream>       // std::cout
#include <string>         // std::string
#include <bitset>         // std::bitset
#include "gpio.h"
#include "sleep.h"

#define DISPLAY_RS_PIN 		1012
#define DISPLAY_RW_PIN 		1013
#define DISPLAY_ENABLE_PIN 	1014
#define DISPLAY_DATA_BASE 	1016
#define DISPLAY_DATA_LEN 	8

#define DISPLAY_HEIGHT 		2
#define DISPLAY_WIDTH 		16

#define BYTE 				8

class Display {
public:
	Display();
	virtual ~Display();

	void init();
	void print(std::string line1, std::string line2);

private:
	Gpio data_bit_[DISPLAY_DATA_LEN];
	Gpio register_select_;
	Gpio read_write_;
	Gpio enable_;
	Sleep sleep;

	void initGpios();
	int initDisplay();
	void setDataBits(const std::string str);
	void setDataBits(const std::bitset<DISPLAY_DATA_LEN> bit);
	void pulseEnableSignal();
	void sendCommand(const std::bitset<10> command);
	void sendData(const std::string data);
	void sendData(const char data);

	void setFunction();
	void displayOnOffFunction();
	void clear();
	void home();
	void setEntryMode();
	void setEntryAddress(const int line_number);

};

#endif /* DISPLAY_H_ */
