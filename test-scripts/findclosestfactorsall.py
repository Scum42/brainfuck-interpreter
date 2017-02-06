import math

x = 0

while x < 255:
	x += 1

	n = math.sqrt(x)
	n = math.floor(n)

	while x % n != 0:
		n -= 1

	m = x/n;

	m = int(m)
	n = int(n)
	x = int(x)

	print(str(n) + "\t*\t" + str(m) + "\t=\t" + str(x))
