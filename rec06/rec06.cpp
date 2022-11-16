/*
 cready by fanyue Meng
 rec06
 */
 

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student {
    friend ostream& operator<<(ostream& os, const Student& student);
public:
    Student(const string& name) : student_name(name), student_grade(14, -1){}
    const string& get_student_name() const {return student_name;}
    void set_grade(int grade, int pos){
        student_grade[pos - 1] = grade;
    }
private:
    string student_name;
    vector<int> student_grade;
};

class Time_slot{
    friend ostream& operator<<(ostream& os, const Time_slot& time);
public:
    Time_slot(const string& day, int hour) : week_day(day), hour_to_start(hour) {}
private:
    string week_day;
    int hour_to_start;
};

class Section {
    friend ostream& operator<<(ostream& os, const Section& sec);
public:
    Section(const string& name, const string& week_day, int hour_to_start) : section_name(name), time_slot(week_day, hour_to_start) {}
    void addStudent(const string& student_name) {
        students.push_back(new Student(student_name));
    }
    size_t find_student(const string& name) const {
        for (size_t index = 0; index < students.size(); index++){
            if (students[index]->get_student_name() == name) {
                return index;
            }
        }
        return students.size();
    }
    void edit_student_grade(const string& name, int grade, int pos) {
        size_t student_index = find_student(name);
        students[student_index]->set_grade(grade, pos);
    }
    ~Section() {
        cout << "Section " << section_name << " is being deleted" << endl;
        for (size_t index = 0; index < students.size(); index++){
            cout << "Deleting " << students[index]->get_student_name() << endl;
            delete students[index];
        }
    }
    Section(const Section& another_section) : section_name(another_section.section_name),
    time_slot(another_section.time_slot){
        for (size_t index = 0; index < another_section.students.size(); index++){
            students.push_back(new Student(*another_section.students[index]));
        }
        
    }
private:
    string section_name;
    Time_slot time_slot;
    vector<Student*> students;
};

class LabWorker {
    friend ostream& operator<<(ostream& os, const LabWorker& instructor);
public:
    LabWorker(const string& name) : section(nullptr), insrtuctor_name(name) {}
    void addSection(Section& sec){
        section = &sec;
    }
    void addGrade(const string& name, int grade, int pos) {
        section->edit_student_grade(name, grade, pos);
    }
private:
    Section* section;
    string insrtuctor_name;
};


// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {

    cout << "Test 1: Defining a section\n";
     Section secA2("A2", "Tuesday", 16);
     cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
     secA2.addStudent("John");
     secA2.addStudent("George");
     secA2.addStudent("Paul");
     secA2.addStudent("Ringo");
     cout << secA2 << endl;
    

    cout << "\nTest 3: Defining a lab worker.\n";
     LabWorker moe( "Moe" );
     cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
     moe.addSection( secA2 );
     cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
     LabWorker jane( "Jane" );
     Section secB3( "B3", "Thursday", 11 );
     secB3.addStudent("Thorin");
     secB3.addStudent("Dwalin");
     secB3.addStudent("Balin");
     secB3.addStudent("Kili");
     secB3.addStudent("Fili");
     secB3.addStudent("Dori");
     secB3.addStudent("Nori");
     secB3.addStudent("Ori");
     secB3.addStudent("Oin");
     secB3.addStudent("Gloin");
     secB3.addStudent("Bifur");
     secB3.addStudent("Bofur");
     secB3.addStudent("Bombur");
     jane.addSection( secB3 );
     cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
     moe.addGrade("John", 17, 1);
     moe.addGrade("Paul", 19, 1);
     moe.addGrade("George", 16, 1);
     moe.addGrade("Ringo", 7, 1);
     cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
     moe.addGrade("John", 15, 3);
     moe.addGrade("Paul", 20, 3);
     moe.addGrade("Ringo", 0, 3);
     moe.addGrade("George", 16, 3);
     cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works:\n";
     doNothing(secA2);
     cout << "Back from doNothing\n\n";

} // main

ostream& operator<<(ostream& os, const Time_slot& time){
    os << "Time slot: [Day: " << time.week_day << ", Start time: ";
    if(time.hour_to_start > 12) {
        os << time.hour_to_start - 12 << "pm]" << endl;
    } else {
        os << time.hour_to_start << "am]" << endl;
    }
    return os;
}

ostream& operator<<(ostream& os, const Section& sec){
    if (sec.students.size() == 0) {
        os << "Section: " << sec.section_name << ", " << sec.time_slot
        << "Students: None" << endl;
    } else {
        os << "Section: " << sec.section_name << ", " << sec.time_slot << " Students: " << endl;
        for (size_t index = 0; index < sec.students.size(); index++) {
            cout << *sec.students[index] << endl;
        }
    }
    return os;
}

ostream& operator<<(ostream& os, const Student& student){
    os << "Name: " << student.student_name << ", Grades: ";
    for (size_t index = 0; index < student.student_grade.size(); index++){
        cout << student.student_grade[index] << " ";
    }
    cout << endl;
    return os;
}

ostream& operator<<(ostream& os, const LabWorker& instructor){
    if (instructor.section == nullptr) {
        os << instructor.insrtuctor_name << " does not have a section" << endl;
    } else {
        cout << instructor.insrtuctor_name << "has " << *instructor.section << endl;
    }
    return os;
}


