/*

LAB1: Program to find prefixes, suffixes and substrings from a given string (Using C, C++ or 
else)

*/

#include <iostream>
#include <cstring>
#include <set>
using namespace std;

void printPrefixes(const char* str, int l) {
    cout << "Prefixes: ε ";  // Printing epsilon (empty string)
    char prefix[100];
    for (int i = 0; i < l; i++) {
        for (int j = 0; j <= i; j++) {
            prefix[j] = str[j];
        }
        prefix[i + 1] = '\0';
        cout << prefix << " ";
    }
    cout << endl;
}

void printSuffixes(const char* str, int l) {
    cout << "Suffixes: ε ";  // Printing epsilon (empty string)
    char suffix[100];
    for (int k = 0; k < l; k++) {
        for (int m = k; m < l; m++) {suffix[m - k] = str[m];
        }
        suffix[l - k] = '\0';
        cout << suffix << " ";
    }
    cout << endl;
}

void printSubstrings(const char* str, int l) {
    cout << "Substrings: ε ";  // Printing epsilon (empty string)
    set<string> unique_substrings; // Use a set to keep track of unique substrings
    for (int n = 0; n < l; n++) {
        for (int o = n; o < l; o++) {
            string sub = string(str).substr(n, o - n + 1); // (start, length) of substring
            if (unique_substrings.find(sub) == unique_substrings.end()) {
                unique_substrings.insert(sub);
                cout << sub << " ";
            }
        }
    }
    cout << endl;
}

int main() {char str[100];
    int choice;
    
    cout << "Enter a string: ";
    cin >> str;
    int l = strlen(str);

    cout << "Choose an option:" << endl;
    cout << "1. Print Prefixes" << endl;
    cout << "2. Print Suffixes" << endl;
    cout << "3. Print Substrings" << endl;
    cout << "4. Print all" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            printPrefixes(str, l);
            break;
        case 2:
            printSuffixes(str, l);
            break;
        case 3:
            printSubstrings(str, l);
            break;case 4:
            printPrefixes(str, l);
            printSuffixes(str, l);
            printSubstrings(str, l);
            break;
        default:
            cout << "Invalid choice" << endl;
    }

    return 0;
}