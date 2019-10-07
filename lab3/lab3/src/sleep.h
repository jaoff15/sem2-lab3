/*
 * Sleep.h
 *
 *  Created on: Sep 30, 2019
 *      Author: jacoboffersen
 */

#ifndef SLEEP_H_
#define SLEEP_H_

#include <chrono>         // std::chrono::seconds
#include <thread>         // std::this_thread::sleep_for
#include <iostream>       // std::cout
#include <string>         // std::string

class Sleep {
public:
	Sleep();
	virtual ~Sleep();

	void microsecond(const unsigned int time);
	void millisecond(const unsigned int time);
};

#endif /* SLEEP_H_ */
