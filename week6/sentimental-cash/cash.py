# TODO

def get_float(str):
	try:
		num = float(str)
		return num
	except ValueError:
		return 0.0

num = 0.0
while num <= 0.0:			# get posivive input
	str = input("Change owed: ")
	num = get_float(str)

num *= 100			# avoid the floating-point rounding errors
coins = 0

while num >= 25:
	num -= 25
	coins += 1

while num >= 10:
	num -= 10
	coins += 1

while num >= 5:
	num -= 5
	coins += 1

while num >= 1:
	num -= 1
	coins += 1

print(coins)
