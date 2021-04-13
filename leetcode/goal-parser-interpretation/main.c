/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2021-04-13
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 请你设计一个可以解释字符串 command 的 Goal 解析器 。command 由 "G"、"()" 和/或 "(al)"
// 按某种顺序组成。 Goal 解析器会将 "G" 解释为字符串 "G"、"()" 解释为字符串 "o" ，"(al)"
// 解释为字符串 "al" 。然后，按原顺序将经解释得到的字符串连接成一个字符串。

// 给你字符串 command ，返回 Goal 解析器 对 command 的解释结果。

//  

// 示例 1：

// 输入：command = "G()(al)"
// 输出："Goal"
// 解释：Goal 解析器解释命令的步骤如下所示：
// G -> G
// () -> o
// (al) -> al
// 最后连接得到的结果是 "Goal"
// 示例 2：

// 输入：command = "G()()()()(al)"
// 输出："Gooooal"
// 示例 3：

// 输入：command = "(al)G(al)()()G"
// 输出："alGalooG"
//  

// 提示：

// 1 <= command.length <= 100
// command 由 "G"、"()" 和/或 "(al)" 按某种顺序组成

// 来源：力扣（LeetCode）
// 链接：https://leetcode-cn.com/problems/goal-parser-interpretation
// 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

bool check_buff(char *buff) {
        if (strcmp(buff, "G") == 0) {
                strcpy(buff, "G");
                return true;
        }
        if (strcmp(buff, "()") == 0) {
                strcpy(buff, "o");
                return true;
        }
        if (strcmp(buff, "(al)") == 0) {
                strcpy(buff, "al");
                return true;
        }
        return false;
}

char *interpret(char *command) {
        char *ans = (char *)malloc(sizeof(char) * (strlen(command) + 1));
        char *buff = (char *)malloc(sizeof(char) * 5);
        memset(buff, 0, sizeof(char) * 5);
        memset(ans, 0, sizeof(char) * (strlen(command) + 1));
        int i = 0, j = 0;
        bool in_pair = false;
        while (i < strlen(command)) {
                buff[j++] = command[i];
                if (command[i] == '(') {
                        in_pair = true;
                }
                if (command[i] == ')') {
                        in_pair = false;
                }
                if (!in_pair && check_buff(buff)) {
                        strcat(ans, buff);
                        memset(buff, 0, sizeof(char) * 5);
                        j = 0;
                }
                i++;
        }
        return ans;
}

int main() {
        char cmd[] = "G()(al)";
        puts(interpret(cmd));
        return 0;
}