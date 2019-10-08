/*
 * Sleep.cpp
 *
 *  Created on: Sep 30, 2019
 *      Author: jacoboffersen
 */

#include "sleep.h"

Sleep::Sleep() {
}

Sleep::~Sleep() {

}

void Sleep::microsecond(const unsigned int time) {
	usleep(time);
}

void Sleep::millisecond(const unsigned int time) {
	usleep(time * 1000);
}

