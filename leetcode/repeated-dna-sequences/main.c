#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uthash.h>

/* 所有 DNA 都由一系列缩写为 'A'，'C'，'G' 和 'T' 的核苷酸组成，
   例如："ACGAATTCCG"。在研究 DNA 时，识别 DNA 中的重复序列有时会对研究非常有帮助。 */

/* 编写一个函数来找出所有目标子串，目标子串的长度为 10，且在 DNA 字符串 s 中出现次数超过一次。 */

/*   */

/* 示例 1： */

/* 输入：s = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT" */
/* 输出：["AAAAACCCCC","CCCCCAAAAA"] */
/* 示例 2： */

/* 输入：s = "AAAAAAAAAAAAA" */
/* 输出：["AAAAAAAAAA"] */

/* 提示： */

/* 0 <= s.length <= 105 */
/* s[i] 为 'A'、'C'、'G' 或 'T' */

/* 来源：力扣（LeetCode） */
/* 链接：https://leetcode-cn.com/problems/repeated-dna-sequences */
/* 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */
#define MAX 1000

struct counter_t {
        int seq;
        int cnt;
        UT_hash_handle hh;
};

char dnaBitmap(char h) {
        char ret = 0;
        switch (h) {
        case 'A':
                ret = 0x00;
                break;
        case 'C':
                ret = 0x01;
                break;
        case 'G':
                ret = 0x02;
                break;
        case 'T':
                ret = 0x03;
                break;
        default:
                break;
        }
        return ret;
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **findRepeatedDnaSequences(char *s, int *returnSize) {
        *returnSize = 0;
        if (strlen(s) < 10) {
                return NULL;
        }
        int i, acc = 0;
        char **ans, **ansp;
        ans = (char **)malloc(MAX * sizeof(char *));
        ansp = ans;
        for (i = 0; i < 10; ++i) {
                acc = (acc << 2) | dnaBitmap(s[i]);
        }
        struct counter_t *counter = NULL;
        struct counter_t *m = NULL;
        m = (struct counter_t *)malloc(sizeof(*m));
        m->seq = acc;
        m->cnt = 1;
        HASH_ADD_INT(counter, seq, m);
        for (i = 0; i < strlen(s) - 10; ++i) {
                acc = ((acc << 2) | dnaBitmap(s[i + 10])) & ((1 << 20) - 1);
                printf("str=%.10s, acc=%d\n", s + i, acc);
                struct counter_t *m = NULL;
                HASH_FIND_INT(counter, &acc, m);
                if (m) {
                        if (++(m->cnt) == 2) {
                                *ansp = (char *)calloc(11, sizeof(char));
                                strncpy(*ansp, s + i + 1, 10 * sizeof(char));
                                ansp++;
                                *returnSize += 1;
                        }
                } else {
                        m = (struct counter_t *)malloc(sizeof(*m));
                        m->seq = acc;
                        m->cnt = 1;
                        HASH_ADD_INT(counter, seq, m);
                }
        }
        return ans;
}

int main(int argc, char *argv[]) {
        char s[] = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
        int returnSize;
        char **ans = findRepeatedDnaSequences(s, &returnSize);
        for (int i = 0; i < returnSize; ++i) {
                puts(ans[i]);
        }

        return 0;
}
