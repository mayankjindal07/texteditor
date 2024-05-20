#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

// Function to save the document to a file
void saveDocument(const string& filename, const string& document) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to save document." << endl;
        return;
    }
    file << document;
    file.close();
    cout << "Document saved successfully." << endl;
}

// Function to insert text at a specified position in the document
void insertText(string& document, int position, const string& text) {
    if (position < 0 || position > document.size()) {
        cout << "Error: Invalid position." << endl;
        return;
    }
    document.insert(position, text);
}

// Function to delete text from the document at a specified position and length
void deleteText(string& document, int position, int length) {
    if (position < 0 || position + length > document.size()) {
        cout << "Error: Invalid position or length." << endl;
        return;
    }
    document.erase(position, length);
}

// Function to search for text within the document
int searchText(const string& document, const string& query) {
    size_t found = document.find(query);
    return (found != string::npos) ? found : -1;
}

int main() {
    string document;
    string filename;

    cout << "Welcome to Text Editor!" << endl;
    cout << "Enter filename to open or create a new document: ";
    cin >> filename;

    ifstream file(filename);
    if (file.is_open()) {
        // Load existing document
        string line;
        while (getline(file, line)) {
            document += line + "\n";
        }
        file.close();
        cout << "Document loaded successfully." << endl;
    } else {
        cout << "New document created." << endl;
    }

    int choice;
    do {
        cout << "\n1. Insert Text\n2. Delete Text\n3. Search Text\n4. Save Document\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle invalid input for choice
        if (cin.fail()) {
            cin.clear(); // Clear the fail state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore remaining characters in the input buffer
            cout << "Invalid input. Please enter a number between 1 and 5." << endl;
            continue; // Skip the rest of the loop and prompt the user again
        }

        switch (choice) {
            case 1: {
                int position;
                string text;
                cout << "Enter position to insert text (starting from 0): ";
                cin >> position;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the newline character in the buffer
                cout << "Enter text to insert: ";
                getline(cin, text);
                insertText(document, position, text);
                break;
            }
            case 2: {
                int position, length;
                cout << "Enter position to delete text (starting from 0): ";
                cin >> position;
                cout << "Enter length of text to delete: ";
                cin >> length;
                deleteText(document, position, length);
                break;
            }
            case 3: {
                string query;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the newline character in the buffer
                cout << "Enter text to search: ";
                getline(cin, query);
                int foundPos = searchText(document, query);
                if (foundPos != -1) {
                    cout << "Text found at position " << foundPos << endl;
                } else {
                    cout << "Text not found." << endl;
                }
                break;
            }
            case 4:
                saveDocument(filename, document);
                break;
            case 5:
                cout << "Exiting Text Editor. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
