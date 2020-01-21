/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     int val;
 *     ListNode next;
 *     ListNode(int x) { val = x; }
 * }
 */
class Solution {
        public ListNode mergeTwoLists(ListNode l1, ListNode l2) {
                ListNode h, c;

                h = new ListNode(0);
                c = h;

                for (; l1 != null && l2 != null;) {
                        if (l1.val < l2.val) {
                                c.next = l1;
                                c = c.next;
                                l1 = l1.next;
                        } else {
                                c.next = l2;
                                c = c.next;
                                l2 = l2.next;
                        }
                }

                // l1 == null or l2 == null

                if (l1 == null) {
                        c.next = l2;
                } else {
                        c.next = l1;
                }
                return h.next;
        }
}
