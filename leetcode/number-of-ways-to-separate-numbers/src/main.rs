// https://leetcode.cn/problems/number-of-ways-to-separate-numbers/
pub struct Solution {}
impl Solution {
    pub fn number_of_combinations(num: String) -> i32 {
        if num.as_bytes()[0] == b'0' {
            return 0;
        }

        let m = 1_000_000_007;
        let n = num.len();
        let mut dp = vec![vec![0; n]; n];
        dp[0].fill(1);
        for i in 1..n {
            if num.as_bytes()[i] == b'0' {
                continue;
            }

            let mut s = 0;
            for j in i..n.min(i + i) {
                let mut ss = (s + dp[2 * i - 1 - j][i - 1]) % m;
                if num[i..=j] >= num[(2 * i - 1 - j)..i] {
                    dp[i][j] = ss;
                } else {
                    dp[i][j] = s;
                }
                s = ss;
            }
            dp[i][n.min(i + i)..].fill(s);
        }
        dp.iter()
            .map(|v| v[n - 1] as i32)
            .fold(0, |acc, v| (acc + v) % m)
    }
}
