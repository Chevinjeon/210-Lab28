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
