/*Wesley Taylor
THIS IS DONE IN C++14
In this problem, we are given a knapsack of fixed capacity C. 
We are also given a list of N objects, each having a weight W(I)
and profit P(I). We can put any subset of the objects into the 
knapsack, as long as the total weight of our selection does not 
exceed C. The goal is to maximize the total profit, which is the 
sum of the profits of each object we put into the knapsack.

Example:
Input:
C = 3
W: 1 2 3
P: 100 5 50

Selected Items:
1
2
Explanation: Possible selections that can be put in the knapsack 
are: 1 with profit 100 2 with profit 5 3 with profit 50 1 and 2 
with profit 105 Note that in this problem, there is no need that 
the some of weights be exactly C. Hence, in this example, 1 is a 
valid solution but since the profit is lower than the maximum, 
is not the final answer.

Input Format

First line is C. 
Second line is the number of objects, N. 
The next N lines, each line contains two numbers: 
the first number is the weight of an object 
the second number is the profit of that object.

Example:
3
3
1 100
2 5
3 50
Constraints

NA

Output Format

Print out the maximum profit.

Example: for the above input 105

Sample Input 0

3
3
1 100
2 5
3 50
Sample Output 0

105
*/

// CODE FOLLOWS

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;


int** li; 
map<int,int>* prof;
int foo(int k, int c){
    if(c <= 0)
        return 0;
    else if(k<0)
        return 0;
    auto memorized = prof[k].find(c);
    if(memorized != prof[k].end())
        return memorized->second;
    if(c < li[k][0]){
        prof[k][c] = foo(k-1,c);
    }
    else{
        int m1 = foo(k-1,c); // Profit without new rock
        int m2 = foo(k-1,c-(li[k][0])) + li[k][1];
        prof[k][c] =  max(m1,m2);
    }
    return prof[k][c];             
}

int main() {
    int capacity;
    int number;
    int arr;
    cin >> capacity;
    cin >> number;
    prof = new map<int,int>[number];
    li = new int*[number];
    for(int i =0; i < number; i++){
        li[i] = new int[2];
        cin >> li[i][0];
        cin >> li[i][1];
    }
    cout << foo(number -1, capacity) ;
    return 0;
}