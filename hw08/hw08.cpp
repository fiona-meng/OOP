// Hw08 created by Fanyue Meng
//#include "polynomial.h"
#include <iostream>
#include <vector>
using namespace std;


class Polynomial{
    // definition of Node
    struct Node;
    // output operator
    friend ostream& operator<<(ostream& os, const Polynomial& rhs);
    // equal operator
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
public:
    //default constructor
    Polynomial();
    // constructor that takes a vector
    Polynomial(const vector<int>& input);
    // destructor
    ~Polynomial();
    // copy constructor
    Polynomial(const Polynomial& rhs);
    // assignment operator
    Polynomial& operator=(const Polynomial& rhs);
    // += operator
    Polynomial& operator+=(const Polynomial& rhs);
    // evaluate
    int evaluate(int val) const;
    // clear up zeros
    void clearup();
    
private:
    size_t degree = 0;
    Node* header;
};

struct Polynomial::Node{
    Node(int node_data = 0, Node* next = nullptr) : data(node_data), next(next) {}
    int data;
    Node* next;
};

void doNothing(Polynomial temp) {}
bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
    return !(lhs == rhs);
}
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
    Polynomial result(lhs);
    result += rhs;
    return result;
}

Polynomial::Polynomial(){
    header = new Node();
}

Polynomial::Polynomial(const vector<int>& input){
    if (input.size() > 0){
        header = new Node(input[0]);
        Node* curr = header;
        for (size_t index = 1; index < input.size(); index++){
            curr->next = new Node(input[index]);
            curr = curr->next;
            degree += 1;
        }
        clearup();
    } else {
        header = new Node();
    }
}

Polynomial::~Polynomial(){
    Node* curr = header;
    while (curr != nullptr){
        Node* deleted_node = curr;
        curr = curr->next;
        delete deleted_node;
    }
}

Polynomial::Polynomial(const Polynomial& rhs) : degree(rhs.degree){
    header = new Node(rhs.header->data);
    const Node* rhs_curr = rhs.header->next;
    Node* lhs_curr = header;
    while (rhs_curr != nullptr){
        lhs_curr->next = new Node(rhs_curr->data);
        lhs_curr = lhs_curr->next;
        rhs_curr = rhs_curr->next;
    }
}
Polynomial& Polynomial::operator=(const Polynomial& rhs){
    if (this != &rhs){
        Node* lhs_curr = header;
        while (lhs_curr != nullptr){
            Node* deleted_node = lhs_curr;
            lhs_curr = lhs_curr->next;
            delete deleted_node;
        }
        header = new Node(rhs.header->data);
        const Node* rhs_curr = rhs.header->next;
        Node* lhs_curr_add = header;
        while (rhs_curr != nullptr){
            lhs_curr_add->next = new Node(rhs_curr->data);
            lhs_curr_add = lhs_curr_add->next;
            rhs_curr = rhs_curr->next;
        }
        degree = rhs.degree;
    }
    return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& rhs){
    Node* lhs_curr = header;
    const Node* rhs_curr = rhs.header;
    if (degree < rhs.degree){
        size_t difference = rhs.degree - degree;
        for(size_t index = 0; index < difference; index++){
            Node* empty = new Node(0, header);
            header = empty;
            lhs_curr = empty;
            degree += 1;
        }
    } else if (degree > rhs.degree){
        size_t difference = degree - rhs.degree;
        for(size_t index = 0; index < difference; index++){
            lhs_curr = lhs_curr->next;
        }
    }
    for(Node* p = lhs_curr; p; p = p->next){
        p->data += rhs_curr->data;
        rhs_curr = rhs_curr->next;
    }
    clearup();
    return *this;
}

int Polynomial::evaluate(int val) const {
    int result = 0;
    const Node* curr = header;
    size_t curr_degree = degree;
    while (curr != nullptr){
        if (curr_degree == 0){
            result += curr->data;
        } else{
            int power_result = 1;
            for (size_t index = 0; index < curr_degree; index++){
                power_result *= val;
            }
            result += curr->data * power_result;
            curr_degree -= 1;
        }
        curr = curr->next;
    }
    return result;
}

void Polynomial::clearup(){
    if (degree == 0){
        return;
    }
    while (header->data == 0 && header->next != nullptr){
        header = header->next;
        degree -= 1;
    }
    
}

ostream& operator<<(ostream& os, const Polynomial& rhs){
    const Polynomial::Node* curr = rhs.header;
    if (curr == nullptr){
        os << "0";
    }
    int count = 0;
    while (count < rhs.degree + 1){
        if (count == rhs.degree){
            os << curr->data;
        } else if (count == rhs.degree - 1){
            if (curr->data != 1){
                os << curr->data << "x + ";
            } else {
                os << "x + ";
            }
        } else if (curr->data != 0){
            if (curr->data != 1){
                os << curr->data << "x^" << rhs.degree - count << " + ";
            } else {
                os << "x^" << rhs.degree - count << " + ";
            }
        }
        curr = curr->next;
        count += 1;
    }
    return os;
}

bool operator==(const Polynomial& lhs, const Polynomial& rhs){
    if (lhs.degree == rhs.degree){
        const Polynomial::Node* lhs_curr = lhs.header;
        const Polynomial::Node* rhs_curr = rhs.header;
        while(lhs_curr != nullptr){
            if (lhs_curr->data != rhs_curr->data){
                return false;
            }
            lhs_curr = lhs_curr->next;
            rhs_curr = rhs_curr->next;
        }
        return true;
    }
    return false;
}

int main() {
    
    //test constructor
    Polynomial p1({17});                 // 17
    Polynomial p2({1, 2});               // x + 2
    Polynomial p3({-1, 5});              // -x + 5
    Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    Polynomial has_a_zero({4, 0, 1, 7}); // 4x^3 + x + 7

    Polynomial temp(p4);
    cout << "temp: " << temp << endl;
    
    //    cerr << "displaying polynomials\n";
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3: " << p3 << endl;
    cout << "p4: " << p4 << endl;
    cout << "has_a_zero: " << has_a_zero << endl;
    
    // Polynomial temp;
     temp = p2 + p3;
     cout << "temp: " << temp << endl;

    cout << "p2 + p3: " << (p2+p3) << endl;
    cout << "p2 + p4: " << (p2+p4) << endl;
    cout << "p4 + p2: " << (p4+p2) << endl;

//    //test copy constructor - the statement below uses the copy constructor
//    //to initialize poly3 with the same values as poly4
    Polynomial p5(p4);
    p5 += p3;
    cout << "Polynomial p5(p4);\n"
         << "p5 += p3;\n";

    cout << "p4: " << p4 << endl;
    cout << "p5: " << p5 << endl;


    cout << "Calling doNothing(p5)\n";
    doNothing(p5);
    cout << "p5: " << p5 << endl;

    //tests the assignment operator
    Polynomial p6;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;  // Causes bools true and false to be printed that way.
    cout << "(p4 == p6) is " << (p4 == p6) << endl;
    p6 = p4;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;
    cout << "(p4 == p6) is " << (p4 == p6) << endl;

    //test the evaluaton
    int x = 5;
    cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(5) << endl;
    cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(5) << endl;

    Polynomial p7({3, 2, 1});           // 3x^2 + 2x + 1
    cout << "p7: " << p7 << endl;
    cout << "Evaluating p7 at " << x << " yields: " << p7.evaluate(5) << endl;

    cout << boolalpha;
    cout << "(p1 == p2) is " << (p1 == p2) << endl;
    cout << "(p1 != p2) is " << (p1 != p2) << endl;

    /*=================================================================
    NEW TEST CODE - test if cleaning the leading 0s
    ===================================================================*/

    Polynomial p8({ 1, 1 });
    Polynomial p9({ -1, 1 });
    Polynomial p10({ 0, 0, 2 });
    //p8 + p9 tests if += does the cleanup()
    //p10 tests if constructor does the cleanup()
    cout << "((p8 + p9) == p10) is " << ((p8 + p9) == p10) << endl;


}
