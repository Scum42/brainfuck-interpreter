import math

x = input("Target number: ")
x = float(x)

n = math.sqrt(x)
n = math.floor(n)

while x % n != 0:
	n -= 1

m = x/n;

m = int(m)
n = int(n)
x = int(x)

print(str(n) + " * " + str(m) + " = " + str(x))
