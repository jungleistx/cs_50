# TODO

def get_int(str):
	try:
		num = int(str)
		return num
	except ValueError:
		return 0

height = 0
while height <= 0 or height > 8:		# get proper height (1-8)
	height = get_int(input("Height: "))

i = 1
while i <= height:
	print(" " * (height - i), end="")	# left padding
	print("#" * i, end="")				# left side
	print("  ", end="")					# middle gap
	print("#" * i)						# right side
	i += 1
