#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 给你一个日志数组 logs。每条日志都是以空格分隔的字串，其第一个字为字母与数字混合的 标识符 。 */

/* 有两种不同类型的日志： */

/* 字母日志：除标识符之外，所有字均由小写字母组成 */
/* 数字日志：除标识符之外，所有字均由数字组成 */
/* 请按下述规则将日志重新排序： */

/* 所有 字母日志 都排在 数字日志 之前。 */
/* 字母日志 在内容不同时，忽略标识符后，按内容字母顺序排序；在内容相同时，按标识符排序。 */
/* 数字日志 应该保留原来的相对顺序。 */
/* 返回日志的最终顺序。 */

/*   */

/* 示例 1： */

/* 输入：logs = ["dig1 8 1 5 1","let1 art can","dig2 3 6","let2 own kit dig","let3 art zero"] */
/* 输出：["let1 art can","let3 art zero","let2 own kit dig","dig1 8 1 5 1","dig2 3 6"] */
/* 解释： */
/* 字母日志的内容都不同，所以顺序为 "art can", "art zero", "own kit dig" 。 */
/* 数字日志保留原来的相对顺序 "dig1 8 1 5 1", "dig2 3 6" 。 */
/* 示例 2： */

/* 输入：logs = ["a1 9 2 3 1","g1 act car","zo4 4 7","ab1 off key dog","a8 act zoo"] */
/* 输出：["g1 act car","a8 act zoo","ab1 off key dog","a1 9 2 3 1","zo4 4 7"] */
/*   */

/* 提示： */

/* 1 <= logs.length <= 100 */
/* 3 <= logs[i].length <= 100 */
/* logs[i] 中，字与字之间都用 单个 空格分隔 */
/* 题目数据保证 logs[i] 都有一个标识符，并且在标识符之后至少存在一个字 */

/* 来源：力扣（LeetCode） */
/* 链接：https://leetcode-cn.com/problems/reorder-data-in-log-files */
/* 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。 */

#define LETTER 1
#define NUMBER 0

int logType(const char *log) {
        char *fb = strchr(log, ' ');
        return *(fb + 1) >= '0' && *(fb + 1) <= '9' ? NUMBER : LETTER;
}

int cmpLetterLog(char *logA, char *logB) {
        char *fbA, *fbB;
        fbA = strchr(logA, ' ');
        fbB = strchr(logB, ' ');

        int res = strcmp(fbA + 1, fbB + 1);
        return res == 0 ? strcmp(logA, logB) : res;
}

int cmpfunc(const void *a, const void *b) {
        char *logA = *(char **)a;
        char *logB = *(char **)b;
        int logTypeA = logType(logA), logTypeB = logType(logB);
        if (logTypeA != logTypeB) {
                return logTypeA < logTypeB;
        }
        // same type
        if (logTypeA == LETTER) {
                return cmpLetterLog(logA, logB);
        }
        return 0;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **reorderLogFiles(char **logs, int logsSize, int *returnSize) {
        qsort(logs, logsSize, sizeof(char *), cmpfunc);
        *returnSize = logsSize;
        return logs;
}

int main(int argc, char *argv[]) {
        char log1[] = "dig1 8 1 5 1";
        char log2[] = "let1 art can";
        char log3[] = "dig2 3 6";
        char log4[] = "let2 own kit dig";
        char log5[] = "lket3 art zero";
        char log6[] = "let0 art can";

        char *logs[] = {log1, log2, log3, log4, log5, log6};
        int returnSize;
        reorderLogFiles(logs, 6, &returnSize);

        for (int i = 0; i < 6; ++i) {
                puts(logs[i]);
        }

        return 0;
}
