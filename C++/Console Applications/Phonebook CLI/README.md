# Phonebook CLI

A simple command-line interface (CLI) application written in C++ to manage contacts. Contacts are stored directly within the source file (`phonebook.cpp`) as comments, making it a self-contained solution.

## Features

- **Add Contacts**: Add a new contact with name, phone number, and/or email in any order. Use `-` for optional fields.
- **Delete Contacts**: Remove a contact by name, phone, or email.
- **Search Contacts**: Search across all fields (name, phone, email).
- **List Contacts**: Display all contacts in a beautifully formatted table.
- **Sort Contacts**: Sort contacts alphabetically by name.
- **Home Page**: View the welcome screen with features.
- **Clear Screen**: Clear the console display.
- **Persistent Storage**: All contacts are saved within the `.cpp` file itself.

## Requirements

- C++ compiler (e.g., g++ with MinGW on Windows or GCC on Linux/macOS)
- Standard C++ libraries (included in the code)

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Upendra237/Programming-Languages.git
   cd phonebook-cli
   ```

2. Compile the code:
   - On Windows (using MinGW):
     ```bash
     g++ phonebook.cpp -o phonebook
     ```
   - On Linux/macOS:
     ```bash
     g++ phonebook.cpp -o phonebook
     ```

3. Run the program:
   - On Windows:
     ```bash
     phonebook
     ```
   - On Linux/macOS:
     ```bash
     ./phonebook
     ```

## Usage

Run the program and use the following commands at the `Phonebook>` prompt:

- `add <name> <phone> <email>`: Add a contact (e.g., `add "Siddhartha Manandhar" 1234567890 sid@example.com`). Use quotes for names with spaces.
- `delete <query>`: Delete by name, phone, or email (e.g., `delete Raz`).
- `search <query>`: Search for a term (e.g., `search 123`).
- `list`: Display all contacts.
- `sort`: Sort contacts alphabetically.
- `home`: Show the home page.
- `cls`: Clear the screen.
- `help`: Display the help menu.
- `exit`: Quit the program.

### Examples
```
Phonebook> add Ram123
Contact added!
Phonebook> add - 9876543210 -
Contact added!
Phonebook> add - - ram@example.com
Contact added!
Phonebook> list
+=====================================================================================================+
|                                    *** PHONEBOOK CONTACTS ***                                       |
+==================================+======================+===========================================+
|               NAME               |         PHONE         |                   EMAIL                  |
+----------------------------------+-----------------------+------------------------------------------+
| Ram123                           | 0000000000            | unknown@none.com                         |
| Unknown                          | 9876543210            | unknown@none.com                         |
| Unknown                          | 0000000000            | ram@example.com                          |
+-----------------------------------+-----------------------+-----------------------------------------+
# TOTAL CONTACTS:                  3
```

## Notes

- Contacts are stored at the end of `phonebook.cpp` in the format `// name:phone:email`.
- The program supports flexible input: add a name, phone, email, or any combination.
- Phone numbers must be 8-15 digits; names can include letters, digits, spaces, hyphens, and apostrophes (1-50 characters).
- Duplicate names (excluding "Unknown") are not allowed.

## Contributing

Feel free to submit issues or pull requests on GitHub. Contributions are welcome!

## License

This project is open-source and available under the MIT License.

## Author

Developed by @Upendra237
