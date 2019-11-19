public int maxLevelSum(TreeNode root) {

    if (root == null)
	return 0;

    int sum_max = root.val, level = 1, max_level = 1;
    Queue<TreeNode> queue = new LinkedList<>();
    queue.offer(root);

    while (!queue.isEmpty()) {

	int size = queue.size(), curr_sum = 0;
	for (int i = 0; i < size; i++) {

	    TreeNode curr = queue.poll();
	    curr_sum += curr.val;
	    if (curr.left != null)
		queue.offer(curr.left);
	    if (curr.right != null)
		queue.offer(curr.right);
	}
	if (curr_sum > sum_max) {
	    sum_max = curr_sum;
	    max_level = level;
	}
	level++;
    }
    return max_level;
}
