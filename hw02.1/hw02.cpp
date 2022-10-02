//Hw02
//created by fanyue meng
//the programe will model a gamee of medieval times
//after each battle, warriors with less strength will die

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// a struct represent warriors including warriors' name and strength
struct Warriors {
    string name;
    int strength;
};


void creat_warriors(const string& name, int strength,
                    vector<Warriors>& warriors_list);
void status(const vector<Warriors>& warriors_list);
size_t find_warrior(const vector<Warriors>& warriors_list,
                    const string& person_name);
void battle(vector<Warriors>& warriors_list, const string& first_person,
            const string& second_person);

int main() {
    ifstream file;
    vector<Warriors> warriors_list;
    // opent the file and check whether it has been opened
    file.open("warriors.txt");
    if (!file) {
        cerr << "Could not open the file.\n";
        exit(1);
    }
    
    string command;
    //we will read the file string by string,
    //if command is warrior,
    //creates a new warrior with the specified name and strength.
    //if command is battle,
    //causes a battle to occur between two warriors.
    //if command is status,
    //lists all warriors, alive or dead, and their strengths.
    while(file >> command) {
        if (command == "Warrior"){
            string name;
            file >> name;
            int strength;
            file >> strength;
            creat_warriors(name, strength, warriors_list);
        } else if (command == "Status"){
            status(warriors_list);
        } else if (command == "Battle") {
            string first_warrior;
            string second_warrior;
            file >> first_warrior;
            file >> second_warrior;
            battle(warriors_list, first_warrior, second_warrior);
        }
    }
    file.close();
}

// function creat_warriors will pass in warrior's name and strength
// and a list of warriors in the vector
//after creat a new warrior, we store it in the warriors list
//the function will modify the vector
void creat_warriors(const string& name, int strength,
                    vector<Warriors>& warriors_list) {
    Warriors new_warriors;
    new_warriors.name = name;
    new_warriors.strength = strength;
    warriors_list.push_back(new_warriors);
}

//function status will display all the warriors
//function status will pass in a vector
//print out how many warriors and warrior's name and current strength
void status(const vector<Warriors>& warriors_list) {
    cout << "There are: " << warriors_list.size() << " warriors" << endl;
    for (size_t index = 0; index < warriors_list.size(); index++) {
        cout << "Warrior: " << warriors_list[index].name << ", strength: "
        << warriors_list[index].strength << endl;
    }
}

//function battle will calculate warrior's strength after battle
//function will pass in a vector which contains all the warriors
//and two warriors's name
//function will modifty warriors' strength after battle
void battle(vector<Warriors>& warriors_list, const string& first_warrior_name,
            const string& second_warrior_name){
    size_t first_warrior_index =
    find_warrior(warriors_list, first_warrior_name);
    size_t second_warrior_index =
    find_warrior(warriors_list, second_warrior_name);
    Warriors first_warrior = warriors_list[first_warrior_index];
    Warriors second_warrior = warriors_list[second_warrior_index];
    cout << first_warrior.name << " battles " << second_warrior.name << endl;
    //the if-else statement will compare two warriors' strength
    //and update new strength after battle
    if (first_warrior.strength == second_warrior.strength
        && first_warrior.strength != 0 && second_warrior.strength != 0) {
        cout << "Mutual Annihilation: " << first_warrior_name << " and "
        << second_warrior_name << " die at each other's hands" << endl;
        warriors_list[first_warrior_index].strength = 0;
        warriors_list[second_warrior_index].strength = 0;
    } else if (first_warrior.strength == 0 && second_warrior.strength > 0) {
        cout << "He's dead, " << second_warrior.name << endl;
    } else if (second_warrior.strength == 0 && first_warrior.strength > 0) {
        cout << "He's dead, " << first_warrior.name << endl;
    } else if (first_warrior.strength > second_warrior.strength &&
               first_warrior.strength != 0 && second_warrior.strength != 0) {
        cout << first_warrior.name << " defeats " <<
        second_warrior.name << endl;
        warriors_list[first_warrior_index].strength =
        first_warrior.strength - second_warrior.strength;
        warriors_list[second_warrior_index].strength = 0;
    } else if (first_warrior.strength < second_warrior.strength &&
               first_warrior.strength != 0 && second_warrior.strength != 0) {
        cout << second_warrior.name << " defeats " <<
        first_warrior.name << endl;
        warriors_list[second_warrior_index].strength =
        second_warrior.strength - first_warrior.strength;
        warriors_list[first_warrior_index].strength = 0;
    } else if (first_warrior.strength == 0 && second_warrior.strength == 0) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
}

// function find_warrior will pass in a vector which contains all the warriors
// and a warrior's name, a string
// after loop over the list a warriors, the function will return the warrior's
// index of warriors list
size_t find_warrior(const vector<Warriors>& warriors_list,
                    const string& person_name) {
    // by comparing name of warrior, the for loop will help to find the
    // warrior's index
    for (size_t index = 0; index < warriors_list.size(); index++) {
        if (warriors_list[index].name == person_name) {
            return index;
        }
    }
    return warriors_list.size();
}
