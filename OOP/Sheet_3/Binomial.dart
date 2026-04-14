import 'dart:io';

int factorial(int x) {
  int sum = 1;
  for (int i = 1; i <= x; i++) {
    sum *= i;
  }
  return sum;
}

int getInt(String msg) {
  String? userInput;
  var value;
  while (true) {
    stdout.write(msg);
    userInput = stdin.readLineSync();
    if (userInput != null) {
      value = int.tryParse(userInput);
      if (value != null) {
        return value;
      }
    }
  }
}

main() {
  int n, k;
  n = getInt("Enter n: ");
  k = getInt("Enter k: ");
  if (k < 0 || n < 0) {
    stdout.writeln("Invalid Input: N and K must be positive.");
    return 1;
  }
  if (k > n)
    stdout.writeln(0);
  else if (k == 0 || k == n)
    stdout.writeln(1);
  else {
    stdout.writeln((factorial(n)) / (factorial(k) * factorial(n - k)));
  }
  return 0;
}
