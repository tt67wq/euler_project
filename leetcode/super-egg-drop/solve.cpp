class Solution {
      public:
        vector<pair<int, int>> q; // egg used, depth

        int superEggDrop(int K, int N) {
                int ans = 0, tail = 1;
                q.resize(N + 2);
                q[0].first = 0;
                q[0].second = 1;

                for (int cnt = 0; tail < N; cnt++) {
                        int egg_used = q[cnt].first, depth = q[cnt].second;

                        //加入左孩子（鸡蛋不碎为左）
                        q[tail].first = egg_used;
                        q[tail].second = q[cnt].second + 1;
                        tail++;

                        //加入右孩子（鸡蛋碎为右）
                        if (egg_used < K - 1) {
                                q[tail].first = egg_used + 1;
                                q[tail].second = q[cnt].second + 1;
                                tail++;
                        }
                }

                return q[N - 1].second;
        }
};
