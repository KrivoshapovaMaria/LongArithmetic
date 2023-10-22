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
    vector<uint16_t> a;  // ������ ��� ��������� ����� a
    vector<uint16_t> b;  // ������ ��� ��������� ����� b
    vector<uint16_t> n;  // ������ ��� ��������� ����� n

    // ����������� �����, ���� ������ ��� ����� �� �������� ������� ������� a, b, n
    LibrFunc(string s1, string s2, string s3);

    // ����� ��� ������������ ����� s � ������ ����� �����
    vector<uint16_t> Switch(string s);
    // ����� ��� ��������� ������� ����� ����� �� �����
    void Print(vector<uint16_t> a);

    // ����� ��� ������������ ��������� � ������ ����� �����
    vector<uint16_t> ConstantToBigInt(int constant);

    // ����� ��� ��������� ���� ��������������� �����
    vector<uint16_t> LongAdd(vector<uint16_t> a, vector<uint16_t> b);

    // ����� ��� �������� ���� ��������������� �����
    vector<uint16_t> LongSub(vector<uint16_t> a, vector<uint16_t> b);

    // ����� ��� ��������� ���� ��������������� �����
    int LongCmp(vector<uint16_t> a, vector<uint16_t> b);

    // ����� ��� �������� ���������������� ����� �� ���� �����
    vector<uint16_t> LongMulOneDigit(vector<uint16_t> a, int b);

    // ����� ��� �������� ���� ��������������� �����
    vector<uint16_t> LongMul(vector<uint16_t> a, vector<uint16_t> b);

    // ����� ��� ����� ���������������� ����� ���� �� ����� ������� ���
    vector<uint16_t> LongShiftDigitsToHigh(vector<uint16_t> a, int b);

    // ����� ��� ��������� ���������������� ����� �� �������
    vector<uint16_t> LongPower(vector<uint16_t> a, vector<uint16_t> b);

    // ����� ��� �������� ������ ���� ��������������� �����
    pair<vector<uint16_t>, vector<uint16_t>> LongDiv(vector<uint16_t> a, vector<uint16_t> b);

};

LibrFunc::LibrFunc(string s1, string s2, string s3)
{
    a = Switch(s1);
    b = Switch(s2);
    n = Switch(s3);
}

vector<uint16_t> LibrFunc::Switch(string s)
{
    // ����� �������� ����� s � ����� �� ������ ������������ ��� ����� � ���� ������� ��������

    char k;
    vector<uint16_t> d2;  // ������ ��� ��������� ������������ �����

    int size = s.length();

    // ���� ������� ����� �� �����, ������ "0" ���� ��� ����������
    if (size % 2 != 0)
    {
        s = "0" + s;
        cout << s;
        size++;
    }

    int j = 0;
    uint16_t* d1 = new uint16_t[size];

    // ������������ ������� ����� � ����� � �������� �� � ����� d1
    for (int i = 0; i < size; i++)
    {
        k = s[i];

        // ��������, �� ������ � ������ (0-9) �� ������ (A-F)
        if (isalpha(s[i]) == 0)
        {
            d1[j] = k - '0';  // ������������ �������� ������ � �������� �����
        }
        else
        {
            d1[j] = k - 'a' + 10;  // ������������ ������� ������ (A-F) � �������� ����� (10-15)
        }
        j++;
    }

    cout << "\nNumber in new system:" << endl;  // �������� ����������� ��� ����� � ���� ������

    // ���������� ���� ����� (� ���������������� ������) � ���������� ������ �� ������ �� ������� d2
    for (int i = 0; i < s.length(); i = i + 2)
    {
        d2.insert(d2.begin(), d1[i] * 16 + d1[i + 1] * 1);  // ��� ����� � �������������� ������, ������������� �������� �� 16
    }

    // �������� ����� � ���� ������
    for (auto i = d2.begin(); i != d2.end(); i++)
    {
        cout << (int)(*i) << " ";
    }

    return d2;  // ��������� ������ ������������ �����
};

vector<uint16_t> LibrFunc::ConstantToBigInt(int constant) {
    // ����� ����������� ��� ��������� �������, ���� ����������� ������ ���� ����� �� ����� ������ ������������ �����

    vector<uint16_t> result;  // ������ ��� ��������� �������� ������ �����

    result.push_back(constant);  // ������ ���������� ����� �� �������

    return result;  // ��������� ������, ������������� ������ ���� �����
}

vector<uint16_t> LibrFunc::LongAdd(vector<uint16_t> a, vector<uint16_t> b) // ��������� ��������������� �����
{
    // �����������, �� ������ ������� ����� �������� �������, ���������� �� ������
    if (a.size() > b.size())
    {
        for (int i = b.size(); i < a.size(); i++)
        {
            b.push_back(0);  // ������ ����� ������� �� ���� ������� 'b', ���� �� �� ����� ����� � ��������, �� ������ 'a'
        }
    }
    if (b.size() > a.size())
    {
        for (int i = a.size(); i < b.size(); i++)
        {
            a.push_back(0);  // ������ ����� ������� �� ���� ������� 'a', ���� �� �� ����� ����� � ��������, �� ������ 'b'
        }
    }

    int carry = 0;  // ���������� ����� ��� ��������� ��������
    vector<uint16_t> c;  // ������ ��� ��������� ���������� ���������
    int temp;

    for (int i = 0; i < a.size(); i++)
    {
        temp = a[i] + b[i] + carry;  // ������� ������ ����� ����� � ���������
        c.push_back(temp & ((int)pow(2, 8) - 1));  // �������� ������ ���� � �����
        carry = temp >> 8;  // �������� �������, �� ���� ������� �� ���������� �����
    }

    if (carry != 0)
    {
        c.push_back(carry); // ������ ���������� ������� �� ����������, ���� �� ����
    }

    return c;  // ��������� ������, ���� ������ ��������� ��������� ��������������� �����
};

vector<uint16_t> LibrFunc::LongSub(vector<uint16_t> a, vector<uint16_t> b)  // ³������� ��������������� �����
{
    vector<uint16_t> c;  // ������ ��� ��������� ���������� ��������

    // �����������, �� ������ ������� ����� �������� �������, ���������� �� ������
    if (a.size() > b.size())
    {
        for (int i = b.size(); i < a.size(); i++)
        {
            b.push_back(0);  // ������ ����� ������� �� ���� ������� 'b', ��� ������� ������� �������
        }
    }
    if (b.size() > a.size())
    {
        for (int i = a.size(); i < b.size(); i++)
        {
            a.push_back(0);  // ������ ����� ������� �� ���� ������� 'a', ��� ������� ������� �������
        }
    }

    // ����������, ��� � ����� ����� ��� �� ���� ���, ��� �� �������� ��'������ ����������
    if (LongCmp(a, b) == 1 || LongCmp(a, b) == 0)
    {
        int borrow = 0;
        int temp;

        // �������� �������� ������� � ����������� ����� �� ������� �������
        for (int i = 0; i < a.size(); i++)
        {
            temp = a[i] - b[i] - borrow;  // ³������ ������ ��� � ��������
            if (temp >= 0)
            {
                c.push_back(temp);  // ���� ��������� �������� ���������� ��� ����, ������ ���� �� ���������� 'c'
                borrow = 0;  // ������� �������
            }
            else
            {
                c.push_back((int)pow(2, 8) + temp);  // ���� ��������� �������� ��'�����, ������ ���� � ������������� �� 256 (2^8)
                borrow = 1;  // ������������ ������� ��� ���������� �������
            }
        }
    }
    else
    {
        cout << "The second number is bigger" << endl;  // �������� �����������, ���� ����� ����� �����
    }

    return c;  // ��������� ������, ���� ������ ��������� �������� ��������������� �����
};

int LibrFunc::LongCmp(vector<uint16_t> a, vector<uint16_t> b) // ������� ��������� ��������������� �����
{
    if (a.size() > b.size())
    {
        for (int i = b.size(); i < a.size(); i++)
        {
            b.push_back(0);  // �������� ������� �������, ���������� ������ ������ ������
        }
    }
    else if (b.size() > a.size())
    {
        for (int i = a.size(); i < b.size(); i++)
        {
            a.push_back(0);  // �������� ������� �������, ���������� ������ ������ ������
        }
    }

    int i = a.size() - 1;  // ��������� ����� ��, ��������� � �����������

    while (a[i] == b[i]) //���� ������� �������
    {
        i = i - 1; //������ ��������� ������
        if (i == -1) //���� ������� ����������
        {
            return 0;   // �� ������, �� ����� ��������
        }
    }
    if (a[i] > b[i])//���� ������ � ����� � ������ �� ������ � ����� b
    {
        return 1; // ����� ����� ����� �� �����
    }
    else
    {
        return -1;  // ����� ����� ����� �� �����
    }
}

vector<uint16_t> LibrFunc::LongShiftDigitsToHigh(vector<uint16_t> a, int f) //���� ���� (����� � ��� ������� �������) �� f 
{
    for (int i = 0; i < f; i++)
    {
        a.insert(a.begin(), 0);  //�������� f ���� �� ������� �������
    }
    return a;
};

vector<uint16_t> LibrFunc::LongMulOneDigit(vector<uint16_t> a, int b) // �������� ���������������� ����� �� ������������ �����
{
    vector<uint16_t> c;  // ��������� ��������
    int carry = 0;  // �������
    int temp;

    for (int i = 0; i < a.size(); i++)
    {
        temp = a[i] * b + carry;  // ������� �������� ������ �� ����� b �� ������ ��������� �������
        c.push_back(temp & ((int)pow(2, 8) - 1));  // �������� ������ ���� (������) � ���������
        carry = temp >> 8;  // �������� ������� ���� ��� �������� ��������
    }

    c.push_back(carry);  // ������ ������� ���� �� ����������

    return c;  // ��������� ��������� ��������
}

vector<uint16_t> LibrFunc::LongMul(vector<uint16_t> a, vector<uint16_t> b) // �������� ��������������� �����
{
    // �������� ����������� ������� ����������
    int maxLen = a.size() + b.size();

    // ������ ��������� ������� �������� ��� �� ������� a �� b
    while (a.size() < maxLen)
    {
        a.push_back(0);
    }
    while (b.size() < maxLen)
    {
        b.push_back(0);
    }

    vector<uint16_t> c(maxLen, 0);  // ��������� ���� ���� ����������� ������� �������
    vector<uint16_t> temp;
    c.push_back(0);

    for (int i = 0; i < a.size(); i++)
    {
        temp = LongMulOneDigit(a, b[i]);  // ������� ����� a �� ������������ ����� b
        temp = LongShiftDigitsToHigh(temp, i);  // ������� ��������� �� ������� ������� �������
        c = LongAdd(temp, c);  // ������ ��������� �� ������������ ������������ ����������
    }

    while ((c.size() >= 1) && (c[c.size() - 1] == 0))
    {
        c.pop_back();  // ��������� �� ��� � ������� ���� ������� c ��� ���������� �� ����������� � ��������� ������ ����
    }

    return c;  // ��������� ��������� ��������
}

vector<uint16_t> LibrFunc::LongPower(vector<uint16_t> a, vector<uint16_t> b)  // ϳ�������� ����� �� ������� �� ������ �������
{
    vector<uint16_t> c;  // ������, ���� ���� ������ ������ ������������� ������� b
    vector<uint16_t> temp;

    // ������������ ������ b � ������� ������ � �������� ���� � ������ c
    for (int i = 0; i < b.size(); i++)
    {
        int x = b[i];
        for (int j = 0; j < 7; j++)
        {
            c.push_back(x % 2);  // �������� ��������� �� ���������� ����� ������� b � ������ ���� �� ������� c
            x = x >> 1;  // ������� ����� b ������ �� ���� �� (����������� �������������� ������ �� 2)
        }
    }

    reverse(c.begin(), c.end());  // ����������� ������, ��� ���� ������ ������������� � ����������� �������
    
    vector<uint16_t> d;  // ������ ��� ����������� ����������
    d.push_back(1);  // ���������� ���� ��������� 1, �� ��������� ��������

    for (int j = 0; j < c.size(); j++)
    {
        if (c[j] == 1)
        {
            d = LongMul(d, a);  // ���� �� ������� ����� 1, ������� �������� ��������� �� a
        }

        a = LongMul(a, a);  // ϳ�������� a �� �������� �� ������� �����
    }

    return d;  // ��������� ��������� ��������� �� �������
}

pair<vector<uint16_t>, vector<uint16_t>> LibrFunc::LongDiv(vector<uint16_t> a, vector<uint16_t> b)
{
    // ��������� �� ��� � ���� ������� 'a' ��� ���������� �������� ������
    while (a[a.size() - 1] == 0)
    {
        a.pop_back();
    }

    // ��������� �� ��� � ���� ������� 'b' ��� ���������� �������� ������
    while (b[b.size() - 1] == 0)
    {
        b.pop_back();
    }

    // ������� ������� ������ �� ����.
    if (b.empty()) {
        throw runtime_error("Division by zero is not allowed.");
    }

    int k = b.size(); // ������� ������� 'b'
    int t;
    vector<uint16_t> c; // ������, ���� ��������������� ��� ���������� ������� �� ������� �����
    vector<uint16_t> r = a; // ������, ���� ��������������� ��� ��������� ����� �� ��� ������
    vector<uint16_t> q; // ������, ����������� ��������� ������ (������)
    q.push_back(0); // ���������� ������ �����

    while (LongCmp(r, b) != -1) // ���� ����� 'r' ����� ��� ������� ������� 'b'
    {
        t = r.size(); // ������� ������� ����� 'r'
        c = LongShiftDigitsToHigh(b, t - k); // ³��������� ������ 'b' �� ��������� �����

        if (LongCmp(r, c) == -1) // ��������� ����� �� ������
        {
            t = t - 1;
            c = LongShiftDigitsToHigh(b, t - k); // �������� ������� ������� �� �������, ���� �������
        }

        if (LongCmp(r, c) >= 0) // ���� ����� ����� ��� ������� �������
        {
            r = LongSub(r, c); // ³������ ������ �� �����
            q = LongAdd(q, LongShiftDigitsToHigh({ 1 }, t - k)); // ������ ������� �� ������
        }
        else
            break;

        // ��������� �� ��� � ������� ���� ����� 'r' ��� ���������� �� ����������� � ��������� ������ ����
        while ((r.size() >= 1) && (r[r.size() - 1] == 0))
        {
            r.pop_back();
        }

        if (r.empty())
        {
            r.push_back(0);
        }
    }

    return make_pair(q, r); // ��������� ����, �� ������ ������� - ������, ������ - ������
}

void LibrFunc::Print(vector<uint16_t> a)  // ����� ��� ������ ���������������� ����� � ���������������� ������
{
    char* c = new char[2 * a.size()];
    // ��������� ����� ������� ��� ��������� ���������������� ������������� �����
    int p1;
    int p2;
    for (int i = 0, j = a.size() - 1; i < 2 * a.size() - 1; i = i + 2, j--)

    {
        p1 = a[j] / 16;  // ������ �������� ������� � �������� ����� �����
        p2 = a[j] % 16;
        if (p1 <= 9)
        {
            c[i] = p1 + '0';  // ���� �� ����� (0-9), ���������� � ������ �� '0' �� '9'
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
            c[i + 1] = p2 + '0';  // ��������� ��� ��������� �����
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
    }
    for (int i = 0; i < 2 * a.size(); i++)

    {
        cout << c[i];  // �������� ������� ���������������� ������������� �����
    }
    cout << endl;
}

// ������� ��� ���������� ���� ��������� ��������
double MeasureTime(function<void()> operation) {
    // �����'������� ��� ������� ��������� ��������
    auto start_time = chrono::high_resolution_clock::now();
    
    // �������� �������� ��������
    operation();
    
    // �����'������� ��� ���������� ��������� ��������
    auto end_time = chrono::high_resolution_clock::now();

    // ���������� ��������� ��������� ��������
    chrono::duration<double> elapsed_time = end_time - start_time;

    // ��������� ��� ��������� �������� � ��������
    return elapsed_time.count();
}

int main()
{
    string s1, s2, s3, s4;

    s2 = "5539647ee7034e20855240a49605dd2f7acf1febcce1b355a63857ba4da6cdb8f552ea153c730d97a1fa97c2bb0630d2375bf91396c9f484101699cc7b5d6d1e6ccd0992582b99977b631045fb465c170a6b7f4b96eeea3bd44302619405bd895db6092100e99d0b652849a83aa33923adf2ecd95ff47206d03ab650e2c012ad";
    s1 = "166204774917731692465071051218633847177575649661847257577738225172643770991995056377238993232343726095055476657806754336269256061881651684346605667474097642554519354407729197504117667461725385675392789405136523964331953461604602583132401264589827197103795360364478041063457183868839728065265361621786808996368";
    s3 = "3ff";
    s4 = "a1";

    LibrFunc A(s1, s2, s3);
    vector<uint16_t> h1 = A.Switch(s4);
    cout << endl;

    vector<uint16_t> zero = A.ConstantToBigInt(0);
    vector<uint16_t> one = A.ConstantToBigInt(1);

    int k = 10;
    int t;
    double time_cmp = MeasureTime([&]() {
        t = A.LongCmp(A.a, A.b);
        });
    cout << "\n a VS b : " << t << endl;
    cout << "Time taken for comparison: " << time_cmp << " seconds" << endl;

    double time_add = MeasureTime([&]() {
        cout << "\n a + b : " ;
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

    pair<vector<uint16_t>, vector<uint16_t>> result;
    double time_div = MeasureTime([&]() {
        result = A.LongDiv(A.a, A.b);
        });
    cout << endl << "Time taken for division: " << time_div << " seconds" << endl;

    vector<uint16_t> quotient = result.first;
    vector<uint16_t> remainder = result.second;
    cout << "\n a / b = : ";
    A.Print(quotient); 

    cout << "\n a % b = : ";
    A.Print(remainder); 
/*
    double time_power = MeasureTime([&]() {
        cout << "\n a ^ b : ";
        A.Print(A.LongPower(A.a, A.b));
        });
    cout << "Time taken for exponentiation: " << time_power << " seconds" << endl;
*/
    //����²���

    cout << "\na*c + b*c = ";
    A.Print(A.LongAdd(A.LongMul(A.a, A.n), A.LongMul(A.b, A.n)));

    cout << "\nc * (a + b) = ";
    A.Print(A.LongMul(A.n, A.LongAdd(A.a, A.b)));

    cout << "\nc * a = ";
    A.Print(A.LongMul(A.a, h1));

    cout << "\na + a ... + a = ";
    vector<uint16_t> h0;
    h0.push_back(0);
    int g = 161;
    for (int i = 0; i < g; i++)
    {
        h0 = A.LongAdd(h0, A.a);
    }
    A.Print(h0);

    return 0;
}
