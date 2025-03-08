#include <iostream>
#include <string>
#include "shell.h"

void start_shell() {
    std::cout << "Shell started. Type 'help' for commands." << std::endl;
    while(true) {
        std::cout << "> ";
        std::string command;
        std::getline(std::cin, command);
        if(command == "help") {
            std::cout << "Available commands: help, exit" << std::endl;
        } else if(command == "exit") {
            std::cout << "Exiting shell." << std::endl;
            break;
        } else {
            std::cout << "Unknown command: " << command << std::endl;
        }
    }
}
