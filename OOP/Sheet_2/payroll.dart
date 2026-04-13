import 'dart:io';

void main() {
  while (true) {
    print('\nEnter Paycode (1:Mgr, 2:Hrly, 3:Comm, 4:Piece, 0:Exit): ');
    int code = int.parse(stdin.readLineSync()!);
    if (code == 0) break;

    double weeklyPay = 0;

    switch (code) {
      case 1: // Manager
        stdout.write('Enter fixed weekly salary: ');
        weeklyPay = double.parse(stdin.readLineSync()!);
        break;

      case 2: // Hourly
        stdout.write('Enter hourly wage: ');
        double wage = double.parse(stdin.readLineSync()!);
        stdout.write('Enter hours worked: ');
        double hours = double.parse(stdin.readLineSync()!);
        weeklyPay = (hours <= 40)
            ? (hours * wage)
            : (40 * wage) + ((hours - 40) * wage * 1.5);
        break;

      case 3: // Commission
        stdout.write('Enter gross weekly sales: ');
        double sales = double.parse(stdin.readLineSync()!);
        weeklyPay = 250 + (sales * 0.057);
        break;

      case 4: // Pieceworker
        stdout.write('Enter number of items produced: ');
        int items = int.parse(stdin.readLineSync()!);
        stdout.write('Enter pay per item: ');
        double perItem = double.parse(stdin.readLineSync()!);
        weeklyPay = items * perItem;
        break;

      default:
        print('Invalid paycode.');
        continue;
    }
    print('Weekly pay is: \$${weeklyPay.toStringAsFixed(2)}');
  }
}
