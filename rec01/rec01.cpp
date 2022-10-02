// rec01_start.cpp
// 2124 22F

#include <iostream> // Tasks 3, 4, 5 and 6
#include <fstream>  // Task 4, 5 and 6
#include <string>   // Task 5
using namespace std;

int main()
{
    // Task 3
    cout << "Task 3\n========\n";
    // Put code for Task 3 here
    cout << "Yay C++!!!\n";

    // Task 4
    cout << "\nTask 4\n========\n";
    // Put code for Task 4 here
    ifstream ifs("integers.txt");

    int anInt;
    int sum = 0;
    while (ifs >> anInt)
    {
        // cout << anInt << endl;
        sum = sum + anInt;
    }
    cout << sum;

    // Task 5
    cout << "\nTask 5\n========\n";
    // Put code for Task 5 here
    ifstream ifss("text.txt");
    if (!ifss)
    {
        cerr << "Could not open the file.\n";
        exit(1);
    }
    string text;
    while (ifss >> text)
    {
        cout << text << endl;
    }
    ifss.close();
    // Task 6
    cout << "\nTask 6\n========\n";
    // Put code for Task 6 here
    ifstream mix("mixed.txt");
    int y;
    int sum_y = 0;
    while (mix >> y)
    {
        sum_y = sum_y + y;
    }
    cout << sum_y;
}


