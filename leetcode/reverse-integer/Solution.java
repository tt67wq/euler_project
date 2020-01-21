
class Solution {
        public int reverse(int x) {
                long n;

                n = 0;
                for (; x != 0;) {
                        n = n * 10 + x % 10;
                        x /= 10;
                }

                if ((int)n == n) {
                        return (int)n;
                }
                return 0;
        }
}
