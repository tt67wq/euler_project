# 欧拉计划(Project Euler)

----

算法练习部分，目录分类一塌糊涂，我也不打算好好整理了，就这么乱吧
解的题有 欧拉计划，ZOJ(这破网站最近登不上了)

### 目录树
```
.
├── classical_clang c语言算法练习
│   ├── array 动态数组
│   ├── avl  avlu树
│   ├── balance_check 平衡检察
│   ├── bigint  大数实现
│   ├── binary_heap  二插堆
│   ├── bloom_filter 布隆过滤器
│   ├── bst 二叉查找树
│   ├── bucket_sort.c 筒排序
│   ├── chinese_num
│   ├── d_heap d堆
│   ├── disjoinset 并查集
│   ├── double_queue 双端链
│   ├── factor 因数分解
│   ├── farey_series 法力序列
│   ├── fft.c 傅里叶变换
│   ├── gcd.c 欧几里得算法
│   ├── genetic_algorithm 遗传算法
│   ├── google_equation.c 谷歌方程式
│   ├── graph 图论部分
│   ├── hash 哈希
│   ├── heap 堆
│   ├── huffman_tree 霍夫曼编码
│   ├── karastuba.c 大数相乘
│   ├── kmp kmp匹配
│   ├── knapsack.c 背包问题
│   ├── lca 离线算法求解公共祖先
│   ├── left_heap 左式堆
│   ├── link_list_c 链表
│   ├── merge_sort 合并排
│   ├── miller_rabin 素数筛查
│   ├── niyuan 中国剩余定理
│   ├── nums_inline 直线上的整数点
│   ├── permutation 排列组合
│   ├── phi_sieve 欧拉计数函数筛子
│   ├── prime_generator 素数生成器
│   ├── prime_sieve 素数筛子
│   ├── queue 队列
│   ├── quick_sort 快排
│   ├── radix_sort.c 基数排序
│   ├── recursive_power.c 递归求幂
│   ├── sa
│   ├── skew_heap 斜堆
│   ├── skip_list 跳表
│   ├── splay_tree 伸展树
│   ├── stack 栈
│   ├── stern_brocot Stern-Brocot树
│   ├── sunday
│   ├── top_sort 拓扑排序
│   ├── trie trie树
│   └── zuhe
├── classical_elixir
│   ├── analytic_geometry 解析几何
│   ├── btree_bfs bfs
│   ├── bucket.ex 桶排序
│   ├── cache.exs 缓存
│   ├── cocktail_sort 鸡尾酒排序
│   ├── coin-change.ex 换硬币问题
│   ├── combination.ex 组合
│   ├── date_tool.ex
│   ├── dijkstra.ex 图论dijkstra
│   ├── disjoin_set.ex 并查集
│   ├── einstein_problem 爱因斯坦思考题
│   ├── elixir_queue 队列
│   ├── factorize.ex 因数分解
│   ├── farey_series.ex 法力序列
│   ├── gcd.exs 欧几里得算法
│   ├── generator.exs
│   ├── insert_sort.exs 插入排序
│   ├── kruskal.ex 最小生成树算法
│   ├── lcm.ex
│   ├── libgraph 图论部分
│   ├── line_hash.ex 线性哈希
│   ├── max_sub_sum.ex
│   ├── merge_sort.ex 合并排
│   ├── miller_rabin_prime.ex 素数校验
│   ├── mod_comb.ex
│   ├── monk_and_monster.ex
│   ├── patricia
│   ├── permutation.ex 排列组合
│   ├── pow_mod.ex
│   ├── prime_sieve.ex 素数筛子
│   ├── red_black_tree 红黑树
│   ├── rle
│   ├── root_convergent.exs
│   ├── shell_sort 希尔排
│   ├── skip_list 跳表
│   ├── skip_list.ex
│   ├── stable_match.ex 稳定匹配
│   ├── step_in_primes.ex
│   ├── string_patricia
│   ├── string_trie
│   ├── suffix_trie 前缀树
│   ├── test_port.ex
│   ├── top_sort 拓扑排序
│   ├── totient_function.ex
│   ├── triangles.exs
│   ├── union_find
│   ├── water_split.ex
│   └── zuheshu.ex
├── classical_golang
│   ├── chinese_remainder 中国剩余定理
│   ├── heap 堆
│   ├── max_min_int.go
│   ├── queue 队列
│   ├── quick_sort 快排
│   ├── reverse_string.go
│   └── union_set 并查集
├── classical_python
│   ├── avl.py avl树
│   ├── bst.py 二叉搜索树
│   ├── crt.py 中国剩余定理
│   ├── factor.py 因数分解
│   ├── manacher 马拉车算法
│   └── sieve.py 素数筛子
├── euler 欧拉计划部分
├── leetcode
│   ├── 4sum-ii
│   ├── add-and-search-word-data-structure-design
│   ├── add-to-array-form-of-integer
│   ├── all-paths-from-source-to-target
│   ├── average-of-levels-in-binary-tree
│   ├── baseball-game
│   ├── basic-calculator
│   ├── basic-calculator-ii
│   ├── beautiful-arrangement
│   ├── beautiful-array
│   ├── best-time-to-buy-and-sell-stock-ii
│   ├── best-time-to-buy-and-sell-stock-iii
│   ├── binary-number-with-alternating-bits
│   ├── binary-search-tree-to-greater-sum-tree
│   ├── binary-tree-maximum-path-sum
│   ├── binary-tree-tilt
│   ├── bitwise-ors-of-subarrays
│   ├── bulb-switcher
│   ├── camelcase-matching
│   ├── check-if-word-is-valid-after-substitutions
│   ├── combinations
│   ├── combination-sum
│   ├── construct-binary-tree-from-inorder-and-postorder-traversal
│   ├── construct-string-from-binary-tree
│   ├── decoded-string-at-index
│   ├── decrease-elements-to-make-array-zigzag
│   ├── deep-dark-fraction
│   ├── delete-and-earn
│   ├── delete-columns-to-make-sorted
│   ├── delete-node-in-a-bst
│   ├── distribute-candies-to-people
│   ├── domino-and-tromino-tiling
│   ├── edit-distance
│   ├── elimination-game
│   ├── find-duplicate-file-in-system
│   ├── find-median-from-data-stream
│   ├── find-smallest-letter-greater-than-target
│   ├── find-the-town-judge
│   ├── first-missing-positive
│   ├── gas-station
│   ├── generate-parentheses
│   ├── global-and-local-inversions
│   ├── guess-numbers
│   ├── hand-of-straights
│   ├── happy-number
│   ├── height-checker
│   ├── house-robber
│   ├── increasing-subsequences
│   ├── insert-interval
│   ├── insertion-sort-list
│   ├── integer-replacement
│   ├── island-perimeter
│   ├── jump-game-ii
│   ├── knight-probability-in-chessboard
│   ├── k-similar-strings
│   ├── kth-largest-element-in-an-array
│   ├── largest-divisible-subset
│   ├── largest-number
│   ├── largest-palindrome-product
│   ├── letter-combinations-of-a-phone-number
│   ├── license-key-formatting
│   ├── linked-list-cycle-ii
│   ├── longest-absolute-file-path
│   ├── longest-common-prefix
│   ├── longest-consecutive-sequence
│   ├── longest-continuous-increasing-subsequence
│   ├── longest-mountain-in-array
│   ├── longest-substring-with-at-least-k-repeating-characters
│   ├── longest-turbulent-subarray
│   ├── matrix-cells-in-distance-order
│   ├── maximum-level-sum-of-a-binary-tree
│   ├── maximum-number-of-balloons
│   ├── maximum-swap
│   ├── maximum-width-of-binary-tree
│   ├── middle-of-the-linked-list
│   ├── minimum-increment-to-make-array-unique
│   ├── minimum-swaps-to-make-sequences-increasing
│   ├── minimum-swaps-to-make-strings-equal
│   ├── minimum-window-substring
│   ├── mirror-reflection
│   ├── next-greater-element-iii
│   ├── number-of-dice-rolls-with-target-sum
│   ├── number-of-ways-to-stay-in-the-same-place-after-some-steps
│   ├── out-of-boundary-paths
│   ├── pascals-triangle-ii
│   ├── peak-index-in-a-mountain-array
│   ├── permutations
│   ├── play-with-chips
│   ├── predict-the-winner
│   ├── product-of-array-except-self
│   ├── rabbits-in-forest
│   ├── range-sum-query-2d-immutable
│   ├── regular-expression-matching
│   ├── relative-sort-array
│   ├── remove-duplicates-from-sorted-array
│   ├── remove-nth-node-from-end-of-list
│   ├── reordered-power-of-2
│   ├── reorder-list
│   ├── repeated-string-match
│   ├── repeated-substring-pattern
│   ├── replace-the-substring-for-balanced-string
│   ├── reshape-the-matrix
│   ├── reveal-cards-in-increasing-order
│   ├── reverse-nodes-in-k-group
│   ├── reverse-only-letters
│   ├── reverse-substrings-between-each-pair-of-parentheses
│   ├── rotate-array
│   ├── rotate-image
│   ├── rotate-list
│   ├── search-insert-position
│   ├── shortest-bridge
│   ├── shortest-completing-word
│   ├── shortest-path-in-binary-matrix
│   ├── shortest-unsorted-continuous-subarray
│   ├── smallest-string-with-swaps
│   ├── smallest-sufficient-team
│   ├── sort-an-array
│   ├── sort-array-by-parity
│   ├── sort-colors
│   ├── sort-list
│   ├── student-attendance-record-i
│   ├── student-attendance-record-ii
│   ├── subarray-product-less-than-k
│   ├── subarray-sums-divisible-by-k
│   ├── subtree-of-another-tree
│   ├── super-egg-drop
│   ├── symmetric-tree
│   ├── to-lower-case
│   ├── ugly-number
│   ├── uncommon-words-from-two-sentences
│   ├── validate-stack-sequences
│   ├── valid-boomerang
│   ├── valid-mountain-array
│   ├── valid-palindrome-ii
│   ├── valid-square
│   ├── verifying-an-alien-dictionary
│   ├── word-pattern
│   └── xor-game
├── lintcode
│   ├── candy
│   ├── find-smallest-letter-greater-than-target
│   ├── kth-smallest-element-in-a-bst
│   ├── longest-common-subsequenc
│   ├── search-in-rotated-sorted-array
│   ├── teemo-attacking
│   └── two-sum
├── README.md
├── xuanxue
│   ├── config.py
│   ├── demo.py
│   ├── __pycache__
│   └── zhouyi.py
└── zoj
    ├── 1001
    ├── 1002
    ├── 1003
    ├── 1004
    ├── 1005
    ├── 1006
    ├── 1007
    ├── 1008
    ├── 1009
    ├── 1010
    ├── 1011
    ├── 1036
    ├── 1037
    ├── 1045
    ├── 1047
    ├── 1048
    ├── 1049
    ├── 1062
    ├── 1067
    ├── 1070
    ├── 1088
    ├── 1091
    ├── calandar
    ├── sekiro
    ├── stone_in_bucket
    └── string_in_pocket

```


### [欧拉计划](https://github.com/tt67wq/euler_project/tree/master/euler)
### [LeetCode](https://github.com/tt67wq/euler_project/tree/master/leetcode)
### [科学算命](https://github.com/tt67wq/euler_project/tree/master/xuanxue)
### [ZOJ](https://github.com/tt67wq/euler_project/tree/master/zoj)

### [Python经典算法实现](https://github.com/tt67wq/euler_project/tree/master/classical_python)
### [C经典算法实现](https://github.com/tt67wq/euler_project/tree/master/classical_clang)
### [Golang经典算法实现](https://github.com/tt67wq/euler_project/tree/master/classical_golang)
### [Elixir经典算法实现](https://github.com/tt67wq/euler_project/tree/master/classical_elixir)

