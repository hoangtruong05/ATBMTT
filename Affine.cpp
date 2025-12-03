#include <iostream>
#include <string>
#include <cctype>
#include <stdexcept>
using namespace std;

// ham tim uscln
int gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a % b);
}

// ham tim nghich dao modular: a^-1 mod n
int modInverse(int a, int m) {
    a %= m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;

    throw invalid_argument("Khong ton tai nghich dao modular!");
}

/* ======================================================
   HÀM MÃ HÓA AFFINE CIPHER
   Cong thuc: E(x) = (a * x + b) mod 26
   Giu nguyen ky tu khong phai chu
====================================================== */

string affineEncrypt(string text, int a, int b) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
    char c = text[i];

        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a'; // Xd chu hoa/thg
            int x = c - base;                  // quy doi ve so 0–25
            char encrypted = (a * x + b) % 26 + base;
            result += encrypted;
        } else {
            result += c;
        }
    }
    return result;
}

/* ======================================================
   HAM GIAI MA AFFINE
   Cong thuc: D(y) = a^¹ * (y - b) mod 26
   Can timm nghich dao modular cua a trc
====================================================== */

string affineDecrypt(string cipher, int a, int b) {
    string result = "";
    int a_inv = modInverse(a, 26); // nghich dao modular cua a
	for(int i = 0; i < cipher.length(); i++){
		char c = cipher[i];
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            int y = c - base;
            char decrypted = (a_inv * (y - b + 26)) % 26 + base;
            result += decrypted;
        } else {
            result += c;
        }
    }
    return result;
}

/* ======================================================
   HAM MAIN
====================================================== */
int main() {
    string text;
    int a, b;

    cout << "Nhap ban goc: ";
    getline(cin, text);

    cout << "Nhap khoa a (a phai nguyen to cung 26): ";
    cin >> a;

    cout << "Nhap khoa b: ";
    cin >> b;

    // Kiem tra a co hop le khong (gcd(a, 26) = 1)
    if (gcd(a, 26) != 1) {
        cout << "Loi: a khong hop le! Phai nguyen to cung 26.\n";
        return 1;
    }

    // Thuc hien ma hoa va giai ma
    string encrypted = affineEncrypt(text, a, b);
    string decrypted = affineDecrypt(encrypted, a, b);

    cout << "\n===== KET QUA =====\n";
    cout << "Ban goc : " << text << endl;
    cout << "Ma hoa  : " << encrypted << endl;
    cout << "Giai ma : " << decrypted << endl;

    return 0;
}

