/*
 * Sleep.cpp
 *
 *  Created on: Sep 30, 2019
 *      Author: jacoboffersen
 */

#include "Sleep.h"

Sleep::Sleep() {
	// TODO Auto-generated constructor stub

}

Sleep::~Sleep() {
	// TODO Auto-generated destructor stub
}

void Sleep::sleepMicrosecond(const unsigned int time) {
	std::this_thread::sleep_for(std::chrono::microseconds(time));
}
void Sleep::sleepMillisecond(const unsigned int time) {
	std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

