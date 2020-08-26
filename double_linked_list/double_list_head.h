#ifndef _LinkedListNode_H_
#define _LinkedListNode_H_


typedef struct ListNode {
    ListNode *next;
    ListNode *prev;
}ListNode;

typedef ListNode ListHead;

//add node between prev and next
inline void __list_add(ListNode *node, ListNode *prev, ListNode *next) {
    next->prev = node;
    node->next = next;
    node->prev = prev;
    prev->next = node;
}

inline void __list_del(ListNode * prev, ListNode * next) {
    next->prev = prev;
    prev->next = next;
}

inline void init_list_head(ListNode *head) {
    head->next = head;
    head->prev = head;
}

inline void list_add(ListNode *node, ListNode *head) {
    __list_add(node, head, head->next);
}

inline void list_add_tail(ListNode *node, ListNode *head) {
    __list_add(node, head->prev, head);
}

inline void list_del(ListNode *entry) {
    __list_del(entry->prev, entry->next);
    entry->prev = 0;
    entry->next = 0;
}

inline void list_replace(ListNode *old, ListNode *newly) {
    newly->next = old->next;
    newly->next->prev = newly;
    newly->prev = old->prev;
    newly->prev->next = newly;
}

inline int list_empty(const ListNode *head) {
    return head->next == head;
}

//offset of TYPE.MEMBER
#define offset_of(type, member) ((size_t) &((type *)0)->member)

//get TYPE's ptr by MEMBER's ptr
#define container_of(ptr, type, member) ({                \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);  \
    (type *)( (char *)__mptr - offset_of(type,member) );})

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define list_for_each(cur, head) \
    for (cur=(head)->next; cur!=(head); cur=cur->next)

#define list_for_each_safe(current, forward, head) \
    for (current=(head)->next, forward=current->next; current!=(head); current=forward, forward=pos->next)

#endif
