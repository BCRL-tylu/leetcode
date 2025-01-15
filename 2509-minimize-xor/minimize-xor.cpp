class Solution {
private:
    unsigned int cb(int n)
    {
        unsigned int count = 0;
        while (n) {
            n &= (n - 1);
            count++;
        }
        return count;
    }
public:
    int minimizeXor(int num1, int num2) {
        int x = cb(num2);
        int count = 0, mask = 0, ml = -1;
        bool larger = false;
    // Traverse the bits from left to right (31 down to 0)
    for (int i = 31; i >= 0; --i) {
        if ((num1 >> i) & 1) {  // Check if the i-th bit is set
            mask |= (1 << i); // Add this bit to the mask
            count++;
            if (count == x){
                larger = true;
                break;
                }
            if (ml == -1) ml = i+1;
        }
    }
        if(larger) return num1 & mask; // return when set bits num1 >= set bits num2
        if(ml<=x) return (1U<<x)-1;
        x -= count;
         int position = 0;  // Start from the rightmost bit
         while (position<=ml && x > 0) {
        // Check if the current bit is 0
         if ((num1 & (1 << position)) == 0) {
            // Set the bit to 1 if it is 0 and k > 0
            num1 |= (1 << position);
            x--;
        }  
        // Move to the next bit
        position++;
    }
        return num1;

    }
};