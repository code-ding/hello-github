#include<iostream>
#include<vector>
using namespace std;

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
int main()
{
    class Solution t;
    string test = "25525511135";
    vector<string> result = t.restoreIpAddresses(test);
    for (int i = 0; i < result.size();i++)
        cout << result[i] << endl;
}   
