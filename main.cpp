#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>


enum InstructionType {
    MEM, // memory call, returns whatever is in memory
    MST, // memory stack
    BF0, // buffer 0
    BF1, // buffer 1
    MOV,
    PSH, // push data onto something, like PSH <data>, <location>(default is MST)
    ERA, // erase, deletes data from buffers or memory
    POP, // removes data from end of memory
    PRA, // pop erase, removes data from a given location of memory
    PRT, // prints the data from the given location
};

// Define the registers and memory
struct CPU {
    int registers[4] = {0}; // Example: Four general-purpose registers
    std::vector<int> memory; // Memory as a vector

    // Function to execute an instruction
    void execute(InstructionType type, int data, int location = 0) {
        switch (type) {
            case MEM:
                // Implement memory read operation
                if (location >= 0 && location < memory.size()) {
                    registers[0] = memory[location];
                }
                break;
            case MST:
                // Implement memory stack operation
                // (You can define this as needed)
                break;
            case BF0:
                // Implement buffer 0 operation
                // (You can define this as needed)
                break;
            case MOV:
                // Implement move operation
                if (location >= 0 && location < 4) {
                    registers[location] = data;
                }
                break;
            case PSH:
                // Implement push operation (default to MST)
                if (location >= 0 && location < memory.size()) {
                    memory.push_back(data);
                }
                break;
            case ERA:
                // Implement erase operation
                if (location >= 0 && location < memory.size()) {
                    memory.erase(memory.begin() + location);
                }
                break;
            case POP:
                // Implement pop operation
                if (!memory.empty()) {
                    memory.pop_back();
                }
                break;
            case PRA:
                // Implement pop erase operation at a given location
                if (location >= 0 && location < memory.size()) {
                    memory.erase(memory.begin() + location);
                }
                break;
            case PRT:
                std::cout << registers[location] <<std::endl;
                break;
            default:
                std::cout << "Invalid instruction" << std::endl;
                break;
        }
    }
};

int main() {
    CPU cpu;

    // Open the instructions file
    std::ifstream inputFile("main.neo");
    if (!inputFile) {
        std::cerr << "Failed to open instructions file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string instructionStr;
        int data, location;

        if (iss >> instructionStr >> data >> location) {
            InstructionType type;

            if (instructionStr == "MEM") {
                type = MEM;
            }
            else if (instructionStr == "MST") {
                type = MST;
            }
            else if (instructionStr == "BF0") {
                type = BF0;
            }
            else if (instructionStr == "BF1") {
                type = BF1;
            }
            else if (instructionStr == "MOV") {
                type = MOV;
            }
            else if (instructionStr == "PSH") {
                type = PSH;
            }
            else if (instructionStr == "ERA") {
                type = ERA;
            }
            else if (instructionStr == "POP") {
                type = POP;
            }
            else if (instructionStr == "PRA") {
                type = PRA;
            }
            else if (instructionStr == "PRT") {
                type = PRT;
            }
            else {
                std::cerr << "Invalid instruction: " << instructionStr << std::endl;
                continue; // Skip this line and move to the next one
            }

            // Execute the instruction
            cpu.execute(type, data, location);
        }
        else {
            std::cerr << "Invalid instruction format: " << line << std::endl;
        }
    }

    // Close the file
    inputFile.close();

    // Optionally, you can print the state of the CPU after executing the instructions.

    return 0;
}