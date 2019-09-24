#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <unistd.h>

int main()
{

// -------------------------------------------------------------------------------------
// 1. Activate GPIO pin (similar to: echo 984 > /sys/class/gpio/export)

	// Define path
	std::string export_path = "/sys/class/gpio/export";

    // Define pin numbers
    std::string led_pin = "984";
    std::string button_pin = "988";

	// Open file
    std::ofstream export_file( export_path.c_str() );

    // Check if the file was actually opened
    if(!export_file.is_open())
    {
        std::cerr << "Unable to open " << export_path << std::endl;
        return -1;
    }

    // Write pin numbers to file
    export_file << led_pin << std::endl << button_pin;

    // Close the file
    export_file.close();


// -------------------------------------------------------------------------------------
// 2. Set directions (similar to: echo "out" > /sys/class/gpio/gpio988/direction)

	// Define paths
	std::string led_path = "/sys/class/gpio/gpio" + led_pin + "/direction";
	std::string button_path = "/sys/class/gpio/gpio" + button_pin + "/direction";

	// Open files
    std::ofstream led_file( led_path.c_str() );
    if(!led_file.is_open())
    {
        std::cerr << "Unable to open " << led_path << std::endl;
        return -1;
    }

    std::ofstream button_file( button_path.c_str() );
    if(!button_file.is_open())
    {
        std::cerr << "Unable to open " << button_path << std::endl;
        return -1;
    }

    // Write directions to the files
    led_file << "out";
    button_file << "in";

    // Close the files
    led_file.close();
    button_file.close();

// -------------------------------------------------------------------------------------
// 3. Read the button state (similar to: cat /sys/class/gpio/gpio988/value)

    // Define path
    std::string read_button_path = "/sys/class/gpio/gpio" + button_pin + "/value";

    // Open file
    std::ifstream read_button_file( read_button_path.c_str() );
    if(!read_button_file.is_open())
    {
        std::cerr << "Unable to open " << read_button_path << std::endl;
        return -1;
    }

    // read value
    std::string button_value;
    read_button_file >> button_value;

// -------------------------------------------------------------------------------------
// 4. Write to the LED (similar to: echo 1 > /sys/class/gpio/gpio988/value)

	// Define path
	std::string write_led_path = "/sys/class/gpio/gpio" + led_pin + "/value";

    // Open file
    std::ofstream write_led_file( write_led_path.c_str() );
    if(!write_led_file.is_open())
    {
        std::cerr << "Unable to open " << write_led_path << std::endl;
        return -1;
    }

    // Write value
    write_led_file << "1";


// -------------------------------------------------------------------------------------
// 5. Link the button an LED

    // Loop forever
    while(true)
    {
    	// Reset the get pointer
    	read_button_file.seekg(0);

    	// Read button value
    	read_button_file >> button_value;

    	// Write button value to LED
    	write_led_file << button_value << std::endl;

    	// Wait 10ms
    	usleep(10000);
    }

    return 0;

}

