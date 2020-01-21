class Solution {
        public boolean isPalindrome(int x) {
                if (x < 0) {
                        return false;
                }

                int r, y, q;

                q = x;
                r = 0;
                y = 0;

                for (; q != 0;) {
                        r = q % 10;
                        y = y * 10 + r;
                        q = q / 10;
                }
                return y == x;
        }
}
