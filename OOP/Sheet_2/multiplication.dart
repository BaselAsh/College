import 'dart:io';
import 'dart:math';

void main() {
  var random = Random();

  while (true) {
    // Generate two positive one-digit integers
    int num1 = random.nextInt(9) + 1;
    int num2 = random.nextInt(9) + 1;
    int correctAnswer = num1 * num2;

    bool answeredCorrectly = false;

    while (!answeredCorrectly) {
      stdout.write('How much is $num1 times $num2? ');
      int? studentAnswer = int.parse(stdin.readLineSync() ?? '');

      if (studentAnswer == correctAnswer) {
        printFeedback(true);
        answeredCorrectly = true;
      } else {
        printFeedback(false);
      }
    }
  }
}

// Problem 5: Randomize responses using a switch structure
void printFeedback(bool isCorrect) {
  var rand = Random();
  int responseIndex = rand.nextInt(4) + 1;

  if (isCorrect) {
    switch (responseIndex) {
      case 1:
        print('Very good!');
        break;
      case 2:
        print('Excellent!');
        break;
      case 3:
        print('Nice work!');
        break;
      case 4:
        print('Keep up the good work!');
        break;
    }
  } else {
    switch (responseIndex) {
      case 1:
        print('No. Please try again.');
        break;
      case 2:
        print('Wrong. Try once more.');
        break;
      case 3:
        print("Don't give up!");
        break;
      case 4:
        print('No. Keep trying.');
        break;
    }
  }
  print(''); // For spacing
}
