#include <iostream>
#include <vector>
#include <chrono>
#include <functional>
#include <cmath>
#include <algorithm>


using namespace std;

class LibrFunc
{
public:
    vector<int> a;
    vector<int> b;
    vector<int> n;

    LibrFunc(string s1, string s2, string s3);

    vector<int> Switch(string s);

    void Print(vector<int> a);

    vector<int> ConstantToBigInt(int constant);

    vector<int> LongAdd(vector<int> a, vector<int> b);

    vector<int> LongSub(vector<int> a, vector<int> b);

    int LongCmp(vector<int> a, vector<int> b);

    vector<int> LongMulOneDigit(vector<int> a, int b);

    vector<int> LongMul(vector<int> a, vector<int> b);

    vector<int> LongShiftDigitsToHigh(vector<int> a, int b);

    vector<int> LongPower(vector<int> a, vector<int> b);

    pair<vector<int>, vector<int>> LongDiv(vector<int> a, vector<int> b);

};

LibrFunc::LibrFunc(string s1, string s2, string s3)
{
    a = Switch(s1);
    b = Switch(s2);
    n = Switch(s3);
}

vector<int> LibrFunc::Switch(string s)
{
    char k;
    vector<int> d2;

    int size = s.length();

    while (size % 4 != 0)
    {
        s = "0" + s;
        size++;
    }

    int j = 0;
    int* d1 = new int[size];

    for (int i = 0; i < size; i++)
    {
        k = s[i];

        if (isalpha(s[i]) == 0)
        {
            d1[j] = k - '0';
        }
        else
        {
            d1[j] = k - 'a' + 10;
        }
        j++;
    }

    cout << "\nNumber in new system:" << endl;

    for (int i = 0; i < s.length(); i = i + 4)
    {
        d2.insert(d2.begin(), d1[i] * pow(16, 3) + d1[i + 1] * pow(16, 2) + d1[i + 2] * 16 + d1[i + 3]);
    }
    
    while ((d2.size() >= 1) && (d2[d2.size() - 1] == 0))
    {
        d2.pop_back();
    }

    for (int i = 0; i < d2.size(); i++)
    {
        cout << d2[i] << " ";
    }
    cout << endl;
    
    delete[] d1; 

    return d2;
}

vector<int> LibrFunc::ConstantToBigInt(int constant) {

    vector<int> result; 

    result.push_back(constant);  

    return result;
}

vector<int> LibrFunc::LongAdd(vector<int> a, vector<int> b) // ????????? ??????????????? ?????
{
 
    if (a.size() > b.size())
    {
        for (int i = b.size(); i < a.size(); i++)
        {
            b.push_back(0);  // ?????? ????? ??????? ?? ???? ??????? 'b', ???? ?? ?? ????? ????? ? ????????, ?? ?????? 'a'
        }
    }
    if (b.size() > a.size())
    {
        for (int i = a.size(); i < b.size(); i++)
        {
            a.push_back(0);  // ?????? ????? ??????? ?? ???? ??????? 'a', ???? ?? ?? ????? ????? ? ????????, ?? ?????? 'b'
        }
    }

    int carry = 0;  // ??????????? ????? ??? ????????? ????????
    vector<int> c;  // ?????? ??? ????????? ?????????? ?????????
    int temp;

    for (int i = 0; i < a.size(); i++)
    {
        temp = a[i] + b[i] + carry;  // ??????? ?????? ????? ????? ? ?????????
        c.push_back(temp & ((int)pow(2, 16) - 1));  // ???????? ?????? ???? ? ?????
        carry = temp >> 16;  // ???????? ???????, ?? ???? ??????? ?? ?????????? ?????
    }

    if (carry != 0)
    {
        c.push_back(carry); // ?????? ?????????? ??????? ?? ??????????, ???? ?? ????
    }

    return c;  // ????????? ??????, ???? ?????? ????????? ????????? ??????????????? ?????
};

vector<int> LibrFunc::LongSub(vector<int> a, vector<int> b)  
{
    vector<int> c;  

    if (a.size() > b.size())
    {
        for (int i = b.size(); i < a.size(); i++)
        {
            b.push_back(0);  
        }
    }
    if (b.size() > a.size())
    {
        for (int i = a.size(); i < b.size(); i++)
        {
            a.push_back(0);  
        }
    }

    if (LongCmp(a, b) == 1 || LongCmp(a, b) == 0)
    {
        int borrow = 0;
        int temp;

        for (int i = 0; i < a.size(); i++)
        {
            temp = a[i] - b[i] - borrow; 
            if (temp >= 0)
            {
                c.push_back(temp);  
                borrow = 0;  
            }
            else
            {
                c.push_back((int)pow(2, 16) + temp); 
                borrow = 1;  
            }
        }
    }
    else
    {
        cout << "The second number is bigger" << endl; 
    }

    while ((c.size() >= 1) && (c[c.size() - 1] == 0))
    {
        c.pop_back();
    }

    return c;  
};

int LibrFunc::LongCmp(vector<int> a, vector<int> b) // ??????? ????????? ??????????????? ?????
{
    if (a.size() > b.size())
    {
        for (int i = b.size(); i < a.size(); i++)
        {
            b.push_back(0);  // ???????? ??????? ???????, ?????????? ?????? ?????? ??????
        }
    }
    else if (b.size() > a.size())
    {
        for (int i = a.size(); i < b.size(); i++)
        {
            a.push_back(0);  // ???????? ??????? ???????, ?????????? ?????? ?????? ??????
        }
    }

    int i = a.size() - 1;  // ????????? ????? ??, ????????? ? ???????????

    while (a[i] == b[i]) //???? ??????? ???????
    {
        i = i - 1; //?????? ????????? ??????
        if (i == -1) //???? ??????? ??????????
        {
            return 0;   // ?? ??????, ?? ????? ?????????
        }
    }
    if (a[i] > b[i])//???? ?????? ? ????? ? ?????? ?? ?????? ? ????? b
    {
        return 1; // ????? ????? ????? ?? ?????
    }
    else
    {
        return -1;  // ????? ????? ????? ?? ?????
    }
}

vector<int> LibrFunc::LongShiftDigitsToHigh(vector<int> a, int f) //???? ???? (????? ? ??? ??????? ???????) ?? f 
{
    for (int i = 0; i < f; i++)
    {
        a.insert(a.begin(), 0);  //???????? f ???? ?? ??????? ???????
    }
    return a;
};

vector<int> LibrFunc::LongMulOneDigit(vector<int> a, int b) // ???????? ???????????????? ????? ?? ???????????? ?????
{
    vector<int> c;  // ????????? ????????
    int carry = 0;  // ???????
    int temp;

    for (int i = 0; i < a.size(); i++)
    {
        temp = a[i] * b + carry;  // ??????? ???????? ?????? ?? ????? b ?? ?????? ?????????? ???????
        c.push_back(temp & ((int)pow(2, 16) - 1));  // ???????? ?????? ???? (??????) ? ?????????
        carry = temp >> 16;  // ???????? ??????? ???? ??? ???????? ????????
    }

    c.push_back(carry);  // ?????? ??????? ???? ?? ??????????

    return c;  // ????????? ????????? ????????
}

vector<int> LibrFunc::LongMul(vector<int> a, vector<int> b) 
{
   
    int maxLen = a.size() + b.size();

    while (a.size() < maxLen)
    {
        a.push_back(0);
    }
    while (b.size() < maxLen)
    {
        b.push_back(0);
    }

    vector<int> c(maxLen, 0);  
    vector<int> temp;
    c.push_back(0);

    for (int i = 0; i < a.size(); i++)
    {
        temp = LongMulOneDigit(a, b[i]);  
        temp = LongShiftDigitsToHigh(temp, i);  
        c = LongAdd(temp, c);
    }

    while ((c.size() >= 1) && (c[c.size() - 1] == 0))
    {
        c.pop_back();
    }

    return c;
}

vector<int> LibrFunc::LongPower(vector<int> a, vector<int> b)  
{
    vector<int> c; 
    vector<int> temp; 

    for (int i = 0; i < b.size(); i++)
    {
        int x = b[i];
        for (int j = 0; j < 15; j++)
        {
            c.push_back(x % 2);
            x = x >> 1;
        }
    }

    while ((c.size() >= 1) && (c[c.size() - 1] == 0))
    {
        c.pop_back();
    }

    vector<int> d;  
    d.push_back(1);

    for (int j = 0; j < c.size(); j++)
    {
        if (c[j] == 1)
        {
            d = LongMul(d, a);  
        }

        a = LongMul(a, a); 
    }

    while ((d.size() >= 1) && (d[d.size() - 1] == 0))
    {
        d.pop_back();
    }

    return d; 
}

pair<vector<int>, vector<int>> LibrFunc::LongDiv(vector<int> a, vector<int> b)
{
    if (b.empty()) {
        throw runtime_error("Division by zero is not allowed.");
    }

    int k = b.size(); 
    int t;
    vector<int> c;
    vector<int> r = a; 
    vector<int> q; 
    q.push_back(0); 

    while (LongCmp(r, b) != -1) 
    {
        t = r.size(); 
        c = LongShiftDigitsToHigh(b, t - k); 

        if (LongCmp(r, c) == -1) 
        {
            t = t - 1;
            c = LongShiftDigitsToHigh(b, t - k); 
        }

        if (LongCmp(r, c) >= 0) 
        {
            r = LongSub(r, c); 
            q = LongAdd(q, LongShiftDigitsToHigh({ 1 }, t - k)); 
        }
        else
            break;

        while ((r.size() >= 1) && (r[r.size() - 1] == 0))
        {
            r.pop_back();
        }

        if (r.empty())
        {
            r.push_back(0);
        }
    }

    return make_pair(q, r); 
}

void LibrFunc::Print(vector<int> a)
{
    char* c = new char[4 * a.size()];

    int p1, p2, p3, p4;

    for (int i = 0, j = a.size() - 1; i < 4 * a.size(); i = i + 4, j--)

    {
        p1 = ( a[j] >> 12) & 0xF;
        p2 = ( a[j] >> 8) & 0xF;
        p3 = ( a[j] >> 4) & 0xF;
        p4 = a[j] & 0xF;

        if (p1 <= 9)
        {
            c[i] = p1 + '0';
        }
        else
        {
            switch (p1)
            {
            case 10: c[i] = 'a';
                break;
            case 11: c[i] = 'b';
                break;
            case 12: c[i] = 'c';
                break;
            case 13: c[i] = 'd';
                break;
            case 14: c[i] = 'e';
                break;
            case 15: c[i] = 'f';
                break;
            }
        }
        if (p2 <= 9)
        {
            c[i + 1] = p2 + '0';
        }
        else
        {
            switch (p2)
            {
            case 10: c[i + 1] = 'a';
                break;
            case 11: c[i + 1] = 'b';
                break;
            case 12: c[i + 1] = 'c';
                break;
            case 13: c[i + 1] = 'd';
                break;
            case 14: c[i + 1] = 'e';
                break;
            case 15: c[i + 1] = 'f';
                break;
            }
        }

        if (p3 <= 9)
        {
            c[i+2] = p3 + '0';
        }
        else
        {
            switch (p3)
            {
            case 10: c[i + 2] = 'a';
                break;
            case 11: c[i + 2] = 'b';
                break;
            case 12: c[i + 2] = 'c';
                break;
            case 13: c[i + 2] = 'd';
                break;
            case 14: c[i + 2] = 'e';
                break;
            case 15: c[i + 2] = 'f';
                break;
            }
        }

        if (p4 <= 9)
        {
            c[i+3] = p4 + '0';
        }
        else
        {
            switch (p4)
            {
            case 10: c[i + 3] = 'a';
                break;
            case 11: c[i + 3] = 'b';
                break;
            case 12: c[i + 3] = 'c';
                break;
            case 13: c[i + 3] = 'd';
                break;
            case 14: c[i + 3] = 'e';
                break;
            case 15: c[i + 3] = 'f';
                break;
            }
        }
    }

    while ((a.size() >= 1) && (a[a.size() - 1] == 0))
    {
        a.pop_back();
    }

    for (int i = 0; i < 4 * a.size(); i++)

    {
        cout << c[i]; 
    }
    cout << endl;
}

double MeasureTime(function<void()> operation) {
    // ?????'??????? ??? ??????? ????????? ????????
    auto start_time = chrono::high_resolution_clock::now();

    // ???????? ???????? ????????
    operation();

    // ?????'??????? ??? ?????????? ????????? ????????
    auto end_time = chrono::high_resolution_clock::now();

    // ?????????? ????????? ????????? ????????
    chrono::duration<double> elapsed_time = end_time - start_time;

    // ????????? ??? ????????? ???????? ? ????????
    return elapsed_time.count();
}

int main()
{
    string s1, s2, s3, s4;

    s1 = "ffd";
    s2 = "3";
    
    s3 = "3ff";
    s4 = "a1";

    LibrFunc A(s1, s2, s3);
    vector<int> h1 = A.Switch(s4);
    cout << endl;
    
    int t;
    double time_cmp = MeasureTime([&]() {
        t = A.LongCmp(A.a, A.b);
        });
    cout << "\n a VS b : " << t << endl;
    cout << "Time taken for comparison: " << time_cmp << " seconds" << endl;

    double time_add = MeasureTime([&]() {
        cout << "\n a + b : ";
        A.Print(A.LongAdd(A.a, A.b));
        });
    cout << "Time taken for addition: " << time_add << " seconds" << endl;

    double time_sub = MeasureTime([&]() {
        cout << "\n a - b : ";
        A.Print(A.LongSub(A.a, A.b));
        });
    cout << "Time taken for subtraction: " << time_sub << " seconds" << endl;
    
    double time_mul = MeasureTime([&]() {
        cout << "\n a * b : ";
        A.Print(A.LongMul(A.a, A.b));
        });
    cout << "Time taken for multiplication: " << time_mul << " seconds" << endl;

    cout << "\n a ^ 2 : ";
    A.Print(A.LongMul(A.a, A.a));
    
    pair<vector<int>, vector<int>> result;
    double time_div = MeasureTime([&]() {
        result = A.LongDiv(A.a, A.b);
        });
    cout << endl << "Time taken for division: " << time_div << " seconds" << endl;

    vector<int> quotient = result.first;
    vector<int> remainder = result.second;
    cout << "\n a / b = : ";
    A.Print(quotient);

    cout << "\n a % b = : ";
    A.Print(remainder);
    
    double time_power = MeasureTime([&]() {
            cout << "\n a ^ b : ";
            A.Print(A.LongPower(A.a, A.b));
            });
    cout << "Time taken for exponentiation: " << time_power << " seconds" << endl;
    
    cout << "\na*c + b*c = ";
    A.Print(A.LongAdd(A.LongMul(A.a, A.n), A.LongMul(A.b, A.n)));

    cout << "\nc * (a + b) = ";
    A.Print(A.LongMul(A.n, A.LongAdd(A.a, A.b)));

    cout << "\nc * a = ";
    A.Print(A.LongMul(A.a, h1));

    cout << "\na + a ... + a = ";
    vector<int> h0;
    h0.push_back(0);
    int g = 161;
    for (int i = 0; i < g; i++)
    {
        h0 = A.LongAdd(h0, A.a);
    }
    A.Print(h0);
    
    return 0;
}