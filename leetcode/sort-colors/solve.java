class Solution {
    public void sortColors(int[] nums) {
        
        int r1 = -1;
        int r2 = -1;
        for(int i = 0;i < nums.length;i++){
            if(nums[i] < 2)
            {
                r2++;
                swap(nums,i,r2);
                if(nums[r2] < 1)
                {
                    r1++;
                    swap(nums,r1,r2);
                }
            }
            
        }
        
        
      
        
    }
    
    void swap(int[]nums,int i,int j)
    {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
}
