import csv
import sys


REQUIRED_ARGC = 2


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) - 1 != REQUIRED_ARGC:
        print('This program requires 2 arguments, first with the database file path and second with the dna sequences one')

    database_filename = sys.argv[1]
    dna_sequence_filename = sys.argv[2]

    # TODO: Read database file into a variable
    people = []
    subsequences = []
    with open(database_filename) as file:
        reader = csv.DictReader(file)
        subsequences = reader.fieldnames[1:]
        for row in reader:
            people.append(row)

    # TODO: Read DNA sequence file into a variable
    sequence = ''
    with open(dna_sequence_filename) as file:
        sequence = file.read()
        sequence = sequence[:len(sequence) - 1]

    # TODO: Find longest match of each STR in DNA sequence
    STRs_longest_matches = {}
    for STR in subsequences:
        longest_match = find_longest_match(sequence, STR)
        STRs_longest_matches[f'{STR}'] = str(longest_match)

    # TODO: Check database for matching profiles
        # Assuming that all STRs should match exactly for only 1 person
        # https://cs50.harvard.edu/x/2024/psets/6/dna/#specification
    for person in people:
        all_STRs_matching = True
        for STR in STRs_longest_matches:
            all_STRs_matching = all_STRs_matching and person[STR] == STRs_longest_matches[STR]

        if all_STRs_matching:
            print(person['name'])
            return

    print('No match')
    return


def find_longest_match(sequence, subsequence):
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
