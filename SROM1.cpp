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
    vector<uint16_t> a;  // Вектор для зберігання числа a
    vector<uint16_t> b;  // Вектор для зберігання числа b
    vector<uint16_t> n;  // Вектор для зберігання числа n

    // Конструктор класу, який приймає три рядки та ініціалізує відповідні вектори a, b, n
    LibrFunc(string s1, string s2, string s3);

    // Метод для перетворення рядка s в вектор цілих чисел
    vector<uint16_t> Switch(string s);
    // Метод для виведення вектора цілих чисел на екран
    void Print(vector<uint16_t> a);

    // Метод для перетворення константи в вектор цілих чисел
    vector<uint16_t> ConstantToBigInt(int constant);

    // Метод для додавання двох багаторозрядних чисел
    vector<uint16_t> LongAdd(vector<uint16_t> a, vector<uint16_t> b);

    // Метод для віднімання двох багаторозрядних чисел
    vector<uint16_t> LongSub(vector<uint16_t> a, vector<uint16_t> b);

    // Метод для порівняння двох багаторозрядних чисел
    int LongCmp(vector<uint16_t> a, vector<uint16_t> b);

    // Метод для множення багаторозрядного числа на одну цифру
    vector<uint16_t> LongMulOneDigit(vector<uint16_t> a, int b);

    // Метод для множення двох багаторозрядних чисел
    vector<uint16_t> LongMul(vector<uint16_t> a, vector<uint16_t> b);

    // Метод для зсуву багаторозрядного числа вліво на певну кількість бітів
    vector<uint16_t> LongShiftDigitsToHigh(vector<uint16_t> a, int b);

    // Метод для піднесення багаторозрядного числа до степеня
    vector<uint16_t> LongPower(vector<uint16_t> a, vector<uint16_t> b);

    // Метод для операції ділення двох багаторозрядних чисел
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
    // Метод конвертує рядок s у числа та виконує перетворення цих чисел у нову систему числення

    char k;
    vector<uint16_t> d2;  // Вектор для зберігання перетворених чисел

    int size = s.length();

    // Якщо довжина рядка не парна, додаємо "0" зліва для коректності
    if (size % 2 != 0)
    {
        s = "0" + s;
        cout << s;
        size++;
    }

    int j = 0;
    uint16_t* d1 = new uint16_t[size];

    // Перетворюємо символи рядка у числа і зберігаємо їх у масиві d1
    for (int i = 0; i < size; i++)
    {
        k = s[i];

        // Перевірка, чи символ є цифрою (0-9) чи літерою (A-F)
        if (isalpha(s[i]) == 0)
        {
            d1[j] = k - '0';  // Перетворюємо цифровий символ у відповідне число
        }
        else
        {
            d1[j] = k - 'a' + 10;  // Перетворюємо літерний символ (A-F) у відповідне число (10-15)
        }
        j++;
    }

    cout << "\nNumber in new system:" << endl;  // Виводимо повідомлення про число у новій системі

    // Конвертуємо пари чисел (в шістнадцятковому форматі) у десятковий формат та додаємо до вектору d2
    for (int i = 0; i < s.length(); i = i + 2)
    {
        d2.insert(d2.begin(), d1[i] * 16 + d1[i + 1] * 1);  // Для чисел у шістнадцятковій системі, використовуємо множення на 16
    }

    // Виводимо числа у новій системі
    for (auto i = d2.begin(); i != d2.end(); i++)
    {
        cout << (int)(*i) << " ";
    }

    return d2;  // Повертаємо вектор перетворених чисел
};

vector<uint16_t> LibrFunc::ConstantToBigInt(int constant) {
    // Метод призначений для створення вектора, який представляє велике ціле число на основі одного константного числа

    vector<uint16_t> result;  // Вектор для зберігання великого цілого числа

    result.push_back(constant);  // Додаємо константне число до вектора

    return result;  // Повертаємо вектор, представляючи велике ціле число
}

vector<uint16_t> LibrFunc::LongAdd(vector<uint16_t> a, vector<uint16_t> b) // Додавання багаторозрядних чисел
{
    // Забезпечуємо, що обидва вектори мають однакову довжину, доповнюючи їх нулями
    if (a.size() > b.size())
    {
        for (int i = b.size(); i < a.size(); i++)
        {
            b.push_back(0);  // Додаємо новий елемент до кінця вектору 'b', поки він не стане такою ж довжиною, як вектор 'a'
        }
    }
    if (b.size() > a.size())
    {
        for (int i = a.size(); i < b.size(); i++)
        {
            a.push_back(0);  // Додаємо новий елемент до кінця вектору 'a', поки він не стане такою ж довжиною, як вектор 'b'
        }
    }

    int carry = 0;  // Ініціалізуємо змінну для зберігання переносу
    vector<uint16_t> c;  // Вектор для зберігання результату додавання
    int temp;

    for (int i = 0; i < a.size(); i++)
    {
        temp = a[i] + b[i] + carry;  // Побітово додаємо числа разом з переносом
        c.push_back(temp & ((int)pow(2, 8) - 1));  // Записуємо менший байт у число
        carry = temp >> 8;  // Отримуємо перенос, що буде доданий на наступному кроці
    }

    if (carry != 0)
    {
        c.push_back(carry); // Додаємо залишковий перенос до результату, якщо він існує
    }

    return c;  // Повертаємо вектор, який містить результат додавання багаторозрядних чисел
};

vector<uint16_t> LibrFunc::LongSub(vector<uint16_t> a, vector<uint16_t> b)  // Віднімання багаторозрядних чисел
{
    vector<uint16_t> c;  // Вектор для зберігання результату віднімання

    // Забезпечуємо, що обидва вектори мають однакову довжину, доповнюючи їх нулями
    if (a.size() > b.size())
    {
        for (int i = b.size(); i < a.size(); i++)
        {
            b.push_back(0);  // Додаємо новий елемент до кінця вектору 'b', щоб зрівняти довжини векторів
        }
    }
    if (b.size() > a.size())
    {
        for (int i = a.size(); i < b.size(); i++)
        {
            a.push_back(0);  // Додаємо новий елемент до кінця вектору 'a', щоб зрівняти довжини векторів
        }
    }

    // Перевіряємо, яке з чисел більше або чи вони рівні, щоб не отримати від'ємного результату
    if (LongCmp(a, b) == 1 || LongCmp(a, b) == 0)
    {
        int borrow = 0;
        int temp;

        // Виконуємо віднімання побітово з урахуванням позик із старших розрядів
        for (int i = 0; i < a.size(); i++)
        {
            temp = a[i] - b[i] - borrow;  // Віднімаємо поточні біти з позичкою
            if (temp >= 0)
            {
                c.push_back(temp);  // Якщо результат віднімання позитивний або нуль, додаємо його до результату 'c'
                borrow = 0;  // Скидаємо позичку
            }
            else
            {
                c.push_back((int)pow(2, 8) + temp);  // Якщо результат віднімання від'ємний, додаємо його з переповненням від 256 (2^8)
                borrow = 1;  // Встановлюємо позичку для наступного розряду
            }
        }
    }
    else
    {
        cout << "The second number is bigger" << endl;  // Виводимо повідомлення, якщо друге число більше
    }

    return c;  // Повертаємо вектор, який містить результат віднімання багаторозрядних чисел
};

int LibrFunc::LongCmp(vector<uint16_t> a, vector<uint16_t> b) // функція порівняння багаторозрядних чисел
{
    if (a.size() > b.size())
    {
        for (int i = b.size(); i < a.size(); i++)
        {
            b.push_back(0);  // Зрівнюємо довжини векторів, доповнюючи менший вектор нулями
        }
    }
    else if (b.size() > a.size())
    {
        for (int i = a.size(); i < b.size(); i++)
        {
            a.push_back(0);  // Зрівнюємо довжини векторів, доповнюючи менший вектор нулями
        }
    }

    int i = a.size() - 1;  // Порівнюємо кожен біт, починаючи з найстаршого

    while (a[i] == b[i]) //поки символи однакові
    {
        i = i - 1; //беремо наступний символ
        if (i == -1) //якщо символи закінчились
        {
            return 0;   // Це означає, що числа ідентичні
        }
    }
    if (a[i] > b[i])//якщо символ з числа а більший за символ з числа b
    {
        return 1; // Перше число більше за друге
    }
    else
    {
        return -1;  // Друге число більше за перше
    }
}

vector<uint16_t> LibrFunc::LongShiftDigitsToHigh(vector<uint16_t> a, int f) //зсув вліво (тобто у бук старших індексів) на f 
{
    for (int i = 0; i < f; i++)
    {
        a.insert(a.begin(), 0);  //дописуємо f нулів до початку вектора
    }
    return a;
};

vector<uint16_t> LibrFunc::LongMulOneDigit(vector<uint16_t> a, int b) // Множення багаторозрядного числа на однорозрядну цифру
{
    vector<uint16_t> c;  // Результат множення
    int carry = 0;  // Перенос
    int temp;

    for (int i = 0; i < a.size(); i++)
    {
        temp = a[i] * b + carry;  // Множимо поточний розряд на цифру b та додаємо попередній перенос
        c.push_back(temp & ((int)pow(2, 8) - 1));  // Записуємо менший байт (розряд) у результат
        carry = temp >> 8;  // Зберігаємо старший байт для наступної ітерації
    }

    c.push_back(carry);  // Додаємо старший байт до результату

    return c;  // Повертаємо результат множення
}

vector<uint16_t> LibrFunc::LongMul(vector<uint16_t> a, vector<uint16_t> b) // Множення багаторозрядних чисел
{
    // Знайдемо максимальну довжину результату
    int maxLen = a.size() + b.size();

    // Додамо необхідну кількість нульових бітів до векторів a та b
    while (a.size() < maxLen)
    {
        a.push_back(0);
    }
    while (b.size() < maxLen)
    {
        b.push_back(0);
    }

    vector<uint16_t> c(maxLen, 0);  // Результат буде мати максимальну можливу довжину
    vector<uint16_t> temp;
    c.push_back(0);

    for (int i = 0; i < a.size(); i++)
    {
        temp = LongMulOneDigit(a, b[i]);  // Множимо число a на однорозрядну цифру b
        temp = LongShiftDigitsToHigh(temp, i);  // Зсуваємо результат на потрібну кількість розрядів
        c = LongAdd(temp, c);  // Додаємо результат до попереднього накопиченого результату
    }

    while ((c.size() >= 1) && (c[c.size() - 1] == 0))
    {
        c.pop_back();  // Видаляємо всі нулі з правого кінця вектора c для оптимізації та позбавлення в результаті зайвих нулів
    }

    return c;  // Повертаємо результат множення
}

vector<uint16_t> LibrFunc::LongPower(vector<uint16_t> a, vector<uint16_t> b)  // Піднесення числа до степеня за схемою Горнера
{
    vector<uint16_t> c;  // Вектор, який буде містити бінарне представлення степеня b
    vector<uint16_t> temp;

    // Перетворюємо степінь b у бінарний вигляд і зберігаємо його у векторі c
    for (int i = 0; i < b.size(); i++)
    {
        int x = b[i];
        for (int j = 0; j < 7; j++)
        {
            c.push_back(x % 2);  // Отримуємо найменший біт останнього числа вектору b і додаємо його до вектора c
            x = x >> 1;  // Зсуваємо число b вправо на один біт (еквівалентно цілочисельному діленню на 2)
        }
    }

    reverse(c.begin(), c.end());  // Перевертаємо вектор, щоб мати бінарне представлення в правильному порядку
    
    vector<uint16_t> d;  // Вектор для накопичення результату
    d.push_back(1);  // Ініціалізуємо його значенням 1, як початкове значення

    for (int j = 0; j < c.size(); j++)
    {
        if (c[j] == 1)
        {
            d = LongMul(d, a);  // Якщо біт степеня рівний 1, множимо поточний результат на a
        }

        a = LongMul(a, a);  // Піднесення a до квадрату на кожному кроці
    }

    return d;  // Повертаємо результат піднесення до степеня
}

pair<vector<uint16_t>, vector<uint16_t>> LibrFunc::LongDiv(vector<uint16_t> a, vector<uint16_t> b)
{
    // Видаляємо всі нулі з кінця вектора 'a' для оптимізації операцій ділення
    while (a[a.size() - 1] == 0)
    {
        a.pop_back();
    }

    // Видаляємо всі нулі з кінця вектора 'b' для оптимізації операцій ділення
    while (b[b.size() - 1] == 0)
    {
        b.pop_back();
    }

    // Обробка помилки ділення на нуль.
    if (b.empty()) {
        throw runtime_error("Division by zero is not allowed.");
    }

    int k = b.size(); // Довжина дільника 'b'
    int t;
    vector<uint16_t> c; // Вектор, який використовується для обчислення дільника на кожному кроці
    vector<uint16_t> r = a; // Вектор, який використовується для зберігання решти під час ділення
    vector<uint16_t> q; // Вектор, представляє результат ділення (частку)
    q.push_back(0); // Ініціалізуємо частку нулем

    while (LongCmp(r, b) != -1) // Поки решта 'r' більше або дорівнює дільнику 'b'
    {
        t = r.size(); // Поточна довжина решти 'r'
        c = LongShiftDigitsToHigh(b, t - k); // Відновлюємо дільник 'b' на поточному кроці

        if (LongCmp(r, c) == -1) // Порівнюємо решту та дільник
        {
            t = t - 1;
            c = LongShiftDigitsToHigh(b, t - k); // Зменшуємо довжину дільника на одиницю, якщо потрібно
        }

        if (LongCmp(r, c) >= 0) // Якщо решта більше або дорівнює дільнику
        {
            r = LongSub(r, c); // Віднімаємо дільник від решти
            q = LongAdd(q, LongShiftDigitsToHigh({ 1 }, t - k)); // Додаємо одиницю до частки
        }
        else
            break;

        // Видаляємо всі нулі з правого кінця решти 'r' для оптимізації та позбавлення в результаті зайвих нулів
        while ((r.size() >= 1) && (r[r.size() - 1] == 0))
        {
            r.pop_back();
        }

        if (r.empty())
        {
            r.push_back(0);
        }
    }

    return make_pair(q, r); // Повертаємо пару, де перший елемент - частка, другий - остача
}

void LibrFunc::Print(vector<uint16_t> a)  // Метод для виводу багаторозрядного числа у шістнадцятковому форматі
{
    char* c = new char[2 * a.size()];
    // Створюємо масив символів для зберігання шістнадцяткового представлення числа
    int p1;
    int p2;
    for (int i = 0, j = a.size() - 1; i < 2 * a.size() - 1; i = i + 2, j--)

    {
        p1 = a[j] / 16;  // Окремо виділяємо старший і молодший байти числа
        p2 = a[j] % 16;
        if (p1 <= 9)
        {
            c[i] = p1 + '0';  // Якщо це цифра (0-9), конвертуємо в символ від '0' до '9'
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
            c[i + 1] = p2 + '0';  // Аналогічно для молодшого байту
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
        cout << c[i];  // Виводимо символи шістнадцяткового представлення числа
    }
    cout << endl;
}

// Функція для вимірювання часу виконання операції
double MeasureTime(function<void()> operation) {
    // Запам'ятовуємо час початку виконання операції
    auto start_time = chrono::high_resolution_clock::now();
    
    // Виконуємо передану операцію
    operation();
    
    // Запам'ятовуємо час завершення виконання операції
    auto end_time = chrono::high_resolution_clock::now();

    // Обчислюємо тривалість виконання операції
    chrono::duration<double> elapsed_time = end_time - start_time;

    // Повертаємо час виконання операції у секундах
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
    //ПЕРЕВІРКА

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
