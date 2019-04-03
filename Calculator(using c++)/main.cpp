#include <iostream>
#include<vector>
#include<string>
#include<stack>
#include<algorithm>

using namespace std;

class Calculator
{
    vector<int> number;
    vector<char> operation;
    stack<int> bracket;
    string s;
    int flag;
public:
    Calculator(string s)
    {
        flag=0;
        this->s = s;
    }
    void Extract()
    {
        int Generate=0;
        for(int i=0;i<s.length();i++)
        {
            if(s[i]=='(')
            {
                bracket.push(i);
                number.push_back(Solve_bracket(++i));
            }
            else
            {
                if(s[i]>='0' && s[i]<='9')
                {
                    Generate=Generate*10 + (s[i]-'0');
                    if(s[i+1]=='(')
                    {
                        if(Generate!=0)
                        {
                            number.push_back(Generate);
                        }
                        operation.push_back('*');
                        Generate=0;
                    }
                }
                else
                {
                    if(Generate!=0)
                    {
                        number.push_back(Generate);
                    }
                    operation.push_back(s[i]);
                    Generate=0;
                }
            }
        }
        if(Generate!=0)
        {
            number.push_back(Generate);
        }
        if(number.size()<=operation.size())
        {
            throw 1;
        }
        else
        {
            Operation(number,operation);
        }
    }
    int Solve_bracket(int &i)
    {
        int Generate=0;
        vector<int> number;
        vector<char> operation;
        while(!bracket.empty())
        {
            if(i==s.size() && !bracket.empty())
            {
                throw 1;
            }
            if(s[i]=='(')
            {
                bracket.push(i);
                number.push_back(Solve_bracket(++i));
            }
            else if(s[i]==')')
            {
                if(Generate!=0)
                {
                    number.push_back(Generate);
                }
                bracket.pop();
                Operation(number,operation);
                return number[0];
            }
            else
            {
                if(s[i]>='0' && s[i]<='9')
                {
                    Generate=Generate*10 + (s[i]-'0');
                    if(s[i+1]=='(')
                    {
                        if(Generate!=0)
                        {
                            number.push_back(Generate);
                        }
                        operation.push_back('*');
                        Generate=0;
                    }
                }
                else
                {
                    if(Generate!=0)
                    {
                        number.push_back(Generate);
                    }
                    operation.push_back(s[i]);
                    Generate=0;
                }
            }
            i++;
        }
    }
    void Operation(vector<int> &number, vector<char> &operation)
    {
        for(int i=0;;)
        {
            if(find(operation.begin(),operation.end(),'*')!=operation.end() || find(operation.begin(),operation.end(),'/')!=operation.end())
            {
                if(operation[i]=='*')
                {
                    number[i]=number[i]*number[i+1];
                    number.erase(number.begin()+i+1);
                    operation.erase(operation.begin()+i);
                }
                else if(operation[i]=='/')
                {
                    number[i]=number[i]/number[i+1];
                    number.erase(number.begin()+i+1);
                    operation.erase(operation.begin()+i);
                }
                else
                {
                    i++;
                }
            }
            else
            {
                break;
            }
        }
        for(int i=0;i<operation.size();)
        {
            if(operation[i]=='+')
            {
                number[i]=number[i]+number[i+1];
                number.erase(number.begin()+i+1);
                operation.erase(operation.begin()+i);
            }
            else if(operation[i]=='-')
            {
                number[i]=number[i]-number[i+1];
                number.erase(number.begin()+i+1);
                operation.erase(operation.begin()+i);
            }
            else
            {
                i++;
            }
        }
    }
    void print()
    {
        for(int i=0;i<number.size();i++)
        {
            cout << number[i] << " ";
        }
        cout << endl;
        for(int i=0;i<operation.size();i++)
        {
            cout << operation[i] << " ";
        }
    }
};

int main()
{
    string s;
    cin >> s;
    Calculator ob(s);
    try
    {
        ob.Extract();
        ob.print();
    }
    catch(int i)
    {
        cout << "Symtax error";
    }
    return 0;
}
