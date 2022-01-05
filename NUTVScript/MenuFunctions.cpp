#include "MenuFunctions.h"
#include <filesystem>

void printMenu() {
    std::cout << "NUTVScript Interpreter by David Fatheree" << std::endl; //prints some starting instructions
    std::cout << "Enter help for list of commands         " << std::endl;
}

void getUserInput() {
//    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //flush the buffer, crashes the program for some reason? allows the user to do things they shouldn't

    std::string str;
    std::string var;
    std::cout << "> ";
    std::cin >> str; //take an input from a user. Note: some strings may remain in the buffer.

    if (str.rfind("ls", 0) == 0) { //runs the ls command
        ls();
    }
    else if (str.rfind("run", 0) == 0) { //runs the interpreter
        std::cin >> var;
        run(var);
    }
    else if (str.rfind("man", 0) == 0) { //runs the man command
        std::cin >> var;
        man(var);
    }
    else if (str.rfind("help", 0) == 0) { //runs the help command
        help();
    }
    else if (str.rfind("exit", 0) == 0) { //exits the program with code 0
        std::exit(0);
    }
    else { //if the user didn't enter a command, tell the user there was an error
        std::cout << "Error: invalid input, try 'help' for a list of commands" << std::endl;
    }
}

void help() { //print all commands available
    std::cout << "\n\n";
    std::cout << "------------------------------------\n";
    std::cout << "|           Help Menu               |" << std::endl;
    std::cout << "| 1. ls - Lists all files           |" << std::endl;
    std::cout << "| 2. run [name] - Runs file         |" << std::endl;
    std::cout << "| 3. help - Displays this           |" << std::endl;
    std::cout << "| 4. man - Detailed info about help |" << std::endl;
    std::cout << "| 5. exit - Exit the interpreter    |" << std::endl;
    std::cout << "------------------------------------\n";
}

//https://www.delftstack.com/howto/cpp/how-to-get-list-of-files-in-a-directory-cpp/
void ls() { //print out all files in the active directory

    std::string path = "/Users/defdo/source/repos/NUTVScript/x64/Debug";

    for (const auto& file : std::filesystem::directory_iterator(path))
        std::cout << file.path() << std::endl;

}

void man(std::string command) { //print out detailed help information about each command as requested

    std::cout << std::endl;

    if (command == "ls") {
        std::cout << "ls - Lists all files in the active directory. NUTVScript scripts must be located in the active directory." << std::endl;
    }
    else if (command == "help") {
        std::cout << "help - Prints out a list of all valid commands in the NUTVScript interpreter." << std::endl;
    }
    else if (command == "run") {
        std::cout << "run [filename] - Runs the NUTVScript interpreter on the input file. NUTVScript scripts must be located in the active directory." << std::endl;
    }
    else if (command == "exit") {
        std::cout << "exit - Exits the NUTVScript interpreter." << std::endl;
    }
    else if (command == "man") {
        std::cout << "man [command] - Prints detailed information about each command in the NUTVScript interpreter." << std::endl;
    }
    else {
        std::cout << "Invalid command entered, try running 'help' for a list of valid commands." << std::endl;
    }

}