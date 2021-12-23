#include<iostream>
#include<vector>
#include<functional>
using namespace std;

//满足条件的第一个数的索引
int first(vector<int> nums, int x, bool close=false){
	auto valid = [x,close](int a)->bool{
		return close?a>=x:a>x;
	};
	if(!valid(nums.back())) return nums.size();
	int st = 0, ed = nums.size()-1;
	while(st<ed){
		int mid = (st+ed)/2;
		if(valid(nums[mid]))
			ed = mid;
		else
			st = mid + 1;
	}
	return st;
}


int n = -1;
bool valid(int a){
	return a>n;
}
int main(){

	vector<int> a = {0,1,2,3,4,5,6,7,8,9,10};
	int index1 = upper_bound(a.begin(),a.end(),n) - a.begin();
	int index2 = first(a,valid);
	cout<<index1<<':'<<index2<<endl;
}