#include <iostream>
#include <string>
#include <cctype>

using namespace std;

/* ============================================================
   HÀM NHÂN MA TR?N 2×2 V?I VECTOR 2×1
   Dùng cho mã hóa và gi?i mã
=========================================================== */
void multiplyMatrix(int M[2][2], int x, int y, int &out1, int &out2) {
    out1 = (M[0][0] * x + M[0][1] * y) % 26;
    out2 = (M[1][0] * x + M[1][1] * y) % 26;
}

/* ============================================================
   TÍNH Ð?NH TH?C MA TR?N 2×2
   det = ad – bc
=========================================================== */
int determinant(int M[2][2]) {
    return (M[0][0] * M[1][1] - M[0][1] * M[1][0] + 26) % 26;
}

/* ============================================================
   TÌM NGH?CH Ð?O MOD 26
=========================================================== */
int modInverse(int a) {
    a %= 26;
    for (int i = 1; i < 26; i++)
        if ((a * i) % 26 == 1)
            return i;
    return -1; // không có ngh?ch d?o
}

/* ============================================================
   TÍNH MA TR?N NGH?CH Ð?O C?A KEY Ð? GI?I MÃ
=========================================================== */
bool inverseMatrix(int M[2][2], int inv[2][2]) {
    int det = determinant(M);
    int detInv = modInverse(det);

    if (detInv == -1)
        return false;

    // Tính adjoint (ma tr?n ph? h?p)
    inv[0][0] =  M[1][1];
    inv[0][1] = -M[0][1];
    inv[1][0] = -M[1][0];
    inv[1][1] =  M[0][0];

    // Nhân v?i ngh?ch d?o d?nh th?c
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            inv[i][j] = (inv[i][j] * detInv) % 26;
            if (inv[i][j] < 0) inv[i][j] += 26;
        }
    }

    return true;
}

/* ============================================================
   MÃ HÓA HILL CIPHER
=========================================================== */
string hillEncrypt(string text, int key[2][2]) {
    string clean = "";

    // L?c ký t?: ch? gi? ch? cái
    for (char c : text)
        if (isalpha(c)) clean += tolower(c);

    // N?u chu?i l? thì thêm 'x'
    if (clean.length() % 2 == 1)
        clean += 'x';

    string cipher = "";

    for (int i = 0; i < clean.length(); i += 2) {
        int x = clean[i]   - 'a';
        int y = clean[i+1] - 'a';

        int out1, out2;
        multiplyMatrix(key, x, y, out1, out2);

        cipher += char(out1 + 'a');
        cipher += char(out2 + 'a');
    }

    return cipher;
}

/* ============================================================
   GI?I MÃ HILL CIPHER
=========================================================== */
string hillDecrypt(string cipher, int key[2][2]) {
    int inv[2][2];

    if (!inverseMatrix(key, inv)) {
        throw runtime_error("Ma tran khoa KHONG kha nghich! Khong the giai ma.");
    }

    string plain = "";

    for (int i = 0; i < cipher.length(); i += 2) {
        int x = cipher[i]   - 'a';
        int y = cipher[i+1] - 'a';

        int out1, out2;
        multiplyMatrix(inv, x, y, out1, out2);

        plain += char(out1 + 'a');
        plain += char(out2 + 'a');
    }

    return plain;
}

/* ============================================================
   HÀM MAIN
=========================================================== */
int main() {
    string text;
    int key[2][2];

    cout << "Nhap ban goc: ";
    getline(cin, text);

    cout << "Nhap ma tran khoa 2x2 (so nguyen):\n";
    cin >> key[0][0] >> key[0][1];
    cin >> key[1][0] >> key[1][1];

    try {
        string encrypted = hillEncrypt(text, key);
        string decrypted = hillDecrypt(encrypted, key);

        cout << "\n===== KET QUA =====\n";
        cout << "Ban goc : " << text << endl;
        cout << "Ma hoa  : " << encrypted << endl;
        cout << "Giai ma : " << decrypted << endl;

    } catch (exception &e) {
        cout << "Loi: " << e.what() << endl;
    }

    return 0;
}

