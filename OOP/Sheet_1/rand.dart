import 'dart:math';

void main() {
  var random = Random();
  print('10 Random numbers between 1 and 100:\n');
  for (int i = 0; i < 10; i++) {
    // nextInt(100) gives 0-99, so we add 1
    print(random.nextInt(100) + 1);
  }
}
