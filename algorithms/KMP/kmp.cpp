#include<iostream>
#include<vector>
using namespace std;
vector<int> get_next(string& p){
	vector<int> next(p.size());
	next[0]=-1;// k：到i-1为止的最长公共前后缀长度，也即是P[i]如果匹配失败，就要看P[k]能否匹配上了
	for(int i=1,k=0;i<p.size();i++,k++){
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
	return next;
}
vector<int> lsps(string str){
	vector<int> lsps(str.size(),0);
	int i=1,k=0;
	while(i<str.size()){
		if(k>=0&&str[i]!=str[k])
			k = k==0?-1:lsps[k-1];
		else
			lsps[i++] = ++k;
	}
	return lsps;
}
vector<int> lsps2next(vector<int> lsps){

}
int main(){
	string s = "abcabcd";
	auto res1 = lsps(s);
	auto res2 = get_next(s);
	for(int i:res2)
		cout<< i<<' ';
	return 0;
}
