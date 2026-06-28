/*
 * GroceryTracker.cpp
 * CS 210 Project Three - Corner Grocer Item-Tracking Program
 *
 * Author:  David Williams
 * Course:  CS 210
 *
 * Purpose: Reads a day's worth of grocery purchase records from a text
 *          file, tallies how often each item was purchased, and lets the
 *          user query that data through a menu (single-item lookup, full
 *          frequency list, and a text histogram). A backup data file
 *          (frequency.dat) is written automatically at program start.
 */

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <limits>

using namespace std;

// ---------------------------------------------------------------------------
// ItemTracker
//
// Owns the item->frequency data and all operations on it. The purchase counts
// are stored in a std::map, which keeps keys sorted alphabetically and gives
// O(log n) lookups. Keeping the data and the operations together in one class
// is what lets main() stay short and readable.
// ---------------------------------------------------------------------------
class ItemTracker {
private:
    // Maps each item name to the number of times it was purchased.
    // std::map keeps the items in sorted (alphabetical) order automatically.
    map<string, int> itemFrequencies;

public:
    // Constructor: loads and tallies the purchase records from inputFileName.
    ItemTracker(const string& inputFileName);

    // Menu Option 1: returns how many times a single item was purchased.
    // Returns 0 if the item never appears in the records.
    int GetFrequencyOf(const string& item) const;

    // Menu Option 2: prints every item with its purchase count.
    void PrintAllFrequencies() const;

    // Menu Option 3: prints every item as a histogram of asterisks.
    void PrintHistogram() const;

    // Writes a backup of all item/count pairs to outputFileName.
    void BackupToFile(const string& outputFileName) const;
};

// ---------------------------------------------------------------------------
// Constructor
//
// Opens the input file and reads it one word at a time. Each word is a single
// item purchase, so every time an item is read its count is incremented. The
// map's operator[] creates the key with a value of 0 on first access, then the
// ++ bumps it to 1 -- so brand-new items and repeat items are handled by the
// same single line.
// ---------------------------------------------------------------------------
ItemTracker::ItemTracker(const string& inputFileName) {
    ifstream inputFile(inputFileName);

    // Guard against a missing or unreadable file so the program fails clearly
    // instead of silently running with no data.
    if (!inputFile.is_open()) {
        cout << "Error: could not open input file \"" << inputFileName << "\"."
            << endl;
        return;
    }

    string item;
    while (inputFile >> item) {   // reads whitespace-separated words
        itemFrequencies[item]++;  // create-if-new, then increment
    }

    inputFile.close();
}

// ---------------------------------------------------------------------------
// GetFrequencyOf
//
// Looks the item up without modifying the map. operator[] is avoided here on
// purpose: on a const map it isn't allowed, and on a normal map it would
// INSERT the missing key with a count of 0. find() just reports whether the
// key exists and leaves the map untouched.
// ---------------------------------------------------------------------------
int ItemTracker::GetFrequencyOf(const string& item) const {
    auto it = itemFrequencies.find(item);
    if (it != itemFrequencies.end()) {
        return it->second;  // found: return the stored count
    }
    return 0;               // not found: it was purchased zero times
}

// ---------------------------------------------------------------------------
// PrintAllFrequencies (Menu Option 2)
//
// Walks the whole map and prints each item next to its count. Because the map
// is sorted, the output comes out alphabetically without any extra work.
// ---------------------------------------------------------------------------
void ItemTracker::PrintAllFrequencies() const {
    for (const auto& pair : itemFrequencies) {
        cout << pair.first << " " << pair.second << endl;
    }
}

// ---------------------------------------------------------------------------
// PrintHistogram (Menu Option 3)
//
// Same walk as above, but instead of printing the number it prints that many
// asterisks, giving a quick visual sense of which items sell most.
// ---------------------------------------------------------------------------
void ItemTracker::PrintHistogram() const {
    for (const auto& pair : itemFrequencies) {
        cout << pair.first << " ";
        for (int i = 0; i < pair.second; i++) {
            cout << "*";
        }
        cout << endl;
    }
}

// ---------------------------------------------------------------------------
// BackupToFile
//
// Writes every item/count pair to a backup file in the same simple
// "Item Count" format. Called once at startup so a saved copy of the day's
// tally always exists independent of the input file.
// ---------------------------------------------------------------------------
void ItemTracker::BackupToFile(const string& outputFileName) const {
    ofstream outputFile(outputFileName);

    if (!outputFile.is_open()) {
        cout << "Error: could not create backup file \"" << outputFileName
            << "\"." << endl;
        return;
    }

    for (const auto& pair : itemFrequencies) {
        outputFile << pair.first << " " << pair.second << endl;
    }

    outputFile.close();
}

// ---------------------------------------------------------------------------
// Menu helpers
// ---------------------------------------------------------------------------

// Prints the menu of choices to the screen.
void PrintMenu() {
    cout << "\n========= Corner Grocer Item Tracker =========" << endl;
    cout << "1. Look up the frequency of a specific item" << endl;
    cout << "2. Print the frequency of all items" << endl;
    cout << "3. Print a histogram of all item frequencies" << endl;
    cout << "4. Exit" << endl;
    cout << "==============================================" << endl;
    cout << "Enter your choice (1-4): ";
}

// Reads a valid menu choice from the user. Re-prompts on any non-numeric or
// out-of-range input so a bad keystroke can't crash or skip past the menu.
int GetMenuChoice() {
    int choice;
    while (true) {
        if (cin >> choice && choice >= 1 && choice <= 4) {
            return choice;
        }

        // Recover from bad input: clear the error flag and discard the rest
        // of the line so the next read starts clean.
        cout << "Invalid choice. Please enter a number from 1 to 4: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// ---------------------------------------------------------------------------
// main
// ---------------------------------------------------------------------------
int main() {
    const string INPUT_FILE = "CS210_Project_Three_Input_File.txt";
    const string BACKUP_FILE = "frequency.dat";

    // Build the tracker (this reads and tallies the input file) and write the
    // backup file immediately, before any user interaction.
    ItemTracker tracker(INPUT_FILE);
    tracker.BackupToFile(BACKUP_FILE);

    int choice = 0;
    do {
        PrintMenu();
        choice = GetMenuChoice();

        switch (choice) {
        case 1: {
            cout << "Enter the item to look up: ";
            string item;
            cin >> item;
            cout << item << " was purchased "
                << tracker.GetFrequencyOf(item) << " time(s)." << endl;
            break;
        }
        case 2:
            cout << "\nItem Purchase Frequencies:" << endl;
            tracker.PrintAllFrequencies();
            break;
        case 3:
            cout << "\nItem Purchase Histogram:" << endl;
            tracker.PrintHistogram();
            break;
        case 4:
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        }
    } while (choice != 4);

    return 0;
}