#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
vector<int> baseline(vector<int>& nums, int k){
	sort(nums.begin(),nums.end());
	return vector<int>(nums.end()-k,nums.end());
}
int topK(vector<int> nums, int k){
	int n = nums.size()-k;
	nth_element(nums.begin(),nums.begin()+n,nums.end());
	return nums[n];
}
int quickSelect(vector<int> nums, int k) {
	if(k<1 || k>nums.size()) return -1;
	int st=0,ed=nums.size();
	while(true){
		int x = nums[st];
		int low = st,high=ed;
		for(int i=st+1;i<high;i++){
			if(nums[i]<x)
				swap(nums[low++],nums[i]);
			else if(nums[i]>x)
				swap(nums[--high],nums[i--]);
		}
		int bigger = ed-high, equal=high-low, smaller = low-st;
		if(bigger<k&&k<=bigger+equal)
			return x;
		else if(k>bigger+equal){
			k = k-bigger-equal;
			ed = low;
		}else
			st = high;
	}
}
int main(){
	for(int j=0;;j++){
		vector<int> nums;
		for(int i=0;i<100;i++)
			nums.push_back(rand());
		bool equal = topK(nums,10)==quickSelect(nums,10);
		cout<<j<<':'<<equal<<endl;
		if(!equal)
			break;
	}
	return 0;
}