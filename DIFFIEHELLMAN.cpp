#include <iostream>
#include <cmath>

// Ham tinh (base^exp) % mod su dung phuong phap luy thua nhi phan
long long modExponentiation(long long base, long long exp, long long mod) {
    long long result = 1;  
    base = base % mod; // dam bao base nam trong pham vi mod
    while (exp > 0) {
        if (exp % 2 == 1) { // neu exp la le, nhan ket qua voi base
            result = (result * base) % mod;
        }
        exp = exp >> 1;  // dich phai mot bit (chia 2)
        base = (base * base) % mod; // cap nhat base = base^2 % mod
    }
    return result; // tra ve ket qua cuoi cung
}

int main() {
    // Khoi tao cac gia tri
    long long q = 353;  // so nguyen to cong khai
    long long a = 3;    // can nguyen thuy
    long long XA = 97;  // khoa bi mat cua nguoi dung A
    long long XB = 233; // khoa bi mat cua nguoi dung B

    // Tinh Y_A = a^XA % q (khoa cong khai cua nguoi dung A)
    long long YA = modExponentiation(a, XA, q);
    std::cout << "Khoa cong khai cua nguoi dung A Y_A = " << YA << std::endl;

    // Tinh Y_B = a^XB % q (khoa cong khai cua nguoi dung B)
    long long YB = modExponentiation(a, XB, q);
    std::cout << "Khoa cong khai cua nguoi dung B Y_B = " << YB << std::endl;

    // Tinh khoa bi mat chung
    long long K_A = modExponentiation(YB, XA, q); // A tinh
    std::cout << "Khoa bi mat chung cua nguoi dung A K_A = " << K_A << std::endl;

    long long K_B = modExponentiation(YA, XB, q); // B tinh
    std::cout << "Khoa bi mat chung cua nguoi dung B K_B = " << K_B << std::endl;

    // Kiem tra khoa bi mat chung co khop khong
    if (K_A == K_B) {
        std::cout << "Khoa bi mat chung da duoc thiet lap thanh cong: " << K_A << std::endl;
    } else {
        std::cout << "Loi: Khoa khong khop!" << std::endl;
    }

    return 0;
}

