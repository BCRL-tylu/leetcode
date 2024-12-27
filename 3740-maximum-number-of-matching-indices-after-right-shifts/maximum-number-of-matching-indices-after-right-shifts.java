class Solution {
  public int maximumMatchingIndices(int[] nums1, int[] nums2) {
    int max = 0;    
    int size = nums1.length;
    int count;
    int index;
    for (int i = 0; i < size; i++) {
      count = 0;
      for (int j = 0; j < size; j++) {
        index = (i + j) % size; 
        if (nums1[index] == nums2[j]) count++;
      }
      max = Math.max(max, count);
    }
    return max;
  }
}