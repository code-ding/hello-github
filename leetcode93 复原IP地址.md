### leetcode93 复原IP地址 ###

之前面试字节跳动遇到该题，当时时间较短，只有大致思路和基本首先框架，没有AC了，今天又正好看见该题。

#### [93. 复原IP地址](https://leetcode-cn.com/problems/restore-ip-addresses/) ####

给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。

有效的 IP 地址正好由四个整数（每个整数位于 0 到 255 之间组成），整数之间用 '.' 分隔。

**示例:**

```c
输入: "25525511135"
输出: ["255.255.11.135", "255.255.111.35"]
```

分析：首先明白，什么是一个合法的IP地址：应该分成4部分，每个部分都应该满足“**数字应该小于255，不能有前缀0**”，其次分析，该用什么方法？在此采用回溯法。

首先考虑，实际上对于每个部分，至多也就三种情况(长度1,2,3)，因此就算暴力去判断，也至多3^4种结果。采用回溯是为了部分剪枝，因此无论什么方法复杂度也就在O(1)内。

回溯法思路就是枚举，只是将不成立的分支均剪掉。

代码注释比较详细，思路很清晰。

```cpp
class Solution
{
private:
    vector<string> result; //存储答案
public:
    vector<string> restoreIpAddresses(string s)
    {
        vector<string> path;
        //如果string是非法的ip字符串则直接返回即可
        if(s.size()<4||s.size()>16)
            return result;
        //进行深搜
        dfs(s, 0, path);
        return result;
    }
    bool is_vaild_ip(string s) //判断是否是一个合法的IP范围
    {
        int ip = stoi(s);
        if(ip>255) //不能超出范围
            return false;
        if(s[0]=='0'&&s.size()>=2)  //不能有前置0
            return false;
        return true;
    }
    //pos表示当前的起始位置,path表示当前已存路径
    void dfs(string &s,int pos,vector<string> &path)
    {
        //path.size==4说明已经添加完成，判断是否已经遍历至结尾,如果已经遍历至结尾则说明是合法的
        if(path.size()==4&&pos==s.size())
        {
            string s = "";
            for (int i = 0; i < 3;i++)
                s = s + path[i] + '.';
            s += path[3];
            result.push_back(s);
            return;
        }
        //如果没有遍历至结尾说明该部分是无效的
        if(path.size()==4&&pos<s.size())
            return;
        //已经存储3个部分后面部分长度太长,则return
        if(path.size()==3&&pos<s.size()-3) //后面太长
            return;
        //回溯经典套路，添加新路径-->回溯-->恢复现场
        for (int i = pos; i < s.size() && i <= pos + 2;i++)
        {
            string ip = s.substr(pos, i - pos + 1); //截取掉
            if(!is_vaild_ip(ip)) //判断是否合法
                break;  //如果不合法说明添加后面也不会合法
            path.push_back(ip);
            dfs(s, i + 1, path);
            path.pop_back();
        }
    }
};
```