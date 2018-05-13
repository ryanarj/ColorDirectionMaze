#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
#include <cstring>
#include <fstream>
using namespace std;

struct Obj{
    int row;
    int column;
    int output;
    string result;
};

// Override the greater than
bool operator < (const Obj&x, const Obj&y);

int main(int argc, char **argv){
    
    // Get the input and output file
    ofstream fileOut;
    ifstream fileIn;
    fileIn.open(argv[1],fstream::in);
    fileOut.open(argv[2],fstream::out);
    
    // Get the indexes
    int NIndex, MIndex;
    fileIn >> NIndex>> MIndex;
    pair<int,int> matrix[NIndex][MIndex];
    string str;
    
    // Get the indexes
    for(int i=0; i<NIndex; i++){
        for(int j=0; j<MIndex; j++){
            fileIn >> str;
            if(str[0] == 'R'){
                matrix[i][j].first=0;
            }else if(str[0] == 'B'){
                matrix[i][j].first=1;
            }else{
                matrix[i][j].first=2;
                continue;}
            
            // Get the string is 3
            if(str.size()==3){
                
                // Get the directions an put it in the second
                if(str[2]=='E'){
                    matrix[i][j].second=0;
                }else if(str[2]=='W'){
                    matrix[i][j].second=1;
                }else if(str[2]=='N'){
                    matrix[i][j].second=2;
                } else matrix[i][j].second=3;
            }else{
                // Get the direction of the other directions
                if(str[2]=='S' && str[3]=='E'){
                    matrix[i][j].second=4;
                }else if(str[2]=='N' && str[3]=='E'){
                    matrix[i][j].second=5;
                }else if(str[2]=='S' && str[3]=='W'){
                    matrix[i][j].second=6;
                }else matrix[i][j].second=7;
            }
        }
    }
    
    // Create the visited matrix
    bool visited[NIndex][MIndex];
    memset(visited, false, sizeof(visited));
    priority_queue<Obj> queue;
    Obj current;
    current.row = 0;
    current.column = 0;
    current.output = 0;
    current.result = "";
    
    // Push the current the value
    queue.push(current);
    while(!queue.empty()){
        current=queue.top();
        queue.pop();
        if(visited[current.row][current.column])
            continue;
        
        // Set the visited
        visited[current.row][current.column]=true;
        if(matrix[current.row][current.column].first==2){
            fileOut<<current.result<<endl;
            return 0;
        }
        
        // Check the east
        if(matrix[current.row][current.column].second == 0){
            for(int i=1;i+current.column<MIndex;i++){
                if(matrix[current.row][current.column].first != matrix[current.row][current.column+i].first){
                    
                    // Count the white spaces
                    int paces = i;
                    string blank = "";
                    while(paces > 0){
                        blank += " ";
                        blank[blank.size()-1] = (paces%10)+'0';
                        paces /= 10;
                    }
                    
                    // Reverse the blank and get the next node
                    reverse(blank.begin(),blank.end());
                    Obj NextNode;
                    NextNode.row = current.row;
                    NextNode.column = current.column+i;
                    NextNode.output = current.output+i;
                    NextNode.result = current.result +blank + "E ";
                    queue.push(NextNode);
                }
            }
        }
        
        // Check the west
        if(matrix[current.row][current.column].second == 1){
            for(int i=1;current.column-i>=0;i++){
                if(matrix[current.row][current.column].first!=matrix[current.row][current.column-i].first){
                    // Count the white spaces
                    int paces = i;
                    string blank = "";
                    while(paces > 0){
                        blank += " ";
                        blank[blank.size()-1]=(paces%10)+'0';
                        paces /= 10;
                    }
                    
                    // Reverse the blank and get the next node
                    reverse(blank.begin(),blank.end());
                    Obj NextNode;
                    NextNode.row = current.row;
                    NextNode.column = current.column-i;
                    NextNode.output = current.output+i;
                    NextNode.result = current.result +blank + "W ";
                    queue.push(NextNode);
                }
            }
        }
        
        // Check the north
        if(matrix[current.row][current.column].second == 2){
            for(int i=1;current.row-i>=0;i++){
                if(matrix[current.row][current.column].first != matrix[current.row-i][current.column].first){
                    // Count the white spaces
                    int paces = i;
                    string blank = "";
                    while(paces>0){
                        blank += " ";
                        blank[blank.size()-1] = (paces%10)+'0';
                        paces/=10;
                    }
                    // Reverse the blank and get the next node
                    reverse(blank.begin(),blank.end());
                    Obj NextNode;
                    NextNode.row = current.row-i;
                    NextNode.column = current.column;
                    NextNode.output = current.output+i;
                    NextNode.result = current.result +blank + "N ";
                    queue.push(NextNode);
                }
            }
        }
        //3 S travel
        if(matrix[current.row][current.column].second == 3){
            for(int i=1;current.row+i<NIndex;i++){
                if(matrix[current.row][current.column].first!=matrix[current.row+i][current.column].first){
                    // Count the white spaces
                    int paces = i;
                    string blank="";
                    while(paces>0){
                        blank+=" ";
                        blank[blank.size()-1]=(paces%10)+'0';
                        paces/=10;
                    }
                    
                    // Reverse the blank and get the next node
                    reverse(blank.begin(),blank.end());
                    Obj NextNode;
                    NextNode.row = current.row+i;
                    NextNode.column = current.column;
                    NextNode.output = current.output+i;
                    NextNode.result = current.result +blank + "S ";
                    queue.push(NextNode);
                }
            }
        }
        // Check the South East
        if(matrix[current.row][current.column].second == 4){
            for(int i=1;current.row+i<NIndex&& current.column+i<MIndex;i++){
                if(matrix[current.row][current.column].first!=matrix[current.row+i][current.column+i].first){
                    // Count the white spaces
                    int paces = i;
                    string blank = "";
                    while(paces > 0){
                        blank += " ";
                        blank[blank.size()-1]=(paces%10)+'0';
                        paces/=10;
                    }
                    
                    // Reverse the blank and get the next node
                    reverse(blank.begin(),blank.end());
                    Obj NextNode;
                    NextNode.row = current.row+i;
                    NextNode.column = current.column+i;
                    NextNode.output = current.output+i;
                    NextNode.result = current.result +blank + "SE ";
                    queue.push(NextNode);
                }
            }
        }
        
        // Check the north east
        if(matrix[current.row][current.column].second == 5){
            for(int i=1;current.row-i>=0 && current.column+i<MIndex;i++){
                if(matrix[current.row][current.column].first!=matrix[current.row-i][current.column+i].first){
                    // Count the white spaces
                    int paces = i;
                    string blank="";
                    while(paces>0){
                        blank+=" ";
                        blank[blank.size()-1]=(paces%10)+'0';
                        paces/=10;
                    }
                    
                    // Reverse the blank and get the next node
                    reverse(blank.begin(),blank.end());
                    Obj NextNode;
                    NextNode.row = current.row-i;
                    NextNode.column = current.column+i;
                    NextNode.output = current.output+i;
                    NextNode.result = current.result + blank + "NE ";
                    queue.push(NextNode);
                }
            }
        }
        
        // Go south west
        if(matrix[current.row][current.column].second == 6){
            for(int i=1; current.row + i < NIndex && current.column-i >= 0;i++){
                if(matrix[current.row][current.column].first != matrix[current.row+i][current.column-i].first){
                    
                    // Count the white spaces
                    int paces = i;
                    string blank = "";
                    while(paces>0){
                        blank += " ";
                        blank[blank.size()-1]=(paces%10)+'0';
                        paces/=10;
                    }
                    
                    // Reverse the blank and get the next node
                    reverse(blank.begin(),blank.end());
                    Obj NextNode;
                    NextNode.row = current.row+i;
                    NextNode.column = current.column-i;
                    NextNode.output = current.output+i;
                    NextNode.result = current.result +blank + "SW ";
                    queue.push(NextNode);
                }
            }
        }
        
        // Go north west
        if(matrix[current.row][current.column].second == 7){
            for(int i=1;current.row-i>=0 && current.column-i>=0;i++){
                if(matrix[current.row][current.column].first!=matrix[current.row-i][current.column-i].first){
                    
                    // Count the white spaces
                    int paces = i;
                    string blank="";
                    while(paces>0){
                        blank+=" ";
                        blank[blank.size()-1]=(paces%10)+'0';
                        paces/=10;
                    }
                    
                    // Reverse the blank and get the next node
                    reverse(blank.begin(),blank.end());
                    Obj NextNode;
                    NextNode.row = current.row-i;
                    NextNode.column = current.column-i;
                    NextNode.output = current.output+i;
                    NextNode.result = current.result +blank + "NW ";
                    queue.push(NextNode);
                }
            }
        }
    }
    
    // print the output.
    fileOut<<"Error: there does exist an exit to the path!. "<<endl;
    return 0;
}

bool operator < (const Obj&x, const Obj&y){
    return x.output > y.output;
}
