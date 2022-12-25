// created by Fanyue Meng
// rec14_test.cpp

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

// Task9
void print_lst(const list<int>& lst){
    for (list<int>::const_iterator iter = lst.begin(); iter != lst.end(); ++iter){
        cout << *iter << " ";
    }
    cout << endl;
}

// Task10
void print_lst2(const list<int>& lst){
    for(int val: lst){
        cout << val << " ";
    }
    cout << endl;
}

// Task11
void print_lst_auto(const list<int>& lst){
    for(auto iter = lst.begin(); iter != lst.end(); ++++iter){
        cout << *iter << " ";
    }
    cout << endl;
}

// Task12
list<int>::const_iterator find_item(const list<int>& lst, int target){
    for(list<int>::const_iterator iter = lst.begin(); iter != lst.end(); ++iter){
        if (*iter == target){
            return iter;
        }
    }
    return lst.end();
}

// Task13
auto find_item_v2(const list<int>& lst, int target){
    for(auto iter = lst.begin(); iter != lst.end(); ++iter){
        if (*iter == target){
            return iter;
        }
    }
    return lst.end();
}

// Task15
bool is_even(int n){
    if (n % 2 == 0){
        return true;
    }
    return false;
}
// Task16
class even{
public:
    bool operator()(int n) const{
        if (n % 2 == 0){
            return true;
        }
        return false;
    }
};

// Task19
// Task20
template <typename first, typename second>
first ourFind(first begin, first end, const second& target){
    for(first iter = begin; iter != end; ++iter){
        if (*iter == target){
            return iter;
        }
    }
    return end;
}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> vec = {7, 3, 11, 4, 5, 9};
    for (int val: vec){
        cout << val << " ";
    }
    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    std::list<int> lst(vec.begin(), vec.end());
    for (int val : lst){
        cout << val << " ";
    }
    
    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(vec.begin(), vec.end());
    for (int val : vec){
        cout << val << " ";
    }
    cout << endl;
    for (int val : lst){
        cout << val << " ";
    }
    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t index = 0; index < vec.size(); index += 2){
        cout << vec[index] << " ";
    }
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
//    for (size_t index = 0; index < lst.size(); index += 2){
//        cout << lst[index] << " ";
//    }
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for (vector<int>::iterator iter = vec.begin(); iter != vec.end(); iter+=2){
        cout << *iter << " ";
    }
    

    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    for (list<int>::iterator iter = lst.begin(); iter != lst.end(); ++++iter){
        cout << *iter << " ";
    }
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    lst.sort();
    for (int val : lst){
        cout << val << " ";
    }
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    print_lst(lst);
    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    print_lst2(lst);
    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    print_lst_auto(lst);
    cout << "=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    
    if (find_item(lst, 7) == lst.end()){
        cout << "7 has not been found" << endl;
    }else {
        cout << *find_item(lst, 7) << " has been found" << endl;
    }
//    cout << *find_item(lst, 7) << " ";
//    cout << *find_item(lst, 2) << " ";
    cout << endl;
    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    if (find_item_v2(lst, 7) == lst.end()){
        cout << "7 has not been found" << endl;
    }else {
        cout << *find_item_v2(lst, 7) << " has been found" << endl;
    }
    cout << endl;
    cout << "=======\n";

    //
    // Generic Algorithms
    //
    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    if (find(lst.begin(), lst.end(), 7) == lst.end()){
        cout << "7 has not been found" << endl;
    }else {
        cout << *find(lst.begin(), lst.end(), 7) << " has been found" << endl;
    }
    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    if (find_if(lst.begin(), lst.end(), is_even) == lst.end()){
        cout << "Even number does not exist" << endl;
    } else {
        cout << *find_if(lst.begin(), lst.end(), is_even) << endl;
    }
    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    if (find_if(lst.begin(), lst.end(), even()) == lst.end()){
        cout << "Even number does not exist" << endl;
    } else {
        cout << *find_if(lst.begin(), lst.end(), even()) << endl;
    }
    cout << "=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    // no parameter
    [] { cout << "Hello Lambda!"; }();
    cout << endl;
    // has parameter
    [] (int a, int b) { cout << a + b << endl; } (4, 5);
    // return the sum instead of printing it
    int result = [] (int a, int b) { return a + b; } (4, 5);
    cout << "the result is: " << result << endl;
    // want to say what the return type for that lambda expression
    int result2 = [] (int a, int b) -> int { return a + b; } (4, 5);
    cout << "the result is: " << result2 << endl;
    // lambda expression
    [] (int n) {return n % 2 == 0;}(2);
    if (find_if(lst.begin(), lst.end(), [] (int n) {return n % 2 == 0;}) == lst.end()){
        cout << "Even number does not exist" << endl;
    } else {
        cout << *find_if(lst.begin(), lst.end(), [] (int n) {return n % 2 == 0;}) << endl;
    }
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* array = new int[lst.size()];
    copy(lst.begin(), lst.end(), array);
    for (size_t index = 0; index < lst.size(); ++index){
        cout << array[index] << " ";
    }
    cout << endl;
    if (find(array, array + 6, 2) == array + 6){
        cout << "Does not found" << endl;
    } else {
        cout << *find(array, array + 6, 2) << endl;
    }
    delete [] array;
    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    cout << *ourFind(lst.begin(), lst.end(), 4) << endl;
    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    cout << *ourFind(lst.begin(), lst.end(), 4) << endl;
    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    vector<string> strings;
    ifstream ifs("pooh-nopunc.txt");
    string word;
    while(ifs>>word){
        if (find(strings.begin(), strings.end(), word) == strings.end()){
            strings.push_back(word);
        }
    }
    cout << "size: " << strings.size() << endl;
    ifs.close();
    for(size_t index = 0; index < strings.size(); ++index){
        cout << strings[index] << " ";
    }
    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    ifstream ifs2("pooh-nopunc.txt");
    string word2;
    set<string> set_container;
    while(ifs2>>word2){
        if (set_container.find(word2) == set_container.end()){
            set_container.insert(word2);
        }
    }
    cout << "size: " << set_container.size() << endl;
    ifs2.close();
    for(const string& word : set_container){
        cout << word << " ";
    }
    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    ifstream ifs3("pooh-nopunc.txt");
    string word3;
    map<string, vector<int>> wordMap;
    int index = 0;
    while(ifs3>>word3){
        wordMap[word3].push_back(index);
        index++;
    }
    cout << wordMap.size() << endl;
    ifs3.close();
    for (auto val: wordMap){
        cout << val.first << " : ";
        for (auto pos : val.second){
            cout << pos << " ";
        }
        cout << endl;
    }
    cout << "=======\n";
}

