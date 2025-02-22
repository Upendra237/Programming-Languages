#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <regex>

// Platform-specific definitions for screen clearing
#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
    #include <windows.h>
#else
    #define CLEAR_COMMAND "clear"
#endif

using namespace std;

// Color codes for console (cross-platform)
#ifdef _WIN32
    enum Color { BLACK = 0, BLUE = 1, GREEN = 2, CYAN = 3, RED = 4, MAGENTA = 5, YELLOW = 6, WHITE = 7, DARK_YELLOW = 14, LIGHT_GRAY = 8, LIGHT_CYAN = 11 };
    void setColor(int color) { // Set console text color on Windows
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }
#else
    void setColor(const string& color) { cout << color; } // Set ANSI color codes on Unix-like systems
    const string RESET = "\033[0m";
    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string YELLOW = "\033[33m";
    const string BLUE = "\033[34m";
    const string MAGENTA = "\033[35m";
    const string CYAN = "\033[36m";
    const string WHITE = "\033[37m";
    const string DARK_YELLOW = "\033[33m";
    const string LIGHT_GRAY = "\033[90m";
    const string LIGHT_CYAN = "\033[96m";
#endif

// Class to represent a contact
class Contact {
private:
    string name;   // Contact name
    string phone;  // Contact phone number
    string email;  // Contact email address

public:
    Contact(const string& n = "Unknown", const string& p = "0000000000", const string& e = "unknown@none.com") 
        : name(n), phone(p), email(e) {} // Constructor with default values
    
    // Getter methods
    string getName() const { return name; }
    string getPhone() const { return phone; }
    string getEmail() const { return email; }
    
    // Setter methods with default value handling
    void setName(const string& n) { name = (n == "-" ? "Unknown" : n); }
    void setPhone(const string& p) { phone = (p == "-" ? "0000000000" : p); }
    void setEmail(const string& e) { email = (e == "-" ? "unknown@none.com" : e); }
    
    string toString() const { return name + ":" + phone + ":" + email; } // Format contact as string for file storage
};

// Validation functions
bool isValidPhone(const string& input) {
    static const regex phoneRegex(R"(^\d{8,15}$)"); // Regex for 8-15 digits
    string digits = input == "-" ? "0000000000" : input;
    return all_of(digits.begin(), digits.end(), [](char c) { return isdigit(c); }) && regex_match(digits, phoneRegex);
}

bool isValidEmail(const string& input) {
    static const regex emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return input == "-" || regex_match(input, emailRegex); // Allow "-" or valid email format
}

bool isValidName(const string& input) {
    if (input == "-" || input.empty()) return true; // Allow "-" or empty for default
    if (input.length() < 1 || input.length() > 50) return false; // Length check
    return all_of(input.begin(), input.end(), [](char c) { return isalpha(c) || isdigit(c) || c == ' ' || c == '-' || c == '\''; });
}

// Field detection
bool isPhone(const string& input) { return isValidPhone(input); }
bool isEmail(const string& input) { return isValidEmail(input) && input.find('@') != string::npos; }
bool isName(const string& input) { return isValidName(input) && !isPhone(input) && !isEmail(input); }

// Load contacts from the last DATA_SECTION in the file
vector<Contact> loadContacts() {
    vector<Contact> contacts;
    ifstream file(__FILE__);
    if (!file.is_open()) return contacts; // Return empty vector if file can't be opened

    vector<string> lines;
    string line;
    while (getline(file, line)) lines.emplace_back(move(line)); // Efficiently read lines
    file.close();

    for (int i = lines.size() - 1; i >= 0; --i) {
        if (lines[i].find("// DATA_SECTION") != string::npos) {
            for (int j = i + 1; j < lines.size(); ++j) {
                if (lines[j].find("// ") == 0) {
                    string entry = lines[j].substr(3);
                    size_t pos1 = entry.find(':');
                    size_t pos2 = entry.find(':', pos1 + 1);
                    if (pos1 != string::npos && pos2 != string::npos) {
                        contacts.emplace_back(entry.substr(0, pos1),
                                              entry.substr(pos1 + 1, pos2 - pos1 - 1),
                                              entry.substr(pos2 + 1));
                    }
                }
            }
            break;
        }
    }
    return contacts;
}

// Save contacts back to the file
void saveContacts(vector<Contact>& contacts) {
    ifstream inFile(__FILE__);
    stringstream buffer;
    vector<string> lines;
    string line;

    while (getline(inFile, line)) lines.emplace_back(move(line));
    inFile.close();

    int lastDataSection = -1;
    for (int i = lines.size() - 1; i >= 0; --i) {
        if (lines[i].find("// DATA_SECTION") != string::npos) {
            lastDataSection = i;
            break;
        }
    }

    if (lastDataSection == -1) {
        for (const auto& l : lines) buffer << l << '\n';
        buffer << "// DATA_SECTION\n";
    } else {
        for (int i = 0; i <= lastDataSection; ++i) buffer << lines[i] << '\n';
    }

    buffer << "// Add your contacts below this line as comments in format: // name:phone:email\n";
    for (const auto& contact : contacts) buffer << "// " << contact.toString() << '\n';

    ofstream outFile(__FILE__);
    outFile << buffer.str(); // Overwrite file with updated content
}

// Display contacts in a formatted table
void displayContacts(const vector<Contact>& contacts) {
    if (contacts.empty()) {
        setColor(LIGHT_GRAY); cout << "\n  *** Phonebook is empty! ***\n"; setColor(WHITE);
        return;
    }
    setColor(BLUE); // Darker blue for borders
    cout << "\n=======================================================================================================+\n";
    setColor(CYAN); // Darker cyan for title
    cout << "|                                    *** PHONEBOOK CONTACTS ***                                        |\n";
    setColor(BLUE);
    cout << "+===================================+=======================+==========================================+\n";
    cout << "|               NAME                |         PHONE         |                   EMAIL                  |\n";
    cout << "+===================================+=======================+==========================================+\n";
    for (const auto& contact : contacts) {
        setColor(WHITE); 
        cout << "| ";
        setColor(LIGHT_CYAN); // Soft cyan for names
        cout << left << setw(33) << contact.getName().substr(0, 33) << " ";
        setColor(WHITE);
        cout << "| ";
        setColor(LIGHT_GRAY); // Soft gray for phone numbers
        cout << setw(21) << contact.getPhone().substr(0, 21) << " ";
        setColor(WHITE);
        cout << "| ";
        setColor(DARK_YELLOW); // Soft dark yellow for emails
        cout << setw(40) << contact.getEmail().substr(0, 40) << " ";
        setColor(WHITE);
        cout << "|\n";
        setColor(BLUE);
        cout << "+-----------------------------------+-----------------------+------------------------------------------+\n";
    }
    setColor(CYAN);
    cout << "# TOTAL CONTACTS: ";
    setColor(YELLOW); // Slightly brighter yellow for total count
    cout << setw(17) << contacts.size() << "\n";
    setColor(WHITE);
}

// Search contacts by name, phone, or email
void searchContacts(const vector<Contact>& contacts, const string& query) {
    bool found = false;
    for (const auto& contact : contacts) {
        if (contact.getName().find(query) != string::npos || 
            contact.getPhone().find(query) != string::npos ||
            contact.getEmail().find(query) != string::npos) {
            setColor(GREEN); 
            cout << contact.getName() << " - " << contact.getPhone() << " - " << contact.getEmail() << '\n';
            setColor(WHITE);
            found = true;
        }
    }
    if (!found) {
        setColor(YELLOW); cout << "No matching contacts found!\n"; setColor(WHITE);
    }
}

// Delete a contact by name, phone, or email
void deleteContact(vector<Contact>& contacts, const string& query) {
    vector<Contact> newContacts;
    bool found = false;
    for (const auto& contact : contacts) {
        if (contact.getName() != query && contact.getPhone() != query && contact.getEmail() != query) {
            newContacts.push_back(contact);
        } else found = true;
    }
    if (found) {
        contacts = move(newContacts);
        saveContacts(contacts);
        setColor(GREEN); cout << "Contact deleted permanently!\n"; setColor(WHITE);
    } else {
        setColor(YELLOW); cout << "Contact not found!\n"; setColor(WHITE);
    }
}

// Check for duplicate names, allowing multiple "Unknown" or "-"
bool hasDuplicateName(const vector<Contact>& contacts, const string& name) {
    return name != "Unknown" && name != "-" && any_of(contacts.begin(), contacts.end(), 
        [&name](const Contact& c) { return c.getName() == name; });
}

// Add a contact with flexible parameters
void addContact(vector<Contact>& contacts, const vector<string>& params) {
    if (params.empty()) {
        setColor(RED); cout << "Please provide at least one parameter!\n"; setColor(WHITE);
        return;
    }

    string name = "-", phone = "-", email = "-";
    bool nameSet = false;

    for (const auto& param : params) {
        if (isPhone(param) && phone == "-") phone = param;
        else if (isEmail(param) && email == "-") email = param;
        else if (isName(param) && !nameSet) {
            name = param;
            nameSet = true;
        }
    }

    if (!isValidName(name)) {
        setColor(RED); cout << "Invalid name! Must be 1-50 characters (letters, digits, spaces, -, ' only).\n"; setColor(WHITE);
        return;
    }
    if (hasDuplicateName(contacts, name)) {
        setColor(YELLOW); cout << "Record with name '" << name << "' already exists!\n"; setColor(WHITE);
        return;
    }
    if (!isValidPhone(phone)) {
        setColor(RED); cout << "Invalid phone number! Must be 8-15 digits.\n"; setColor(WHITE);
        return;
    }
    if (!isValidEmail(email)) {
        setColor(RED); cout << "Invalid email format!\n"; setColor(WHITE);
        return;
    }

    contacts.emplace_back(name, phone, email);
    saveContacts(contacts);
    setColor(GREEN); cout << "Contact added!\n"; setColor(WHITE);
}

// Sort contacts alphabetically by name
void sortContacts(vector<Contact>& contacts) {
    sort(contacts.begin(), contacts.end(), 
         [](const Contact& a, const Contact& b) { return a.getName() < b.getName(); });
    saveContacts(contacts);
    setColor(GREEN); cout << "Contacts sorted alphabetically!\n"; setColor(WHITE);
}

// Display home page
void displayHome() {
    system(CLEAR_COMMAND);
    setColor(LIGHT_CYAN); 
    cout << "+------------------------------------------+\n";
    cout << "|       Welcome to Phonebook CLI           |\n";
    cout << "|     Developed by: @Upendra237            |\n";
    cout << "|   First Release: February 20, 2025       |\n";
    cout << "+------------------------------------------+\n"; 
    setColor(WHITE);
    cout << "\nFeatures:\n";
    setColor(DARK_YELLOW);
    cout << "  * Add contacts with name, phone, email (auto-detected)\n";
    cout << "  * Delete by name, phone, or email\n";
    cout << "  * Search across all fields\n";
    cout << "  * Beautiful table display\n";
    cout << "  * Sort alphabetically\n";
    cout << "  * Use '-' for optional fields\n";
    cout << "  * All contacts saved within the .cpp file\n";
    setColor(LIGHT_GRAY);
    cout << "\nType 'help' for commands\n";
    setColor(WHITE);
}

// Display help menu
void displayHelp() {
    setColor(LIGHT_CYAN);
    cout << "\n+------------------+------------------------------------------+\n";
    cout << "| Command          | Description                              |\n";
    cout << "+------------------+------------------------------------------+\n";
    setColor(WHITE);
    cout << "| 1. add           | Add a new contact (any order)            |\n";
    cout << "| 2. delete        | Delete by name, phone, or email          |\n";
    cout << "| 3. search        | Search across all fields                 |\n";
    cout << "| 4. list          | Show all contacts                        |\n";
    cout << "| 5. sort          | Sort alphabetically                      |\n";
    cout << "| 6. home          | Show home page                           |\n";
    cout << "| 7. cls           | Clear screen                             |\n";
    cout << "| 8. exit          | Quit program                             |\n";
    setColor(LIGHT_CYAN);
    cout << "+------------------+------------------------------------------+\n";
    setColor(LIGHT_GRAY);
    cout << "Note: Use '-' for optional fields (e.g., add Ram - ram@example.com)\n";
    setColor(WHITE);
}

// Parse input allowing flexible order and spaces in name
vector<string> parseInput(const string& input, string& command) {
    vector<string> params;
    stringstream ss(input);
    ss >> command;
    string param;
    while (getline(ss >> ws, param, ' ')) {
        if (!param.empty()) {
            if (param.front() == '"' && param.back() != '"') {
                string rest;
                getline(ss, rest, '"');
                param = param.substr(1) + " " + rest;
            } else if (param.front() == '"' && param.back() == '"') {
                param = param.substr(1, param.length() - 2);
            }
            params.push_back(param);
        }
    }
    return params;
}

// Main function to run the phonebook CLI
int main() {
    vector<Contact> contacts = loadContacts();
    string input, command;

    displayHome();

    while (true) {
        setColor(MAGENTA); cout << "Phonebook> "; setColor(WHITE);
        getline(cin, input);
        
        vector<string> params = parseInput(input, command);
        transform(command.begin(), command.end(), command.begin(), ::tolower);

        if (command == "add" && !params.empty()) addContact(contacts, params);
        else if (command == "delete" && !params.empty()) deleteContact(contacts, params[0]);
        else if (command == "cls") system(CLEAR_COMMAND);
        else if (command == "search" && !params.empty()) searchContacts(contacts, params[0]);
        else if (command == "list") displayContacts(contacts);
        else if (command == "sort") sortContacts(contacts);
        else if (command == "home") displayHome();
        else if (command == "help") displayHelp();
        else if (command == "exit") { setColor(GREEN); cout << "Goodbye!\n"; setColor(WHITE); break; }
        else { setColor(RED); cout << "Invalid command! Type 'help' for available commands.\n"; setColor(WHITE); }
    }
    return 0;
}

// DATA_SECTION
// Add your contacts below this line as comments in format: // name:phone:email