[count and say](https://leetcode.com/problems/count-and-say/submissions/)

```javascript
var countAndSay = function(n) {
    if(n===1)
        return "1"
    var s = countAndSay(n-1)  
    s = s.match(/(.)\1*/g)
    s = s.map(x=>`${x.length}${x[0]}`)
    return s.join('')
};
```

