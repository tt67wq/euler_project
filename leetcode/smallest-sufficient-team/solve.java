/**
 * @author li
 * @version 1.0
 * @date 2019-09-28 22:12
 * S是一个整数，表示一个二进制集合。S中第i位是1表示该集合包含标号是i的技能。
 * 令dp[S]表示要获得集合S表示的技能的最小花费.也就是最少需要选多少人。
 * 假设技能个数是n，那么要求的最小花费就是dp[(1 << n)-1]。
 * 对于状态转移方程:
 * 假设当前第i个人的技能集合是整数now.我们就拿当前的技能集合
 * now去更新每一个dp[now|j], 0 <= j < (1 << n)的值。
 * 使用team列表维护每一个集合S的最优团队列表，team[(1<<n)-1]即最终团队成员列表
 **/
class Solution {
    public int[] smallestSufficientTeam(String[] reqSkills, List<List<String>> peoSkills) {
        if (reqSkills == null || reqSkills.length == 0) {
            return new int[0];
        }
        int n = reqSkills.length;
        Map<String, Integer> map = new HashMap<>(n);
        // 技能、序号映射
        for (int i = 0; i < reqSkills.length; i++) {
            map.put(reqSkills[i], i);
        }
        int[] dp = new int[(1 << n)];
        Arrays.fill(dp, -1);
        // 技能集合i所需的最小团队编号列表
        List<List<Integer>> team = new ArrayList<>(1 << n);
        for (int i = 0; i < (1 << n); i++) {
            team.add(new LinkedList<>());
        }
        // 集合0表示的技能的最小花费是0
        dp[0] = 0;
        for (int i = 0; i < peoSkills.size(); i++) {
            int now = 0;
            for (String s : peoSkills.get(i)) {
                int x = map.get(s);
                now |= (1 << x);
            }
            for (int j = 0; j < (1 << n); j++) {
                // 更新已经计算过的集合
                if (dp[j] >= 0) {
                    // 将要更新的集合x
                    int x = now | j;
                    // 如果集合没有计算过或者可以优化
                    if (dp[x] == -1 || dp[x] > dp[j] + 1) {
                        dp[x] = dp[j] + 1;
                        team.get(x).clear();
                        team.get(x).addAll(team.get(j));
                        team.get(x).add(i);
                    }
                }
            }
        }
        // team[(1<<n)-1]即最终团队
        int[] ans = new int[team.get((1 << n) - 1).size()];
        int i = 0;
        for (int idx : team.get((1 << n) - 1)) {
            ans[i++] = idx;
        }
        return ans;
    }
}
