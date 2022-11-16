/*
  rec08_starter.cpp
  Starter Code for required functionality
  Yes, of course, you may add other methods.
  And no, this won't compile. You have to fix the cyclic association.
 */
//rec08 created by fanyue Meng

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;
class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student* st);
    void removeStudentsFromCourse();

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course* course);

    // Student method needed by Course
    void removedFromCourse(Course*);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string&);
    bool addStudent(const string&);
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;
    
    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}

size_t Registrar::findStudent(const string& student_name) const{
    for (size_t index = 0; index < students.size(); index++){
        if (students[index]->getName() == student_name){
            return index;
        }
    }
    return students.size();
}

size_t Registrar::findCourse(const string& course_name) const{
    for (size_t index = 0; index < courses.size(); index++){
        if(courses[index]->getName() == course_name){
            return index;
        }
    }
    return courses.size();
}

Registrar::Registrar(){}
bool Registrar::addCourse(const string& course_name){
    if (findCourse(course_name) == courses.size()){
        courses.push_back(new Course(course_name));
        return true;
    }
    return false;
}
bool Registrar::addStudent(const string& student_name){
    if (findStudent(student_name) == students.size()){
        students.push_back(new Student(student_name));
        return true;
    }
    return false;
}

bool Registrar::enrollStudentInCourse(const string& studentName,
                                      const string& courseName){
    size_t student_index = findStudent(studentName);
    size_t course_index = findCourse(courseName);
    if (course_index == courses.size() || student_index == students.size()){
        return false;
    }
    courses[course_index]->addStudent(students[student_index]);
    students[student_index]->addCourse(courses[course_index]);
    return true;
}
bool Registrar::cancelCourse(const string& courseName){
    size_t course_index = findCourse(courseName);
    if (course_index == courses.size()){
        return false;
    }
    courses[course_index]->removeStudentsFromCourse();
    delete courses[course_index];
    for (size_t index = course_index; index < courses.size() - 1; index++){
        courses[index] = courses[index+1];
    }
    courses.pop_back();
    return true;
}

void Registrar::purge(){
    for (size_t index = 0; index< courses.size(); index++){
        delete courses[index];
    }
    for (size_t index = 0; index< students.size(); index++){
        delete students[index];
    }
    courses.clear();
    students.clear();
}

Course::Course(const string& courseName) : name(courseName) {}
const string& Course::getName() const{
    return name;
}
bool Course::addStudent(Student* st){
    for (size_t index = 0; index < students.size(); index++){
        if (students[index]->getName() == st->getName()){
            return false;
        }
    }
    students.push_back(st);
    return true;
}

void Course::removeStudentsFromCourse(){
    for (size_t index = 0; index < students.size(); index++){
        students[index]->removedFromCourse(this);
    }
    students.clear();
}

ostream& operator<<(ostream& os, const Course& rhs){
    if (rhs.students.size() == 0){
        os << rhs.name << ": No Students";
    } else {
        os << rhs.name << ": ";
        for (size_t index = 0; index < rhs.students.size(); index++){
            os << rhs.students[index]->getName();
        }
        
    }
    return os;
}

Student::Student(const string& name) : name(name){}
const string& Student::getName() const{
    return name;
}

bool Student::addCourse(Course* course){
    for (size_t index = 0; index < courses.size(); index++){
        if (courses[index]->getName() == course->getName()){
            return false;
        }
    }
    courses.push_back(course);
    return true;
}


void Student::removedFromCourse(Course* course){
    size_t finding_index = courses.size();
    for (size_t index = 0; index < courses.size(); index++){
        if (courses[index]->getName() == course->getName()){
            finding_index = index;
        }
    }
    if (finding_index != courses.size()){
        for (size_t index = finding_index; index + 1< courses.size(); index++){
            courses[index] = courses[index+1];
        }
        courses.pop_back();
    }
}

ostream& operator<<(ostream& os, const Student& rhs){
    if (rhs.courses.size() == 0){
        os << rhs.name << " ";
        os << "No Courses";
    } else {
        os << rhs.name << ": ";
        for (size_t index = 0; index < rhs.courses.size(); index++){
            os << rhs.courses[index]->getName() << " ";
        }
    }
    return os;
}

ostream& operator<<(ostream& os, const Registrar& rhs){
    os << "Registrar's Report" << endl;
    os << "Courses: " << endl;

    for (size_t index = 0; index < rhs.courses.size(); index++){
        os << *rhs.courses[index] << endl;
    }
    os << "Students:  " << endl;
    for (size_t index = 0; index< rhs.students.size(); index++){
        os << *rhs.students[index] << endl;
    }
    return os;
}
