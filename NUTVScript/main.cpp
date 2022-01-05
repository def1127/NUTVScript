#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include <string>

#include "MenuFunctions.h"

int main() {

    printMenu();
    
    while (true) {
        getUserInput();
    }
    
    return 0;
}
