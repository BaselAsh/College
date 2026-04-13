void main() {
  double myPi = 0;
  int termsToReach314 = 0;
  int termsToReach3141 = 0;

  print('Terms | Approximation');
  print('---------------------');

  for (int k = 0; k < 20000; k++) {
    myPi += 4 * ((k % 2 == 0 ? 1 : -1) / (2 * k + 1));

    // Print first 10 terms for the table
    if (k < 10) {
      print('${(k + 1).toString().padRight(5)} | $myPi');
    }

    // Logic to find when specific milestones are hit
    String s = myPi.toString();
    if (termsToReach314 == 0 && s.startsWith('3.14')) termsToReach314 = k + 1;
    if (termsToReach3141 == 0 && s.startsWith('3.141'))
      termsToReach3141 = k + 1;
  }

  print('\nMilestones:');
  print('Terms to reach 3.14: $termsToReach314');
  print('Terms to reach 3.141: $termsToReach3141');
}
