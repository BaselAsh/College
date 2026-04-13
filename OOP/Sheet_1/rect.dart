import 'dart:io';

void main() {
  stdout.write('Enter length: ');
  double length = double.parse(stdin.readLineSync()!);

  stdout.write('Enter width: ');
  double width = double.parse(stdin.readLineSync()!);

  print('The area of the rectangle is: ${length * width}');
}
