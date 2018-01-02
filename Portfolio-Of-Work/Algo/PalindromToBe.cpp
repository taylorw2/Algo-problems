/*Wesley Taylor
Given a non-empty string s, you may delete at most one character.
 Judge whether you can make it a palindrome.

Example 1: Input: "aba" Output: True

Example 2: Input: "abca" Output: True Explanation: 
You could delete the character 'c'.

Example 3: Input: "abcd" Output: False

Input Format

A string with lowercase 'a' to 'z'

Constraints

NA

Output Format

True or False

Sample Input 0

aba
Sample Output 0

True
Sample Input 1

abca
Sample Output 1

True
Sample Input 2

abcd
Sample Output 2

False
*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {    
    string pali;
    cin >> pali;
    int length = pali.length();
    int i = 0;
    int j = length -1;
    bool minus = true;
    bool palidrome = true;
    while(i < j && palidrome){
        if(pali[i] == pali[j]){
            i++;
            j--;
        }else if(pali[i+1] == pali[j] && minus){
            i++;
            minus = false;
        }else if(pali[i+1] == pali[j]&& !minus){
            palidrome = false;
        }else if(pali[j-1] == pali[i]){
            minus = false;
            j--;
        }else if(pali[j-1] == pali[i] && !minus){
            palidrome = false;
        }else
            palidrome = false;
    }
    if(palidrome)
        cout << "True";
    else
        cout << "False";
    return 0;
}

