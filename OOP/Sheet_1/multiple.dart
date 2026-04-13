import 'dart:io';

void main() {
  int runAgain;

  do {
    stdout.write('First number = ? ');
    int first = int.parse(stdin.readLineSync()!);

    stdout.write('Second number = ? ');
    int second = int.parse(stdin.readLineSync()!);

    if (first % second == 0) {
      print('--> $first is a multiple of $second');
    } else {
      print('--> $first is not a multiple of $second');
    }

    stdout.write('\nrun again ? ... enter 1 to YES or 0 for NO ');
    runAgain = int.parse(stdin.readLineSync()!);
    print(''); // New line for spacing
  } while (runAgain == 1);
}
