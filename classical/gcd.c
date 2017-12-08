/* 求最大公约数, 欧几里得算法 */

int gcd(int m, int n) {
  int r;
  if (m <= 0 || n <= 0)
    return 0;
  r = m % n;
  return r > 0 ? gcd(n, r) : n;
}
