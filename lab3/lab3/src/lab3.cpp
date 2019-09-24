//============================================================================
// Name        : lab3.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include "Keypad.h"

int main() {
	Keypad keypad;
	while (1) {
		std::string key = keypad.getKeyPressed();
		if (key != "") {
			std::cout << key << std::endl;
		}
	}
	return 0;
}
