alphabet='àáâãabcdeéêèẽfghiìíîĩjklmnñoòóõôpqrstuùúũûvwxyỳýỹŷz'

def main():
    text = input("Text: ")
    grade = calculate_coleman_liau_grade(text)

    validate_and_handle_output(grade)

def count_words(text):
   return len(text.split(' '))

def count_sentences(text):
    counter = 0
    prev = ''
    for letter in text:
        if (
            letter == '!' or letter  == '.' or letter == '?'
        ) and prev.lower() in alphabet:
            counter += 1
        prev = letter
    return counter

def count_letters(text):
    counter = 0
    for letter in text:
        if letter.lower() in alphabet:
            counter += 1
    return counter

def calculate_coleman_liau_grade(text):
    words_length = count_words(text)

    L = count_letters(text) / words_length * 100
    S = count_sentences(text) / words_length * 100

    index = 0.0588 * L - 0.296 * S - 15.8

    return round(index)

def validate_and_handle_output(grade):
    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print("Grade", grade)

main()
