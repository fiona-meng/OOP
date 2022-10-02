//
//  rec02.cpp
//  2124
//
//  Created by fiona meng on 2022/9/9.
//

// Conway's Game of life
// by Fanyue Meng
// The program will create a game which will have living cell and dead cell
// Each genergation will be different according to the world' rule


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ifstream int_world("life.txt");
    if (!int_world){
        cerr << "Could not open the file.\n";
        exit(1);
    }
    cout << "inital world.\n";
    
    vector<string> world;
    string val;
    while (int_world >> val){
        world.push_back(val);
    }
    int_world.close();
    
    for (size_t i = 0; i < world.size(); ++i) {
        cout << world[i] << endl;
    }
    
    size_t world_size_x = world.size();
    size_t world_size_y = world[0].size();
    
    for (int w = 0; w < 10; ++w){
        
        vector<string> newworld = world;
        
        for (size_t i = 0; i < world_size_x; ++i){
            for (size_t j = 0; j < world_size_y; ++j){
                int neighbors = 0;
    //            if (i > 0 && j > 0 && i < world_size_y && j < world_size_x){
                    if (i>0 && j >0 && world[i - 1][j - 1] == '*'){
                        neighbors = neighbors + 1;
                    }
                    
                    if (i > 0 && world[i - 1][j] == '*'){
                        neighbors = neighbors + 1;
                    }
                    
                    if (i > 0 && j < world_size_y && world[i - 1][j + 1] == '*'){
                        neighbors = neighbors + 1;
                    }
                    
                    if (j > 0 && world[i][j - 1] == '*'){
                        neighbors = neighbors + 1;
                    }
                    
                    if (j < world_size_y && world[i][j + 1] == '*'){
                        neighbors = neighbors + 1;
                    }
                    
                    if (i < world_size_x && j > 0 && world[i + 1][j - 1] == '*'){
                        neighbors = neighbors + 1;
                    }
                    
                    if (j < world_size_y && world[i + 1][j] == '*'){
                        neighbors = neighbors + 1;
                    }
                    
                    if (i < world_size_x && j < world_size_y && world[i + 1][j + 1] == '*'){
                        neighbors = neighbors + 1;
                    }
                    
                    if (world[i][j] == '*')
                    {
                        if(neighbors < 2 || neighbors > 3)
                        {
                            newworld[i][j] =  '-';
                        }
                    }
                    else{
                        if(neighbors == 3)
                        {
                            newworld[i][j] = '*';
                        }
                    }
                
                    
                
            }
        }
        world = newworld;
        cout << "=================="<<endl;
        cout << "Generation " << w+1 << endl;
        for (size_t i = 0; i < world.size(); ++i) {
            cout << world[i] << endl;
        }
    }
}

