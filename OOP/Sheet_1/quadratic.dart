import 'dart:io';
import 'dart:math';

void main() {
  print('For ax² + bx + c = 0, enter coefficients:');
  stdout.write('a: ');
  double a = double.parse(stdin.readLineSync()!);
  stdout.write('b: ');
  double b = double.parse(stdin.readLineSync()!);
  stdout.write('c: ');
  double c = double.parse(stdin.readLineSync()!);

  double discriminant = pow(b, 2) - (4 * a * c);

  if (discriminant > 0) {
    double x1 = (-b + sqrt(discriminant)) / (2 * a);
    double x2 = (-b - sqrt(discriminant)) / (2 * a);
    print('Two real roots: x1 = $x1, x2 = $x2');
  } else if (discriminant == 0) {
    double x = -b / (2 * a);
    print('One real root: x = $x');
  } else {
    print('The equation has no real roots (Complex roots).');
  }
}
