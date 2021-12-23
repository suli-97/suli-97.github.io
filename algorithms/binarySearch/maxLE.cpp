#include<vector>
#include<iostream>
using namespace std;
bool checkLE(int x, int target){
	return x<=target;
}
int searchMaxLE(vector<int>& nums, int target) {
	if(checkLE(nums.back(),target))
		return nums.back();
	if(!checkLE(nums[0],target))
		return INT_MIN;
	int low = 0, high = nums.size()-2;
	while(low<high){
		int mid = (low+high+1)/2;
		if(checkLE(nums[mid],target)) 
			low = mid;
		else
			high=mid-1;
	}
	return nums[low];
}

int baseMaxLE(vector<int> x, int target){
	int i = upper_bound(x.begin(),x.end(),target) - x.begin();
	if(i==0) return INT_MIN;
	return x[i-1];
}
int main(){
	vector<int> x;
	while(true){
		x.clear();
		for(int i=0;i<37;i++)
			x.push_back(rand()%100);
		sort(x.begin(),x.end());
		int target = rand()%100;
		int res1 = baseMaxLE(x,target);
		int res2 = searchMaxLE(x,target);
		if(res1!=res2){
			while(true)
				cout<<"wrong"<<endl;
		}else
			cout<<res1<<endl;
	}
}