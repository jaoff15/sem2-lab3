//============================================================================
// Name        : lab3.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include "Keypad.h"
#include "Display.h"

int main() {

	Display display;
	display.init();
	display.print("Test123");

//	Keypad keypad;
//	keypad.init();
//	while (1) {
//		std::string key = keypad.NumpadDriver();
//		if (key != "") {
//			std::cout << key << std::endl;
//		}
//	}
	return 0;
}
