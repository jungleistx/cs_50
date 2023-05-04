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
coin_amount = 0
coins = [25, 10, 5, 1]

for i in range(len(coins)):
	while num >= coins[i]:
		num -= coins[i]
		coin_amount += 1

print(coin_amount)
