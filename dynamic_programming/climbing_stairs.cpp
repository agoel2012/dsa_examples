#include <iostream>
#include <vector>

using namespace std;

long long fibonaccirec(int n) {

  if (n <= 1) {
    return 1;
  }

  return (fibonaccirec(n - 1) + fibonaccirec(n - 2));
}

long long fibonaccidp(int n) {

  vector<long long> dp(n + 1, 0);
  dp[0] = 1;
  dp[1] = 1;

  for (int i = 2; i <= n; i++) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }

  return dp[n];
}

long long fibonacci(int n) { return fibonaccirec(n); }

int main(int argc, char *argv[]) {

  if (argc < 2) {
    cout << "Usage: ./main <num>" << endl;
    return 1;
  }

  int n = atoi(argv[1]);
  cout << fibonacci(n) << endl;
  return 0;
}
