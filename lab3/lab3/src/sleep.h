/*
 * Sleep.h
 *
 *  Created on: Sep 30, 2019
 *      Author: jacoboffersen
 */

#ifndef SLEEP_H_
#define SLEEP_H_

#include <iostream>
#include <string>         // std::string
#include <unistd.h>

class Sleep {
public:
	Sleep();
	virtual ~Sleep();

	void microsecond(const unsigned int time);
	void millisecond(const unsigned int time);
};

#endif /* SLEEP_H_ */
