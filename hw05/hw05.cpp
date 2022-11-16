// hw05 created by Fanyue Meng
// hw05 also will deal with class noble and warrior
// but this time we also need to consider handling error

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// Define your classes here
// Warrior class will represent warrior's name, strength and whether be hired
class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& war);
public:
    Warrior(const string& name_warrior, double strength_warrior) :
    warrior_name(name_warrior), strength(strength_warrior), hired(false) {}
    const string& getName() const {return warrior_name;}
    bool get_hired_status() const {return hired;}
    void set_hired_status(bool current_status) {hired = current_status;}
    double get_strength() const {return strength;}
    void set_strength(double curr_strength) {
        strength = curr_strength;
    }
private:
    string warrior_name;
    double strength;
    bool hired;
};

//Noble class with noble's name, warriors, and life status
class Noble{
    friend ostream& operator<<(ostream& os, const Noble& nob);
public:
    Noble(const string& name_noble) : noble_name(name_noble), alive(true) {}
    const string& get_noble_name() const{return noble_name;}
    bool hire(Warrior& war) {
        bool has_hired = false;
        // check the warrior has not been hired and noble is alive
        if (!war.get_hired_status() && alive){
            noble_warrior.push_back(&war);
            war.set_hired_status(true);
            has_hired = true;
        } else if (!alive){
            cout << noble_name
            << " is dead, so noble cannot hire any warrior!" << endl;
        } else {
            cout << "Attempting to hire " << war.getName() << " by "
            << noble_name << " faild!" << endl;
        }
        return has_hired;
    }
    
    //noble fire warrior
    bool fire(Warrior& war) {
        bool has_fired = false;
        if (war.get_hired_status() && alive){
            // loop over to find warrior
            for (size_t index = 0; index < noble_warrior.size(); index++){
                if (!has_fired){
                    if(noble_warrior[index] == &war){
                        has_fired = true;
                        noble_warrior[index]->set_hired_status(false);
                    }
                }else{
                    // swap
                    noble_warrior[index - 1] = noble_warrior[index];
                }
            }
            if(has_fired){
                noble_warrior.pop_back();
            }
        }
        else if (!alive){
            cout << noble_name <<
            " is dead, so noble cannot fire any warrior!" << endl;
        }
        else {
            cout << "Attempting to fire " << war.getName() << " by "
            << noble_name << " faild!" << endl;
        }
        return has_fired;
    }

    //calculate total strength of warriors
    double total_strength() const{
        double total_strength = 0.0;
        for (size_t index = 0; index < noble_warrior.size(); index++){
            total_strength += noble_warrior[index]->get_strength();
        }
        return total_strength;
    }

    //set new stength for each warrior after battle
    void new_strength(double ratio) {
        for (size_t index = 0; index < noble_warrior.size(); index++){
            noble_warrior[index]->set_strength
            ((noble_warrior[index]->get_strength()) * (1 - ratio));
        }
    }

    //provide battle for two noble
    void battle(Noble& another_noble) {
        cout << noble_name << " battles " << another_noble.noble_name << endl;
        double my_strength = total_strength();
        double another_strength = another_noble.total_strength();
        if (!alive && another_noble.alive){
            cout << "He's dead, " << another_noble.noble_name << endl;
        } else if (alive && !another_noble.alive){
            cout << "He's dead, " << noble_name << endl;
        } else if (!alive && !another_noble.alive){
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
        } else {
            if(my_strength == another_strength){
                cout << "Mutual Annihilation: " << noble_name << " and " <<
                another_noble.noble_name << " die at each other's hands"
                << endl;
                alive = false;
                another_noble.alive = false;
                new_strength(1);
                another_noble.new_strength(1);
            } else if (my_strength < another_strength){
                cout << another_noble.noble_name << " defeats "
                << noble_name << endl;
                alive = false;
                new_strength(1);
                another_noble.new_strength(my_strength/another_strength);
            } else if (my_strength > another_strength){
                cout << noble_name << " defeats "
                << another_noble.noble_name << endl;
                another_noble.alive = false;
                another_noble.new_strength(1);
                new_strength(another_strength/my_strength);
            }
        }
    }
    
private:
    string noble_name;
    vector<Warrior*> noble_warrior;
    bool alive;
};


// Utility functions provided for you, defined below.
size_t find_warrior(const vector<Warrior*>& warriors,
                    const string& warrior_name);
size_t find_noble(const vector<Noble*>& nobles, const string& noble_name);
void display(const vector<Noble*>& nobles, const vector<Warrior*>& warriors);
void hire(const string& noble_name, const string& warrior_name,
          const vector<Noble*>& all_nobles,
          const vector<Warrior*>& all_warriors);
void fire(const string& noble_name, const string& warrior_name,
          const vector<Noble*>& all_nobles,
          const vector<Warrior*>& all_warriors);

int main() {
    ifstream ifs("nobleWarriors.txt");
    if (!ifs) {
        cerr << "Could not open the file.\n";
        exit(1);
    }
    vector<Noble*> all_nobles;
    vector<Warrior*> all_warriors;
    string command;
    while (ifs >> command) {
        if (command == "Noble"){
            string noble_name;
            ifs >> noble_name;
            if (find_noble(all_nobles, noble_name) != all_nobles.size()){
                cout << "fail to add the noble: " << noble_name << endl;
            } else {
                all_nobles.push_back(new Noble(noble_name));
            }
        } else if (command == "Warrior"){
            string warrior_name;
            ifs >> warrior_name;
            double warrior_strength;
            ifs >> warrior_strength;
            if (find_warrior(all_warriors, warrior_name)
                != all_warriors.size()){
                cout << "fail to add the warrior: " << warrior_name << endl;
            } else {
                all_warriors.push_back(new Warrior
                                       (warrior_name, warrior_strength));
            }
        } else if (command == "Hire") {
            string hire_noble_name;
            string hire_warrior_name;
            ifs >> hire_noble_name;
            ifs >> hire_warrior_name;
            hire(hire_noble_name, hire_warrior_name, all_nobles, all_warriors);
        } else if (command == "Status") {
            display(all_nobles, all_warriors);
        } else if (command == "Fire") {
            string fire_noble_name;
            string fire_warrior_name;
            ifs >> fire_noble_name;
            ifs >> fire_warrior_name;
            fire(fire_noble_name, fire_warrior_name, all_nobles, all_warriors);
        } else if (command == "Battle") {
            string first_noble;
            string second_noble;
            ifs >> first_noble;
            ifs >> second_noble;
            size_t first_noble_index = find_noble(all_nobles, first_noble);
            size_t second_noble_index = find_noble(all_nobles, second_noble);
            if (first_noble_index == all_nobles.size()){
                cout << "Noble: " << first_noble << "does not exist!" << endl;
            } else if (first_noble_index == all_nobles.size()){
                cout << "Noble: " << second_noble << "does not exist!" << endl;
            } else {
                Noble& noble_1 = *all_nobles[first_noble_index];
                Noble& noble_2 = *all_nobles[second_noble_index];
                noble_1.battle(noble_2);
            }
        } else if (command == "Clear") {
            for (size_t index = 0; index < all_nobles.size(); index++){
                delete all_nobles[index];
            }
            for (size_t index = 0; index < all_warriors.size(); index++){
                delete all_warriors[index];
            }
            all_nobles.clear();
            all_warriors.clear();
        }
    }
    ifs.close();
}

//
// Utility functions
//
// hire. Calls Noble's hire method and displays error message on failure.
void hire(const string& noble_name, const string& warrior_name,
          const vector<Noble*>& all_nobles,
          const vector<Warrior*>& all_warriors) {
    size_t noble_index = find_noble(all_nobles, noble_name);
    size_t warrior_index = find_warrior(all_warriors, warrior_name);
    if (noble_index == all_nobles.size()){ // noble does not exist
        if (warrior_index == all_warriors.size()){ // warrior  does not exist
            cout << "Both of noble and warrior does not exist" << endl;
        } else { // warrior exist
            cout << noble_name << " does not exist" << endl;
        }
    } else { // noble exist
        if (warrior_index == all_warriors.size()){ // warrior does not exist
            cout << "Attempting to hire using unknown warrior: "
            << warrior_name << endl;
        } else{
            all_nobles[noble_index]->hire(*all_warriors[warrior_index]);
        }
    }
}

// fire. Calls Noble's fire method,
// displaying message on succsess and error message on failure
void fire(const string& noble_name, const string& warrior_name,
          const vector<Noble*>& all_nobles,
          const vector<Warrior*>& all_warriors) {
    size_t noble_index = find_noble(all_nobles, noble_name);
    size_t warrior_index = find_warrior(all_warriors, warrior_name);
    if (noble_index != all_nobles.size()){ // noble exist
        if (warrior_index != all_warriors.size()){ // warrior exist
            all_nobles[noble_index]->fire(*all_warriors[warrior_index]);
            cout << "You don't work for me anymore " << warrior_name
            << "! -- " << noble_name << ". " << endl;
        }
        else{
            cout << warrior_name << " does not exist, so cannot fired by "
            << noble_name << endl;
        }
    } else { // noble does not exist
        if (warrior_index != all_warriors.size()){ // warrior exist
            cout << noble_name << " does not exist, so cannot fire" << endl;
        }
        else { // warrior does not exist
            cout << "Both of noble and warrior does not exist" << endl;
        }
    }
}

//display information of warrior
ostream& operator<<(ostream& os, const Warrior& war){
    os << war.warrior_name << ": " << war.strength;
    return os;
}

//display information of noble
ostream& operator<<(ostream& os, const Noble& nob){
    os << nob.noble_name << " has an army of " << nob.noble_warrior.size();
    for (size_t index = 0; index < nob.noble_warrior.size(); index++) {
        os << endl << "\t\t" << *nob.noble_warrior[index];
    }
    return os;
}


size_t find_warrior(const vector<Warrior*>& warriors,
                    const string& warrior_name){
    for (size_t index = 0; index < warriors.size(); index++){
        if (warriors[index]->getName() == warrior_name) {
            return index;
        }
    }
    return warriors.size();
}


size_t find_noble(const vector<Noble*>& nobles, const string& noble_name){
    for (size_t index = 0; index < nobles.size(); index++){
        if (nobles[index]->get_noble_name() == noble_name) {
            return index;
        }
    }
    return nobles.size();
}

void display(const vector<Noble*>& nobles, const vector<Warrior*>& warriors){
    cout << "Status" << endl;
    cout << "======" << endl;
    cout << "Nobles:" << endl;
    for (size_t index = 0; index < nobles.size(); index++){
        cout << *nobles[index] << endl;
    }
    if (nobles.size() == 0){
        cout << "NONE" << endl;
    }
    cout << endl;
    cout << "Unemployed Warriors:" << endl;
    int number_unemployed = 0;
    for (size_t index = 0; index < warriors.size(); index++){
        if (warriors[index]->get_hired_status() == false){
            cout << "\t\t" << *warriors[index] << endl;
            number_unemployed += 1;
        }
    }
    if (number_unemployed == 0){
        cout << "NONE" << endl;
    }
}


