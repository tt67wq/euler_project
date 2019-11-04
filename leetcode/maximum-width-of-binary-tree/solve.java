class Solution {
    
    private int maxW = 0;
    
    public int widthOfBinaryTree(TreeNode root) {
        /**
        假设满二叉树表示成数组序列, 根节点所在的位置为1, 则任意位于i节点的左右子节点的index为2*i, 2*i+1
        用一个List保存每层的左端点, 易知二叉树有多少层List的元素就有多少个. 那么可以在dfs的过程中记录每个
        节点的index及其所在的层level, 如果level > List.size()说明当前节点就是新的一层的最左节点, 将其
        加入List中, 否则判断当前节点的index减去List中对应层的最左节点的index的宽度是否大于最大宽度并更新
        **/
        dfs(root, 1, 1, new ArrayList<>());
        return maxW;
    }
    
    private void dfs(TreeNode r, int level, int index, List<Integer> left) {
        if(r == null) return;
        if(level > left.size()) left.add(index);
        maxW = Math.max(maxW, index - left.get(level-1) + 1);
        dfs(r.left, level+1, index*2, left);
        dfs(r.right, level+1, index*2+1, left);
    }
}
