# TODO

def get_input():
	str = ""
	while not str:
		str = input("Text: ")
	return str

str = get_input()
words = 1
sentences = 0
letters = 0
length = len(str)

i = 0
while i < length:
	if str[i] in ['.', '?', '!']:
		sentences += 1
	elif str[i] == ' ':
		words += 1
	elif str[i].isalpha():
		letters += 1
	i += 1

L = 100.0 / words * letters
S = 100.0 / words * sentences
grade = 0.0588 * L - 0.296 * S - 15.8

if grade < 1:
	print("Before Grade 1")
elif grade > 16:
	print("Grade 16+")
else:
	print("Grade", int(round(grade)))
