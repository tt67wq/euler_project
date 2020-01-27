class Solution {
        public boolean canPlaceFlowers(int[] flowerbed, int n) {
                int count, can, first, i;

                count = 0;
                can = 0;
                first = 0;

                for (; first < flowerbed.length && flowerbed[first] == 0;) {
                        count++;
                        first++;
                }

                if (first == flowerbed.length) {
                        return (flowerbed.length + 1) / 2 >= n;
                }
                can += count / 2;
                count = 0;

                for (i = first + 1; i < flowerbed.length; i++) {
                        if (flowerbed[i] == 1) {
                                can += (count - 1) / 2;
                                count = 0;
                        } else {
                                count++;
                        }
                }
                can += (count / 2);
                return can >= n;
        }
}
