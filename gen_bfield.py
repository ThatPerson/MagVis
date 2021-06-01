import numpy as np
import sys
import math
try:
    fn = sys.argv[1]
except IndexError:
    print("python gen_bfield.py <output>")

dt = 0.001

command = input("> ")

time = 0

with open(fn, "w") as out:
	while (command != "exit") :
		k = command.split()
		if (k[0] == "pulse"):
			try:
				PLW = float(k[1])
				ANG = float(k[2]) * (np.pi / 180.)
				ORR = float(k[3])
				PHA = float(k[4]) * (np.pi / 180.)
			except IndexError:
				print("Did not understand")
				continue
			length = (ANG/2.) / PLW
			steps = length / dt
			for T in np.arange(0, length, dt):

				out.write("%f %f %f\n" % (math.sin((T + PHA) * ORR), math.cos((T + PHA) * ORR), 1))
		elif (k[0] == "delay"):
			try:
				TIME = float(k[1])
			except IndexError:
				print("Did not understand")
				continue
			for T in np.arange(0, TIME, dt):
				out.write("%f %f %f\n" % (0, 0, 1))
		else:
			print("Not recognized")
		command = input("> ")
			
		
