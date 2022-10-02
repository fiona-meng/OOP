// Homework 1: Caesar Cypher
// Fanyue Meng
// Given a file of text that has been encrypted,
// we need to decrypt by according steps


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


char rotateChar(int distance, char encrypted_val);
void rotateLine(int distance, string& encrypted_line);


int main() {
    // open the file and check whether it is opened
    ifstream encrypted_file("encrypted.txt");
    if (!encrypted_file){
        cerr << "Could not open the file.\n";
        exit(1);
    }
    
    int distance;
    encrypted_file >> distance;
    
        
    vector<string> encrypted;
    string line;
    
    
    // The while loop will push content from encrypted_file as a line
    while (getline(encrypted_file, line)) {
        encrypted.push_back(line);
    }
    
    // close the file
    encrypted_file.close();
    
    //The for loop will decrypted the whole vector
    for (size_t index = 0; index < encrypted.size(); ++index) {
        rotateLine(distance, encrypted[index]);
        }
    
    // The for loop will print out content from back
    for (size_t i = encrypted.size() - 1; i > 0 ; --i) {
     cout << encrypted[i] << endl;
     }
}


// The function will decrypted a character according to the rotate distance
// The function take the distant we need to rotate and a character
// The fucntion will return a decrypted character
char rotateChar(int distance, char encrypted_char) {
    char decrypt_val;
    
    // The if-else loop will first check whether the character is uppercase
    // If the character is not uppercase,the character will not be changed
    // If it's a uppercase character, we need to rotate by according steps
    if ('A' <= encrypted_char || encrypted_char >= 'Z') {
        if ((encrypted_char - distance) < 65) {
            decrypt_val = encrypted_char - distance + 26;
        } else if ((encrypted_char - distance) > 90){
            decrypt_val = encrypted_char - distance - 26;
        } else {
            decrypt_val = encrypted_char - distance;
        }
    } else {
        decrypt_val = encrypted_char;
    }
    return decrypt_val;
}


// The function will decrypted a line of character
// by using the function rotate_char
// The function rotateLine will take the distant we need to rotate
// and a line of character
// The function will change the encrypted line of character to decrypted

void rotateLine(int distance, string& encrypted_line) {
    //The for loop will take a line of characters
    //and will use function rotate_char to decrypted every character
    for (size_t index = 0; index < encrypted_line.size(); ++index){
        encrypted_line[index] = rotateChar(distance, encrypted_line[index]);
        
    }
}
