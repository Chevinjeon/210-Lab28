#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <ctime>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

void delete_goat(set<Goat> &trip);
void add_goat(set<Goat> &trip, string [], string []);
void display_trip(set<Goat> trip);
int main_menu();
void display_goat_menu(set<Goat> trip);

// STL Algorithm function declarations (8 new options)
void find_goat(set<Goat> &trip);
void count_goats_by_age(set<Goat> &trip);
void find_if_old_goat(set<Goat> &trip);
void for_each_display(set<Goat> &trip);
void transform_goat_names(set<Goat> &trip);
void accumulate_total_age(set<Goat> &trip);
void remove_if_young_goat(set<Goat> &trip);
void sort_by_age_display(set<Goat> &trip);

int main() {
    srand(time(0));
    
    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    set<Goat> trip;
    bool again = true;

    while (again) {
        int choice = main_menu();
        switch(choice) {
            case 1:
                add_goat(trip, names, colors);
                break;
            case 2:
                delete_goat(trip);
                break;
            case 3:
                display_trip(trip);
                break;
            case 4:
                find_goat(trip);
                break;
            case 5:
                count_goats_by_age(trip);
                break;
            case 6:
                find_if_old_goat(trip);
                break;
            case 7:
                for_each_display(trip);
                break;
            case 8:
                transform_goat_names(trip);
                break;
            case 9:
                accumulate_total_age(trip);
                break;
            case 10:
                remove_if_young_goat(trip);
                break;
            case 11:
                sort_by_age_display(trip);
                break;
            case 12:
                again = false;
                cout << "\nThanks for using Goat Manager 3002!\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    }

    return 0;
}

// Task 2: Display main menu and get user choice
int main_menu() {
    cout << "\n*** GOAT MANAGER 3002 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Find a goat\n";
    cout << "[5] Count goats by age\n";
    cout << "[6] Find if old goat\n";
    cout << "[7] For each display\n";
    cout << "[8] Transform goat names\n";
    cout << "[9] Accumulate total age\n";
    cout << "[10] Remove young goats\n";
    cout << "[11] Sort by age display\n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    return choice;
}

// Display the goat selection submenu
void display_goat_menu(set<Goat> trip) {
    int index = 1;
    for (const Goat& g : trip) {
        cout << "    [" << index << "] " << g.get_name() 
             << " (" << g.get_age() << ", " << g.get_color() << ")\n";
        index++;
    }
}

// Task 3: Add a goat to the trip
void add_goat(set<Goat> &trip, string names[], string colors[]) {
    string name = names[rand() % SZ_NAMES];
    string color = colors[rand() % SZ_COLORS];
    int age = rand() % (MAX_AGE + 1);
    
    Goat newGoat(name, age, color);
    auto result = trip.insert(newGoat);
    if (result.second) {
        cout << "\nAdded: " << name << " (" << age << ", " << color << ")\n";
    } else {
        cout << "\nGoat " << name << " already exists in the set.\n";
    }
}

// Task 3: Delete a goat from the trip
void delete_goat(set<Goat> &trip) {
    if (trip.empty()) {
        cout << "\nNo goats to delete.\n";
        return;
    }
    
    display_goat_menu(trip);
    cout << "\nWhich goat to delete? --> ";
    int choice;
    cin >> choice;
    
    if (choice >= 1 && choice <= (int)trip.size()) {
        auto it = trip.begin();
        for (int i = 1; i < choice; i++) {
            it++;
        }
        cout << "\nDeleted: " << it->get_name() << " (" 
             << it->get_age() << ", " << it->get_color() << ")\n";
        trip.erase(it);
    } else {
        cout << "Invalid choice.\n";
    }
}

// Task 3: Display all goats in the trip
void display_trip(set<Goat> trip) {
    if (trip.empty()) {
        cout << "\nNo goats on the trip.\n";
        return;
    }
    
    cout << "\n*** Current Trip ***\n";
    display_goat_menu(trip);
}

// Milestone 1: STL find - Find a goat by name
void find_goat(set<Goat> &trip) {
    if (trip.empty()) {
        cout << "\nNo goats to search.\n";
        return;
    }
    
    cout << "\nEnter goat name to find: ";
    string searchName;
    cin >> searchName;
    
    // Create a temporary goat with just the name for comparison
    Goat searchGoat(searchName);
    auto it = trip.find(searchGoat);
    
    if (it != trip.end()) {
        cout << "\nFound: " << it->get_name() << " (" 
             << it->get_age() << ", " << it->get_color() << ")\n";
    } else {
        cout << "\nGoat \"" << searchName << "\" not found.\n";
    }
}

// Milestone 2: STL count_if - Count goats with age >= threshold
void count_goats_by_age(set<Goat> &trip) {
    if (trip.empty()) {
        cout << "\nNo goats to count.\n";
        return;
    }
    
    cout << "\nEnter minimum age threshold: ";
    int threshold;
    cin >> threshold;
    
    int count = count_if(trip.begin(), trip.end(), 
        [threshold](const Goat& g) { return g.get_age() >= threshold; });
    
    cout << "\nGoats with age >= " << threshold << ": " << count << "\n";
}

// Milestone 3: STL find_if - Find first goat with age >= threshold
void find_if_old_goat(set<Goat> &trip) {
    if (trip.empty()) {
        cout << "\nNo goats to search.\n";
        return;
    }
    
    cout << "\nEnter minimum age threshold: ";
    int threshold;
    cin >> threshold;
    
    auto it = find_if(trip.begin(), trip.end(), 
        [threshold](const Goat& g) { return g.get_age() >= threshold; });
    
    if (it != trip.end()) {
        cout << "\nFirst old goat found: " << it->get_name() << " (" 
             << it->get_age() << ", " << it->get_color() << ")\n";
    } else {
        cout << "\nNo goats found with age >= " << threshold << ".\n";
    }
}

// Milestone 4: STL for_each - Display all goats using for_each
void for_each_display(set<Goat> &trip) {
    if (trip.empty()) {
        cout << "\nNo goats to display.\n";
        return;
    }
    
    cout << "\n*** Goats (using for_each) ***\n";
    for_each(trip.begin(), trip.end(), [](const Goat& g) {
        cout << "    " << g.get_name() << " (" << g.get_age() 
             << ", " << g.get_color() << ")\n";
    });
}

// Milestone 5: STL transform - Create uppercase name list
void transform_goat_names(set<Goat> &trip) {
    if (trip.empty()) {
        cout << "\nNo goats to transform.\n";
        return;
    }