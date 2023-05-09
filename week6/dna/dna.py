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


    with open(sys.argv[2], "r") as dna_file:

        for line in dna_file:
            dna_sequence_full = line[:-1]           # delete trailing newline

    for dna_part, repeat_amount in sequences.items():        # chop each dict into key, value and find the value
        repeat_amount = longest_match(dna_sequence_full, dna_part)
        sequences[dna_part] = repeat_amount


    for people in person:

        found = True
        i = 1
        for sequence, amount in sequences.items():
            if amount != int(people[i]):
                found = False
                break
            i += 1

        if found == True:
            print(people[0])
            return

    print("No match.")

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

"""
    python3 dna.py databases/small.csv sequences/1.txt        Bob.
    python3 dna.py databases/small.csv sequences/2.txt        No match.
    python3 dna.py databases/small.csv sequences/3.txt        No match.
    python3 dna.py databases/small.csv sequences/4.txt        Alice.
    python3 dna.py databases/large.csv sequences/5.txt        Lavender.
    python3 dna.py databases/large.csv sequences/6.txt        Luna.
    python3 dna.py databases/large.csv sequences/7.txt        Ron.
    python3 dna.py databases/large.csv sequences/8.txt        Ginny.
    python3 dna.py databases/large.csv sequences/9.txt        Draco.
    python3 dna.py databases/large.csv sequences/10.txt       Albus.
    python3 dna.py databases/large.csv sequences/11.txt       Hermione.
    python3 dna.py databases/large.csv sequences/12.txt       Lily.
    python3 dna.py databases/large.csv sequences/13.txt       No match.
    python3 dna.py databases/large.csv sequences/14.txt       Severus.
    python3 dna.py databases/large.csv sequences/15.txt       Sirius.
    python3 dna.py databases/large.csv sequences/16.txt       No match.
    python3 dna.py databases/large.csv sequences/17.txt       Harry.
    python3 dna.py databases/large.csv sequences/18.txt       No match.
    python3 dna.py databases/large.csv sequences/19.txt       Fred.
    python3 dna.py databases/large.csv sequences/20.txt       No match.
"""