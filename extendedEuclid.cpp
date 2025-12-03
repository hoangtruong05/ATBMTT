#include<iostream>
using namespace std;

//int extendedEuclid(int a, int b,int &d, int &x, int &y){
//	if(b == 0){
//		d = a;
//		x = 1;
//		y = 0;
//		return d;
//	}
//	
//	int x2 = 1, x1 = 0;
//	int y2 = 0, y1 = 1;
//	
//	int q, r;
//	while(b>0){
//		q = a/b;
//		r = a%b;
//		x = x2 - q*x1;
//		y = y2 - q*y1;
//		
//		a = b;
//		b = r;
//		x2 = x1;
//		x1 = x;
//		y2 = y1; 
//		y1 = y;
//	}
//	
//	d = a;
//	x = x2;
//	y = y2;
//	
//	return d;
//}

int extendedEuclid(int a, int b, int &x, int &y){
	if(b==0){
		x =1; 
		y =0;
		return a;
	}
	int x1, y1;
	int d = extendedEuclid(b, a%b, x1, y1);
	
	x = y1;
	y = x1 - (a/b)*y1;
	return d;
}
int main(){
	int a,b,x,y,d;
	cout<<"Nhap vao hai so nguyen a, b: "<<endl;
	cin>>a>>b;
	int gcd = extendedEuclid(a,b,x,y);
	cout<<"USCLN la: "<<gcd;
//	int gcd = extendedEuclid(a,b,d,x,y);
//	cout<<"USCLN la :"<<gcd<<endl;
//	cout<<"He so x la: "<<x<<endl;
//	cout<<"He so y la: "<<y<<endl;
//	cout<<"PT: "<<a<<" * "<<x<<" + "<<b<<" * "<<y<<" = "<<d; 
	
}
