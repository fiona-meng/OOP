// Hw04 Created by Fanyue Meng
// This assignment will display medieval game
// warriors will led by noble
// whether the battle will win depends on total strength of warriors

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Define your classes here
// Warrior class will represent warrior's name, strength and whether be hired
class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& war);
public:
    // constructor of Warrior
    Warrior(const string& name_warrior, double strength_warrior) :
    warrior_name(name_warrior), strength(strength_warrior), hired(false) {}
    // get name of warrior
    const string& getName() const {return warrior_name;}
    //get warrior's hire status
    bool get_hired_status() const {return hired;}
    //set warrior's hire status
    void set_hired_status(bool current_status) {hired = current_status;}
    //get strength of warrior
    double get_strength() const {return strength;}
    //set strength of warrior
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
    //constructor of Noble
    Noble(const string& name_noble) : noble_name(name_noble), alive(true) {}
    //get name of noble
    const string& getName() const{return noble_name;}
    //noble hire a warrior
    bool hire(Warrior& war) {
        // check the warrior has not been hired and noble is alive
        if (!war.get_hired_status() && alive){
            noble_warrior.push_back(&war);
            war.set_hired_status(true);
            return true;
        } else{
            return false;
        }
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
        }
        // detele the last repeat warrior
        // if nobel fire a warrior in the previous step
        if(has_fired){
            noble_warrior.pop_back();
        }
        return has_fired;
    }

    //calculate total strength of warriors
    double total_strength() const{
        double total_strength = 0.0;
        // loop over to the total stength of nobel's warriors
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
        // if one of them are dead
        if (!alive && another_noble.alive){
            cout << "He's dead, " << another_noble.noble_name << endl;
            // if one of them are dead
        } else if (alive && !another_noble.alive){
            cout << "He's dead, " << noble_name << endl;
            // if both of them are dead
        } else if (!alive && !another_noble.alive){
            cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
            // if both of them are alive
        } else {
            // if they have same strength
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
void hire(Noble& nob, Warrior& war);
void fire(Noble& nob, Warrior& war);

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
    
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
    
    hire(jim, nimoy);
    hire(lance, theGovernator);
    hire(art, wizard);
    hire(lance, dylan);
    hire(linus, lawless);
    hire(billie, mrGreen);
    hire(art, cheetah);
    hire(art, nimoy);
    
    cout << "==========\n\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n\n";

    fire(art, cheetah);
    cout << art << endl;
    fire(lance, nimoy);
    cout << lance << endl;
    cout << "==========\n\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);
    cout << "==========\n\n";

    cout << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
}

//
// Utility functions
//
// hire. Calls Noble's hire method and displays error message on failure.
void hire(Noble& nob, Warrior& war) {
    if (!nob.hire(war)) {
    cerr << nob.getName() << " failed to hire " << war.getName() << endl;
    }
}

// fire. Calls Noble's fire method,
// displaying message on succsess and error message on failure
void fire(Noble& nob, Warrior& war) {
    if (nob.fire(war)) {
    cout << war.getName() << ", you don't work for me any more! -- "
        << nob.getName() << ".\n";
    } else {
    cerr << nob.getName() << " failed to fire " << war.getName() << endl;
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
