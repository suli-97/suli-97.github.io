[返回上页](..)

# 快速选择算法

- 快速选择算法其实就是应用快排的思想，求取第K大的数

  首先随机从数组抽一个数出来，然后从“头”到“尾”遍历一遍，把比这个数小的放左边，比这个数大的放右边，一样大的自然就在中间。

  然后比较这个数的排序和K，如果要求的数比他大，就去右边递归寻找，反之就去左边，如果刚好就找到这个数了。

  这样下去，如果运气好，每次都二分的话，我们有

  T(n)=T(n/2)+n=n+n/2+n/4+...=O(n)

  如果运气不好的话，每次都取到最小的值，我们有

  T(n)=T(n-1)+n=n+(n-1)+...=O(n^2)

  但是平均下来的话我们还是有O(n)的，只是最差是O(n^2).

- 难点：

  1. 怎么能使问题规模一定在缩小，而且不浪费计算？

     如果我们每次递归至少把我们选择的数排除掉（比如最坏情况），那么我们的问题规模就一定是在缩小的，所以记得这么定义“头”和“尾"，头定义成第一个元素的索引（比如0），尾巴定义为最后一个元素的索引+1，也就是第一个取不到的元素。（这是最常见的定义，也是最好用的定义

     我们从两头定义好high和low的栈顶位置，其中high指向加进去的最后一个元素的位置，low指向我们即将加入的位置（注意这个区别）然后for(int i=st;i<high;i++)这样遍历。 然后假设我们最后得到的结果是

     (St, ..., low-1),(low, ... ,high-1)(i=high,...,ed-1)ed.

     我们如果往大的数里找，那么下一步递归应该让

     st=high.ed不变

     相反则

     ed=low,st不变.

     优雅的对称。

  2. 怎么能够正确的原地把大于小于等于的分开？

     对于我们可能遍历到的数，分为三种情况。

     1. 这个数大于轴

        那么我们把它swap到“--high“的位置，然后注意**继续判断当前位置**的数，因为我们换回来的数我们不能直接跳过。

     2. 这个数小于轴

        那么我们把它swap到“low++”的位置，直接判断下一个数, 因为我们知道交换过来的数一定等于轴（prove later

     3. 这个数等于轴

        那么我们什么都不做，跳到下一个数

     最后我们得到的大于轴的数bigger=ed-high，smaller=low-st，equal=high-low。

     (St, ..., low-1),(low, ... ,high-1)(i=high,...,ed-1)ed.

     

     ***为什么当这个数小于轴时，交换回来的数我们不用看呢？***

     因为你想，一开始的时候 i=low。也就是说交换的数就是本身这种情况下，我们肯定不需要处理

     什么时候i会大于low呢？

     当碰到大于轴的数的时候，我们会继续判断当前的数，所以i的位置不变，low也不变，这不会导致i和low之间有相对距离

     当碰到小于轴的时候，i和low都+1，也不会出现相对距离

     只有等于轴的时候，i会+1，而low无动作，正是这种情况导致了i和low之间可能有相对距离。

     所以i和low之间肯定充满的都是轴，所以如果是从low交换回来的数，我们根本不用处理，直接看下一个数就好。

```c++
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
```

