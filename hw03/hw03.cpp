// Hw 03 created by fanyue meng
// rewrite the warriror game using class rather than struct
// This time, a warrior with name has a weapon and weapon's strength

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// class Warrior represent a warrior which contains warrior's name
// and warrior's weapon
class Warrior {
    friend ostream& operator<<(ostream& os, const Warrior& warrior);
public:
    // constructer of warrior with warrior's name, weapon's name
    // and weapon's strength
    Warrior (const string& name, const string& weapon, int strength)
    : warrior_name(name), warrior_weapon(weapon, strength) {}
    //method get_warrior_name will return warrior's name
    const string& get_warrior_name() const {return warrior_name;}
    
    void two_warrior_battle (Warrior& second_warrior);

private:
    // class Weapon represent weapon which contains weapon's name
    // and weapon's strength
    // there is no anthor object can access warrior's weapon except warrior
    class Weapon {
        friend ostream& operator<<(ostream& os, const Weapon& weapon);
    public:
        //constructer of weapon with weapon's name and weapon's strength
        Weapon (const string& weapon, int strength)
        : weapon_name(weapon), weapon_strength(strength) {}
        // method get_strength will return weapon's strength
        int get_strength() const {return weapon_strength; }
        // method set_strength will set new weapon strength
        void set_strength(int new_strength) {weapon_strength = new_strength;}
    private:
        string weapon_name;
        int weapon_strength;
    };
    
    string warrior_name;
    Weapon warrior_weapon;
    friend ostream& operator<<(ostream& os, const Warrior::Weapon& weapon);
};

size_t find_warrior(const vector<Warrior>& warriors_list,
                    const string& warrior_name);
void status (const vector<Warrior>& warrior_vector);

int main() {
    // open the file "warriors.txt"
    // and check whether it has been opened successfully
    ifstream ifs("warriors.txt");
    if (!ifs) {
        cerr << "Could not open the file.\n";
        exit(1);
    }
    vector<Warrior> warrior_vector;
    string command;
    //we will read the file string by string,
    //if command is warrior,
    //creates a new warrior and store with the specified warrior's name,
    //name of weapon, and strength of weapon
    //if command is battle,
    //causes a battle to occur between two warriors.
    //if command is status,
    //lists all warrior's name, weapon's name and weapon's strengths.
    while (ifs >> command) {
        if (command == "Warrior") {
            string name_warrior;
            ifs >> name_warrior;
            string name_weapon;
            ifs >> name_weapon;
            int weapon_strength;
            ifs >> weapon_strength;
            warrior_vector.emplace_back
            (name_warrior, name_weapon, weapon_strength);
        } else if (command == "Status") {
            status(warrior_vector);
        } else if (command == "Battle") {
            string first_name;
            ifs >> first_name;
            string second_name;
            ifs >> second_name;
            warrior_vector[find_warrior(warrior_vector, first_name)].
            two_warrior_battle
            (warrior_vector[find_warrior(warrior_vector, second_name)]);
        }
    }
    ifs.close();
}


// function find_warrior will return the index of warrior we are looking for
// the function will take warrior list and warrior's name as input
// by loop over the list of warrior,
// return the index which has the warrior name we are looking for
size_t find_warrior(const vector<Warrior>& warriors_list,
                    const string& warrior_name) {
    for (size_t index = 0; index < warriors_list.size(); index++) {
        if (warriors_list[index].get_warrior_name() == warrior_name) {
            return index;
        }
    }
    return warriors_list.size();
}

//method of warrior, two warrior battle,
//will calculate warrior's strength after battle
//it will pass in second warrior as opponent
//it will modifty warriors' strength after battle
void Warrior::two_warrior_battle (Warrior& second_warrior) {
    int first_warrior_strength = warrior_weapon.get_strength();
    int second_warrior_strength = second_warrior.warrior_weapon.get_strength();
    cout << warrior_name << " battles " << second_warrior.warrior_name << endl;
    //the if-else statement will compare two warriors' strength
    //and update new strength after battle
    if (first_warrior_strength == second_warrior_strength
        && first_warrior_strength != 0 && second_warrior_strength != 0) {
        cout << "Mutual Annihilation: " << warrior_name << " and "
        << second_warrior.warrior_name << " die at each other's hands" << endl;
        warrior_weapon.set_strength(0);
        second_warrior.warrior_weapon.set_strength(0);
    } else if (first_warrior_strength == 0 && second_warrior_strength> 0) {
        cout << "He's dead, " << second_warrior.warrior_name << endl;
    } else if (second_warrior_strength == 0 && first_warrior_strength > 0) {
        cout << "He's dead, " << warrior_name << endl;
    } else if (first_warrior_strength > second_warrior_strength &&
               first_warrior_strength != 0 && second_warrior_strength != 0) {
        cout << warrior_name << " defeats " <<
        second_warrior.warrior_name << endl;
        warrior_weapon.set_strength
        (first_warrior_strength - second_warrior_strength);
        second_warrior.warrior_weapon.set_strength(0);
    } else if (first_warrior_strength < second_warrior_strength &&
               first_warrior_strength != 0 && second_warrior_strength != 0) {
        cout << second_warrior.warrior_name << " defeats " <<
        warrior_name << endl;
        second_warrior.warrior_weapon.set_strength
        (second_warrior_strength - first_warrior_strength);
        warrior_weapon.set_strength(0);
    } else if (first_warrior_strength == 0 && second_warrior_strength == 0) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
}

//output operator for class weapon will
//print out name of weapon and strength of weapon
ostream& operator<<(ostream& os, const Warrior::Weapon& weapon) {
    os << "weapon: " << weapon.weapon_name << ", " << weapon.weapon_strength;
    return os;
}

//output operator for class warrior will print out warrior's name
//and warrior's weapon
ostream& operator<<(ostream& os, const Warrior& warrior) {
    os << "Warrior: " << warrior.warrior_name << ", " <<
    warrior.warrior_weapon;
    return os;
}

//function status will display all the warriors
//function status will pass in a warrior's vector
//print out how many warriors
//and warrior's name, weapon's name and weapon's strength
void status (const vector<Warrior>& warrior_vector) {
    cout << "There are: " << warrior_vector.size() << " warriors" << endl;
    for (size_t index = 0; index < warrior_vector.size(); index++){
        cout << warrior_vector[index] << endl;
    }
}
