# Logic Gates Table Generator

A command-line tool for generating and visualizing truth tables for various logic gates. This program provides an interactive interface to work with different types of logic gates and visualize their behavior through colorful truth tables.
```
+============================================================+
|           Welcome to Logic Gates Table Generator           |
+============================================================+
|                                                            |
|                        Developed By                        |
|                                                            |
|                       Upendra Shahi                        |
|                                                            |
+------------------------------------------------------------+
|                          Features                          |
+------------------------------------------------------------+
| Available Logic Gates:                                     |
| -> Basic Gates: AND, OR, NOT                               |
| -> Complex Gates: NAND, NOR, XOR, XNOR                     |
| Program Features:                                          |
| -> Default: Support for up to 16 inputs per gate           |
| -> Interactive command-line interface                      |
| -> Colorful truth table visualization                      |
| -> Real-time output generation                             |
+------------------------------------------------------------+
| Version 1.0 | First Release: 2025 February 16              |
+============================================================+

Type HELP to see available commands
Press ENTER to continue...
```

## Features

### Supported Logic Gates
- **Basic Gates**
  - AND Gate
  - OR Gate
  - NOT Gate
- **Complex Gates**
  - NAND Gate
  - NOR Gate
  - XOR Gate
  - XNOR Gate

### Program Capabilities
- Default: Supports up to 16 inputs per gate, with the option to add more.
- Interactive command-line interface
- Colorful truth table visualization
- Real-time output generation
- Cross-platform compatibility (Windows/Linux/macOS)

## Installation

### Prerequisites
- C++ compiler (GCC, Clang, or MSVC)
- Support for ANSI color codes in terminal

### Building the Program
1. Clone the repository:
   ```bash
   [git clone https://github.com/Upendra237/logic-gates-table-generator.git](https://github.com/Upendra237/Programming-Languages.git)
   cd Programming-Languages/Logic-Gates-Table-Generator
   ```

2. Compile the program:
   ```bash
   g++ -std=c++11 logic_gates_table_generator.cpp -o logic_gates
   ```
    OR
    ```bash
    g++ logic_gates_table_generator.cpp -o logic_gates
    ```

3. Run the program:
   ```bash
   ./logic_gates
   ```

## Usage

### Available Commands
- `OR [num_inputs]` - Display OR gate truth table
- `AND [num_inputs]` - Display AND gate truth table
- `NOT` - Display NOT gate truth table
- `NAND [num_inputs]` - Display NAND gate truth table
- `NOR [num_inputs]` - Display NOR gate truth table
- `XOR [num_inputs]` - Display XOR gate truth table
- `XNOR [num_inputs]` - Display XNOR gate truth table
- `HELP` - Show help message
- `CLS` - Clear screen
- `EXIT` - Exit program

```
[logic]> HELP

+=============================================+
|        Logic Gates Command Reference        |
+=============================================+
| Available Commands                          |
+---------------------------------------------+
| OR [num_inputs]   -> Display OR gate table  |
| AND [num_inputs]  -> Display AND gate table |
| NOT               -> Display NOT gate table |
| NAND [num_inputs] -> Display NAND gate table|
| NOR [num_inputs]  -> Display NOR gate table |
| XOR [num_inputs]  -> Display XOR gate table |
| XNOR [num_inputs] -> Display XNOR gate table|
+---------------------------------------------+
| Utility Commands                            |
+---------------------------------------------+
| HELP              -> Show this help message |
| CLS               -> Clear terminal screen  |
| EXIT              -> Exit the program       |
+---------------------------------------------+
| Note: [num_inputs] is optional (default: 2) |
+=============================================+
```
### Examples

1. Generate a 2-input AND gate truth table:
   ```
   [logic]> AND
   ```

2. Generate a 3-input OR gate truth table:
   ```
   [logic]> OR 3
   ```

3. Generate a NOT gate truth table:
   ```
   [logic]> NOT
   ```

### Sample Output
```
[logic]> OR 4

+==============================================+
|        OR Gate Truth Table (4 inputs)        |
+==============================================+
+==============================================+
|               INPUTS              ||  OUTPUT |
+========+========+========+========++=========+
|   A0   |   A1   |   A2   |   A3   ||   OUT   |
+========+========+========+========++=========+
|   0    |   0    |   0    |   0    ||    0    |
+--------+--------+--------+--------++---------+
|   0    |   0    |   0    |   1    ||    1    |
+--------+--------+--------+--------++---------+
|   0    |   0    |   1    |   0    ||    1    |
+--------+--------+--------+--------++---------+
|   0    |   0    |   1    |   1    ||    1    |
+--------+--------+--------+--------++---------+
|   0    |   1    |   0    |   0    ||    1    |
+--------+--------+--------+--------++---------+
|   0    |   1    |   0    |   1    ||    1    |
+--------+--------+--------+--------++---------+
|   0    |   1    |   1    |   0    ||    1    |
+--------+--------+--------+--------++---------+
|   0    |   1    |   1    |   1    ||    1    |
+--------+--------+--------+--------++---------+
|   1    |   0    |   0    |   0    ||    1    |
+--------+--------+--------+--------++---------+
|   1    |   0    |   0    |   1    ||    1    |
+--------+--------+--------+--------++---------+
|   1    |   0    |   1    |   0    ||    1    |
+--------+--------+--------+--------++---------+
|   1    |   0    |   1    |   1    ||    1    |
+--------+--------+--------+--------++---------+
|   1    |   1    |   0    |   0    ||    1    |
+--------+--------+--------+--------++---------+
|   1    |   1    |   0    |   1    ||    1    |
+--------+--------+--------+--------++---------+
|   1    |   1    |   1    |   0    ||    1    |
+--------+--------+--------+--------++---------+
|   1    |   1    |   1    |   1    ||    1    |
+========+========+========+========++=========+
```

## Features in Detail

### 1. Multiple Input Support
- Each gate (except NOT) supports 1 to 16 inputs
- Default number of inputs is 2 if not specified
- NOT gate always uses 1 input

### 2. Color Coding
- Green: Logic 1 (TRUE)
- Red: Logic 0 (FALSE)
- Cyan: Table borders
- Yellow: Headers
- Blue: Input labels
- White: Regular text

### 3. Error Handling
- Invalid input detection
- Input range validation
- Command validation
- Graceful error recovery

## Technical Details

### Implementation
- Written in C++
- Uses ANSI color codes for formatting
- Implements bitwise operations for efficiency
- Cross-platform compatible design

### Code Structure
- Modular function design
- Clear separation of concerns
- Well-documented code
- Consistent error handling

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request. For major changes, please open an issue first to discuss what you would like to change.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Author

**Upendra Shahi**
- Initial Release: February 16, 2025
- Version: 1.0

## Acknowledgments

- Thanks to all contributors and users
- Special thanks to the C++ community for inspiration and support

## Contact

If you have any questions or suggestions, please feel free to reach out:
- GitHub: [[Your GitHub Profile](https://github.com/Upendra237/)]
