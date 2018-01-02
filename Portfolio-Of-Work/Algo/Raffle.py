# Wesley Taylor
#In a party there are N persons and we have M raffles. One person 
#may participate in any number of raffles (from 0 to M). At the 
#end of the day, host of the party comes to you and gives you M 
#lists. Each list contains multiple integer numbers which are the 
#"raffle ID numbers" of the participants. Then, for each list an 
#integer number, I, is announced to determine the winner of the 
#raffle: the winner is the person with raffle ID number K such 
#that K is larger than exactly I numbers in that list. To help 
#the host to find the winners you want to write a program.

#Input Format

#First line of the input is N and M. Then, there are M lines, 
#each one contains integer numbers between 1 and N. Each list may 
#contain at most N numbers. At the end of each line there is -1. 
#After these lines there is one line which contains M integers to 
#announce the winners. If the j-th number in this line is I it 
#means that the winner of list j is the person whose ID is exactly 
#larger than I other persons in that list. If I is larger than 
#number of people in list j, then that list does not have a winner.

#Example:
#8 3
#1 4 2 3 -1
#5 2 1 8 6 3 7 -1
#4 6 8 3 1 -1
#2 5 8
#Comment: there are 8 people in this party and we have 3 raffles. In the first raffle, participants' IDs are 1, 4, 2, and 3. In the second raffle, IDs are 5, 2, ... Winner of the first raffle is 3 (3 is exactly larger than 2 other numbers in that list). Winner of the second raffle is 7 (7 is larger than 1, 2, 3, 5, and 6 in the second raffle). Third raffle does not have a winner (there are only 5 participants but the winner's ID has to be larger than 8 other IDs, which is impossible).

#Constraints

#NA

#Output Format

#For each list print the ID of the winner. If there is no winner, print -1.

#Example: For the example in the Input part we will have: 3 7 -1

#Sample Input 0

#8 3
#1 4 2 3 -1
#5 2 1 8 6 3 7 -1
#4 6 8 3 1 -1
#2 5 8
#Sample Output 0

#3
#7
#-1

line = input().split()
n =  int(line[0])
m = int(line[1])

array = []

for i in range(0,m):
    string = input().split()
    for item in range(len(string)):
        string[item] = int(string[item])
    array.append(string)
    
for i in range(0,m):
    array[i].pop()
    
for i in range(0,m):
    array[i].sort()

num = input().split()
for item in range(len(num)):
    num[item] = int(num[item])
    
for item in range(len(num)):
    if num[item] >= len(array[item]):
       print("-1")
    else:
       print(array[item][num[item]])



