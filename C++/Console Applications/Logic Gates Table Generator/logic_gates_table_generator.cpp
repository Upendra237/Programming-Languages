/**
 * @file logic_gates_table_generator.cpp
 * @brief A command-line tool for generating and visualizing truth tables for various logic gates
 * @author Upendra Shahi
 * @version 1.0
 * @date 2025-02-16
 * 
 * This program generates truth tables for basic and complex logic gates including
 * AND, OR, NOT, NAND, NOR, XOR, and XNOR gates. It supports up to 16 inputs and
 * provides a colorful, interactive command-line interface.
 */

 #include <iostream>
 #include <string>
 #include <vector>
 #include <cmath>
 #include <iomanip>
 #include <algorithm>
 #include <limits>
 
 using namespace std;
 
 /**
  * @brief ANSI Color codes for terminal output styling
  * These constants define the color codes used for terminal text formatting
  */
 const string RESET = "\033[0m";     // Reset all formatting
 const string BOLD = "\033[1m";      // Bold text
 const string RED = "\033[31m";      // Error messages and '0' values
 const string GREEN = "\033[32m";     // Success messages and '1' values
 const string YELLOW = "\033[33m";    // Warnings and headers
 const string BLUE = "\033[34m";      // Information and prompts
 const string MAGENTA = "\033[35m";   // Titles
 const string CYAN = "\033[36m";      // Borders and structure
 const string WHITE = "\033[37m";     // Regular text
 
 /**
  * @brief Enables ANSI color support in Windows terminal
  * This function ensures color codes work properly in Windows Command Prompt
  */
 void enableColors() {
     #ifdef _WIN32
         system("color");
     #endif
 }
 
 /**
  * @brief Generates all possible input combinations for n inputs
  * @param n Number of inputs
  * @return Vector of vectors containing all possible binary combinations
  * 
  * This function generates a truth table matrix with 2^n rows, where each row
  * represents one possible combination of input values.
  */
 vector<vector<int>> generateCombinations(int n) {
     int totalCombinations = pow(2, n);
     vector<vector<int>> combinations(totalCombinations, vector<int>(n));
     for (int i = 0; i < totalCombinations; ++i) {
         for (int j = 0; j < n; ++j) {
             combinations[i][j] = (i >> (n - j - 1)) & 1;
         }
     }
     return combinations;
 }
 
 /**
  * @brief Basic Logic Gate Functions
  * Each function implements the logic for a specific gate type
  */
 
 int orGate(const vector<int>& inputs) {
     for (int input : inputs) {
         if (input == 1) return 1;  // OR gate returns 1 if any input is 1
     }
     return 0;
 }
 
 int andGate(const vector<int>& inputs) {
     for (int input : inputs) {
         if (input == 0) return 0;  // AND gate returns 0 if any input is 0
     }
     return 1;
 }
 
 int notGate(int input) {
     return input == 0 ? 1 : 0;  // NOT gate inverts the input
 }
 
 /**
  * @brief Complex Logic Gate Functions
  * These gates are implemented using combinations of basic gates
  */
 
 int nandGate(const vector<int>& inputs) {
     return !andGate(inputs);  // NAND is AND followed by NOT
 }
 
 int norGate(const vector<int>& inputs) {
     return !orGate(inputs);   // NOR is OR followed by NOT
 }
 
 int xorGate(const vector<int>& inputs) {
     int result = inputs[0];
     for (size_t i = 1; i < inputs.size(); i++) {
         result ^= inputs[i];  // XOR operation using bitwise XOR
     }
     return result;
 }
 
 int xnorGate(const vector<int>& inputs) {
     return !xorGate(inputs);  // XNOR is XOR followed by NOT
 }
 /**
 * @brief Clears the terminal screen
 * Cross-platform function to clear terminal output
 */
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/**
 * @brief Displays the truth table for a logic gate
 * @param combinations Vector of input combinations
 * @param outputs Vector of corresponding outputs
 * @param gate Name of the logic gate
 * @param numInputs Number of inputs for the gate
 * 
 * Generates a formatted, colored truth table showing all input combinations
 * and their corresponding outputs for the specified logic gate.
 */
void displayTable(const vector<vector<int>>& combinations, 
                 const vector<int>& outputs, 
                 const string& gate, 
                 int numInputs) {
    enableColors();
    
    // Calculate table dimensions
    int columnWidth = 8;
    int inputWidth = numInputs * columnWidth + (numInputs - 1);
    int outputWidth = 8;
    int totalWidth = inputWidth + outputWidth + 3;

    // Lambda for text centering
    auto centerText = [](const string& text, int width) -> string {
        int padding = width - text.length();
        int leftPad = padding / 2;
        int rightPad = padding - leftPad;
        return string(leftPad, ' ') + text + string(rightPad, ' ');
    };

    cout << "\n";
    
    // Title section for larger tables
    if (numInputs >= 4) {
        cout << CYAN << "+" << string(totalWidth, '=') << "+" << RESET << "\n";
        string title = gate + " Gate Truth Table (" + to_string(numInputs) + " inputs)";
        cout << CYAN << "|" << MAGENTA << BOLD << centerText(title, totalWidth) 
             << CYAN << "|" << RESET << "\n";
        cout << CYAN << "+" << string(totalWidth, '=') << "+" << RESET << "\n";
    }

    // Table header
    cout << CYAN << "+" << string(totalWidth, '=') << "+" << RESET << "\n";
    cout << CYAN << "| " << YELLOW << BOLD << centerText("INPUTS", inputWidth-1) 
         << CYAN << "||" << YELLOW << BOLD << "  OUTPUT " << CYAN << "|" << RESET << "\n";

    // Column headers
    cout << CYAN << "+";
    for (int i = 0; i < numInputs; i++) {
        cout << string(columnWidth, '=');
        if (i < numInputs - 1) cout << "+";
    }
    cout << "++" << string(outputWidth + 1, '=') << "+" << RESET << "\n";

    cout << CYAN << "|";
    for (int i = 0; i < numInputs; i++) {
        string header = " A" + to_string(i) + " ";
        cout << BLUE << BOLD << centerText(header, columnWidth) << CYAN << "|";
    }
    cout << "|" << BLUE << BOLD << "   OUT   " << CYAN << "|" << RESET << "\n";

    // Separator
    cout << CYAN << "+";
    for (int i = 0; i < numInputs; i++) {
        cout << string(columnWidth, '=');
        if (i < numInputs - 1) cout << "+";
    }
    cout << "++" << string(outputWidth + 1, '=') << "+" << RESET << "\n";

    // Table content
    for (size_t i = 0; i < combinations.size(); ++i) {
        // Input values
        cout << CYAN << "|";
        for (int j = 0; j < numInputs; j++) {
            string value = " " + to_string(combinations[i][j]) + " ";
            cout << (combinations[i][j] ? GREEN : RED) << BOLD 
                 << centerText(value, columnWidth) << CYAN << "|";
        }
        
        // Output value
        cout << "|" << (outputs[i] ? GREEN : RED) << BOLD 
             << "    " << outputs[i] << "    " << CYAN << "|" << RESET << "\n";

        // Row separator
        if (i < combinations.size() - 1) {
            cout << CYAN << "+";
            for (int j = 0; j < numInputs; j++) {
                cout << string(columnWidth, '-');
                if (j < numInputs - 1) cout << "+";
            }
            cout << "++" << string(outputWidth + 1, '-') << "+" << RESET << "\n";
        }
    }

    // Bottom border
    cout << CYAN << "+";
    for (int i = 0; i < numInputs; i++) {
        cout << string(columnWidth, '=');
        if (i < numInputs - 1) cout << "+";
    }
    cout << "++" << string(outputWidth + 1, '=') << "+" << RESET << "\n\n";
}
/**
 * @brief Displays the help menu with available commands
 * Shows a formatted list of all available commands and their descriptions
 */
 void displayHelp() {
    // Fixed width for help menu
    const int width = 45;  // Reduced width to prevent overflow

    // Title section
    cout << "\n" << CYAN << "+" << string(width, '=') << "+" << RESET << "\n";
    cout << CYAN << "|" << MAGENTA << BOLD 
         << "        Logic Gates Command Reference        " 
         << CYAN << "|" << RESET << "\n";
    cout << CYAN << "+" << string(width, '=') << "+" << RESET << "\n";
    
    // Commands section header
    cout << CYAN << "|" << YELLOW << BOLD << " Available Commands" 
         << string(26, ' ') << CYAN << "|" << RESET << "\n";
    cout << CYAN << "+" << string(width, '-') << "+" << RESET << "\n";
    
    // Basic Gates
    cout << CYAN << "| " << BLUE << BOLD << "OR" << WHITE << " [num_inputs]" 
         << string(3, ' ') << GREEN << "->" << string(1, ' ')
         << WHITE << "Display OR gate table  " << CYAN << "|" << RESET << "\n";
    
    cout << CYAN << "| " << BLUE << BOLD << "AND" << WHITE << " [num_inputs]" 
         << string(2, ' ') << GREEN << "->" << string(1, ' ')
         << WHITE << "Display AND gate table " << CYAN << "|" << RESET << "\n";
    
    cout << CYAN << "| " << BLUE << BOLD << "NOT" << string(15, ' ')
         << GREEN << "->" << string(1, ' ')
         << WHITE << "Display NOT gate table " << CYAN << "|" << RESET << "\n";

    // Complex Gates
    cout << CYAN << "| " << BLUE << BOLD << "NAND" << WHITE << " [num_inputs] "
         << GREEN << "->" << string(1, ' ')
         << WHITE << "Display NAND gate table" << CYAN << "|" << RESET << "\n";

    cout << CYAN << "| " << BLUE << BOLD << "NOR" << WHITE << " [num_inputs]"
         << string(2, ' ') << GREEN << "->" << string(1, ' ')
         << WHITE << "Display NOR gate table " << CYAN << "|" << RESET << "\n";

    cout << CYAN << "| " << BLUE << BOLD << "XOR" << WHITE << " [num_inputs]"
         << string(2, ' ') << GREEN << "->" << string(1, ' ')
         << WHITE << "Display XOR gate table " << CYAN << "|" << RESET << "\n";

    cout << CYAN << "| " << BLUE << BOLD << "XNOR" << WHITE << " [num_inputs] "
         << GREEN << "->" << string(1, ' ')
         << WHITE << "Display XNOR gate table" << CYAN << "|" << RESET << "\n";
    
    // Utility Commands
    cout << CYAN << "+" << string(width, '-') << "+" << RESET << "\n";
    cout << CYAN << "| " << YELLOW << BOLD << "Utility Commands" 
         << string(28, ' ') << CYAN << "|" << RESET << "\n";
    cout << CYAN << "+" << string(width, '-') << "+" << RESET << "\n";
    
    cout << CYAN << "| " << BLUE << BOLD << "HELP" << string(14, ' ')
         << GREEN << "->" << string(1, ' ')
         << WHITE << "Show this help message " << CYAN << "|" << RESET << "\n";
    
    cout << CYAN << "| " << BLUE << BOLD << "CLS" << string(15, ' ')
         << GREEN << "->" << string(1, ' ')
         << WHITE << "Clear terminal screen  " << CYAN << "|" << RESET << "\n";
    
    cout << CYAN << "| " << BLUE << BOLD << "EXIT" << string(14, ' ')
         << GREEN << "->" << string(1, ' ')
         << WHITE << "Exit the program       " << CYAN << "|" << RESET << "\n";
         
    // Note section
    cout << CYAN << "+" << string(width, '-') << "+" << RESET << "\n";
    cout << CYAN << "| " << YELLOW << BOLD << "Note" << RESET << WHITE 
         << ": [num_inputs] is optional (default: 2) " 
         << CYAN << "|" << RESET << "\n";
    cout << CYAN << "+" << string(width, '=') << "+" << RESET << "\n\n";
}

/**
 * @brief Displays the welcome screen with program information
 * Shows program title, developer info, features, and version information
 */
 void Welcome() {
    clearScreen();
    const int width = 60;  // Standard width for welcome screen

    // Program Title
    cout << "\n" << CYAN << "+" << string(width, '=') << "+" << RESET << "\n";
    cout << CYAN << "|" << MAGENTA << BOLD << string((width - 37) / 2, ' ') 
         << "Welcome to Logic Gates Table Generator" << string((width - 37) / 2, ' ') 
         << CYAN << "|" << RESET << "\n";
    cout << CYAN << "+" << string(width, '=') << "+" << RESET << "\n";
    
    // Developer Information
    cout << CYAN << "|" << string(width, ' ') << "|" << RESET << "\n";
    cout << CYAN << "|" << YELLOW << BOLD << string((width - 12) / 2, ' ') 
         << "Developed By" << string((width - 12) / 2, ' ') 
         << CYAN << "|" << RESET << "\n";
    cout << CYAN << "|" << string(width, ' ') << "|" << RESET << "\n";
    cout << CYAN << "|" << BLUE << BOLD << string((width - 13) / 2, ' ') 
         << "Upendra Shahi" << string((width - 13) / 2 + 1, ' ') 
         << CYAN << "|" << RESET << "\n";
    
    // Features Section
    cout << CYAN << "|" << string(width, ' ') << "|" << RESET << "\n";
    cout << CYAN << "+" << string(width, '-') << "+" << RESET << "\n";
    cout << CYAN << "|" << YELLOW << BOLD << string((width - 8) / 2, ' ') 
         << "Features" << string((width - 8) / 2, ' ') 
         << CYAN << "|" << RESET << "\n";
    cout << CYAN << "+" << string(width, '-') << "+" << RESET << "\n";
    
    // Available Gates
    cout << CYAN << "| " << YELLOW << BOLD << "Available Logic Gates:" << RESET 
         << string(width - 23, ' ') << CYAN << "|" << RESET << "\n";
    cout << CYAN << "| " << GREEN << "-> " << WHITE << "Basic Gates: " << BLUE << "AND" << WHITE << ", " 
         << BLUE << "OR" << WHITE << ", " << BLUE << "NOT" 
         << string(width - 29, ' ') << CYAN << "|" << RESET << "\n";
    cout << CYAN << "| " << GREEN << "-> " << WHITE << "Complex Gates: " << BLUE << "NAND" << WHITE << ", " 
         << BLUE << "NOR" << WHITE << ", " << BLUE << "XOR" << WHITE << ", " 
         << BLUE << "XNOR" << string(width - 39, ' ') << CYAN << "|" << RESET << "\n";
    
    // Program Features
    cout << CYAN << "| " << YELLOW << BOLD << "Program Features:" << RESET 
         << string(width - 18, ' ') << CYAN << "|" << RESET << "\n";
    cout << CYAN << "| " << GREEN << "-> " << RED << "Default: "<< WHITE << "Support for up to 16 inputs per gate" 
         << string(width - 49, ' ') << CYAN << "|" << RESET << "\n";
    cout << CYAN << "| " << GREEN << "-> " << WHITE << "Interactive command-line interface" 
         << string(width - 38, ' ') << CYAN << "|" << RESET << "\n";
    cout << CYAN << "| " << GREEN << "-> " << WHITE << "Colorful truth table visualization" 
         << string(width - 38, ' ') << CYAN << "|" << RESET << "\n";
    cout << CYAN << "| " << GREEN << "-> " << WHITE << "Real-time output generation" 
         << string(width - 31, ' ') << CYAN << "|" << RESET << "\n";
    
    // Version Information
    cout << CYAN << "+" << string(width, '-') << "+" << RESET << "\n";
    cout << CYAN << "| " << GREEN << BOLD << "Version 1.0 | First Release: 2025 February 16" 
         << string(width - 46, ' ') << CYAN << "|" << RESET << "\n";
    cout << CYAN << "+" << string(width, '=') << "+" << RESET << "\n\n";
    
    // User Instructions
    cout << WHITE << "Type " << BLUE << BOLD << "HELP" 
         << WHITE << " to see available commands" << RESET << "\n";
    cout << WHITE << "Press " << BLUE << BOLD << "ENTER" 
         << WHITE << " to continue..." << RESET;
    
    cin.get();
    clearScreen();
}

/**
 * @brief Main program function
 * @return int Exit status (0 for success)
 * 
 * Handles the main program loop, command processing, and user interaction
 */
int main() {
    enableColors();
    Welcome();

    string command;
    int numInputs = 2;  // Default number of inputs
    bool isRunning = true;

    while (isRunning) {
        // Display command prompt
        cout << CYAN << BOLD << "[logic]> " << WHITE;
        getline(cin, command);
        
        // Convert command to uppercase for case-insensitive comparison
        string upperCommand = command;
        transform(upperCommand.begin(), upperCommand.end(), upperCommand.begin(), ::toupper);

        // Process commands
        if (upperCommand == "HELP") {
            displayHelp();
        } 
        else if (upperCommand == "EXIT") {
            cout << "\n" << YELLOW << "Thank you for using Logic Gates Lab!" << RESET << "\n";
            cout << BLUE << "Developed by: " << WHITE << "Upendra Shahi" << RESET << "\n\n";
            isRunning = false;
        } 
        else if (upperCommand == "CLS") {
            clearScreen();
        } 
        else if (!upperCommand.empty()) {
            // Parse gate command and number of inputs
            size_t spacePos = upperCommand.find(' ');
            string gate = upperCommand.substr(0, spacePos);
            string numInputsStr = spacePos != string::npos ? upperCommand.substr(spacePos + 1) : "";

            // Handle different gate types
            if (gate == "NOT") {
                numInputs = 1;  // NOT gate always has 1 input
            } 
            else if (gate == "OR" || gate == "AND" || gate == "NAND" || 
                     gate == "NOR" || gate == "XOR" || gate == "XNOR") {
                // Process number of inputs
                if (numInputsStr.empty()) {
                    numInputs = 2;  // Default to 2 inputs
                } 
                else {
                    try {
                        numInputs = stoi(numInputsStr);
                        if (numInputs < 1 || numInputs > 16) {
                            cout << RED << "Error: Number of inputs must be between 1 and 16." 
                                 << RESET << "\n";
                            continue;
                        }
                    } 
                    catch (const invalid_argument& e) {
                        cout << RED << "Error: Invalid number of inputs. Using default (2)." 
                             << RESET << "\n";
                        numInputs = 2;
                    }
                }
            } 
            else {
                cout << RED << "Error: Invalid command. Type " << BLUE << "HELP" 
                     << RED << " for available commands." << RESET << "\n";
                continue;
            }

            // Generate and display truth table
            vector<vector<int>> combinations = generateCombinations(numInputs);
            vector<int> outputs(combinations.size());

            // Calculate outputs based on gate type
            for (size_t i = 0; i < combinations.size(); ++i) {
                if (gate == "OR") outputs[i] = orGate(combinations[i]);
                else if (gate == "AND") outputs[i] = andGate(combinations[i]);
                else if (gate == "NOT") outputs[i] = notGate(combinations[i][0]);
                else if (gate == "NAND") outputs[i] = nandGate(combinations[i]);
                else if (gate == "NOR") outputs[i] = norGate(combinations[i]);
                else if (gate == "XOR") outputs[i] = xorGate(combinations[i]);
                else if (gate == "XNOR") outputs[i] = xnorGate(combinations[i]);
            }

            displayTable(combinations, outputs, gate, numInputs);
        }
    }

    return 0;
}
