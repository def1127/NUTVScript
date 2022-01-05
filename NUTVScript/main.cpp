#include <iostream>

#include "MenuFunctions.h"
#include "interpreter.h"

int main() {

    printMenu();
    
    while (true) { //forever run the menu
        getUserInput();
    }
    
    return 0;
}
