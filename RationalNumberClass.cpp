#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
class RNum {
private:
	long long fNom;
	long long fDenom;
	long long __gcd(long long a, long long b) {
		while (a) {
			a%=b;
			swap(a,b);
		}
		return b;
	}
	void Reduce() {
		long long gcd = __gcd(abs(fNom),abs(fDenom));
		this->fNom/=gcd;
		this->fDenom/=gcd;
	}
	void Normalize() {
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
	explicit RNum(long long f1=0, long long f2=1) :fNom(f1), fDenom(f2) {}
	RNum const operator+(RNum const& r2)const {
		RNum t = RNum( this->fNom * r2.fDenom + this->fDenom * r2.fNom, this->fDenom * r2.fDenom );
		t.Normalize();
		return t;
	}
	RNum const operator-(RNum const& r2)const { 
		RNum t = RNum( this->fNom * r2.fDenom - this->fDenom * r2.fNom, this->fDenom * r2.fDenom );	
		t.Normalize();
		return t;
	}
	RNum const operator*(RNum const& r2)const {
		RNum t = RNum( this->fNom * r2.fNom, this->fDenom * r2.fDenom );
		t.Normalize();
		return t;
	}
	RNum const operator/(RNum const& r2)const {
		RNum t = RNum( this->fNom * r2.fDenom, this->fDenom * r2.fNom );
		t.Normalize();
		return t;
	}
	RNum& operator+=(RNum const& r2) {
	}
};
