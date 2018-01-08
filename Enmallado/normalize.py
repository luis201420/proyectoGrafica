from math import sqrt
infile = open("pCloud.xyz","r")

points = []
maxX,maxY,maxZ = 0 , 0 , 0
minX,minY,minZ = 100000 , 100000 , 100000

for line in infile:
	xyz = line.split(" ")
	if maxX < float(xyz[0]):
		maxX = float(xyz[0])
	if maxY < float(xyz[1]):
		maxY = float(xyz[1])
	if maxZ < float(xyz[2]):
		maxZ = float(xyz[2])
	if minX > float(xyz[0]):
		minX=float(xyz[0])
	if minY > float(xyz[1]):
		minY=float(xyz[1])
	if minZ > float(xyz[2]):
		minZ=float(xyz[2])
	points.append(xyz)

ofile = open("normalized.dat","w")
for point in points:
	x = ((float(point[0]))-minX)/(maxX-minX)
	y = ((float(point[1]))-minY)/(maxY-minY)
	z = ((float(point[2]))-minZ)/(maxZ-minZ)
	ofile.write(str(x) + " " + str(y) + " "+str(z) + "\n")
ofile.close()
