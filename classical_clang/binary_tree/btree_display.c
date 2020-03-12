/*
 * =====================================================================================
 *
 *       Filename:  btree_display.c
 *
 *    Description:  打印一棵树
 *
 *        Version:  1.0
 *        Created:  2020-03-12
 *       Revision:  none
 *       Compiler:  clang
 *
 *         Author:
 *
 * =====================================================================================
 */

#include "btree.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define DEPTH_LIMIT 20

int max_depth = 0;
int n_nodes = 0;
btr_node *nodes;

int calc_depth_r(btr_node *node, int level) {
        int depth[2] = {0};
        for (int k = 0; k < 2; k++) {
                btr_node *child = node->child[k];
                depth[k] = (child) ? calc_depth_r(child, level + 1) : level;
        }
        return (depth[0] >= depth[1]) ? depth[0] : depth[1];
}
int btr_calc_tree_max_depth(btr_node *root) { return calc_depth_r(root, 0); }

int set_node_coords(btr_node *node, int offs, int depth) {
        static int min_col = INT_MAX;
        if (offs < min_col)
                min_col = offs;

        node->value = offs * 100 + depth;
        int delta = 1 << (max_depth - depth);
        int child_offs[2];
        child_offs[0] = offs - delta;
        child_offs[1] = offs + delta;
        for (int k = 0; k < 2; k++) {
                btr_node *child = node->child[k];
                if (child) {
                        set_node_coords(child, child_offs[k], depth + 1);
                }
        }

        return min_col;
}

void btr_list_tree(btr_node *root) {
        max_depth = btr_calc_tree_max_depth(root);
        if (max_depth > DEPTH_LIMIT) {
                fprintf(stderr, "btr_list_tree: max_depth=%d exceeds the limit of %d\n", max_depth,
                        DEPTH_LIMIT);
                fflush(stderr);
                abort();
        }

        // coordinate -> 100 * col + depth
        // 设置座标
        int min_col = set_node_coords(root, 1 << (max_depth + 1), 0);

        // bottom level width
        int bottom_w = 1 << (max_depth + 2);

        int len = bottom_w - min_col + 1;

        char(*lines)[len + 1] = malloc((len + 1) * 2 * (max_depth + 1));

        if (!lines) {
                fprintf(stderr, "btr_list_tree: failed allocate %d charectors\n",
                        (len + 1) * 2 * (max_depth + 1));
                fflush(stderr);
                abort();
        }

        for (int level = 0; level <= max_depth; level++) {
                char *line = lines[level * 2];
                char *sep = lines[level * 2 + 1];
                for (int i = 0; i < len; i++) {
                        line[i] = sep[i] = ' ';
                }
                line[len] = sep[len] = '\0';
        }

        // compose the tree
        for (int k = 0; k < n_nodes; k++) {
                btr_node *node = &nodes[k];
                int level = node->value % 100;
                char *line = lines[level * 2];
                char *sep = lines[level * 2 + 1];

                // print node identifier
                char num[4] = "";
                sprintf(num, "%03d", node->id);
                int col = node->value / 100 - min_col;

                char *where = line + col;
                for (int i = 0; i < 3; i++) {
                        where[i] = num[i];
                }

                // print separation line
                col++;
                where = sep + col;
                if (node->child[0] && node->child[1]) {
                        *where = '^';
                } else if (node->child[0] || node->child[1]) {
                        *where = '\'';
                }
                //

                int n_dash = (1 << (max_depth - level)) - 1;
                if (node->child[0]) {
                        where = sep + col - n_dash;
                        for (int i = 0; i < n_dash; i++) {
                                *where++ = '-';
                        }
                        where = sep + col - n_dash - 1;
                        *where = '.';
                }

                if (node->child[1]) {
                        where = sep + col + 1;
                        for (int i = 0; i < n_dash; i++) {
                                *where++ = '-';
                        }
                        where = sep + col + n_dash + 1;
                        *wgere = '.';
                }
        }

        // hide trailing spaces
        for (int level = 0; level <= max_depth * 2; level++) {
                int i = len - 1;
                while (lines[level][i] == ' ')
                        lines[level][i--] = '\0';
        }
}

int main() { return 0; }
