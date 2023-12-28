#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <functional>

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
    vector<int> LongShiftDigitsToLow(vector<int> a, int b);
    vector<int> LongShiftBitsToHigh(vector<int> a, int f);
    vector<int> LongShiftBitsToLow(vector<int> a, int f);
    vector<int> LongPower(vector<int> a, vector<int> b);
    pair<vector<int>, vector<int>> LongDiv(vector<int> a, vector<int> b);
    vector<int> Long_remainder(vector<int> a, vector<int> b);
    vector<int> Long_quotient(vector<int> a, vector<int> b);
    vector<int> GSD(vector<int> a1, vector<int> b1);
    vector<int> Evklid_GSD(vector<int> a, vector<int> b);
    vector<int> LCM(vector<int> a, vector<int> b);
    vector<int> Mu(vector<int> n);
    vector<int> BarRed(vector<int> a, vector<int> b);
    vector<int> LongAddRed(vector<int> a, vector<int> b);
    vector<int> LongMulRed(vector<int> a, vector<int> b, vector<int> n);
    vector<int> LongSubRed(vector<int> a, vector<int> b);
    vector<int> LongPowerRed(vector<int> a, vector<int> b, vector<int> n);
    vector<int> LongSquareRed(vector<int> a, vector<int> n);
    vector<int> Normalized(vector<int> a);
    int BitsLength(vector<int> a);
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

    //cout << "\n in new system:" << endl;

    for (int i = 0; i < s.length(); i = i + 4)
    {
        d2.insert(d2.begin(), d1[i] * pow(16, 3) + d1[i + 1] * pow(16, 2) + d1[i + 2] * 16 + d1[i + 3]);
    }
    /*
    for (int i = 0; i < d2.size(); i++)
    {
        cout << d2[i] << " ";
    }
    cout << endl;
    */
    delete[] d1;

    return d2;
}
vector<int> LibrFunc::ConstantToBigInt(int constant) {

    vector<int> result;

    result.push_back(constant);

    return result;
}
vector<int> LibrFunc::LongAdd(vector<int> a, vector<int> b)
{

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

    int carry = 0;
    vector<int> c;
    int temp;

    for (int i = 0; i < a.size(); i++)
    {
        temp = a[i] + b[i] + carry;
        c.push_back(temp & ((int)pow(2, 16) - 1));
        carry = temp >> 16;
    }

    if (carry != 0)
    {
        c.push_back(carry);
    }

    return c;
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
        cout << "The second a is bigger" << endl;
    }
    c = Normalized(c);
    return c;
};
int LibrFunc::LongCmp(vector<int> a, vector<int> b)
{
    if (a.size() > b.size())
    {
        for (int i = b.size(); i < a.size(); i++)
        {
            b.push_back(0);
        }
    }
    else if (b.size() > a.size())
    {
        for (int i = a.size(); i < b.size(); i++)
        {
            a.push_back(0);
        }
    }

    int i = a.size() - 1;

    while (a[i] == b[i])
    {
        i = i - 1;
        if (i == -1)
        {
            return 0;
        }
    }
    if (a[i] > b[i])
    {
        return 1;
    }
    else
    {
        return -1;
    }
}
vector<int> LibrFunc::LongShiftDigitsToHigh(vector<int> a, int f)
{
    for (int i = 0; i < f; i++)
    {
        a.insert(a.begin(), 0);
    }
    return a;
};
vector<int> LibrFunc::LongShiftDigitsToLow(vector<int> a, int f)
{
    for (int i = 0; i < f; i++)
    {
        a.push_back(0);
        a.erase(a.begin());
    }
    return a;
}
vector<int> LibrFunc::LongShiftBitsToHigh(vector<int> a, int f) {
    if (f <= 0 || a == vector<int>{0}) {
        return a;
    }

    int remainder = f % 16;
    f /= 16;
    vector<int> result = LongShiftDigitsToHigh(a, f);

    if (remainder > 0) {
        for (int i = 0; i < remainder; ++i) {
            int last_bit = (result.back() >> 15) & 1;
            for (int j = result.size() - 1; j > 0; --j) {
                result[j] = ((result[j] << 1) ^ ((result[j - 1] >> 15) & 1)) & 0xFFFF;
            }
            result[0] = (result[0] << 1) & 0xFFFF;
            if (last_bit != 0) {
                result.push_back(last_bit);
            }
        }
    }

    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }

    return result;
}
vector<int> LibrFunc::LongShiftBitsToLow(vector<int> n, int f) {
    if (f <= 0 || n == vector<int>{0}) {
        return n;
    }

    int remainder = f % 16;
    f /= 16;
    vector<int> result = n;
    //Print(result);  //неправильно
    for (int i = 0; i < f; ++i) {
        result.erase(result.begin());
    }

    if (remainder > 0) {
        for (int i = 0; i < remainder; ++i) {
            //int last_bit = (result[0] & 1) << 15;
            for (size_t j = 0; j < result.size() - 1; ++j) {
                result[j] = ((result[j] >> 1) ^ ((result[j + 1] & 1) << 15)) & 0xFFFF;
            }
            result[result.size() - 1] = (result[result.size() - 1] >> 1) & 0xFFFF;
        }
    }
    //Print(n); //не правильно

    result = Normalized(result);

    return result;

}
vector<int> LibrFunc::LongMulOneDigit(vector<int> a, int b)
{
    vector<int> c;
    int carry = 0;
    uint32_t temp;

    for (int i = 0; i < a.size(); i++)
    {
        temp = a[i] * b + carry;
        c.push_back(temp & ((int)pow(2, 16) - 1));
        carry = temp >> 16;
    }

    c.push_back(carry);
    return c;
}
vector<int> LibrFunc::LongMul(vector<int> a, vector<int> b)
{
    int maxlen = a.size() + b.size();

    while (a.size() < maxlen)
    {
        a.push_back(0);
    }
    while (b.size() < maxlen)
    {
        b.push_back(0);
    }

    vector<int> c;
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
/*vector<int> LibrFunc::LongMul(vector<int> a, vector<int> b)
{
    if (LongCmp(a, b) == -1) {
        return LongMul(b, a);
    }

    std::vector<int> c(a.size() + b.size(), 0);

    for (size_t i = 0; i < b.size(); ++i) {
        int carry = 0;
        for (size_t j = 0; j < a.size(); ++j) {
            uint32_t temp = c[i + j] + a[j] * b[i] + carry;
            c[i + j] = temp & (static_cast<int>(1) << 16) - 1;
            carry = temp >> 16;
        }

        if (carry > 0) {
            c[i + a.size()] += carry;
        }
    }

    while (c.size() > 1 && c.back() == 0) {
        c.pop_back();
    }

    return c;
}*/
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

    return d;
}
int LibrFunc::BitsLength(vector<int> a) {
    int result;
    int t;
    for (t = 15; t >= 0; t--) {
        if ((a[a.size() - 1] & (1 << t)) != 0) {
            break;
        }
    }
    result = (a.size() - 1) * 16 + t + 1;
    return result;
}
pair<vector<int>, vector<int>> LibrFunc::LongDiv(vector<int> a, vector<int> b)
{
    if (b.empty()) {
        throw runtime_error("Division by zero is not allowed.");
    }

    if (LongCmp(a, b) == 0) {
        return make_pair(ConstantToBigInt(1), ConstantToBigInt(0));
    }

    int k = BitsLength(b);
    int t;
    vector<int> c;
    vector<int> r = a;
    vector<int> q;
    q.push_back(0);

    while (LongCmp(r, b) != -1)
    {
        t = BitsLength(r);
        c = LongShiftBitsToHigh(b, t - k);

        if (LongCmp(r, c) == -1)
        {
            t -= 1;
            int len = t - k;
            c = LongShiftBitsToHigh(b, len);
        }

        r = LongSub(r, c);

        q = LongAdd(q, LongShiftBitsToHigh({ 1 }, t - k));
        /*
        while ((r.size() >= 1) && (r[r.size() - 1] == 0))
        {
            r.pop_back();
        }

        if (r.empty())
        {
            r.push_back(0);
        }
        */
    }
    return make_pair(q, r);
}
void LibrFunc::Print(vector<int> a)
{
    char* c = new char[4 * a.size()];

    int p1, p2, p3, p4;

    for (int i = 0, j = a.size() - 1; i < 4 * a.size(); i = i + 4, j--)

    {
        p1 = (a[j] >> 12) & 0xF;
        p2 = (a[j] >> 8) & 0xF;
        p3 = (a[j] >> 4) & 0xF;
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
            c[i + 2] = p3 + '0';
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
            c[i + 3] = p4 + '0';
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

    for (int i = 0; i < 4 * a.size(); i++)

    {
        cout << c[i];
    }
}
vector<int> LibrFunc::Long_remainder(vector<int> a, vector<int> b)
{
    return LongDiv(a, b).second;
}
vector<int> LibrFunc::Long_quotient(vector<int> a, vector<int> b)
{
    return LongDiv(a, b).first;
}
vector<int> LibrFunc::GSD(vector<int> a, vector<int> b) {
    vector<int> d = ConstantToBigInt(1);
    int cmp = 0;
    int sub = 0;
    while (a[0] % 2 == 0 && b[0] % 2 == 0) {
        a = LongShiftBitsToLow(a, 1);

        b = LongShiftBitsToLow(b, 1);

        d = LongShiftBitsToHigh(d, 1);
    }

    while (a[0] % 2 == 0) {
        a = LongShiftBitsToLow(a, 1);
    }

    while (LongCmp(b, ConstantToBigInt(0)) != 0) {

        cmp = cmp + 1;

        while (b[0] % 2 == 0) {
            b = LongShiftBitsToLow(b, 1);
        }

        int lc = LongCmp(a, b);
        cmp = cmp + 1;

        vector<int> subAB, minAB;
        if (lc == 1) {
            minAB = b;
            subAB = LongSub(a, b);
            sub = sub + 1;
        }
        else if (lc == -1) {
            minAB = a;
            subAB = LongSub(b, a);
            sub = sub + 1;
        }
        else {
            minAB = b;
            subAB = ConstantToBigInt(0);
        }

        a = minAB;
        b = subAB;
    }

    d = LongMul(d, a);

    //cout << "Comparisons:" << cmp << endl;
    //cout << "Subtraction:" << sub << endl;
    return d;
}
vector<int> LibrFunc::Evklid_GSD(vector<int> a, vector<int> b) {
    int cmp = 0;
    int div = 0;
    while (LongCmp(a, ConstantToBigInt(0)) != 0 && LongCmp(b, ConstantToBigInt(0)) != 0) {
        int cmp_num = LongCmp(a, b);
        cmp = cmp + 3;

        if (cmp_num == 1) {
            a = Long_remainder(a, b);
            div = div + 1;
        }
        else if (cmp_num == -1) {
            b = Long_remainder(b, a);
            div = div + 1;
        }
        else {
            b = ConstantToBigInt(0);
        }
    }

    vector <int> res = LongAdd(a, b);

    //cout << "Comparisons:" << cmp << endl;
    //cout << "Division:" << div << endl;
    return res;
}
vector<int> LibrFunc::LCM(vector<int> a, vector<int> b)
{
    vector<int> gsd = Evklid_GSD(a, b);
    vector<int> k = LongMul(a, b);
    vector <int> d;
    d = Long_quotient(k, gsd);
    /*if (gsd == ConstantToBigInt(1)) {
        d = k;
    }
    else {
        d = Long_quotient(k, gsd);
    }*/
    d = Normalized(d);
    return d;
};
vector<int> LibrFunc::Mu(vector<int> n)
{
    //n = Normalized(n);
    vector<int>  m;
    int k = n.size(); //у Віки 32, у мене 64
    //cout << k << endl;
    m = ConstantToBigInt(1);
    m = LongShiftDigitsToHigh(m, 2 * k);
    //l = LongShiftDigitsToHigh({1}, k);
    //Print(l);
    //cout << endl;
    m = Long_quotient(m, n);
    //Print(l);
    //cout << endl;
    return m;
    //Print(m); //мю рахує правильно
};
vector<int> LibrFunc::BarRed(vector<int> a, vector<int> n)
{
    vector <int> m = Mu(n);
    vector <int> q, r;
    int k = n.size();
    q = LongShiftBitsToLow(a, (k - 1) * 16);
    q = LongMul(q, m);
    q = LongShiftBitsToLow(q, (k + 1) * 16);
    r = LongSub(a, LongMul(q, n));
    while (LongCmp(r, n) != -1)
    {
        r = LongSub(r, n);
    }
    while ((r.size() >= 1) && (r[r.size() - 1] == 0))
    {
        r.pop_back();
    }
    r = Normalized(r);
    return r;
}
vector<int> LibrFunc::LongAddRed(vector<int> a, vector<int> b)
{
    vector <int> c;
    vector <int> d;
    c = LongAdd(a, b);
    d = BarRed(c, n);
    d = Normalized(d);
    return d;
}
vector<int> LibrFunc::LongSubRed(vector<int> a, vector<int> b)
{
    vector <int> c;
    vector <int> d;
    if (LongCmp(a, b) == -1) {
        while (LongCmp(a, b) == -1) {
            a = LongAdd(a, n);
            d = LongSub(a, b);
        }
    }

    c = LongSub(a, b);
    d = BarRed(c, n);
    d = Normalized(d);
    return d;
}
vector<int> LibrFunc::LongMulRed(vector<int> a, vector<int> b, vector<int> n)
{
    vector <int> c, d;
    c = LongMul(a, b);
    d = BarRed(c, n);
    d = Normalized(d);
    return d;
}
vector<int> LibrFunc::LongPowerRed(vector<int> a, vector<int> b, vector<int> n)
{
    vector<int> c;
    vector<int> temp;

    for (int i = 0; i < b.size(); i++)
    {
        int x = b[i];
        for (int j = 0; j < 16; j++)
        {
            c.push_back(x % 2);
            x = x >> 1;
        }
    }

    c = Normalized(c);

    vector<int> d;
    d.push_back(1);

    for (int j = 0; j < c.size(); j++)
    {
        if (c[j] == 1)
        {
            d = BarRed(LongMul(d, a), n);
        }

        a = BarRed(LongMul(a, a), n);
    }

    d = Normalized(d);
    return d;
}
vector<int> LibrFunc::LongSquareRed(vector<int> a, vector<int> n)
{
    vector<int> c = LongMulRed(a, a, n);
    return c;
}
vector<int> LibrFunc::Normalized(vector<int> a) {
    if (a.empty()) {
        a.push_back(0);
    }

    for (int i = a.size() - 1; i > 0; --i) {
        if (a[i] != 0) {
            break;
        }

        a.pop_back();
    }

    return a;
}
double MeasureTime(function<void()> operation) {
    auto start_time = chrono::high_resolution_clock::now();

    operation();

    auto end_time = chrono::high_resolution_clock::now();

    chrono::duration<double> elapsed_time = end_time - start_time;

    return elapsed_time.count();
}

int main()
{
    string s1, s2, s3, s4, s5;
    
    s1 = "6a19830a1b4ee6e5dae6cf6ce944c31eefd620d2ae72d19b0ec6b559d9fdb4463b5e92dbabab2618911663c4c3314a6d5966b77beb8e75faa8eae69de3896c8ffe8f1811c19abba146e95ff029df1ba890302bd5e9c65de56a2d8613764e517d45d9e17f74f3ab28e986bdb15f3133037d33aaafdb34a53068ebb60c59d788af";
    s2 = "6eb60127fb09dbea6b9b9aba31e42c9cfe34ea050f0a674114d1fac8d0bfce90567cc335e50beddf54fc37b9e2f03387882f5cb6cf63c58d599981d76128610f11f85cdea5ddf5dc579148e6768d92e5c35d6047a7b431538f5e9fe47585813850d11f3f8a363cea9c26f0411c4032a28fd1d34e66195217a68d09d733f9a3a5";
    s3 = "4cb6da5cd6d11df313fcab03159605369f53d9dcbd57af71c804acad2814d0689b38e61fa33d13d4cadc30d8eaa4499ebd2490c11e1702ab543e25e44e4d65e90992e3335e1e170f7ecad816c7688340ef505907e64be341655045cca1b6a56e5d1dcbd78f0237a4083c2856e19163011f1429cc698c458be208720b5c0698c5";
    s4 = "a1";
    s5 = "ff";
    int g = 161;
    vector<int> h0, h1, h2;
    h0.push_back(0);
    LibrFunc A(s1, s2, s3);
    h1 = A.Switch(s4);
    h2 = A.Switch(s5);

    double time_GSD = MeasureTime([&]() {
        cout << "GSD: ";
        A.Print(A.GSD(A.a, A.b));
        });
    cout << endl << "Time taken: " << time_GSD << " seconds" << endl;

    double time_Evklid_GSD = MeasureTime([&]() {
        cout << "Evklid_GSD : ";
        A.Print(A.Evklid_GSD(A.a, A.b));
        });
    cout << endl << "Time taken: " << time_Evklid_GSD << " seconds" << endl;

    double time_LCM = MeasureTime([&]() {
        cout << endl << "LCM : ";
        A.Print(A.LCM(A.a, A.b));
        });
    cout << endl << "Time taken: " << time_LCM << " seconds" << endl;

    double time_addmod = MeasureTime([&]() {
        cout << "\n mod+ : ";
        A.Print(A.LongAddRed(A.a, A.b));
        });
    cout << endl << "Time taken: " << time_addmod << " seconds" << endl;
    
    double time_submod = MeasureTime([&]() {
        cout << "mod- : ";
        A.Print(A.LongSubRed(A.a, A.b));
        });
    cout << endl << "Time taken: " << time_submod << " seconds" << endl;
    double time_mulmod = MeasureTime([&]() {
        cout << "mod* : ";
        A.Print(A.LongMulRed(A.a, A.b, A.n));
        });
    cout << endl << "Time taken: " << time_mulmod << " seconds" << endl;
    
    double time_squaremod = MeasureTime([&]() {
        cout << "mod^2 : ";
        A.Print(A.LongSquareRed(A.a, A.n));
        });
    cout << endl << "Time taken: " << time_squaremod << " seconds" << endl;

    double time_powermod = MeasureTime([&]() {
        cout << "\nmod^ : ";
        A.Print(A.LongPowerRed(A.a, A.b, A.n));
        });
    cout << endl << "Time taken: " << time_powermod << " seconds" << endl;

    cout << "\n(a * c + b * c)mod p = ";
    A.Print(A.LongAddRed(A.LongMulRed(A.a, h2, A.n), A.LongMulRed(A.b, h2, A.n)));
    cout << endl;
    cout << "\n(c * (a + b))mod p = ";
    A.Print(A.LongMulRed(h2, A.LongAddRed(A.a, A.b), A.n));
    cout << endl;
    cout << "\n(c * a) mod p = ";
    A.Print(A.LongMulRed(A.a, h1, A.n));
    cout << endl;
    cout << "\n (a + a ... + a) mod p = ";
    for (int i = 0; i < g; i++)
    {
        h0 = A.LongAddRed(h0, A.a);
    }
    A.Print(h0);
    /*
    cout << endl;
    cout << "* : ";
    A.Print(A.LongMul(A.a, A.b));
    cout << endl;
    cout << "mod : ";
    A.Print(A.BarRed(A.a, A.n));
    cout << endl;
    cout << "+ : ";
    A.Print(A.LongAdd(A.a, A.b));
    cout << endl;
    cout << "- : ";
    A.Print(A.LongSub(A.a, A.b));
    cout << "/ : ";
    A.Print(A.Long_quotient(A.a, A.b));
    cout << endl;
    cout << "% : ";
    A.Print(A.Long_remainder(A.a, A.b));
    cout << endl;
    cout << "^2 : ";
    A.Print(A.LongMul(A.a, A.a));
    cout << endl;
    cout << "^ : ";
    A.Print(A.LongPower(A.a, A.b));
    cout << endl; 
  */
    return 0;
}