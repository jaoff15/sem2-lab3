/*
 * Gpio.cpp
 *
 *  Created on: Sep 24, 2019
 *      Author: jacoboffersen
 */

#include "Gpio.h"

Gpio::Gpio() {

}

Gpio::~Gpio() {

}

void Gpio::initializePin(std::string pin) {
	pin_ = pin;
	// Define path
	std::string export_path = "/sys/class/gpio/export";
	// Open file
	std::ofstream export_file(export_path.c_str());

	// Check if the file was actually opened
	if (!export_file.is_open()) {
		std::cerr << "Unable to open " << export_path << std::endl;
		//		return -1;
	} else {
		// Write pin numbers to file
		export_file << pin << std::endl;

		// Close the file
		export_file.close();

		path_ = "/sys/class/gpio/gpio" + pin_ + "/direction";

		// Write direction
		Gpio::setDirection(in);
		initialized_ = true;
	}
}

void Gpio::setDirection(const Direction dir) {
	if (initialized_) {
		std::ofstream file(path_.c_str());
		if (!file.is_open()) {
			std::cerr << "Unable to open " << path_ << std::endl;
//			return -1;
		} else {
			// Write directions to the file
			file << (dir == in) ? "in" : "out";

			// Close the file
			file.close();
		}
	}
}

void Gpio::setValue(const bool value) {
	if (initialized_) {
		// Define path
		std::string write_path = path_ + "/value";

		// Open file
		std::ofstream write_file(write_path.c_str());
		if (!write_file.is_open()) {
			std::cerr << "Unable to open " << write_path << std::endl;
//		return -1;
		} else {
			// Write value
			write_file << (value == true) ? "1" : "0";
		}
	}
}

bool Gpio::getValue() {
	if (initialized_) {
		// Define read path
		std::string read_path = path_ + "/value";
		std::ifstream read_file(read_path.c_str());
		if (!read_file.is_open()) {
			std::cerr << "Unable to open " << read_path << std::endl;
			return -1;
		}

		// read value
		std::string value;
		read_file >> value;
		return value == "1";
	}
}
