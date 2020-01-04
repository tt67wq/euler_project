/*
 * 链表插入排序(由小到大)。
 * 输入：链表的头指针，
 * 输出：排序后链表的头指针。
 * 实现方法：将原链表拆成两部分：链表1仍以head为头指针，链表结点有序。链表2以head2为头指针，链表结点无序。
 * 将链表2中的结点依次插入到链表1中，并保持链表1有序。
 * 最后链表1中包含所有结点，且有序。
 */
LinkList LinkInsertSort(LinkList head) {
        // current指向当前待插入的结点。
        LinkList head2, current, p, q;

        if (head == NULL)
                return head;

        //第一次拆分。
        head2 = head->next;
        head->next = NULL;

        while (head2) {
                current = head2;
                head2 = head2->next;

                //寻找插入位置，插入位置为结点p和q中间。
                for (p = NULL, q = head; q && q->data <= current->data; p = q, q = q->next)
                        ;

                if (q == head) {
                        //将current插入最前面。
                        head = current;
                } else {
                        p->next = current;
                }
                current->next = q;
        }
        return head;
}
