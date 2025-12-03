#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime>
using namespace std;

// Ham tinh a^b mod p bang phuong phap binh phuong nhanh
long long powerMod(long long a, long long b, long long p){
    long long result = 1;  
    a = a % p; // dam bao a luon nho hon p
    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % p;
        }
        b = b / 2;
        a = (a * a) % p;
    }
    return result;
}

// Ham kiem tra so nguyen to bang thuat toan Miller-Rabin
bool millerRabin(long long p, int k){
    if (p <= 1) 
        return false;
    if (p == 2) 
        return true;
    
    long long q = p - 1;
    int s = 0;
    
    while (q % 2 == 0) {
        q = q / 2;
        s++;
    }
    
    for (int i = 0; i < k; i++) {
        long long a = 2 + rand() % (p - 2); // chon a ngau nhien
        cout << "Lan kiem tra " << i+1 << ": a = " << a << endl; // hien thi a
        
        long long x = powerMod(a, q, p);
        
        if (x == 1 || x == p - 1)
            continue;
        
        bool isPrime = false;
        for (int j = 0; j < s - 1; j++) {
            x = (x * x) % p;
            if (x == p - 1) {
                isPrime = true;
                break;
            }
        }
        
        if (!isPrime)
            return false;
    }
    
    return true;
}

int main(){
    srand(time(0)); // khoi tao random seed
    
    long long p;
    int k = 5; // so lan kiem tra
    
    cout << "Nhap so p can kiem tra: ";
    cin >> p;
    
    if (millerRabin(p, k)) {
        cout << p << " la so nguyen to" << endl;
    } else {
        cout << p << " khong la so nguyen to" << endl;
    }
    
    return 0;
}

