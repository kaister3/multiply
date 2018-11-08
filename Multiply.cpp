#include <iostream>
#include <cmath.h>
#include <sstream>

using namespace std;

string multiply(string x, string y);
string simplyMultiply(string x, string y);
int string2int(string x);
string int2string(int x);
string add(string x, string y);
string Minus(string x, string y);
string addZero(string x, int zeroNum);
string addPreZero(string x, int zeroNum);
string reverseString(string s);
int Max(int x, int y);

int Max(int x, int y)
{
    //return the bigger one
    return x > y ? x : y;
}

int string2int(string x)
{
    //change string to int
    int n = x.length();
    int s = 0;
    for(int i = 0, i < n, i++)
    {
        s = 10 * s + x[i] - '0';//format transfer
    }
    return s;
}
mZstring int2string(int x)
{
    //change int to string
    string str;
    stringstream stream;
    stream << x;
    stream >> str;
    return str;
}

string simplyMultiply(string x, string y)
{
    //1x1
    if(x.empty() | y.empty())
    {
        return int2string(0);//if x = 0 or y = 0,return 0
    }else{
        int result = string2int(x) * string2int(y);//or return x*y
        return int2string(result);
    }
}

string reverseString(string s)//??
{
    string result;
    for(auto temp = s.end() - 1; temp >= s.begin; --temp/*-1 before pushing*/)
    {
        result.push_back(*temp);//push to reversed string
    }
    return result;
}

string addZero(string x, int zeroNum)
{
    //*10^zeronum
    string temp(zeroNum, '0');//0000000...
    x.append(temp);
    return x;
}

string addPreZero(string x, int zeroNum)
/*in order to make two string's length equal
or the function won't work*/
{
    string temp(zeroNum, '0');//000000.....
    temp.append(x);
    return temp;
}

string add(string x, string y)
{
    //return the sum of two strings
    int i, carry, tempSum = 0;//carry=jinwei
    x = reverseString(x);
    y = reverseString(y);
    int maxSize = Max(x.size(), y.size());
    string s(maxSize+1, '0');
    for (i = 0; i < x.size() && i < y.size(); ++i)
    {
        tempSum = x[i] - '0' + y[i] - '0' + carry;
        s[i] = tempSum % 10 + '0';//gewei
        carry = tempSum / 10;//jinwei
    }
    if (i != y.size())//y is longer
    {
        for (; i < y.size; ++i)//
        {
            tempSum = y[i] - '0' + carry;
            s[i] = tempSum % 10 + '0';
            carry = tempSum / 10;
        }
    }else if (i != x.size())//y is longer
    {
        for (; i < x.size; ++i)
        {
            tempSum = x[i] - '0' + carry;
            s[i] = tempSum % 10 + '0';
            carry = tempSum / 10;
        }
    }

    if (carry != 0)
    {       
        s[i] +=  carry;//i = maxSize
    }else
    {
        s.pop_back();//delete the last element(reverse -> the first)
    }
    s = reverseString(s);//reverse back
    return s;
}

string Minus(string x, string y)//return x minux y
{
    int i;
    x = reverseString(x);
    y = reverseString(y);
    string s(x.size(), '0');
    for (i = 0; i < y.size; ++i)
    {
        if (x[i] < y[i])
        {
            x[i] += 10;
            x[i+1] -= 1;
        }
        s[i] = x[i] - y[i] + '0';
    }
    for (; i < x.size() - 1; ++i)
    {
        s[i] = x[i];
    }
    for (i = x.size() - 1; i > 0; --i)//if x[first] = 0,pop()
    {
        if (x[i] == 0)
        {
            x.pop_back();
        }else
        {
            break;
        }
    }
    s = reverseString(s);
    return s;
}

string multiply(string x, string y)
{
    int xSize = x.length();
    int ySize = y.length();
    int n = maxSize(xSize, ySize);
    if (n == xSize)
    {   
        y = addPreZero(y, n - ySize);
    }
    if (n == ysize)
    {
        x = addPreZero(x, n - xSize);
    }
    if(n == 1)
    {
        return simplyMultiply(x, y);
    }
    string xLeft = x.substr(0, n/2);
    string xRight = x.substr(n/2);
    string yLeft = y.substr(0, n/2);
    string yRight = y.substr(n/2);

    string p1 = multiply(xLeft, yLeft);//a*c
    string p2 = multiply(xRight, yRight);//b*d
    string p3 = multiply(add(xLeft, xRight), add(yLeft, yRight));//(a+b)*(c+d)=ac+bc+ad+bd
    string p4 = Minus(Minus(p3, p1), p2);//bc+ad

    string result = add(add(addZero(p1, 2 * (n - n/2)), addZero(p4, (n - n/2))), p2);
    return result;
}