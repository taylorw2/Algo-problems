#wesley Taylor
#Dr. Larson
#CPSC 3400
import math
def processFile(fileName):
	file = open(fileName)
	d= []	# item that will hold lines
	for line in file:
		line = line.rstrip()
		l = line.split(",")
		l[2] = int(l[2])
		l[3] = float(l[3])
		l[4] = float(l[4])
		d.append(l)
	file.close()
	return d

def countState(l):
	case ={} #used for quick lookup
	h = []   #will be returned item
	a = []	 #Item to be stored in h
	for line in l:
		if (line[2] >= 100000):
			if (line[1] not in case):
				case[line[1]] = 1
			else:
				case[line[1]] = case[line[1]] + 1
	for element in case:
		a = [element, case[element]]
		h.append(a)
	h = sorted(h)
	for item in h:
		print(item)

def findRange(l):
	li =[0,0,0,0,0,0,0]
	for item in l:
		if(item[2] > 999999):
			li[0]= li[0]+1
		elif(999999 >= item[2] >= 750000):
			li[1] = li[1]+1
		elif(749999 >= item[2] >= 500000):
			li[2] = li[2]+1
		elif(499999 >= item[2] >= 400000):
			li[3] = li[3]+1
		elif(399999 >= item[2] >= 300000):
			li[4] = li[4]+1
		elif(299999 >= item[2] >= 200000):
			li[5] = li[5]+1
		elif(199999 >= item[2] >= 100000):
			li[6] = li[6]+1
	for index in range(0,len(li)):
		if(index == 0):
			print("> 1000000",":",li[0])
		elif(index == 1):
			print("999999 - 750000",":",li[1])
		elif(index == 2):
			print("749999 - 500000",":",li[2])
		elif(index == 3):
			print("499999 - 400000",":",li[3])
		elif(index == 4):
			print("399999 - 300000",":",li[4])
		elif(index == 5):
			print("299999 - 200000",":",li[5])
		elif(index == 6):
			print("199999 - 100000",":",li[6])

def northern(l):
	h = []
	h = sorted(l,key = lambda lat: lat[3],reverse = True)
	for index in range(0,20):
		print(h[index][0],", ",h[index][1])

def haversine(lat1, lat2, long1, long2):
	deg_to_rad = math.pi/180.0
	phi1 = (90.0 - lat1)*deg_to_rad
	phi2 = (90.0 - lat2)*deg_to_rad
	theta1 = long1*deg_to_rad
	theta2 = long2*deg_to_rad
	cos = (math.sin(phi1)*math.sin(phi2)*math.cos(theta1 - theta2) +
		math.cos(phi1)*math.cos(phi2))
	arc = math.acos(cos)*6371
	return arc

def findClosest(l):
	h=[]
	sLat = 47.6205
	sLong = 122.3509
	for item in l:
		if (item[1] != "Washington"):
			a = [item[0],item[1],item[2],item[3],item[4],haversine(sLat,item[3],sLong,item[4])]
			h.append(a)
	h = sorted(h,key = lambda lat: lat[5],reverse = False)
	for index in range(0,10):
		print(h[index][0],",",h[index][1])

def findFurthest(l):
	h=[]
	sLat = 47.6205
	sLong = 122.3509
	for item in l:
		a = [item[0],item[1],item[2],item[3],item[4],haversine(sLat,item[3],sLong,item[4])]
		h.append(a)
	h = sorted(h,key = lambda lat: lat[5],reverse = True)
	for index in range(0,10):
		print(h[index][0],",",h[index][1])

file = "cities.csv"           
d = processFile(file)
print("\nStates number of citys with 100000 peeps")
countState(d)
print("\nCounting the number of cities in a range")
findRange(d)
print("\nThe 20 northern most cities are")
northern(d)
print("\nThe closest 10 cities not in WA")
findClosest(d)
print("\nThe Furthest Cities from Seattle")
findFurthest(d)