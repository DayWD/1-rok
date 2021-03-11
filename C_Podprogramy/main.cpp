//Dawid Urbanik

#include <iostream>
#include <string>
#include <cstdarg>

using namespace std;

string Sum_loop_1(string::size_type i,string::size_type j,string a,string b,string::size_type k){
    if(i<0 || k<i)
        return a;
    a[j]+=(b[i]-'0');
    i--;
    j--;
    return Sum_loop_1(i,j,a,b,k);
}

string Sum_loop_2(string::size_type i,string a,string b,string::size_type k){
    if(i<1 || k<i)
        return a;
    if(a[i] > '9')
    {
        int d = a[i]-'0';
        a[i-1] = ((a[i-1]-'0') + d/10) + '0';
        a[i] = (d%10)+'0';
    }
    i--;
    return Sum_loop_2(i,a,b,k);
}

string Sum(string a, string b)
{
    if(a.size() < b.size())
        swap(a, b);

    a = Sum_loop_1(b.size()-1,a.size()-1,a,b,a.size());

    a = Sum_loop_2(a.size()-1,a,b,a.size());
    if(a[0] > '9')
    {
        string k;
        k+=a[0];
        a[0] = ((a[0]-'0')%10)+'0';
        k[0] = ((k[0]-'0')/10)+'0';
        a = k+a;
    }
    return a;
}


string without_zero(string a)
{
    if(a.size() <= 1 || a[0]>'0')
        return a;
    a = a.substr(1);
    return without_zero(a);
}

string Mult_loop_1(string::size_type i,string::size_type j,string b,string a,string temp_b_2,string zero_b){
    if(j>b.size()-1)
    {
        return temp_b_2;
    }
    string temp="";
    int var;

    if(j<b.size()-1)
        zero_b+="0";
    var = ((a[i]-'0') * (b[j]-'0')) ;
    if(var > 9)
    {
        string k="";
        temp = (var%10)+'0';
        k = (var/10)+'0';
        temp = k+temp;
    }
    else
        temp += (char)(var + '0');
    temp+=zero_b;
    if(!temp_b_2.empty()) {
        temp = Sum(temp, temp_b_2);
    }
    temp_b_2=temp;

    j--;
    return Mult_loop_1(i,j,b,a,temp_b_2,zero_b);
}
string Mult_loop_2(string::size_type i,string b,string a,string temp_b_2,string zero_b,string zero_a,string temp_2){
    if(i>a.size()-1)
    {
        return temp_2;
    }
    if(i<a.size()-1)
        zero_a+="0";
    temp_b_2 = Mult_loop_1(i,b.size()-1,b,a,temp_b_2,zero_b);

    zero_b="";
    temp_b_2+=zero_a;
    if(!temp_2.empty()) {
        temp_b_2 = Sum(temp_b_2, temp_2);
    }
    temp_2=temp_b_2;
    temp_b_2="";

    i--;
    return Mult_loop_2(i,b,a,temp_b_2,zero_b,zero_a,temp_2);
}

string Multiply_f(string a,string b)
{
    if(a.size() < b.size())
        swap(a, b);

    string temp_2="";
    string temp="";
    string zero_a="";
    string zero_b="";
    string temp_b_2="";
    temp_2 = Mult_loop_2(a.size()-1,b,a,temp_b_2,zero_b,zero_a,temp_2);

    temp_2 = without_zero(temp_2);
    return temp_2;
}

string Multiply(string a,string b)
{
    int a_sign=0;
    int b_sign=0;

    if(a[0]=='-'){
        a_sign=1;
        a=a.substr(1);
    }
    if(b[0]=='-'){
        b_sign=1;
        b=b.substr(1);
    }
    if(a[0]=='+'){
        a=a.substr(1);
    }
    if(b[0]=='+'){
        b=b.substr(1);
    }

    a = without_zero(a);
    b = without_zero(b);

    if(a.empty() && !b.empty())
    {
        return "0";
    }
    if(b.empty() && !a.empty())
    {
        return "0";
    }
    if(b.empty() && a.empty())
    {
        return "0";
    }
    if(a_sign == 0 && b_sign == 0)
    {
        return Multiply_f(a,b);
    }
    if(a_sign == 1 && b_sign == 1)
    {
        return Multiply_f(a,b);
    }
    if(a_sign == 0 && b_sign == 1)
    {
        if(a[0] == '0' || b[0] == '0')
            return "0";

        string c = "-";
        c += Multiply_f(a, b);
        return c;
    }
    if(a_sign == 1 && b_sign == 0)
    {
        if(a[0] == '0' || b[0] == '0')
            return "0";

        string c = "-";
        c += Multiply_f(a, b);
        return c;
    }
    return "E";
}

string Sub_loop_1(string::size_type i,string::size_type j,string a,string b,string::size_type k){
    if(i<0 || k<i)
        return a;
    a[j]-=(b[i]-'0');
    i--;
    j--;
    return Sub_loop_1(i,j,a,b,k);
}

string Sub_loop_2(string::size_type i,string a,string b,string::size_type k){
    if(i<1 || k<i)
        return a;
    if(a[i] < '0')
    {
        int d = a[i]-'0';
        a[i-1] = ((a[i-1]-'0') + (d-10)/10) + '0';
        a[i] = (d%10) + 10 +'0';
    }
    i--;
    return Sub_loop_2(i,a,b,k);
}

string Subtract(string a, string b)
{

    a = Sub_loop_1(b.size()-1,a.size()-1,a,b,a.size());

    a = Sub_loop_2(a.size()-1,a,b,a.size());

    if(a[0] == '0' && a.size() >1)
    {
        a = a.substr(1);
    }
    a = without_zero(a);
    return a;
}

string Add(string a,string b)
{
    int a_sign=0;
    int b_sign=0;

    if(a[0]=='-'){
        a_sign=1;
        a=a.substr(1);
    }
    if(b[0]=='-'){
        b_sign=1;
        b=b.substr(1);
    }
    if(a[0]=='+'){
        a=a.substr(1);
    }
    if(b[0]=='+'){
        b=b.substr(1);
    }

    a = without_zero(a);
    b = without_zero(b);

    if(a.empty() && !b.empty())
    {
        return b;
    }
    if(b.empty() && !a.empty())
    {
        return a;
    }
    if(b.empty() && a.empty())
    {
        return a;
    }
    if(a_sign == 0 && b_sign == 0)
    {
         return Sum(a,b);
    }
    if(a_sign == 1 && b_sign == 1)
    {
        string c="-";
        c+=Sum(a,b);
        return c;
    }
    if(a_sign == 0 && b_sign == 1)
    {
        int beswap=0;
        if((a.size()<b.size()) || (a.size() == b.size() && a<b)){
            swap(a,b);
            beswap=1;
        }
        if(beswap==1) {
            string c="";
            if(Subtract(a, b) != "0")
                c = "-";
            c += Subtract(a, b);
            return c;
        }
        return Subtract(a, b);
    }
    if(a_sign == 1 && b_sign == 0)
    {
        int beswap=0;
        if((a.size()<b.size()) || (a.size() == b.size() && a<b)){
            swap(a,b);
            beswap=1;
        }
        if(beswap==0) {
            string c="";
            if(Subtract(a, b) != "0")
            c = "-";
            c += Subtract(a, b);
            return c;
        }
        return Subtract(a, b);
    }
    return "E";
}

string do_Sum(string::size_type i,const string *a,string output,string::size_type k)
{
    if(i>k)
        return output;
    output = Add(output,a[i]);
    i--;
    return do_Sum(i,a,output,k);
}
string do_Sum_2(va_list args,int i,string output)
{
    if(i<0)
        return output;
    string k = va_arg(args,const char*);
    output = Add(output,k);
    i--;
    return do_Sum_2(args,i,output);
}
string Sum(int i,const string* a)
{
    return do_Sum(i-1,a,"0",i-1);
}
string Sum(int i, ...)
{
    va_list args;
    va_start(args, i);
    string output = do_Sum_2(args,i-1,"0");
    va_end(args);
    return output;
}
void Sum(string *output, int i, const string * a)
{
    *output =  do_Sum(i-1,a,"0",i-1);
}
void Sum(string *output, int i, ...)
{
    va_list args;
    va_start(args, i);
     *output = do_Sum_2(args,i-1,"0");
    va_end(args);
}
void Sum(string &output, int i, const string * a)
{
    output =  do_Sum(i-1,a,"0",i-1);
}
void Sum(string &output, int i, ...)
{
    va_list args;
    va_start(args, i);
    output = do_Sum_2(args,i-1,"0");
    va_end(args);
}

string do_Mult(string::size_type i,const string *a,string output,string::size_type k)
{
    if(i>k)
        return output;
    output = Multiply(output,a[i]);
    i--;
    return do_Mult(i,a,output,k);
}
string do_Mult_2(va_list args,int i,string output)
{
    if(i<0)
        return output;
    string k = va_arg(args,const char*);
    output = Multiply(output,k);
    i--;
    return do_Mult_2(args,i,output);
}
string Mult(int i,const string* a)
{
    return do_Mult(i-1,a,"1",i-1);
}
string Mult(int i, ...)
{
    va_list args;
    va_start(args, i);
    string output = do_Mult_2(args,i-1,"1");
    va_end(args);
    return output;
}
void Mult(string *output, int i, const string * a)
{
    *output =  do_Mult(i-1,a,"1",i-1);
}
void Mult(string *output, int i, ...)
{
    va_list args;
    va_start(args, i);
    *output = do_Mult_2(args,i-1,"1");
    va_end(args);
}
void Mult(string &output, int i, const string * a)
{
    output =  do_Mult(i-1,a,"1",i-1);
}
void Mult(string &output, int i, ...)
{
    va_list args;
    va_start(args, i);
    output = do_Mult_2(args,i-1,"1");
    va_end(args);
}

string Operation(string (*op) (int,const string*),int k,const string* b)
{
    return op(k,b);
}

int Repacking(int i,string* a,va_list args)
{
    if(i<0)
        return 0;
    a[i]=va_arg(args, const char*);
    i--;
    return Repacking(i,a,args);
}

string Operation(string (*op) (int,const string*),int k, ...)
{
    va_list args;
    va_start(args, k);
    string a[k];
    Repacking(k-1,a,args);
    string output = op(k,a);
    va_end(args);
    return output;
}

void Operation(string *a,string (*op) (int,const string*),int k,const string* b)
{
    *a = op(k,b);
}
void Operation(string &a,string (*op) (int,const string*),int k,const string* b)
{
    a = op(k,b);
}
void Operation(string *s,string (*op) (int,const string*),int k, ...)
{
    va_list args;
    va_start(args, k);
    string a[k];
    Repacking(k-1,a,args);
    *s = op(k,a);
    va_end(args);

}
void Operation(string &s,string (*op) (int,const string*),int k, ...)
{
    va_list args;
    va_start(args, k);
    string a[k];
    Repacking(k-1,a,args);
    s = op(k,a);
    va_end(args);

}

int main()
{
    string a = "+";
    string b = "-10";
    string c;
//    c = without_zero(a);
//    c = Multiply(a,b);
    const string MONTHS[3] = { "1","9"};
//    const string MONTHS[3] = { "-1","","+1"};

    c = Sum(3,"0","-1","+1");

    cout<<c;

    return 0;
}
