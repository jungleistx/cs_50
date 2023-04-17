#! /bin/bash

# check that there is 1 argument given
if [ $# != 1 ]
then
	printf "Usage: week2/wordle/$0 wordsize\n"
	exit
fi

# check that the argument is a valid wordsize
# $NUM is the linenumber selected randomly. Modulo is based on the size of the wordlist
# $LIST is wordlist for the selected wordsize
case $1 in
	4)
		NUM=$(($RANDOM%6623))
		LIST="week2/wordle/wordlists/eng_4.txt"
	;;
	5)
		NUM=$(($RANDOM%15920))
		LIST="week2/wordle/wordlists/eng_5.txt"
	;;
	6)
		NUM=$(($RANDOM%26340))
		LIST="week2/wordle/wordlists/eng_6.txt"
	;;
	7)
		NUM=$(($RANDOM%38311))
		LIST="week2/wordle/wordlists/eng_7.txt"
	;;
	8)
		NUM=$(($RANDOM%48212))
		LIST="week2/wordle/wordlists/eng_8.txt"
	;;
	*)
		printf "Error: wordsize must be either 4, 5, 6, 7, or 8\n"
		exit
	;;
esac

# word in randomized line nr in $LIST
WORD=$(sed -n ${NUM}p $LIST)

gcc week2/wordle/main.c libft.a -o wordle
# printf "${NUM}\n"			# DEBUG line nr
# sed -n ${NUM}p $LIST		# DEBUG answer
./wordle $(echo $WORD) $(echo $1)
rm wordle
