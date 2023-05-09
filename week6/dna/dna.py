import csv
import sys


def main():

    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} data.csv sequence.txt")
        exit(1)

    sequences = {}      # empty dict for different sequences
    person = []         # empty list for person

    with open(sys.argv[1], "r") as file_csv:
        lines = csv.reader(file_csv)

        for line in lines:
            if line[0] == 'name':       # first line, save the sequences in a dict with value 0
                for sequence in line[1:]:       # type(str), skip 'name'
                    if isinstance(sequence, str):
                        sequences[sequence] = 0
            else:
                person.append(line)     # add the whole line to 'person' list (list of lists)

    # # debug
    # print (sequences)
    # print()
    # for line in person:
    #     print(line)
    """
        name,AGATC,AATG,TATC
        Alice,2,8,3
        Bob,4,1,5
        Charlie,3,2,5
    """

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as dna_file:

        for line in dna_file:
            dna_sequence_full = line[:-1]           # delete trailing newline
            # print(dna_sequence_full)


    # TODO: Find longest match of each STR in DNA sequence

    # TODO: Check database for matching profiles

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
