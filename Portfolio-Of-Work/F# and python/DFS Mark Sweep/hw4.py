#Wesley Taylor
#Dr. Larson
#CPSC 3400
#hw4

import sys

def processFile(fileName):
	file = open(fileName)
	firstLine = file.readline()
	firstLine = firstLine.rstrip()
	ret = (int(firstLine), {}, {}) #(num, ints only, str allowed)
	for line in file:
		line = line.rstrip()
		line = line.split(",")
		if(line[0].isdigit()):
			line[0] = int(line[0])
			line[1] = int(line[1])
			if line[0] in ret[1]:
				(ret[1][line[0]]).append(line[1])
			else:
				ret[1][line[0]] = [line[1]]
		if((type(line[0]) == str)):
			line[1] = [int(line[1])]
			ret[2][line[0]] = line[1]
	return ret

def dfs(key, diction,l, visited):
	for num in key:
		if((num not in diction) or
			num == diction[num][0]):
			return l
		if(num in diction):
			#if(sys.getsizeof(diction[num]) == 72):
#this happens to be the size of a single int in a list - points for style	
			if(len(diction[num]) == 1):
				if(num not in visited):
					visited.append(num)
					dfs(diction[num],diction,l, visited)
					l.append(diction[num][0])
			else:
				for item in diction[num]:
					if(item not in visited):
						visited.append(item)
						dfs([item],diction,l,visited)
						l.append(item)
	return l

def markSweep(n, intList, strList):
	allo = list(range(n))
	mark = []
	deallo = []
	for item in strList:
		v = []
		l = []
		l.append(strList[item][0])
		strList[item] = dfs(strList[item],intList,l,v)
		for loc in strList[item]:
			if(loc not in mark):
				mark.append(loc)
	for num in allo:
		if(num not in mark):
			deallo.append(num)
	return(mark, deallo)

file = sys.argv[1]
l = processFile(file)
ret = markSweep(l[0],l[1],l[2])
for item in l[1]:
	print(sys.getsizeof(l[1][item]))
mstr = ""
sstr = ""
(ret[0]).sort()
ret[1].sort()
for i in ret[0]:
	mstr += str(i) +" " 
for i in ret[1]:
	sstr += str(i) + " "
print("Marked Nodes: ", mstr)
print("Swept Nodes: ", sstr)