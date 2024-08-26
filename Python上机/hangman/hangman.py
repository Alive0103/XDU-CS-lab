import random


def choose_word(words):
    """从单词列表中随机选择一个单词"""
    return random.choice(words)


def display_word(word, guessed_letters):
    """显示当前猜中的字符和未猜中的字符"""
    guessed_word = ''
    for letter in word:
        if letter in guessed_letters:
            guessed_word += letter
        else:
            guessed_word += '_'
    return guessed_word



def hangman():
    with open('words.txt', 'r') as file:
        words = file.read().split()
    word = choose_word(words)
    # print(word)
    guessed_letters = []
    maxwe = 8
    chances = maxwe
    guessed_right_letters = []
    left_letters = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
                    'u', 'v', 'w', 'x', 'y', 'z']
    guessed_word2 = ["_", "_", "_", "_", "_", "_", "_", "_"]

    print("Welcome to Hangman!")
    print("The word has {} letters.".format(len(word)))

    for i in range(100):
        print("Chances left: {}".format(chances))
        print("Guessed  right letters: {}".format(", ".join(guessed_right_letters)))
        print("The letters you have not use: {}".format(", ".join(left_letters)))

        guess = input("Guess a letter: ").lower()

        if chances == 8:
            print(" +---+\n")
            print("     |\n")
            print(" 0   |\n")
            print("     |\n")
            print("     |\n")
            print("     |\n")
            print("========\n")
        elif chances == 7:
            print(" +---+\n")
            print(" |   |\n")
            print(" 0   |\n")
            print("     |\n")
            print("     |\n")
            print("     |\n")
            print("========\n")
        elif chances == 6:
            print(" +---+\n")
            print(" |   |\n")
            print(" 0   |\n")
            print("/    |\n")
            print("     |\n")
            print("     |\n")
            print("========\n")
        elif chances == 5:
            print(" +---+\n")
            print(" |   |\n")
            print(" 0   |\n")
            print("/|   |\n")
            print("     |\n")
            print("     |\n")
            print("========\n")
        elif chances == 4:
            print(" +---+\n")
            print(" |   |\n")
            print(" 0   |\n")
            print("/|\  |\n")
            print("     |\n")
            print("     |\n")
            print("========\n")
        elif chances == 3:
            print(" +---+\n")
            print(" |   |\n")
            print(" 0   |\n")
            print("/|\  |\n")
            print("/ \  |\n")
            print("     |\n")
            print("========\n")
        elif chances == 2:
            print(" +---+\n")
            print(" |   |\n")
            print("[0   |\n")
            print("/|\  |\n")
            print("/ \  |\n")
            print("     |\n")
            print("========\n")
        elif chances == 1:
            print(" +---+\n")
            print(" |   |\n")
            print("[0]  |\n")
            print("/|\  |\n")
            print("/ \  |\n")
            print("     |\n")
            print("========\n")

        if len(guess) != 1 or not guess.isalpha():
            print("Invalid input. Please enter a single letter.")
            continue

        if guess in guessed_letters:
            print("You have already guessed that letter. Try again.")
            continue

        guessed_letters.append(guess)

        if guess not in word:
            chances -= 1
            left_letters.remove(guess)
            print("Wrong guess!")

        else:
            left_letters.remove(guess)
            guessed_word = display_word(word, guessed_letters)
            guessed_right_letters.append(guess)
            print("Correct guess!")
            print(guessed_word)

            if "_" not in guessed_word:
                print("Congratulations! You guessed the word{}!".format(word))
                break
        if chances == 0:
            print("Game over! The word was: {}".format(word))
            break


hangman()
