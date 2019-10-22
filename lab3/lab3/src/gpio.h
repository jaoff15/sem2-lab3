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
#include "sleep.h"

#define LOCAL false		// Disable IO handling for local tests on pc

typedef enum {
	in, out
} Direction;

class Gpio {
public:
	Gpio();
	virtual ~Gpio();

	/* Set IO pin number */
	void setPinNumber(const std::string pin);

	/* Set GPIO path if it is different than the default (/sys/class/gpio)*/
	void setGpioPath(const std::string path);

	/* Export pin */
	int exportPin();

	/* Unexport pin */
	int unexportPin();

	/* Set pin direction */
	int setDirection(const Direction dir);

	/* Set pin value */
	int setValue(const bool value);

	/* Read pin value */
	int getValue(bool *value);

	std::string getPin();

private:
	Sleep sleep;
	std::string gpio_path_;  // Path to the GPIO
	std::string path_;		 // Path to the pin itself
	std::string pin_;		 // Pin number

};

#endif /* GPIO_H_ */
