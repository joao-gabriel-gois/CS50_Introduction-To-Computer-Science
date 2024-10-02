def get_sentimental_height(description=""):
    try:
        value = int(input(description))
        # Business Logic the only acceptable height (sentimental one)
        if value > 0 and value <= 8:
            return value
        return get_sentimental_height(description)
    except ValueError:
        return get_sentimental_height(description)


def print_mario_pyramid(height):
    for i in range(height):
        print((height - i - 1) * ' ', end='')
        print((i + 1) * '#', end='  ')
        print((i + 1) * '#')


def main():
    height = get_sentimental_height('Height: ')
    print_mario_pyramid(height)


main()
