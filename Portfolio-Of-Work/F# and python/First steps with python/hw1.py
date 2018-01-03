#Wesley Taylor
#CPSC 3400
# Dr. Larson
# HW1.py

import sys
def processfile(string):
    file = open(string)
    new_dict = {}
    word = ""
    i = 0
    for line in file:
        line = line.rstrip()
        l = line.split(" ")
        for word in l:
            if(i == 3):
                i = 0
            if word in new_dict:
                new_dict[word][i] = new_dict[word][i] + 1
            else:
                if( i == 0):
                    new_dict[word] = [1,0,0]
                elif(i == 1):
                    new_dict[word] = [0,1,0]
                else:
                    new_dict[word] = [0,0,1]
            i = i + 1
    for val in new_dict:
    	new_dict[val] = tuple(new_dict[val]) 
    return new_dict

def getFirstPlaceVotes(dict, str):
    return dict[str][0]

#used selection sort
def createFavoritecolorList(dict):
	l = []
	gl = []
	rl = []
	for word in dict:
		a = (word, dict[word][0], dict[word][1],dict[word][2])
		l.append(a)
	last = len(l) - 1
	while l:
		a = l[last]
		for i in range(len(l)):
			#if tied in first place votes
			if(l[i][1] == a[1]):
				#if tied in second place votes
				if(l[i][2] == a[2]):
					#if tied in third place votes
					if(l[i][3] == a[3]):
						#see if the strings are alphabetical
						if(l[i][0] < a[0]):
							a = l[i]
							b = l[last]
							l[last] = l[i]
							l[i] = b
					elif(l[i][3] > a[3]):
						a = l[i]
						b = l[last]
						l[last] = l[i]
						l[i] = b
				elif(l[i][2] > a[2]):
					a = l[i]
					b = l[last]
					l[last] = l[i]
					l[i] = b
			elif(l[i][1] > a[1]):
				a = l[i]
				b = l[last]
				l[last] = l[i]
				l[i] = b
		if(l[last][1] > 0):
			gl.append(l[last])
		del l[last]
		last = last - 1
	for item in gl:
		rl.append(item[0])

	return rl
def createColorScoreDict(d):
	sDict = {}
	for word in d:
		sDict[word] = ((d[word][0]*3)+(d[word][1]*2)+(d[word][2]*1))
	return sDict

def printDictionary(d):
	l = sorted(d)
	for element in l:
		print(element, ":" , d[element])

file = sys.argv[1]
print(file)           
d = processfile(file)
if "blue" in d:
	color = "blue"
	num = getFirstPlaceVotes(d, color)
	print(num)
else:
	print(0)
if "green" in d:
	color = "green"
	num = getFirstPlaceVotes(d, color)
	print(num)
else:
	print(0)
l = createFavoritecolorList(d)
print(l)
sD = createColorScoreDict(d)
printDictionary(sD)

        
