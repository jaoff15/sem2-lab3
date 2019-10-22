//============================================================================
// Name        : lab3.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>

#include "display.h"
#include "keypad.h"

int main() {
	std::string str1 = "Line 1";
	std::string str2 = "Line 2";
	Display display;
	display.init();
	display.print(str1, str2);

	Keypad keypad;
	keypad.init();

	Sleep sleep;

	std::cout << "Started" << std::endl;

	while (1) {

		std::string key = keypad.NumpadDriver();
		if (key != "") {
			std::cout << key << std::endl;

			if (key == "1D") {
				str1 = "";
				sleep.millisecond(500);
			} else {
				if (str1.length() >= 16) {	// Remove first element if string becomes too long
					str1 = str1.substr(1);
				}
				str1 += key;
			}
			display.print(str1, key);
		}
	}
	return 0;
}
