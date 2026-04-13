import 'dart:io';

void main() {
  stdout.write('Enter your name: ');
  String name = stdin.readLineSync()!;

  stdout.write('Enter your age: ');
  int age = int.parse(stdin.readLineSync()!);

  stdout.write('Enter your favorite color: ');
  String color = stdin.readLineSync()!;

  print('\n--- User Profile ---');
  print('Name: $name\nAge: $age\nFavorite Color: $color');
}
