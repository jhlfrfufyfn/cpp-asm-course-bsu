#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
class RNum {
private:
	long long fNom;
	long long fDenom;
	long long __gcd(long long a, long long b) {
		while (b) {
			a %= b;
			swap(a, b);
		}
		return a;
	}
	void Reduce() {
		long long gcd = __gcd(abs(fNom), abs(fDenom));
		this->fNom /= gcd;
		this->fDenom /= gcd;
	}
	void const Normalize() {
		if (this->fNom < 0 && this->fDenom < 0) {
			this->fDenom = -this->fDenom;
			this->fNom = -this->fNom;
		}
		else if (this->fNom > 0 && this->fDenom < 0) {
			this->fDenom = -this->fDenom;
			this->fNom = -this->fNom;
		}
		Reduce();
	}
public:
	explicit RNum(long long f1 = 0, long long f2 = 1) :fNom(f1), fDenom(f2) {this->Normalize();}
	RNum operator+(RNum const& r2)const {
		RNum t = RNum(this->fNom * r2.fDenom + this->fDenom * r2.fNom, this->fDenom * r2.fDenom);
		t.Normalize();
		return t;
	}
	RNum operator-(RNum const& r2)const {
		RNum t = RNum(this->fNom * r2.fDenom - this->fDenom * r2.fNom, this->fDenom * r2.fDenom);
		t.Normalize();
		return t;
	}
	RNum operator*(RNum const& r2)const {
		RNum t = RNum(this->fNom * r2.fNom, this->fDenom * r2.fDenom);
		t.Normalize();
		return t;
	}
	RNum operator/(RNum const& r2)const {
		RNum t = RNum(this->fNom * r2.fDenom, this->fDenom * r2.fNom);
		t.Normalize();
		return t;
	}
	RNum& operator+=(RNum const& r2) {
		*this=*this+r2;
		return *this;
	}
	RNum& operator-=(RNum const& r2) {
		*this = *this - r2;
		return *this;
	}
	RNum& operator*=(RNum const& r2) {
		*this = *this * r2;
		return *this;
	}
	RNum& operator/=(RNum const& r2) {
		*this = *this / r2;
		return *this;
	}
	bool const operator<(RNum const& r2)const {
		long long comDenom=this->fDenom*r2.fDenom;
		long long thisNom=this->fNom*r2.fDenom;
		long long r2Nom=r2.fNom*this->fDenom;
		if(thisNom<r2Nom)
			return 1;
		else
			return 0;
	}
	bool const operator==(RNum const& r2)const {
		if(this->fNom==r2.fNom&&this->fDenom==r2.fDenom)
			return 1;
		else
			return 0;
	}
	bool const operator>(RNum const& r2)const {
		if((!(*this<r2))&&(!(*this==r2)))
			return 1;
		else
			return 0;
	}
	friend ostream& operator<<(ostream &out, const RNum& x) {
		out << x.fNom << "/" << x.fDenom;
		return out;
	}
};
int main() {
	RNum A(1,3),B(15,3);
	cout<<"A+B= "<<A+B<<"\n";
	cout<<"A*B= "<<A*B<<"\n";
	cout<<"A/B= "<<A/B<<"\n";
	cout<<"A<B= "<<(A<B)<<"\n";
	cout<<"A=B= "<<(A==B)<<"\n";
	cout<<"A>B= "<<(A>B)<<"\n";
	system("pause");
	return 0;
}
