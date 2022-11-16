// Hw06 created by Fanyue Meng
//single file for world of Nobles and Warriors with runaway method

// Comment out these two includes for the single file solution
//#include "Noble.h"
//#include "Warrior.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Comment out this using namespace for the single file solution
//using namespace WarriorCraft;

class Noble;

// Warrior class
class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& war);
public:
    Warrior(const string& name_warrior, double strength_warrior);
    const string& getName() const;
    bool isHired() const;
    void set_hired_status(bool current_status);
    double get_strength() const;
    void set_strength(double curr_strength);
    void set_noble(Noble* noble);
    bool runaway();
private:
    string warrior_name;
    double strength;
    bool hired;
    Noble* boss;
};

//Noble class with noble's name, warriors, and life status
class Noble{
    friend ostream& operator<<(ostream& os, const Noble& nob);
public:
    Noble(const string& name_noble);
    const string& get_noble_name() const;
    bool hire(Warrior& war);
    bool fire(Warrior& war);
    double total_strength() const;
    void new_strength(double ratio);
    void battle(Noble& another_noble);
    bool remove_warrior(const Warrior& war);
private:
    string noble_name;
    vector<Warrior*> noble_warrior;
    bool alive;
};


int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
     << lance << endl
     << jim << endl
     << linus << endl
     << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
     << lance << endl
     << jim << endl
     << linus << endl
     << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha
     << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha
     << wizard.isHired() << endl;
    cout << "===============================================\n\n";
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
    os << endl;
    return os;
}


//constructor of warrior
Warrior::Warrior(const string& name_warrior, double strength_warrior) :
warrior_name(name_warrior), strength(strength_warrior),
hired(false), boss(nullptr) {}
//get name of warrior
const string& Warrior::getName() const {return warrior_name;}
//get hire status
bool Warrior::isHired() const {return hired;}
//set hire status
void Warrior::set_hired_status(bool current_status) {hired = current_status;}
//get strength of warrior
double Warrior::get_strength() const {return strength;}
//set strength
void Warrior::set_strength(double curr_strength) {
    strength = curr_strength;
}
//set warrior's boss
void Warrior::set_noble(Noble* noble){
    boss = noble;
}

//Noble constructor
Noble::Noble(const string& name_noble) : noble_name(name_noble), alive(true) {}
//get name of noble
const string& Noble::get_noble_name() const{return noble_name;}
//hire a warrior
bool Noble::hire(Warrior& war) {
    bool has_hired = false;
    // check the warrior has not been hired and noble is alive
    if (!war.isHired() && alive){
        noble_warrior.push_back(&war);
        war.set_hired_status(true);
        has_hired = true;
        war.set_noble(this);
    } else if (!alive){
        cout << noble_name
        << " is dead, so noble cannot hire any warrior!" << endl;
    }
    return has_hired;
}
//fire a warriorr
bool Noble::fire(Warrior& war) {
    bool has_fired = false;
    if (war.isHired() && alive){
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
            cout << "You don't work for me anymore " << war.getName()
            << "! -- " << noble_name << ". " << endl;
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
double Noble::total_strength() const{
    double total_strength = 0.0;
    for (size_t index = 0; index < noble_warrior.size(); index++){
        total_strength += noble_warrior[index]->get_strength();
    }
    return total_strength;
}

//set new stength for each warrior after battle
void Noble::new_strength(double ratio) {
    for (size_t index = 0; index < noble_warrior.size(); index++){
        noble_warrior[index]->set_strength
        ((noble_warrior[index]->get_strength()) * (1 - ratio));
    }
}

//provide battle for two noble
void Noble::battle(Noble& another_noble) {
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

//warrior runaway method
bool Warrior::runaway() {
    bool has_runaway = false;
    if (boss != nullptr){
        cout << warrior_name << " flees in terror, abandoning his lord, " << boss->get_noble_name() << endl;
        boss->remove_warrior(*this);
        boss = nullptr;
        has_runaway = true;
    }
    return has_runaway;
}

// remove a warrior when the warrior runaway
bool Noble::remove_warrior(const Warrior& war) {
    bool has_fired = false;
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
    return has_fired;
    
}
