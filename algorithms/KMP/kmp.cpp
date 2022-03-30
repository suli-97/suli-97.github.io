#include<iostream>
#include<vector>
using namespace std;
vector<int> getNext(string& p){
	int n=p.size(), k;
	vector<int> next(n+1); //这里+1是因为要最后一个元素描述如果全部匹配上了，那么下次匹配的offset应该从哪里开始😊
	next[0]=-1, k=0; // k：到i-1为止的最长公共前后缀长度，也即是P[i]如果匹配失败，就要看P[k]能否匹配上了
	for(int i=1;i<n;i++,k++){
		// 如果相等，那么i匹配失败，k肯定也匹配失败，所以顺延到之前的，因为等号有传递性，所以不用递归下去
		if(p[i]==p[k])
			next[i]=next[k];
		// 如果不相等，那么有可能可以匹配上前一个
		else
			next[i]=k;
		// 更新k的值从 K[i-1] 到 K[i]
		while(k!=-1 && p[k]!=p[i]) 
			k=next[k];
	}
	next[n] = k; // 如果匹配成功（或者可以理解为最后一个元素是空的，肯定空!=p[k]，所以有可能匹配到k）那么跳到k
	return next;
}
vector<int> search(string target, string pattern){
	vector<int> next = getNext(pattern); // next is length m+1
	int i=0, j=0, n=target.size(), m=pattern.size();
	vector<int> res;
	while (i<n) {
		if (j<m && (j==-1 || target[i] == pattern[j]))
			i++, j++;
		else {
			if (j==m) //记录下匹配成功的点 然后回退
				res.push_back(i-m);
			j = next[j];
		}
	}
	if (j==m) res.push_back(i-m);
	return res;
}
int main(){
	string s = "89049132653564309569340329432895631767034951570475423807582340578047354543245324632467624723467902439705479";
	string p = "475";
	vector<int> res = search(s,p);
	for (int x:res)
		cout<<x<<" ";
	cout <<endl;
}
