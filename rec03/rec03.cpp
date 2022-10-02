
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// hydrocarbs.txt
struct Molecular {
    vector<string> formula_name;
    int carbon_number;
    int hydrogen_number;
};

void open_file(ifstream& file);
void fill_vector(ifstream& file, vector<Molecular>& moleculars);
void insert(vector<Molecular>& moleculars, const string& name, int num_carbon, int num_hydrogen);
size_t find_location(const vector<Molecular>& moleculars, int num_carbon, int num_hydrogen);
void sort_vector(vector<Molecular>& moleculars);
void display_vector(const vector<Molecular>& moleculars);
void display_formula(const Molecular& mole);

int main() {
    ifstream file;
    vector<Molecular> moleculars;
    open_file(file);
    fill_vector(file, moleculars);
    sort_vector(moleculars);
    display_vector(moleculars);
    file.close();
}

void open_file(ifstream& file){
    string file_name;
    cout << "input your file name: ";
    cin >> file_name;
    file.open(file_name);

    while (!file){
        cerr << "failed to open " << file_name << endl;
        file.clear();
        cout << "input your file name: ";
        cin >> file_name;
        file.open(file_name);
}
}


void fill_vector(ifstream& file, vector<Molecular>& moleculars){
    string name;
    char carbon;
    int num_carbon;
    char hydrogen;
    int num_hydrogen;
    while (file >> name >> carbon >> num_carbon >> hydrogen >> num_hydrogen) {
        insert(moleculars, name, num_carbon, num_hydrogen);
    }
}

void insert(vector<Molecular>& moleculars, const string& name, int num_carbon, int num_hydrogen) {
    // find_location(moleculars, num_carbon, num_hydrogen);
    if (find_location(moleculars, num_carbon, num_hydrogen) == moleculars.size()){
        Molecular mole;
        mole.formula_name.push_back(name);
        mole.carbon_number = num_carbon;
        mole.hydrogen_number = num_hydrogen;
        moleculars.push_back(mole);
    } else {
        moleculars[find_location(moleculars, num_carbon, num_hydrogen)].formula_name.push_back(name);
    }
    
}


size_t find_location(const vector<Molecular>& moleculars, int num_carbon, int num_hydrogen){
    for (size_t index = 0; index < moleculars.size(); ++index){
        if ((moleculars[index].carbon_number == num_carbon)
            && (moleculars[index].hydrogen_number == num_hydrogen)){
            return index;
        }
    }
    return moleculars.size();
}


void sort_vector(vector<Molecular>& moleculars){
    for (size_t i = 0; i < moleculars.size(); ++i){
        for (size_t j = 0; j < moleculars.size() - 1; ++j){
            if (moleculars[j].carbon_number > moleculars[j+1].carbon_number
                || (moleculars[j].carbon_number == moleculars[j+1].carbon_number &&
                    moleculars[j].hydrogen_number > moleculars[j+1].hydrogen_number)){
                Molecular temp =moleculars[j];
                moleculars[j] = moleculars[j+1];
                moleculars[j+1] = temp;
    
            }
            
        }
    }
}

void display_vector(const vector<Molecular>& moleculars){
    for (size_t index = 0; index < moleculars.size(); ++index){
        display_formula(moleculars[index]);
    }
}

void display_formula(const Molecular& mole){
    cout << 'C' << mole.carbon_number << 'H' << mole.hydrogen_number << '\t';
    for (const string& name : mole.formula_name) {
        cout << name << '\t';
    }
    cout << endl;
    
}
