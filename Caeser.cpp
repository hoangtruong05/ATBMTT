#include <bits/stdc++.h>
using namespace std;
// Ham ma hoa
string maHoa(string text, int k){
	string result = "";
	for(int i =0; i<text.length(); i++){
		char x = text[i];
		if(isupper(x)){
			result += char((int(x + k -65)%26 +65));
		}
		else if(islower(x)){
			result += char((int(x +k -97)%26 + 97));
		}
		else
			result += x;
	}
	return result;
}
//Giai ma
string giaiMa(string text, int k){
	string result = "";
	for(int i =0; i<text.length(); i++){
		char x = text[i];
		if(isupper(x)){
			result += char((int(x - k - 65 + 26)%26 +65));
		}
		else if(islower(x)){
			result += char((int(x - k - 97 +26 )%26 + 97));
		}
		else
			result += x;
	}
	return result;
}

int main() {
    string m;
    int k;
    int choice;

    do {
        cout << "\n================ MENU ================\n";
        cout << "1. Ma hoa van ban\n";
        cout << "2. Giai ma van ban\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "======================================\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore(); // xóa newline trong buffer

        if (choice == 1) {
            cout << "\nNhap vao ban ro: ";
            getline(cin, m);
            cout << "Nhap vao khoa k (so nguyen): ";
            cin >> k;
            cin.ignore();

            cout << "\nBan ma hoa: " << maHoa(m, k) << endl;
        }
        else if (choice == 2) {
            cout << "\nNhap vao ban ma hoa: ";
            getline(cin, m);
            cout << "Nhap vao khoa k (so nguyen): ";
            cin >> k;
            cin.ignore();

            cout << "\nBan giai ma: " << giaiMa(m, k) << endl;
        }
        else if (choice == 0) {
            cout << "\nThoat chuong trinh...\n";
        }
        else {
            cout << "\nLua chon khong hop le. Vui long chon lai!\n";
        }

    } while (choice != 0);

    return 0;
}
