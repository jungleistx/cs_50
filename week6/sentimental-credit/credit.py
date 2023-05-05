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


def count_checksum(len, number, card_type):
	num = int(number)
	total = 0
	last = 0
	i = 0
	while i < len:
		last = num % 10
		if i % 2 == 0:			# add to total
			total += last
		else:					# multiple by 2
			if last > 4:		# over 10, separate digits and add
				total += (last - (9 - last))
				'''
					5 * 2 = 10, 1 + 0 = 1 	-> 		5 - (9 - 5) = 1
					6 * 2 = 12, 1 + 2 = 3 	-> 		6 - (9 - 6) = 3
					7 * 2 = 14, 1 + 4 = 5 	-> 		7 - (9 - 7) = 5
					8 * 2 = 16, 1 + 6 = 7 	-> 		8 - (9 - 8) = 7
					9 * 2 = 18, 1 + 8 = 9 	-> 		9 - (9 - 9) = 9
				'''
			else:
				total += (last * 2)
		num = int(num / 10)		# get new last number
		i += 1

	if total % 10 == 0:			# legit card_number and type
		print(card_type)
	else:
		print_invalid()


patterns = ["^\d{13}$", "^\d{15}$", "^\d{16}$"]		# match 13,15,16, all digits
card_number = get_cardnumber()

if re.search(patterns[0], card_number):		# len 13
	validate_number = r'^4.*'				# start with 4
	if re.search(validate_number, card_number):
		count_checksum(13, card_number, "VISA")
	else:
		print_invalid()
elif re.search(patterns[1], card_number):	# len 15
	validate_number = r'^3[47].*'			# start with 3 and second either 4,7
	if re.search(validate_number, card_number):
		count_checksum(15, card_number, "AMEX")
	else:
		print_invalid()
elif re.search(patterns[2], card_number):	# len 16
	validate_number = r'^5[1-5].*'			# start with 5 and second either 1,2,3,4,5
	if re.search(validate_number, card_number):
		count_checksum(16, card_number, "MASTERCARD")
	else:
		validate_number = r'^4.*'			# start with 4
		if re.search(validate_number, card_number):
			count_checksum(16, card_number, "VISA")
		else:
			print_invalid()
else:
	print_invalid()
