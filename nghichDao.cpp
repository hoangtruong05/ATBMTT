#include<iostream>
using namespace std;

int extendedEuclid(int a, int b, int&x, int &y){
	if(b==0){
		x = 1;
		y = 0;
		return a;
	}
	
	int x1, y1;
	int d = extendedEuclid(b, a%b, x1, y1);
	
	x = y1;
	y = x1 - (a/b)*y1;
	
	return d;
}

int nghichDao(int a, int n){
	int x, y;
	int d = extendedEuclid(a, n, x, y);
	if(d!=1) return -1;
	else{
		x = (x%n +n)%n;
		return x;
	}
}
int main(){
	int a, n;
		cout<<"Nhap vao so a:"<<endl;
		cin>>a;
		cout<<"Nhap vao so n:"<<endl;
		cin>>n;
	int d = nghichDao(a,n);
	if(d == -1){
		cout<<"Khong ton tai nghich dao cua a mod n"<<endl;
	}
	else
		cout<<"Nghich dao cua a mod n la: "<<d;
	
	
}
