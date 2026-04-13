import 'dart:io';
import 'dart:math';

void main() {
  var random = Random();
  int correctCount = 0;
  int totalQuestions = 10;

  print(
    'Welcome to the Multiplication Quiz! Answer $totalQuestions questions.\n',
  );

  for (int i = 1; i <= totalQuestions; i++) {
    int num1 = random.nextInt(9) + 1;
    int num2 = random.nextInt(9) + 1;
    int correctAnswer = num1 * num2;

    stdout.write('Question $i: How much is $num1 times $num2? ');
    int? answer = int.tryParse(stdin.readLineSync() ?? '');

    if (answer == correctAnswer) {
      printFeedback(true, random);
      correctCount++;
    } else {
      printFeedback(false, random);
    }
  }

  double percentage = (correctCount / totalQuestions) * 100;
  print('\nQuiz Complete! Your score: ${percentage.toStringAsFixed(0)}%');

  if (percentage < 75) {
    print('Please ask your instructor for extra help.');
  } else {
    print('Congratulations, you are ready to move to the next level!');
  }
}

void printFeedback(bool isCorrect, Random rand) {
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
}
