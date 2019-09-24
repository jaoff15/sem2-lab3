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

typedef enum {
	in, out
} Direction;

class Gpio {
public:
	Gpio(std::string pin);
	virtual ~Gpio();

	void setDirection(const Direction dir);
	void setValue(const bool value);
	bool getValue();

private:
	std::string path_;
	std::string pin_;
};

#endif /* GPIO_H_ */
