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

void Gpio::setPinNumber(const std::string pin) {
	pin_ = pin;
}

void Gpio::setGpioPath(const std::string path) {
	gpio_path_ = path;
}

int Gpio::exportPin() {
	// Define path
	std::string export_path = gpio_path_ + "/export";
	// Open file
	std::ofstream export_file(export_path.c_str());

	// Check if the file was actually opened
	if (!export_file.is_open()) {
		std::cerr << "Unable to open " << export_path << std::endl;
		return -1;
	}
	// Write pin numbers to file
	export_file << pin_ << std::endl;

	// Close the file
	export_file.close();

	path_ = gpio_path_ + "/gpio" + pin_ + "/direction";

	// Write direction
	Gpio::setDirection(in);
	initialized_ = true;

	return 0;
}

int Gpio::unexportPin() {

}

int Gpio::setDirection(const Direction dir) {
	if (initialized_) {
		std::ofstream file(path_.c_str());
		if (!file.is_open()) {
			std::cerr << "Unable to open " << path_ << std::endl;
			return -1;
		}
		// Write directions to the file
		file << (dir == in) ? "in" : "out";

		// Close the file
		file.close();
		return 0;
	}
	return 1;
}

int Gpio::setValue(const bool value) {
	if (initialized_) {
		// Define path
		std::string write_path = path_ + "/value";

		// Open file
		std::ofstream write_file(write_path.c_str());
		if (!write_file.is_open()) {
			std::cerr << "Unable to open " << write_path << std::endl;
			return -1;
		}
		// Write value
		write_file << (value == true) ? "1" : "0";
		return 0;
	}
	return 1;
}

int Gpio::getValue(bool *value) {
	if (initialized_) {
		// Define read path
		std::string read_path = path_ + "/value";
		std::ifstream read_file(read_path.c_str());
		if (!read_file.is_open()) {
			std::cerr << "Unable to open " << read_path << std::endl;
			return -1;
		}

		// read value
		std::string read_value;
		read_file >> read_value;
		*value = read_value == "1";
		return 0;
	}
	return 1;
}
