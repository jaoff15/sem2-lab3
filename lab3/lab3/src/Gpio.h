/*
 * Gpio.h
 *
 *  Created on: Sep 24, 2019
 *      Author: jacoboffersen
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <unistd.h>

#define LOCAL false

typedef enum {
	in, out
} Direction;

class Gpio {
public:
	Gpio();
	virtual ~Gpio();

	void setPinNumber(const std::string pin);
	void setGpioPath(const std::string path);
	int exportPin();
	int unexportPin();
	int setDirection(const Direction dir);
	int setValue(const bool value);
	int getValue(bool *value);

	std::string getPin();

private:
	bool initialized_;

	std::string gpio_path_;
	std::string path_;
	std::string pin_;
};

#endif /* GPIO_H_ */
