/*
 * Display.h
 *
 *  Created on: Sep 26, 2019
 *      Author: jacoboffersen
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "Gpio.h"
#include <iostream>       // std::cout
#include <string>         // std::string
#include <bitset>         // std::bitset
#include <chrono>         // std::chrono::seconds
#include <thread>         // std::this_thread::sleep_for

#define DISPLAY_DATA_BASE 1016
#define DISPLAY_DATA_LEN 8
#define DISPLAY_RS_PIN 1012
#define DISPLAY_RW_PIN 1013
#define DISPLAY_ENABLE_PIN 1014

class Display {
public:
	Display();
	virtual ~Display();

	void DisplayDriver();
	void init();
	void print(std::string str);
	void clear();

private:
	Gpio data_bit_[DISPLAY_DATA_LEN] = { };
	Gpio register_select_;
	Gpio read_write_;
	Gpio enable_;

	void initGpios();
	int initDisplay();
	void setDataBits(const std::string str);
	void setDataBits(const std::bitset<DISPLAY_DATA_LEN> bit);
	void pulseEnableSignal();
	void sendCommand(const std::string command);
	void sendData(const std::string data);
	void sendData(const char data);
};

#endif /* DISPLAY_H_ */
