class Solution {
public:
    ListNode* first; 

    bool check(ListNode* head) {
        if (!head) {
            return true; 
        }

        if (!check(head->next)) {
            return false;
        }

        if (first->val != head->val) {
            return false;
        }
        first = first->next;

        return true;
    }

    bool isPalindrome(ListNode* head) {
        first = head;
        return check(head);
    }
};
