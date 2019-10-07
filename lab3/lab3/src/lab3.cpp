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
	std::string str = "Dickbutt";
	Display display;
	display.init();
	display.print(str);

	Keypad keypad;
	keypad.init();

	Sleep sleep;

	std::cout << "Started" << std::endl;
	while (1) {
		std::string key = keypad.NumpadDriver();
		if (key != "") {
			std::cout << key << std::endl;
			if (key == "1D") {
				str = "";
				sleep.millisecond(500);
			} else {
				if (str.length() >= 16) {	// Remove first element if string becomes too long
					str = str.substr(1);
				}
				str += key;
			}
			display.print(str);
		}
	}
	return 0;
}
