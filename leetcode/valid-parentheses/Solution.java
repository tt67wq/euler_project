class Solution {
        public boolean isValid(String s) {
                Stack<Character> stack;
                char[] cs;
                int i, l;
                char c;

                stack = new Stack<>();
                cs = s.toCharArray();
                l = cs.length;

                for (i = 0; i < l; i++) {
                        c = cs[i];
                        if (stack.size() == 0) {
                                stack.push(c);
                        } else if (isPair(stack.peek(), c)) {
                                stack.pop();
                        } else {
                                stack.push(c);
                        }
                }
                return stack.size() == 0;
        }

        private boolean isPair(char a, char b) {
                if (a == '(' && b == ')') {
                        return true;
                }
                if (a == '[' && b == ']') {
                        return true;
                }
                if (a == '{' && b == '}') {
                        return true;
                }
                return false;
        }
}
