这道题是我第一遍刷题时就跳过的一道题，，，因为当时的我太菜了，也没有学过编译原理。看到有限自动机这个fancy的名字，我就被吓到了，于是就跳过了这道题。之后在ucsd上haskell这节函数式编程课之后，刚好要写一个小编译器，里面所学到的State Monad完全可以cover这道题。时隔一年，重新审视这道题，暗喜于这小半年上课没有白费。

​		核心理念就是把每个小函数抽象成一个计算节点（纯函数）（有点像Tensorflow中的计算图模型），规定好每个计算节点的输入为一个字符，计算内容是根据输入判断下一步走向哪一个节点，输出是下一个节点的编号/指针。如果最后落在了可以当作结束位置的点就表明成功，反则失败。

```c++
#include<iostream>
using namespace std;
vector<vector<int>> jumpTable = {
    {1,  3, -1,  2},
    {-1,  3, -1,  2},
    {-1,  4,  6,  2},
    {-1, -1, -1,  5},
    {-1, -1,  6,  5},
    {-1, -1,  6,  5},
    {7,  -1, -1,  8},
    {-1, -1, -1,  8},
    {-1, -1, -1,  8}};
unordered_set<int> dict= {2,4,5,8};
unordered_map<char,int> m = {
    {'+',0},
    {'-',0},
    {'.',1},
    {'e',2},
    {'E',2}};
class Solution {
public:
    int typeMap(char c){
        if(m.find(c) != m.end()) return m[c];
        if( isdigit(c)) return 3;
        return -1;
    }
    
    bool isNumber(string s) {
        int current = 0;
        for(char c: s){
            int type = typeMap(c);
            if( type == -1) return false;
            current = jumpTable[current][type];
            if(current == -1) return false;
        }
        if (dict.find(current) != dict.end()) return true;
        return false;
    }  
};
```

​		函数式的做法大同小异，在这里函数被抽象成了计算图，所有的计算不是在数据上的计算而是在函数上的计算。monad中的bind被我简化成了mergeFunc。函数式yyds！（头一次体会到haskell的简洁

```c++
string s;
// 核心代码就这下面三个函数，说是核心其实也没啥难度，后面就都是搭积木而已
function<vector<int>(int)> multiFunc(function<vector<int>(int)> f){
    return [f](int index_){
        int index = index_;
        while(true){
            vector<int> tmp = f(index);
            if( tmp.size() == 0 ) return index == index_ ? tmp : vector<int>{index};
            index = tmp[0];
        }
    };
}
function<vector<int>(int)> mergeFunc( vector<function<vector<int>(int)>> list){
    auto f = new function<vector<int>(int,int)>();
    *f = [list, f](int index, int i=0) -> vector<int>{
        if(i == list.size()) return {index};
        vector<int> v = list[i](index);
        vector<int> res;
        for(int next: v){
            vector<int> temp = (*f)(next,i+1);
            if(temp.size()) res.insert(res.end(),temp.begin(),temp.end());
        }
        return res;
    };
    return [f](int index){return (*f)(index,0);};
}
function<vector<int>(int)> orFunc( vector<function<vector<int>(int)>> list){
    return [list](int index)->vector<int>{
        vector<int> res;
        for(auto f:list){
            vector<int> temp = f(index);
            res.insert(res.end(),temp.begin(),temp.end());
        }
        return res;
    };
}

function<vector<int>(int)> singleCheck(function<bool(char)> f){
    return [f](int index) -> vector<int>{
        return (index >= s.size() || index < 0 || f(s[index]) ) ? vector<int>{} : vector<int>{index+1};
    };
}
auto isDigit = singleCheck([](char c)->bool{return !isdigit(c);});
auto isAlpha = singleCheck([](char c)->bool{return !isalpha(c);});
auto isSign = singleCheck([](char c)->bool{return c != '+' && c != '-';});
auto isDot = singleCheck([](char c)->bool{return c!='.';});
auto isE = singleCheck([](char c)->bool{return c!='e' && c!= 'E';});
function<vector<int>(int)> isBlank = [](int index)->vector<int>{return {index}; };

auto isUnsignedInt = multiFunc(isDigit);

auto orSign = orFunc({isSign, isBlank});
auto orUnsignedInt = orFunc({isUnsignedInt, isBlank});

auto isInt = mergeFunc({orSign,isUnsignedInt});

auto isUnsignedFloat1 = mergeFunc({isUnsignedInt, isDot, orUnsignedInt});
auto isUnsignedFloat2 = mergeFunc({isDot, isUnsignedInt});

auto isUnsignedFloat = orFunc({isUnsignedFloat1,isUnsignedFloat2});

auto isFloat = mergeFunc({orSign,isUnsignedFloat});

auto isFloatOrInt = orFunc({isFloat, isInt});

auto isEInt = mergeFunc({isE, isInt});
auto orEInt = orFunc({isBlank, isEInt});

auto isN = mergeFunc({ isFloatOrInt, orEInt});


class Solution {
public:
    bool isNumber(string s_) {
        s = s_;
        vector<int> end = isN(0);
        for(int i : end)
            if(i == s.size()) return true;
        return false;
    }  
};
```

