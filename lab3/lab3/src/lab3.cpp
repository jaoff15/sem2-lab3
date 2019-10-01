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
//	std::cout << "Instanciating display" << std::endl;
	Display display;
//	std::cout << "Display initializing" << std::endl;
	display.init();
	display.print("Dickbutt");

	Keypad keypad;
	keypad.init();
//
	std::cout << "Started" << std::endl;
	while (1) {
		std::string key = keypad.NumpadDriver();
		if (key != "") {
			std::cout << key << std::endl;
		}
	}
	return 0;
}
