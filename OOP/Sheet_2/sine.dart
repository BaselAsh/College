import 'dart:io';
import 'dart:math';

// Helper function for factorial
double factorial(int n) {
  if (n == 0) return 1;
  double result = 1;
  for (int i = 1; i <= n; i++) result *= i;
  return result;
}

void main() {
  stdout.write('Enter value of x (in radians): ');
  double x = double.parse(stdin.readLineSync()!);
  stdout.write('Enter number of terms (k): ');
  int k = int.parse(stdin.readLineSync()!);

  double customSin = 0;
  for (int n = 0; n < k; n++) {
    double term = (pow(-1, n) / factorial(2 * n + 1)) * pow(x, 2 * n + 1);
    customSin += term;
  }

  print('\nResults:');
  print('Custom Taylor Series Sin($x) ≈ $customSin');
  print('Pre-defined math.sin($x)  = ${sin(x)}');
  print('Difference: ${(sin(x) - customSin).abs()}');
}
