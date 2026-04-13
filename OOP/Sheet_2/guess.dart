import 'dart:io';
import 'dart:math';

void main() {
  var random = Random();
  bool playAgain = true;

  while (playAgain) {
    int targetNumber = random.nextInt(100) + 1;
    bool guessedCorrectly = false;

    print('\nI have a number between 1 and 100.');
    print('Can you guess my number?');
    stdout.write('Please type your first guess: ');

    while (!guessedCorrectly) {
      int? guess = int.tryParse(stdin.readLineSync() ?? '');

      if (guess == null) {
        stdout.write('Invalid input. Please enter a number: ');
        continue;
      }

      if (guess == targetNumber) {
        print('Excellent! You guessed the number!');
        guessedCorrectly = true;
      } else if (guess < targetNumber) {
        stdout.write('Too low. Try again: ');
      } else {
        stdout.write('Too high. Try again: ');
      }
    }

    stdout.write('\nWould you like to play again (y or n)? ');
    String choice = stdin.readLineSync()?.toLowerCase() ?? 'n';
    if (choice != 'y') playAgain = false;
  }
  print('Thanks for playing!');
}
