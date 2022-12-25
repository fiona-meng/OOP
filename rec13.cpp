// Rec13 created by Fanyue Meng
// Doubly linked list
//  Test code

#include <cstdlib>
#include <iostream>
using namespace std;


class List {
    struct Node{
        Node(int data = 0, Node* prior = nullptr, Node* next = nullptr) : data(data), prior(prior), next(next) {}
        int data;
        Node* prior;
        Node* next;
    };
    
    friend ostream& operator<<(ostream& os, const List& lst){
        const Node* curr = lst.header->next;
        while(curr != lst.trailer){
            os << curr->data << ' ';
            curr = curr->next;
        }
        return os;
    }
public:
    class iterator{
        friend List;
        friend bool operator==(const iterator& lhs, const iterator& rhs){
            return (lhs.node == rhs.node);
        }
    public:
        iterator(Node* node) : node(node){}
        iterator& operator++(){
            node = node->next;
            return *this;
        }
        iterator& operator--(){
            node = node->prior;
            return *this;
        }
        int& operator*() const{
            return node->data;
        }
    private:
        Node* node;
    };

    List() : lst_size(0) {
        header = new Node();
        trailer = new Node(0, header, nullptr);
        header->next = trailer;
    }
    void push_back(int data) {
        Node* new_node = new Node(data, trailer->prior, trailer);
        new_node->prior->next = new_node;
        new_node->next->prior = new_node;
        lst_size++;
    }
    void pop_back(){
        if (lst_size > 0){
            Node* removed_node = trailer->prior;
            Node* prior_removed_node = removed_node->prior;
            prior_removed_node->next = trailer;
            trailer->prior = prior_removed_node;
            delete removed_node;
            lst_size--;
        }
    }
    
    int front() const{
        return header->next->data;
    }
    
    int& front() {
        return header->next->data;
    }
    
    int back() const{
        return trailer->prior->data;
    }
    
    int& back() {
        return trailer->prior->data;
    }
    
    size_t size() const {
        return lst_size;
    }
    void push_front(int data) {
        Node* new_node = new Node(data, header, header->next);
        new_node->prior->next = new_node;
        new_node->next->prior = new_node;
        lst_size++;
    }
    void pop_front() {
        if (lst_size > 0){
            Node* removed_node = header->next;
            header->next = removed_node->next;
            removed_node->next->prior = header;
            delete removed_node;
            lst_size--;
        }
    }
    void clear() {
        while (lst_size > 0) {
            pop_back();
        }
    }
    
    int operator[](size_t i) const{
        const Node* curr = header->next;
        for (size_t index = 0; index < i; index++){
            curr = curr->next;
        }
        return curr->data;
    }
    
    int& operator[](size_t i) {
        Node* curr = header->next;
        for (size_t index = 0; index < i; index++){
            curr = curr->next;
        }
        return curr->data;
    }
    iterator begin() const {
        return iterator(header->next);
    }
    iterator end() const {
        return iterator(trailer);
    }
    iterator insert(iterator iter, int data){
        Node* curr = iter.node;
        Node* new_node = new Node(data, curr->prior, curr);
        new_node->prior->next = new_node;
        new_node->next->prior = new_node;
        lst_size++;
        return iter.operator--();
    }
    iterator erase(iterator iter){
        Node* curr = iter.node;
        curr->prior->next = curr->next;
        curr->next->prior = curr->prior;
        delete curr;
        lst_size--;
        return iter.operator++();
    }
private:
    size_t lst_size;
    Node* header;
    Node* trailer;
};

// Task 1
void printListInfo(const List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList){
//     theList.front() = 17;
//     theList.back() = 42;
// }

void changeFrontAndBack(List& theList){
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

//// Task 8
//void doNothing(List aList) {
//    cout << "In doNothing\n";
//    printListInfo(aList);
//    cout << endl;
//    cout << "Leaving doNothing\n";
//}
bool operator!=(const List::iterator& lhs, const List::iterator& rhs){
    return !(lhs == rhs);
}
int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    printListInfo(myList);
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);


    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

//    // Task 8
//    cout << "\n------Task Eight------\n";
//    cout << "Copy control\n";
//    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
//    myList.clear();
//    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
//    printListInfo(myList);
//    cout << "Calling doNothing(myList)\n";
//    doNothing(myList);
//    cout << "Back from doNothing(myList)\n";
//    printListInfo(myList);
//
//    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
//    List listTwo;
//    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
//    printListInfo(listTwo);
//    cout << "listTwo = myList\n";
//    listTwo = myList;
//    cout << "myList: ";
//    printListInfo(myList);
//    cout << "listTwo: ";
//    printListInfo(listTwo);
//    cout << "===================\n";
}
