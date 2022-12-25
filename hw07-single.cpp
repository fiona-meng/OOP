// Hw07 created by Fanyue Meng
// Using inheritance and Cyclic association
// Game of Battle
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Protectors;
class Noble{
    friend ostream& operator<<(ostream& os, const Noble& noble);    
public:
    Noble(const string& noble_name);
    const string& get_name() const;
    virtual void battleCry() const = 0;
    virtual void new_strength(double) = 0;
    virtual double get_strength() const = 0;
    virtual void display() const = 0;
    virtual bool remove_protector(const Protectors& protector) = 0;
    void battle(Noble& another_noble);
protected:
    bool is_alive() const;
private:
    bool noble_alive;
    string noble_name;
};

class Protectors{
    friend ostream& operator<<(ostream& os, const Protectors& protectors);
public:
    Protectors(const string& protectors_name, double protectors_strength);
    const string& get_name() const;
    void set_noble(Noble* noble);
    Noble* get_noble() const;
    virtual void defend() const = 0;
    double get_protectors_strength() const;
    void set_strength(double new_strength);
    bool runaway();

private:
    Noble* protectors_noble;
    string protector_name;
    double strength;
};


class Lord : public Noble{
public:
    Lord(const string& lord_name);
    bool hires(Protectors& protector);
    bool fire(Protectors& protector);
    void battleCry() const;
    double get_strength() const;
    void new_strength(double ratio);
    bool remove_protector(const Protectors& protector);
    void display() const;
private:
    vector<Protectors*> protectors;
};

class PersonWithStrengthToFight: public Noble{
public:
    PersonWithStrengthToFight(const string& person_name, int person_strength);
    double get_strength() const;
    void battleCry() const;
    void new_strength(double ratio);
    bool remove_protector(const Protectors& protector);
    void display() const;
private:
    double strength;
};


class Wizard : public Protectors{
public:
    Wizard(const string& wizard_name, double wizard_strength);
    void defend() const;
};

class Warriors : public Protectors{
public:
    Warriors(const string& name, double strength);
    void defend() const;
};

class Archer: public Warriors{
public:
    Archer(const string& name, double strength);
    void defend() const;
};

class Swordsman: public Warriors{
public:
    Swordsman(const string& name, double strength);
    void defend() const;
};



// Noble definition
ostream& operator<<(ostream& os, const Noble& noble){
    os << "Noble Name: " << noble.noble_name << endl;
    os << "Noble Alive: " << boolalpha << noble.noble_alive << endl;
    noble.display();
    return os;
}

Noble::Noble(const string& noble_name) : noble_name(noble_name), noble_alive(true) {}
const string& Noble::get_name() const {
    return noble_name;
}
void Noble::battle(Noble& another_noble) {
    cout << noble_name << " battles " << another_noble.noble_name << endl;
    double first_noble_strength = get_strength();
    double second_noble_strength = another_noble.get_strength();
    if (!noble_alive && another_noble.noble_alive){
        another_noble.battleCry();
        cout << "He's dead, " << another_noble.noble_name<< endl;
    } else if (noble_alive && !another_noble.noble_alive){
        battleCry();
        cout << "He's dead, " << noble_name << endl;
    } else if (!noble_alive && !another_noble.noble_alive){
        cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
    } else {
        battleCry();
        another_noble.battleCry();
        if(first_noble_strength == second_noble_strength){
            cout << "Mutual Annihilation: " << noble_name << " and " <<
            another_noble.noble_name << " die at each other's hands"
            << endl;
            noble_alive = false;
            another_noble.noble_alive = false;
            new_strength(1);
            another_noble.new_strength(1);
        } else if (first_noble_strength < second_noble_strength){
            cout << another_noble.noble_name << " defeats "
            << noble_name << endl;
            noble_alive = false;
            new_strength(1);
            another_noble.new_strength(first_noble_strength/second_noble_strength);
        } else if (first_noble_strength > second_noble_strength){
            cout << noble_name << " defeats "
            << another_noble.noble_name << endl;
            another_noble.noble_alive = false;
            another_noble.new_strength(1);
            new_strength(second_noble_strength/first_noble_strength);
        }
    }
}
bool Noble::is_alive() const {return noble_alive;}

//Protectors definition
ostream& operator<<(ostream& os, const Protectors& protectors){
    os << protectors.protector_name << " has strength " << protectors.strength << endl;
    return os;
}
Protectors::Protectors(const string& protectors_name, double protectors_strength) : strength(protectors_strength), protector_name(protectors_name), protectors_noble(nullptr){}
const string& Protectors::get_name() const {
    return protector_name;
}
void Protectors::set_noble(Noble* noble) {
    protectors_noble = noble;
}
Noble* Protectors::get_noble() const {
    return protectors_noble;
}
double Protectors::get_protectors_strength() const{
    return strength;
}
void Protectors::set_strength(double new_strength){
    strength = new_strength;
}
bool Protectors::runaway() {
    bool has_runaway = false;
    if (protectors_noble != nullptr){
        cout << protector_name << " flees in terror, abandoning his lord, " << protectors_noble->get_name() << endl;
        protectors_noble->remove_protector(*this);
        protectors_noble = nullptr;
        has_runaway = true;
    }
    return has_runaway;
}

// Lord definition
Lord::Lord(const string& lord_name) : Noble(lord_name) {}
bool Lord::hires(Protectors& protector) {
    bool has_hired = false;
    // check the warrior has not been hired and noble is alive
    if (protector.get_noble() == nullptr && is_alive()){
        protectors.push_back(&protector);
        protector.set_noble(this);
    }
    return has_hired;
}
bool Lord::fire(Protectors& protector){
    bool has_fired = false;
    if (protector.get_noble() != nullptr && is_alive()){
        // loop over to find protector
        for (size_t index = 0; index < protectors.size(); index++){
            if (!has_fired){
                if(protectors[index] == &protector){
                    has_fired = true;
                    protector.set_noble(nullptr);
                }
            }else{
                // swap
                protectors[index - 1] = protectors[index];
            }
        }
        if(has_fired){
            protectors.pop_back();
            cout << "You don't work for me anymore " << protector.get_name()
            << "! -- " << get_name() << ". " << endl;
        }
    }
    else if (!is_alive()){
        cout << get_name() <<
        " is dead, so noble cannot fire any protector!" << endl;
    }
    else {
        cout << "Attempting to fire " << protector.get_name() << " by "
        << get_name() << " faild!" << endl;
    }
    return has_fired;
}
void Lord::battleCry() const {
    for(size_t index = 0; index < protectors.size(); index++){
        protectors[index]->defend();
    }
}
double Lord::get_strength() const {
    double total_strength = 0;
    for (size_t index = 0; index < protectors.size(); index++){
        total_strength += protectors[index]->get_protectors_strength();
    }
    return total_strength;
}
void Lord::new_strength(double ratio) {
    for (size_t index = 0; index < protectors.size(); index++){
        protectors[index]->set_strength
            ((protectors[index]->get_protectors_strength()) * (1 - ratio));
        }
}

bool Lord::remove_protector(const Protectors& protector) {
    bool has_fired = false;
    for (size_t index = 0; index < protectors.size(); index++){
        if (!has_fired){
            if(protectors[index] == &protector){
                has_fired = true;
                protectors[index]->set_noble(nullptr);
            }
        }else{
            // swap
            protectors[index - 1] = protectors[index];
        }
    }
    if(has_fired){
        protectors.pop_back();
    }
    return has_fired;
}

void Lord::display() const {
    cout << "Lord: " << Noble::get_name() << " has following protectors: " << endl;
    for (size_t index = 0; index < protectors.size(); index++) {
        cout << *protectors[index] << endl;
    }
}

// PersonWithStrengthToFight Definition:
PersonWithStrengthToFight::PersonWithStrengthToFight(const string& person_name, int person_strength) : Noble(person_name), strength(person_strength) {}

double PersonWithStrengthToFight::get_strength() const {
    return strength;
}

void PersonWithStrengthToFight::battleCry() const {
    if (is_alive()) {
        cout << "Ugh!" << endl;
    }
}

void PersonWithStrengthToFight::new_strength(double ratio) {
    strength = strength * (1 - ratio);
}

bool PersonWithStrengthToFight::remove_protector(const Protectors& protector) {
    return false;
}

void PersonWithStrengthToFight::display() const {
    cout << "Person with Strength to fight: " << Noble::get_name() << "has strength:  " << strength << endl;
}

// Wizard definition
Wizard::Wizard(const string& wizard_name, double wizard_strength) : Protectors(wizard_name, wizard_strength) {}

void Wizard::defend() const{
    cout << "POOF!" << endl;
}

//Warriors definition
Warriors::Warriors(const string& name, double strength) : Protectors(name, strength) {}

void Warriors::defend() const {
    cout << " says: Take that in the name of my lord, " << get_noble()->get_name() << endl;
}

// Archer definition
Archer::Archer(const string& name, double strength) : Warriors(name, strength) {}

void Archer::defend() const{
    cout << "TWANG!  " << get_name();
    Warriors::defend();
}

//Swordsman definition
Swordsman::Swordsman(const string& name, double strength) : Warriors(name, strength) {}

void Swordsman::defend() const {
    cout << "CLANG!  " << get_name();
    Warriors::defend();
}

int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    joe.battle(randy);
    joe.battle(sam);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    janet.battle(barclay);
    janet.hires(samantha);
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(barclay);
    sam.battle(barclay);
    joe.battle(barclay);
}
