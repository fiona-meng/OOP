
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

#include <cstdlib>

//
//         From linked list library in the course's sample code
//
struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};


//
//          Solution to recitation goes here:
//            (const on Node* is optional)

// Inserts the list toSplice after prior.
// We assume that neither toSplice nor prior is null
// This is a destructive function. Both toSplice and the Node pointed
// to by prior are modifed.
void splice(Node* toSplice, Node* prior){
    Node* old_next = prior->next;
    prior->next = toSplice;
    Node* curr = toSplice;
    while (curr->next != nullptr){
        curr = curr->next;
    }
    curr->next = old_next;
}

// Does the sequence of data VALUES in pattern appear anywhere contiguously
// in that order in target?
// Return the position where a match is found, otherwise null.
Node* isSublist(Node* pattern, Node* target);
const Node* isSublist(const Node* pattern, const Node* target){
    if (pattern == nullptr) {
        return target;
    }
    if (target == nullptr) {
        return nullptr;
    }
    const Node* result = nullptr;
    while (target != nullptr){
        const Node* pattern_copy = pattern;
        if (target->data == pattern_copy->data){
            const Node* result_pointer = target;
            const Node* curr_target = target;
            const Node* curr_pattern = pattern;
            bool matched = true;
            while (curr_pattern != nullptr && matched){
                if (curr_target == nullptr){
                    matched = false;
                }
                if (matched) {
                    if (curr_target->data == curr_pattern->data){
                        curr_target = curr_target->next;
                        curr_pattern = curr_pattern->next;
                    } else {
                        matched = false;
                    }
                }
            }
            if (matched == true) {
                return result_pointer;
            }
        }
        target = target->next;
    }
    return result;
}

// test the nodes in listB looking for the first one to match a node
// from listA. Note that we are matching the addresses of the nodes,
// not the data they hold.
//Node* sharedListBruteForce(Node* listA, Node* listB);
const Node* sharedListBruteForce(const Node* listA, const Node* listB){
    const Node* curr_A = listA;
    while (curr_A){
        const Node* curr_B = listB;
        while(curr_B){
            if (curr_A == curr_B){
                return curr_B;
            }
            curr_B = curr_B->next;
        }
        curr_A = curr_A->next;
    }
    return nullptr;
}

// Use an "unordered set", i.e. a hashtable, to identify the first
// element in listB that is also in listA.
//Node* sharedListUsingSet(Node* listA, Node* listB);
const Node* sharedListUsingSet(const Node* listA, const Node* listB){
    unordered_set<const Node*> stuff;
    while(listA){
        stuff.insert(listA);
        listA = listA->next;
    }
    while(listB){
        if (stuff.find(listB) != stuff.end()){
            return listB;
        }
        listB = listB->next;
    }
    return nullptr;
}



///////////////////////////////////////////////////////////////////////////////
//
// Provided test code
//
void listAddHead(Node*& headPtr, int entry);
void listPrint(const Node* headPtr);
void listClear(Node*& headPtr);
Node* listBuild(const vector<int>& vals);
void match(const Node* target, const Node* pattern);

int main() {
    Node* listOne = listBuild({5,7,9,1});

    Node* listTwo = listBuild({6,3,2});

    cout << "Part One:\n\n";
    cout << "L1: ";
    listPrint(listOne);
    cout << "L2: ";
    listPrint(listTwo);

    Node* target = listOne->next;
    cout << "Target: ";
    listPrint(target);


    cout << "Splicing L2 at target in L1\n";
    splice(listTwo, target);
    cout << "L1: ";
    listPrint(listOne);
    cout << "L2: ";
    listPrint(listTwo);

    listClear(listOne);
    // Since listTwo is now part of listOne, we have already cleared it
//    listClear(listTwo);

    cout << "=====================\n\n"
         << "Part two: \n\n";

    // Target: 1 2 3 2 3 2 4 5 6
    target = listBuild({1, 2, 3, 2, 3, 2, 4, 5, 6});
    cout << "Target: ";
    listPrint(target);
    cout << endl;

    // Attempt Match: 1
    // Node* m1 = nullptr;
    Node* m1 = listBuild({1});
    match(target, m1);
    listClear(m1);

    // Attempt Match: 3 9
    // Node* m2 = nullptr;
    Node* m2 = listBuild({3, 9});
    match(target, m2);
    listClear(m2);

    // Attempt Match: 2 3
    // Node* m3 = nullptr;
    Node* m3 = listBuild({2, 3});
    match(target, m3);
    listClear(m3);

    // Attempt Match: 2 4 5 6
    Node* m4 = listBuild({2, 4, 5, 6});
    match(target, m4);
    listClear(m4);

    // Attempt Match: 2 3 2 4
    Node* m5 = listBuild({2, 3, 2, 4});
    match(target, m5);
    listClear(m5);

    // Attempt Match: 5 6 7
    Node* m6 = listBuild({5, 6, 7});
    match(target, m6);
    listClear(m6);

    // Attempt Match:
    m1 = listBuild({6});
    match(target, m1);
    listClear(m1);

    // Attempt Match:
    m1 = nullptr;
    match(target, m1);

    cout << "Task Three\n";
    cout << "Target: ";
    listPrint(target);

    cout << "Matching target against self:\n";
    cout << "Brute force: ";
    listPrint(sharedListBruteForce(target, target));
    cout << "Using Set:   ";
    listPrint(sharedListUsingSet(target, target));

    cout << "Matching target against dup of self:\n";
    //Node* dupOfTarget = listDup(target);
    Node* dupOfTarget = listBuild({1, 2, 3, 2, 3, 2, 4, 5, 6});
    cout << "Brute force: ";
    listPrint(sharedListBruteForce(target, dupOfTarget));
    cout << "Using Set:   ";
    listPrint(sharedListUsingSet(target, dupOfTarget));
    listClear(dupOfTarget);

    cout << "Matching target against part of self from fourth node:\n";
    cout << "Brute force: ";
    listPrint(sharedListBruteForce(target, target->next->next->next));
    cout << "Using Set:   ";
    listPrint(sharedListUsingSet(target, target->next->next->next));

    cout << "testing against another list whose fourth node"
         << " matches target's fifth node\n";
    Node* another = target->next->next->next->next;
    listAddHead(another, 7);
    listAddHead(another, 6);
    listAddHead(another, 5);
    cout << "other list:\n";
    listPrint(another);

    cout << "Brute force: ";
    const Node* startOfShared = sharedListBruteForce(target, another);
    listPrint(startOfShared);

    cout << "Using Set:   ";
    startOfShared = sharedListUsingSet(target, another);
    listPrint(startOfShared);

    // Clean up
    listClear(target);
    for (Node* p = another; p != startOfShared; ) {
    Node* pNext = p->next;
        delete p;
    p = pNext;
    }

} // main

//
// Functions for test code
//

// match the target with the pattern. Calls isSublist to do the work.
void match(const Node* target, const Node* pattern) {
    cout << "Attempt pattern: ";
    listPrint(pattern);
    const Node* result = isSublist(pattern, target);
    if (result)
        listPrint(result);
    else
        cout << "Failed to match\n";
    cout << endl;
} // match

void listAddHead(Node*& headPtr, int entry) {
    headPtr = new Node(entry, headPtr);
} // listAddHead

// listPrint prints out the data values in the list.
// All the values are printed on a single line with blanks separating them.
void listPrint(const Node* headPtr) {
    const Node* p = headPtr;
    //    while (p != NULL) {
    while (p != nullptr) {
        cout << p->data << ' ';
        // that you know why!
        p = p->next;
    }
    cout << endl;
} // listPrint

// Need to add this to the provided functions
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
} // listClear

Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listAddHead(result, vals[index-1]);
    }
    return result;
} // listBuild
