class Solution {
        public int[] twoSum(int[] nums, int target) {
                Map<Integer, Integer> map;
                int i, l, tmp;
                int[] ans;

                ans = new int[2];
                map = new HashMap<>();
                l = nums.length;
                for (i = 0; i < l; i++) {
                        tmp = target - nums[i];
                        if (map.containsKey(tmp)) {
                                ans[0] = map.get(tmp);
                                ans[1] = i;
                                return ans;
                        }
                        map.put(nums[i], i); //不存在，则加入
                }
                throw new RuntimeException("No two sum solution");
        }
}
