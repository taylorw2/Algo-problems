#Wesley Taylor
#Dr. Larson
#CPSC 3400
#HW3
import sys
import os

class BadFileFormat(Exception):
	pass

class ImproperDate(Exception):
	pass

class indexError(Exception):
	pass

def leapYear(year):
	if(((year % 4 == 0) and (year%100!=0))
		or(year%400 == 0)):
		return True
	else:
		return False

def genFinalDates(year):
	l = []
	i = 0
	thirtyOne = [1,3,5,7,8,10,12]
	thirty = [4,6,9,11]
	feb = [2]
	if(type(year) == int):
		for index in range(1,13):
			if (index in thirtyOne):
				l.append((index,31,year))
			elif(index in thirty):
				l.append((index,30,year))
			else:
				if(leapYear(year)):
					l.append((index,29,year))
				else:
					l.append((index,28,year))
		while(i < len(l)):
			yield l[i]
			i = i + 1

def createDataList(fileName):
	a =[]
	# list of months with how many days then Feb
	thirtyOne = [1,3,5,7,8,10,12]
	thirty = [4,6,9,11]
	feb = [2]
	# see if file is empty
	if(os.path.getsize(fileName) == 0):
		raise BadFileFormat
	else:	
		file = open(fileName)
		for line in file:
			line = line.rstrip()
			b = line.split(" ")
			# make sure every line has 3 numbers
			if(len(b) ==  3):
				# make sure the 3 items are numbers and nothing else
				if(b[0].isdigit() and b[1].isdigit() and b[2].isdigit()):
					b = tuple([int(b[0]),int(b[1]),int(b[2])])
				else:
					raise BadFileFormat
					a = None
			else:
				raise BadFileFormat
				a = None
	#except BadFileFormat:
	#	print("Bad File Format Exception")
	#do improper date and move all except to outside the function
		#checking year
			if(b[2] < 1800):
				raise ImproperDate
				a = None
		#checking month if b[1] is not in list exception
		#checking for month in which list
			elif(b[1] in thirtyOne):
				if(b[1] > 31 or b[1] < 0):
					raise ImproperDate
					a = None
			elif(b[1] in thirty):
				if(b[1] > 30 or b[1] < 0):
					raise ImproperDate
					a= None
			elif(b[1] in feb):
				if(leapYear(b[2])):
					if((b[0]>29) or (b[0]<0)):						
						raise ImproperDate
						a= None
				else:
					if((b[0]>28) or (b[0]<0)):
						raise ImproperDate
						a= None
			if(a != None):
				a.append(b)
		file.close()
		return a



#This begins Main
file = sys.argv[1]
try:
	l = createDataList(file)
	for item in l:
		print(item)
except BadFileFormat:
	print("Bad File Format Exception")
	sys.exit()
except ImproperDate:
	print("The date was improperly formated")
	sys.exit()
except FileNotFoundError:
	print("File was not found")
	sys.exit()
print("\n")
try:
	for index in genFinalDates(l[0][2]):
		print(index)
except NotAnInteger:
	print("The parameter was not an Integer")
	sys.exit()
j = 0
for index in genFinalDates(l[0][2]):
	j = j + index[1]
print(j)
latestDate = max(l, key = lambda x:(x[2],x[0],x[1]))
print(latestDate)
sortedDate = sorted(l, key = lambda x:(x[2],x[0],x[1]), reverse = False)
print(sortedDate)
compList = [i[2] for i in l] 
print(compList)
monthList = ["Jan", "Feb", "Mar", "Apr","May", "Jun", "Jul", "Aug", "Sept","Oct", "Nov", "Dec"] 
strList= [(monthList[(index[0]-1)]+" " +str(index[1])+", "+str(index[2]))for index in l]
print(strList)
