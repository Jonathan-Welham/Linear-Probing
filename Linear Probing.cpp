/*
 * HackerRank link: https://www.hackerrank.com/contests/cst370-s20-hw10/challenges/closed-hashing/submissions/code/1323302483
 * Title: hw10_2.cpp
 * Abstract: This program simulates the operations of linear probing
 * Author: Jonathan Welham
 * ID: 6781
 * Date: 05/02/2020
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Function declarations
int check(vector<pair<int,string>> &v1Hash, int positionCheck);
void deleteValue(vector<pair<int,string>> &v1Hash, int userinput, int& size, int &counter);
bool search(vector<pair<int,string>> &v1Hash, int user, int &size);
int isPrime(int number);
int nextPrime(int n);
void displayStatus(vector<pair<int, string>> &v1Hash, int display);
void insert(vector<pair<int,string>> &v1Hash, int &size, int &temp, int &counter);
//void commands(vector<pair<int, string>> &v1Hash, int n, int count);


int main(){

    int n;
    int numCommands;
    int count = 0;
    string userIn;
    vector<pair<int,string>> v1Hash;

    cin >> n;
    cin >> numCommands;

    for(int i = 0; i < n; i++){
        v1Hash.push_back(make_pair(0, "Empty"));
    }

    for(int i = 0; i < numCommands; i++){
        cin >> userIn;
        if(userIn == "insert"){
            int temp;
            cin >> temp;
            insert(v1Hash, n, temp, count);
        }

        else if(userIn == "displayStatus"){
            int displayVal;
            cin >> displayVal;
            displayStatus(v1Hash, displayVal);
        }

        else if(userIn == "tableSize"){
            cout << n << endl;
        }

        else if(userIn == "search"){
            int input;
            cin >> input;
            bool answer = search(v1Hash, input, n);
            if(answer){
                cout << input << " Found" << endl;
            }else{
                cout << input << " Not found" << endl;
            }
        }

        else if(userIn == "delete"){
            int temp2;
            cin >> temp2;
            deleteValue(v1Hash, temp2, n, count);
        }
    }
}

int check(vector<pair<int, string>> &v1Hash, int positionCheck){
    if(positionCheck >= v1Hash.size()){
        positionCheck = 0;
    }
    for(int i = positionCheck; i < v1Hash.size(); i++){
        if(v1Hash[i].second == "Empty" || v1Hash[i].second == "Deleted"){
            return i;
        }
        if(i == v1Hash.size() - 1){
            i = 0;
        }
    }
    return 0;
}

//delete value
void deleteValue(vector<pair<int, string>> &v1Hash, int userinput, int &size, int &counter){
    for(int i = 0; i < size; i++){
        if(userinput == v1Hash[i].first){
            v1Hash[i].second = "Deleted";
            break;
        }
    }
    counter--;
}

//Search
bool search(vector<pair<int, string>> &v1Hash, int user, int &size){
    bool TF = false;
    for(int i = 0; i < size; i++){
        if(v1Hash[i].first == user && v1Hash[i].second == "Active"){
            TF = true;
        }
    }
    return TF;
}

//Check if prime
int isPrime(int number){
    bool isPrime = true;
    for(int i = 2; i <= number / 2; ++i){
        if(number % i == 0){
            isPrime = false;
        }
    }
    return isPrime;
}

//find next prime
int nextPrime(int n){
    if (n <= 1){
        return 2;
    }

    int prime = n;
    bool found = false;

    while (!found){
        prime++;
        if (isPrime(prime))
            found = true;
    }
    return prime;
}

//Display status
void displayStatus(vector<pair<int, string>> &v1Hash, int display){
    if(v1Hash[display].second == "Empty"){
        cout << "Empty" << endl;
    }else{
        cout << v1Hash[display].first << " ";
        cout << v1Hash[display].second << endl;
    }
}

//insert new value
void insert(vector<pair<int, string>> &v1Hash, int &size, int &temp, int &counter){
    counter++;
    float load = float(counter)/float(size);

    if(load > 0.5){

        int loadFactor = size * 2;
        size = nextPrime(loadFactor);
        vector<pair<int, string>> tempHash;

        for(int i = 0; i < size; i++){
            tempHash.push_back(make_pair(0,"Empty"));
        }

        for(int i = 0; i < v1Hash.size(); i++){
            if(v1Hash[i].second == "Active"){
                int remr = v1Hash[i].first % size;
                tempHash[remr].first = v1Hash[i].first;
                tempHash[remr].second = "Active";
            }
        }
        v1Hash = tempHash;
    }

    int overflow = temp % size;

    if(v1Hash[overflow].second == "Active"){
        overflow = check(v1Hash, overflow + 1);
    }
    if((v1Hash[overflow].second == "Empty" || v1Hash[overflow].second == "Deleted")){
        v1Hash[overflow].first = temp;
        v1Hash[overflow].second = "Active";
    }
}
