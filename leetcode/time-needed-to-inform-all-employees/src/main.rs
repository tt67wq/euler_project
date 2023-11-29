// https://leetcode.cn/problems/time-needed-to-inform-all-employees/
pub struct Solution {}

impl Solution {
    pub fn num_of_minutes(n: i32, head_id: i32, manager: Vec<i32>, inform_time: Vec<i32>) -> i32 {
        fn dfs(
            graph: &Vec<Vec<usize>>,
            manager: &Vec<i32>,
            inform_time: &Vec<i32>,
            i: usize,
        ) -> i32 {
            let mut max = 0;
            if graph[i].is_empty() {
                return max;
            }
            for j in 0..graph[i].len() {
                max = max.max(dfs(graph, manager, inform_time, graph[i][j]));
            }
            max + inform_time[i]
        }

        let mut graph = vec![vec![]; n as usize];
        for i in 0..n as usize {
            if manager[i] != -1 {
                graph[manager[i] as usize].push(i);
            }
        }
        return dfs(&graph, &manager, &inform_time, head_id as usize);
    }
}
