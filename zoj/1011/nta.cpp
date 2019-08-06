/*
 * =====================================================================================
 *
 *       Filename:  nta.cpp
 *
 *    Description:  zoj 1011 实在自己用C做不出，去网上抄一个过来搞懂吧
 *
 *        Version:  1.0
 *        Created:  2019-08-01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  fangyuan
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
using namespace std;

int N, M, K, cs = 0, L, ts;
int sign[16][10][100][2], size[15][10];
char tree[3000];
char ch[1000];

void trans(int r, int c) // r表示数字，c表示字母，下同。
{
        int i, l = strlen(ch);
        int sum = 0, x[2], j, k;
        for (i = 0, j = 0; i < l; i++) {
                if (ch[i] >= '0' && ch[i] <= '9')
                        sum = sum * 10 + ch[i] - '0';
                else {
                        x[j] = sum;
                        sum = 0;
                        j = 1 - j;
                        if (j == 0) {
                                k = size[r][c];
                                sign[r][c][k][0] = x[0], sign[r][c][k][1] = x[1];
                                size[r][c]++;
                        }
                }
        }
        x[1] = sum;
        k = size[r][c];
        sign[r][c][k][0] = x[0], sign[r][c][k][1] = x[1];
        size[r][c]++;
}

int init() {
        cin >> N >> M >> K;
        gets(ch);
        memset(size, 0x00, sizeof(size));
        int i, j;
        for (i = 0; i < N; i++) {
                for (j = 0; j < K; j++) {
                        gets(ch);
                        trans(i, j);
                }
        }
        for (i = 0; i < 3000; i++)
                tree[i] = '*';
        // ps ();
        return N;
}

int dfs(int node, int s) // 强搜吧……
{
        int r = s, c = tree[node] - 'a', left = node * 2, right = node * 2 + 1;
        // printf  ( "%c %d ", tree[node], s );
        if (tree[node] == '*')
                return s < N && s >= N - M;
        int i;
        for (i = 0; i < size[r][c]; i++) {
                int ls = sign[r][c][i][0], rs = sign[r][c][i][1];
                if (dfs(left, ls) && dfs(right, rs))
                        return 1;
        }
        return 0;
}

void proc() {
        if (cs++)
                printf(" ");
        printf("NTA%d: ", cs);
        int i, j;
        while (cin >> L) {
                if (L == -1)
                        break;
                ts = 0;
                for (i = 0; i <= L; i++) {
                        for (j = 0; j < (1 << i); j++)
                                cin >> tree[++ts];
                }
                // pt ();
                if (dfs(1, 0))
                        printf("Valid ");
                else
                        printf("Invalid ");
        }
}

int main() {
        // freopen ( "in.txt", "r", stdin );
        while (init()) {
                proc();
        }
        return 0;
}
