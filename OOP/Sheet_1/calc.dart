import 'dart:io';

void main() {
  stdout.write('Enter your name : ');
  String? name = stdin.readLineSync();
  print('Welcome $name\n');

  stdout.write('Now give me a number : ');
  double num1 = double.parse(stdin.readLineSync()!);

  stdout.write('Now give me another number : ');
  double num2 = double.parse(stdin.readLineSync()!);

  print('\nThe sum of $num1 and $num2 is ${num1 + num2}');
  print('The result of subtracting $num2 from $num1 is ${num1 - num2}');
  print('The product of $num1 and $num2 is ${num1 * num2}');
  print('The result of dividing $num1 by $num2 is ${num1 / num2}');
  print('The remainder after dividing $num1 by $num2 is ${num1 % num2}');
}
