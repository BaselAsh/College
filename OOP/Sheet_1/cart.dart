import 'dart:io';

void main() {
  List<String> items = [];
  List<double> prices = [];
  double total = 0;

  while (true) {
    stdout.write('Enter an item (or "done" to exit): ');
    String input = stdin.readLineSync()!.toLowerCase();

    if (input == 'done') break;

    stdout.write('Enter the price: ');
    double price = double.parse(stdin.readLineSync()!);

    items.add(input);
    prices.add(price);
    total += price;
  }

  print('\nShopping cart:');
  for (int i = 0; i < items.length; i++) {
    print('${items[i].padRight(10)} \$${prices[i].toStringAsFixed(1)}');
  }
  print('\nTotal price: \$${total.toStringAsFixed(2)}');
}
