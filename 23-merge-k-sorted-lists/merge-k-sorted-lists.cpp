// Custom comparator for the priority queue
struct Compare {
    bool operator()(ListNode* l1, ListNode* l2) {
        return l1->val > l2->val; // Min-heap based on node values
    }
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, Compare> minHeap;

        // Push the head of each list into the min-heap
        for (ListNode* list : lists) {
            if (list) {
                minHeap.push(list);
            }
        }

        ListNode dummy; // Dummy node to simplify the result list
        ListNode* tail = &dummy;

        while (!minHeap.empty()) {
            // Get the smallest node from the heap
            ListNode* smallestNode = minHeap.top();
            minHeap.pop();

            // Add the smallest node to the merged list
            tail->next = smallestNode;
            tail = tail->next; // Move the tail pointer forward

            // If there is a next node in the list, push it into the min-heap
            if (smallestNode->next) {
                minHeap.push(smallestNode->next);
            }
        }

        tail->next = nullptr; // Ensure the last node points to nullptr
        return dummy.next; // Return the head of the merged linked list
    }
};
