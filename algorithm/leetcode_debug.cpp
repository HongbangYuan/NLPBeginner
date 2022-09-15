//
// Created by HarryPotter on 2022/9/7.
//
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

class Solution {
public:

    int _maxSubArray(vector<int> & nums,int lo,int hi){
        int N = hi - lo;
        if(N == 0){
            return 0;
        }
        if(N == 1){
            return nums[lo];
        }
        if(N == 2){
            int result;
            result = max(nums[lo],nums[lo+1]);
            result = max(result,nums[lo] + nums[lo+1]);
            return result;
        }

        int mid = (lo + hi) >> 1;
        int max_left_sum = -std::numeric_limits<int>::max();
        int left_sum = 0;
        for(int i = mid-1;i >= lo;i--){
            left_sum += nums[i];
            if(left_sum > max_left_sum)
                max_left_sum = left_sum;
        }
        int max_right_sum = -std::numeric_limits<int>::max();
        int right_sum = 0;
        for(int i = mid; i<hi;i++){
            right_sum += nums[i];
            if(right_sum > max_right_sum)
                max_right_sum = right_sum;
        }
        return max({max_left_sum + max_right_sum, _maxSubArray(nums, lo, mid), _maxSubArray(nums,mid,hi)});
    }

    int maxSubArray(vector<int>& nums) {
        int max_sum = nums[0];
        int curr_sum = nums[0];
        for(int i = 1;i < nums.size();i++){
            curr_sum = max(curr_sum+nums[i],nums[i]);
            max_sum = max(max_sum,curr_sum);
        }
        return max_sum;
//        int N = nums.size();
//        if(N == 1){
//            return nums[0];
//        }
//        if(N == 2){
//            int result;
//            result = max(nums[0],nums[1]);
//            result = max(result,nums[0] + nums[1]);
//            return result;
//        }
//
//        auto result = _maxSubArray(nums,0,N);
//        return result;
    }
};

int main(){

//    vector<int> a = {1};
    vector<int> a = {-2,1,-3,4,-1,2,1,-5,4};
    Solution solution;
    int sum = solution.maxSubArray(a);
    cout << sum << endl;
    cout << "Hello World!" << endl;
}
