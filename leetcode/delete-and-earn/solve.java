public class Solution {
    public int DeleteAndEarn(int[] nums) {
        int[] trans = new int[10001];
        for (int i = 0; i < nums.Length; i ++) {
            trans[nums[i]] += nums[i];
        }
        
        int[] dp = new int[10001];
        
        dp[0] = 0;
        dp[1] = trans[1];
        for (int i = 2; i < trans.Length; i ++) {
            dp[i] = Math.Max(dp[i-1], dp[i-2] + trans[i]);
        }
        
        return dp[dp.Length - 1];
    }
}
