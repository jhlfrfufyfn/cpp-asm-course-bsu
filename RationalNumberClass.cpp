#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
class RNum {
private:
	int fNom;
	int fDenom;
	int __gcd(int a, int b) {
		while (b) {
			a %= b;
			swap(a, b);
		}
		return a;
	}
	void Reduce() {
		int gcd = __gcd(abs(fNom), abs(fDenom));
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

	explicit RNum(int f1 = 0, int f2 = 1) :fNom(f1), fDenom(f2) { 
		if (fDenom == 0) {
			throw invalid_argument("Denominator equals zero!");
		}
		this->Normalize(); 
	}

	int& Numerator() { return fNom; }
	const int& Numerator()const{ return fNom; }
	int& Denominator(){ return fDenom; }
	const int& Denominator() const{ return fDenom; }
	
	explicit operator double()const{ return (double)fNom/fDenom; }

	inline const RNum operator+(RNum const& r2)const {
		RNum t = RNum(this->fNom * r2.fDenom + this->fDenom * r2.fNom, this->fDenom * r2.fDenom);
		t.Normalize();
		return t;
	}

	inline const RNum operator-(RNum const& r2)const {
		RNum t = RNum(this->fNom * r2.fDenom - this->fDenom * r2.fNom, this->fDenom * r2.fDenom);
		t.Normalize();
		return t;
	}

	inline const RNum operator*(RNum const& r2)const {
		RNum t = RNum(this->fNom * r2.fNom, this->fDenom * r2.fDenom);
		t.Normalize();
		return t;
	}

	inline const RNum operator/(RNum const& r2)const {
		RNum t = RNum(this->fNom * r2.fDenom, this->fDenom * r2.fNom);
		t.Normalize();
		return t;
	}

	inline const RNum operator+(int r2)const {
		RNum t=*this+RNum(r2);
		t.Normalize();
		return t;
	}

	inline const RNum operator-(int r2)const {
		RNum t = *this-RNum(r2);
		t.Normalize();
		return t;
	}

	inline const RNum operator*(RNum const& r2)const {
		RNum t = *this * RNum(r2);
		t.Normalize();
		return t;
	}

	inline const RNum operator/(RNum const& r2)const {
		RNum t = *this / RNum(r2);
		t.Normalize();
		return t;
	}

	inline RNum& operator=(RNum const& r2) {
		return *this;
	}

	inline RNum& operator+=(RNum const& r2) {
		*this = *this + r2;
		return *this;
	}

	inline RNum& operator-=(RNum const& r2) {
		*this = *this - r2;
		return *this;
	}

	inline RNum& operator*=(RNum const& r2) {
		*this = *this * r2;
		return *this;
	}

	inline RNum& operator/=(RNum const& r2) {
		*this = *this / r2;
		return *this;
	}

	inline RNum& operator+=(int r2) {
		*this = *this + RNum(r2);
		return *this;
	}

	inline RNum& operator-=(int r2) {
		*this = *this - RNum(r2);
		return *this;
	}

	inline RNum& operator*=(int r2) {
		*this = *this * RNum(r2);
		return *this;
	}

	inline RNum& operator/=(int r2) {
		*this = *this / RNum(r2);
		return *this;
	}

	bool const operator<(RNum const& r2)const {
		long long comDenom = this->fDenom*r2.fDenom;
		long long thisNom = this->fNom*r2.fDenom;
		long long r2Nom = r2.fNom*this->fDenom;
		if (thisNom < r2Nom)
			return 1;
		else
			return 0;
	}

	bool const operator==(RNum const& r2)const {
		if (this->fNom == r2.fNom&&this->fDenom == r2.fDenom)
			return 1;
		else
			return 0;
	}

	bool const operator>(RNum const& r2)const {
		if ((!(*this < r2)) && (!(*this == r2)))
			return 1;
		else
			return 0;
	}

	friend ostream& operator<<(ostream &out, const RNum& x) {
		out << x.fNom;
		if(x.fDenom!=1)
			out << "/" << x.fDenom;
		return out;
	}

	friend istream& operator >> (istream &in, RNum& r) {
		int a;
		in>>a;
		r.Numerator()=a;
		in.ignore(1);
		in>>a;
		r.Denominator()=a;
		return in;
	}


};

inline KRat const  operator + (int a, KRat const& r2)
{
	return KRat(a * r2.fDenom + r2.fNum, r2.fDenom);
}

inline KRat  operator * (int a, const KRat& r2)
{
	return KRat(a*r2.fNum, r2.fDenom);
}

inline KRat const  operator - (int a, KRat const& r2)
{
	return KRat(a * r2.fDenom + r2.fNum, r2.fDenom);
}

inline KRat const  operator / (int a, KRat const& r2)
{
	return KRat(a * r2.fDenom + r2.fNum, r2.fDenom);
}


int main() {
	RNum A, B;
	cin>>A>>B;
	cout << "A+B= " << A + B << "\n";
	cout << "A*B= " << A*B << "\n";
	cout << "A/B= " << A / B << "\n";
	cout << "A<B= " << (A < B) << "\n";
	cout << "A=B= " << (A == B) << "\n";
	cout << "A>B= " << (A > B) << "\n";
	A = B;
	cout << "A= " << A << "\n";
	cout << "B= " << B << "\n";
	system("pause");
	return 0;
}
