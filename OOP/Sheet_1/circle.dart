import 'dart:io';
import 'dart:math';

void main() {
  stdout.write('radius of the circle = ? ');
  double r = double.parse(stdin.readLineSync()!);

  double diameter = 2 * r;
  double circumference = 2 * pi * r;
  double area = pi * pow(r, 2);

  print('\n${"diameter".padLeft(15)} = $diameter');
  print('${"circumference".padLeft(15)} = $circumference');
  print('${"area".padLeft(15)} = $area');
}
