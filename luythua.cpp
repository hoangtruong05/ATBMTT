#include <iostream>
using namespace std;

long long calcExponent(long long a, long long b, long long n) {
    long long f = 1;

    // Tim bit cao nhat cua b (MSB)
    int k = 0;
    long long temp = b;
    while (temp > 1) {
        temp >>= 1;   // chia 2
        k++;
    }
    // Luc nay k la vtri bit cao nhat trong b

    // Duyet tu bit k xuong bit 0
    for (int i = k; i >= 0; i--) {
        f = (f * f) % n;                 // f = f^2 mod n

        // Lay bit i cua b
        int bi = (b >> i) & 1;

        if (bi == 1) {
            f = (f * a) % n;             // Neu bit = 1 thi nhan them a
        }
    }

    return f;
}

int main() {
    long long a, b, n;
    cout << "Nhap a, b, n: ";
    cin >> a >> b >> n;

    cout << "Ket qua (a^b mod n) = " 
         << calcExponent(a, b, n) << endl;

    return 0;
}
