#include "system/System.h"
#include <iostream>

using namespace std;

int main()
{
    try
    {
        System system;  // Initialize the system
        system.start(); // Start the system's main loop
    }
    catch (const std::exception &e)
    {
        std::cerr << "An error occurred: " << e.what() << endl;
    }
    catch (...)
    {
        std::cerr << "An unknown error occurred." << endl;
    }

    return 0;
}
