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

class Sleep {
public:
	Sleep();
	virtual ~Sleep();

	void sleepMicrosecond(const unsigned int time);
	void sleepMillisecond(const unsigned int time);
};

#endif /* SLEEP_H_ */
