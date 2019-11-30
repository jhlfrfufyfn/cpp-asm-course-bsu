#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
class RNum;
///===============================================================================================================
class RNumProxyNum {
public:
	RNumProxyNum(RNum &r) :_r(r) {}
	inline RNum& operator=(int a);
	inline operator int();
private:
	RNum& _r;
};
///===============================================================================================================
class RNumProxyDenum {
public:
	RNumProxyDenum(RNum &r) :_r(r) {}
	inline RNum& operator=(const int a);
	inline operator int();
private:
	RNum& _r;
};
///===============================================================================================================
class RNum {
private:
	friend class RNumProxyNum;
	friend class RNumProxyDenum;
	int _num;
	int _denum;
	int __gcd(int a, int b) {
		while (b) {
			a %= b;
			swap(a, b);
		}
		return a;
	}
	void Reduce() {
		int gcd = __gcd(abs(_num), abs(_denum));
		this->_num /= gcd;
		this->_denum /= gcd;
	}
	void const Normalize() {
		if (this->_num < 0 && this->_denum < 0) {
			this->_denum = -this->_denum;
			this->_num = -this->_num;
		}
		else if (this->_num > 0 && this->_denum < 0) {
			this->_denum = -this->_denum;
			this->_num = -this->_num;
		}
		Reduce();
	}
public:
	explicit RNum(int f1 = 0, int f2 = 1) :_num(f1), _denum(f2) {
		if (_denum == 0) {
			throw invalid_argument("Denominator equals zero!");
		}
		this->Normalize();
	}

	RNumProxyNum Numerator() { return *this; }
	const int Numerator() const { return _num; }
	RNumProxyDenum Denumenator() { return *this; }
	const int& Denumenator() const { return _denum; }

	explicit operator double()const { return (double)_num / _denum; }

	inline const RNum operator+(RNum const& r2)const {
		RNum t = RNum(this->_num * r2._denum + this->_denum * r2._num, this->_denum * r2._denum);
		t.Normalize();
		return t;
	}

	inline const RNum operator-(RNum const& r2)const {
		RNum t = RNum(this->_num * r2._denum - this->_denum * r2._num, this->_denum * r2._denum);
		t.Normalize();
		return t;
	}

	inline const RNum operator*(RNum const& r2)const {
		RNum t = RNum(this->_num * r2._num, this->_denum * r2._denum);
		t.Normalize();
		return t;
	}

	inline const RNum operator/(RNum const& r2)const {
		RNum t = RNum(this->_num * r2._denum, this->_denum * r2._num);
		t.Normalize();
		return t;
	}

	inline const RNum operator+(int r2)const {
		RNum t = *this + RNum(r2);
		t.Normalize();
		return t;
	}

	inline const RNum operator-(int r2)const {
		RNum t = *this - RNum(r2);
		t.Normalize();
		return t;
	}

	inline const RNum operator*(int r2)const {
		RNum t = *this * RNum(r2);
		t.Normalize();
		return t;
	}

	inline const RNum operator/(int r2)const {
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
		long long comDenom = this->_denum*r2._denum;
		long long thisNom = this->_num*r2._denum;
		long long r2Nom = r2._num*this->_denum;
		if (thisNom < r2Nom)
			return 1;
		else
			return 0;
	}

	bool const operator==(RNum const& r2)const {
		if (this->_num == r2._num&&this->_denum == r2._denum)
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
		out << x._num;
		if (x._denum != 1)
			out << "/" << x._denum;
		return out;
	}

	friend istream& operator >> (istream &in, RNum& r) {
		int a;
		in >> a;
		r.Numerator() = a;
		in.ignore(1);
		in >> a;
		r.Denumenator() = a;
		return in;
	}


	friend inline RNum const  operator + (int a, RNum const& r2);

	friend inline RNum const  operator * (int a, RNum const& r2);

	friend inline RNum const  operator - (int a, RNum const& r2);

	friend inline RNum const  operator / (int a, RNum const& r2);
};

inline const RNum  operator + (int a, RNum const& r2)
{
	return RNum(a) + r2;
}

inline const RNum  operator * (int a, const RNum& r2)
{
	return RNum(a)*r2;
}

inline const RNum operator - (int a, RNum const& r2)
{
	return RNum(a) - r2;
}

inline const RNum operator / (int a, RNum const& r2)
{
	return RNum(a) / r2;
}

///===============================================================================================================

inline RNum & RNumProxyDenum::operator=(int a) {
	if (a == 0)
		throw invalid_argument("Denominator equals zero!");
	_r._denum = a;
	_r.Normalize();
	return _r;
}

inline RNum & RNumProxyNum::operator=(int a)
{
	_r._num = a;
	_r.Normalize();
	return _r;
}

inline RNumProxyNum::operator int() {
	return _r._num;
}

inline RNumProxyDenum::operator int() {
	return _r._denum;
}


///===============================================================================================================

///===============================================================================================================
int main() {
	RNum A, B;
	cin >> A >> B;
	cout << "A+B= " << A + B << "\n";
	cout << "A*B= " << A*B << "\n";
	cout << "A/B= " << A / B << "\n";
	cout << "A<B= " << (A < B) << "\n";
	cout << "A=B= " << (A == B) << "\n";
	cout << "A>B= " << (A > B) << "\n";
	A = B;
	cout << "A= " << A << "\n";
	cout << "B= " << B << "\n";
	cout << "A + 5 = " << 5 + A << "\n";
	cout << "A * 5 = " << 5 * A << "\n";
	cout << "A - 5 = " << 5 - A << "\n";
	cout << "A / 5 = " << 5 / A << "\n";
	cout << double(A) << "\n";
	A.Denumenator()=0;
	cout<< A << " " << double(A) <<"\n";
	system("pause");
	return 0;
}
