#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
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