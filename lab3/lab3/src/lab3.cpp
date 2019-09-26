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
	keypad.init();
	while (1) {
		std::string key = keypad.NumpadDriver();
		if (key != "") {
			std::cout << key << std::endl;
		}
	}
	return 0;
}
