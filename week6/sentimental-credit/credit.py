# TODO
import re

def print_invalid():
	print('INVALID')
	exit(1)


def get_cardnumber():
	str = ""
	while not str:
		str = input('Number: ')
	return str


patterns = ["^\d{13}$", "^\d{15}$", "^\d{16}$"]		# match 13,15,16, all digits
card_number = get_cardnumber()
ret_value = 0

if re.search(patterns[0], card_number):		# len 13
	validate_number = r'^4.*'				# start with 4
	if re.search(validate_number, card_number):
		print("VISA")
	else:
		print_invalid()
elif re.search(patterns[1], card_number):	# len 15
	validate_number = r'^3[47].*'			# start with 3 and second either 4,7
	if re.search(validate_number, card_number):
		print("AMEX")
	else:
		print_invalid()
elif re.search(patterns[2], card_number):	# len 16
	validate_number = r'^5[1-5].*'		# start with 5 and second either 1,2,3,4,5
	if re.search(validate_number, card_number):
		print("MASTERCARD")
	else:
		validate_number = r'^4.*'			# start with 4
		if re.search(validate_number, card_number):
			print("VISA")
		else:
			print_invalid()
else:
	print_invalid()
