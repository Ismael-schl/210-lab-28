//Lab 28 | COMCSC 210 | Ismael Hadi
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void sort_trip(list<Goat> &trip);
void reverse_trip(list<Goat> &trip);
void display_trip(list<Goat> trip);
void search_trip(list<Goat> trip);
void unique_trip(list<Goat> &trip);
void double_ages(list<Goat> &trip);
void senior_search(list<Goat> trip);
void clear_trip(list<Goat> &trip);
int main_menu();

int main() {
    srand(time(0));
    bool again;

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

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 11) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4: 
                cout << "Sorting goats.\n";
                sort_trip(trip);
                break;
            case 5:
                cout << "Reversing trip.\n";
                reverse_trip(trip);
                break;
            case 6:
                cout << "Removing duplicate goats.\n";
                unique_trip(trip);
                break;
            case 7:
                search_trip(trip);
                break;
            case 8:
                cout << "Doubling all ages..." << endl;
                double_ages(trip);
                break;
            case 9:
                cout << "Searching for seniors\n.";
                senior_search(trip);
                break;
            case 10:
                cout << "Clearing trip.\n";
                clear_trip(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Sort goats\n";
    cout << "[5] Reversing goats\n";
    cout << "[6] Remove any duplicate goats\n";
    cout << "[7] Search for a goat.\n";
    cout << "[8] Double all goats' ages.\n";
    cout << "[9] Search for senior goats.\n";
    cout << "[10] Clear trip.\n";
    cout << "[11] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 11) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void sort_trip(list<Goat> &trip) {
    trip.sort();
    cout << "Trip sorted." << endl;
}

void reverse_trip(list<Goat> &trip) {
    reverse(trip.begin(), trip.end());
    cout << "Trip reversed." << endl;
}

void unique_trip(list<Goat> &trip) {
    trip.sort();
    auto newTrip = unique(trip.begin(), trip.end());
    trip.erase(newTrip, trip.end());
}

void search_trip(list<Goat> trip) {
    string target;
    cout << "Enter the name of the goat you are searching for: ";
    cin >> target;
    bool found = false;
    auto it = find_if(trip.begin(), trip.end(), [target](Goat &g))
        if (g.get_name() == target) {
            cout << "Found " << target << "(" << g.get_age() << ", " << g.get_color() << ")" << endl;
   
    if (!found) {
        cout << target << " not found. " << endl;
    }
}

void senior_search(list<Goat> trip) {
    bool rSeniors = any_of(trip.begin(), trip.end(), [](Goat &g) { return g.get_age() >25;});
    if (rSeniors) {
        cout << "There are senior goats, of age greater than 25 years, on the trip" << endl;
    }
    else 
        cout << "There are no senior goats on this trip." << endl;
}

void double_ages(list<Goat> &trip) {
    for_each(trip.begin(), trip.end(), [](Goat &g) {g.set_age(g.get_age() *2);});
    cout << "All ages have been doubled." << endl;
}

void clear_trip(list<Goat> &trip) {
    trip.clear();
    cout << "Trip has been cleared of goats.\n";
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}