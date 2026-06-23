#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <string>
using namespace std;

class GroceryTracker {
public:
    GroceryTracker(const string& inputFileName, const string& backupFileName) {
        this->inputFileName = inputFileName;
        this->backupFileName = backupFileName;
    }

    void LoadData() {
        ifstream inputFile;
        string itemName;

        inputFile.open(inputFileName);

        if (!inputFile.is_open()) {
            cout << "Error: Could not open input file." << endl;
            return;
        }

        while (inputFile >> itemName) {
            itemFrequency[itemName]++;
        }

        inputFile.close();
    }

    void CreateBackupFile() const {
        ofstream outputFile;

        outputFile.open(backupFileName);

        if (!outputFile.is_open()) {
            cout << "Error: Could not create backup file." << endl;
            return;
        }

        for (const auto& item : itemFrequency) {
            outputFile << item.first << " " << item.second << endl;
        }

        outputFile.close();
    }

    int GetItemFrequency(const string& itemName) const {
        auto item = itemFrequency.find(itemName);

        if (item != itemFrequency.end()) {
            return item->second;
        }

        return 0;
    }

    void PrintAllFrequencies() const {
        for (const auto& item : itemFrequency) {
            cout << item.first << " " << item.second << endl;
        }
    }

    void PrintHistogram() const {
        for (const auto& item : itemFrequency) {
            cout << left << setw(15) << item.first << " ";
            for (int i = 0; i < item.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }

private:
    string inputFileName;
    string backupFileName;
    map<string, int> itemFrequency;
};

void PrintMenu() {
    cout << endl;
    cout << "Corner Grocer Menu" << endl;
    cout << "1. Search for an item frequency" << endl;
    cout << "2. Display all item frequencies" << endl;
    cout << "3. Display histogram" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

int GetValidatedMenuChoice() {
    int userChoice;

    while (true) {
        cin >> userChoice;

        if (!cin.fail() && userChoice >= 1 && userChoice <= 4) {
            return userChoice;
        }

        cout << "Invalid input. Please enter a number from 1 to 4: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    GroceryTracker tracker("CS210_Project_Three_Input_File.txt", "frequency.dat");
    int menuChoice;
    string itemToSearch;

    tracker.LoadData();
    tracker.CreateBackupFile();

    do {
        PrintMenu();
        menuChoice = GetValidatedMenuChoice();

        switch (menuChoice) {
        case 1:
            cout << "Enter the item name: ";
            cin >> itemToSearch;
            cout << itemToSearch << " was purchased "
                 << tracker.GetItemFrequency(itemToSearch) << " time(s)." << endl;
            break;

        case 2:
            cout << endl << "Item Purchase Frequencies" << endl;
            tracker.PrintAllFrequencies();
            break;

        case 3:
            cout << endl << "Item Purchase Histogram" << endl;
            tracker.PrintHistogram();
            break;

        case 4:
            cout << "Exiting program." << endl;
            break;

        default:
            cout << "Invalid option." << endl;
            break;
        }

    } while (menuChoice != 4);

    return 0;
}
