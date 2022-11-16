// rec11 created by Fanyue Meng

#include <iostream>
#include <vector>
using namespace std;

class Instrument{
public:
    virtual void makeSound() const = 0;
    virtual void normal_play() const = 0;
private:
    
};

void Instrument::makeSound() const{
    cout << "To make a sound... ";
}

class Brass: public Instrument{
public:
    Brass(unsigned input_size) : size(input_size) {}
    void makeSound() const{
        Instrument::makeSound();
        cout << "blow on a mouthpiece of size " << size << endl;
    }
private:
    unsigned size;
};

class Trumpet: public Brass{
public:
    Trumpet(unsigned size) : Brass(size) {}
    void normal_play() const{
        cout << "Toot";
    }
};

class Trombone: public Brass{
public:
    Trombone(unsigned size) : Brass(size) {}
    void normal_play() const{
        cout << "Blat";
    }
};



class String: public Instrument{
public:
    String(unsigned input_pitch) : pitch(input_pitch) {}
    void makeSound() const{
        Instrument::makeSound();
        cout << "bow a string with pitch " << pitch << endl;
    }
private:
    unsigned pitch;
};

class Violin: public String{
public:
    Violin(unsigned pitch) : String(pitch) {}
    void normal_play() const{
        cout << "Screech";
    }
private:
};

class Cello: public String{
public:
    Cello(unsigned pitch) : String(pitch) {}
    void normal_play() const{
        cout << "Squawk";
    }
private:

};



class Precussion: public Instrument{
public:
    void makeSound() const{
        Instrument::makeSound();
        cout << "hit me!" << endl;
    }
private:
};

class Drum: public Precussion{
public:
    void normal_play() const{
        cout << "Boom";
    }
private:
};

class Cymbal: public Precussion{
public:
    void normal_play() const{
        cout << "Crash";
    }
private:
};


class Musician {
public:
    Musician() : instr(nullptr) {}

    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    void testPlay() const {
        if (instr) instr->makeSound();
        else cerr << "have no instr\n";
    }
    
    void mus_play() const {
        if (instr != nullptr){
            instr->normal_play();
        }
    }

private:
    Instrument* instr;
};

class MILL{
public:
    void receiveInstr(Instrument& ins){
        ins.makeSound();
        for (size_t index = 0; index < instrument_library.size(); index++){
            if (instrument_library[index] == nullptr){
                instrument_library[index] = &ins;
                return;
            }
        }
        instrument_library.push_back(&ins);
    }
    
    void dailyTestPlay() const{
        for(size_t index = 0; index < instrument_library.size(); index++){
            if (instrument_library[index] != nullptr){
                instrument_library[index]->makeSound();
            }
        }
    }
    
    Instrument* loanOut(){
        for (size_t index = 0; index < instrument_library.size(); index++){
            if (instrument_library[index] != nullptr){
                Instrument* loaned_ins = instrument_library[index];
                instrument_library[index] = nullptr;
                return loaned_ins;
            }
        }
        return nullptr;
    }
private:
    vector<Instrument*> instrument_library;
};

class Orch{
public:
    void addPlayer(Musician& musician){
        musician_lst.push_back(&musician);
    }
    
    void play() const{
        for(size_t index = 0; index < musician_lst.size(); index++){
            musician_lst[index]->mus_play();
        }
        cout << endl;
    }
    
private:
    vector<Musician*> musician_lst;
};

int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ----------------------------------------\n";
     Drum drum;
     Cello cello(673);
     Cymbal cymbal;
     Trombone tbone(4);
     Trumpet trpt(12) ;
     Violin violin(567) ;
  
    // use the debugger to look at the mill
    cout << "Define the MILL ------------------------------------------------\n";
     MILL mill;
  
    cout << "Put the instruments into the MILL ------------------------------\n";
     mill.receiveInstr(trpt);
     mill.receiveInstr(violin);
     mill.receiveInstr(tbone);
     mill.receiveInstr(drum);
     mill.receiveInstr(cello);
     mill.receiveInstr(cymbal);
  
    cout << "Daily test -----------------------------------------------------\n"
     << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();
     cout << endl;
  
    cout << "Define some Musicians-------------------------------------------\n";
     Musician harpo;
     Musician groucho;
      
     cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
     groucho.testPlay();
     cout << endl;
     groucho.acceptInstr(mill.loanOut());
     cout << endl;
     groucho.testPlay();
     cout << endl;
     cout << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();
  
     cout << endl << endl;
  
     groucho.testPlay();
     cout << endl;
     mill.receiveInstr(*groucho.giveBackInstr());
     harpo.acceptInstr(mill.loanOut());
     groucho.acceptInstr(mill.loanOut());
     cout << endl;
     groucho.testPlay();
     cout << endl;
     harpo.testPlay();
     cout << endl;
     cout << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();
  
     cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
  
     // fifth
     mill.receiveInstr(*groucho.giveBackInstr());
     cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
     mill.receiveInstr(*harpo.giveBackInstr());

  
     cout << endl;
     cout << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();
     cout << endl;
  
     cout << endl;


    //
    // PART TWO
    //
    
    
    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
    
    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
    
}
