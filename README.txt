Hangman! By Dan Poumakis
The program will display underscores based on the number of letters. For example, the word apple will display “_ _ _ _ _”. The objective is to enter a letter that is in the word to reveal it on the display. If the user were to enter “a”, the program would change the display to “a _ _ _ _” and then continue to prompt until you either run out of guess, guess incorrectly too many times or you win! When you guess incorrectly your number of wrong guesses increases resulting in the hangman to display another body part. You have a total of 6 incorrect guesses before the hangman is hanged. To make it more interesting, your total number of guesses allowed is the length of the word + 2. In this case, you have a total of 7 guesses despite being right or wrong.
At first I wrote this program using no array and no pointers/addresses. The program worked and did what it needed to do. I found out that we could use arrays so I then went on it made it do what I wanted it to do. After the class that we were introduced to pointers, I went ahead and tried to make my code easier to read and more organized. In fact, just reading the variable and function names you can get an idea of exactly what’s happening.
Here is an overview:
·         Display the underscore version of the actual word to the user
·         Prompt, store, verify guess from user
·         Check for the guess in the word
·         Check to see if the user wins by comparing underscore word to the actual word
·         Display the hangman to the user
·         Check number of wrong guesses, less than 6 continue… else game over
·         Check number of total guesses, less than length of word + 2 continue… else prompt user for final guess
·         Check if game over… Did another function flip the gameOver flag? If so print goodbye message
·         If not game over… Loop again