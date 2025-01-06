class Solution {
private:
    // Function to merge two sorted linked lists
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummy;          // Dummy node to simplify merging
        ListNode* tail = &dummy; // Pointer to the end of the merged list
        while (l1 && l2) {
            if (l1->val < l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next; // Move the tail pointer forward
        }
        // Attach the remaining elements (if any)
        if (l1) {
            tail->next = l1;
        } else {
            tail->next = l2;
        }
        return dummy.next; // Return the merged sorted list
    }

    // Function to perform merge sort on the linked list
    ListNode* mergeSort(ListNode* head) {
        if (!head || !head->next) {
            return head; // Base case: if head is null or only one node
        }

        ListNode* mid = getMid(head); // Get the middle node to split the list
        ListNode* left = mergeSort(head); // Sort the left half
        ListNode* right = mergeSort(mid); // Sort the right half

        return merge(left, right); // Merge the sorted halves
    }

    // Helper function to find the middle of the linked list
    ListNode* getMid(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }

        ListNode* slow = head;
        ListNode* fast = head->next;

        // Move fast pointer two steps and slow pointer one step
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* mid = slow->next;
        slow->next = nullptr; // Split the list into two halves
        return mid; // Return the second half
    }

public:
    ListNode* mergeKLists(std::vector<ListNode*>& lists) {
        // Step 1: Append all ListNode into a single linked list
        ListNode dummy; // Dummy node to simplify the appending process
        ListNode* tail = &dummy;

        for (ListNode* list : lists) {
            while (list) {
                tail->next = new ListNode(list->val); // Create a new node and append
                tail = tail->next; // Move the tail pointer
                list = list->next; // Move to the next node in the current list
            }
        }

        // Step 2: Sort the combined linked list using merge sort
        return mergeSort(dummy.next); // Return the head of the sorted linked list
    }
};