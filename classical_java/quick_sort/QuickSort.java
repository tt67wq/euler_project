public class QuickSort {
        public static void main(String[] args) {
                int[] nums;
                int l;

                nums = new int[] {12, 23, 4, 65, 76, 22, 13, 2, 1, 0};
                l = nums.length;

                quick_sort(nums, 0, l - 1);
                view_list(nums);
                return;
        }
        private static void quick_sort(int[] nums, int begin, int end) {

                int i, j, tmp;

                if (begin < end) {
                        i = begin + 1;
                        j = end;
                        for (; i < j;) {
                                if (nums[i] > nums[begin]) {
                                        // swap
                                        tmp = nums[i];
                                        nums[i] = nums[j];
                                        nums[j] = tmp;
                                        j--;
                                } else {
                                        i++;
                                }
                        }
                        // j == i
                        if (nums[i] >= nums[begin]) {
                                i--;
                        }
                        tmp = nums[i];
                        nums[i] = nums[begin];
                        nums[begin] = tmp;

                        quick_sort(nums, begin, i);
                        quick_sort(nums, j, end);
                }
                return;
        }
        private static void view_list(int[] nums) {
                int i, l;
                l = nums.length;
                for (i = 0; i < l; i++) {
                        System.out.printf("%d ", nums[i]);
                }
                System.out.print("\n");
        }
}
