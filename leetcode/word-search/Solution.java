class Solution {
        public boolean exist(char[][] board, String word) {
                int l, w, i, j;
                boolean[][] vis;

                l = board.length;
                w = board[0].length;
                vis = new boolean[l][w];

                for (i = 0; i < l; i++) {
                        for (j = 0; j < w; j++) {
                                if (board[i][j] == word.charAt(0)) {
                                        if (dfs(board, word, 0, i, j, vis)) {
                                                return true;
                                        }
                                }
                        }
                }
                return false;
        }

        private boolean dfs(char[][] board, String word, int deep, int r, int c, boolean[][] vis) {
                if (deep >= word.length()) {
                        return true;
                }
                if (r >= board.length || c >= board[0].length || r < 0 || c < 0) {
                        return false;
                }
                if (vis[r][c] || board[r][c] != word.charAt(deep)) {
                        return false;
                }
                deep++;
                vis[r][c] = true;
                if (dfs(board, word, deep, r + 1, c, vis) || dfs(board, word, deep, r, c + 1, vis) || dfs(board, word, deep, r - 1, c, vis) ||
                    dfs(board, word, deep, r, c - 1, vis)) {
                        return true;
                }
                vis[r][c] = false;
                return false;
        }
}
