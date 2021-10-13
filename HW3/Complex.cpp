#include "Complex.h"
#include <cmath>


Complex::Complex(const double re, const double im)
{
	real=re;
	imag=im;
}

Complex::Complex(const Complex& c)
{
	real=c.real;
	imag=c.imag;
}

Complex& Complex::operator=(const Complex& c)
{
	real=c.real;
	imag=c.imag;
	return *this;
}

Complex Complex::Polar(const double leng, const double arg)
{
	real=leng*cos(arg);
	imag=leng*sin(arg);
	return Complex(real,imag);
}

	
double Complex::Real()
{
	return real;
}

double Complex::Imag()
{
	return imag;
}

double Complex::Norm()
{
	return imag*imag+real*real;
}
	
double Complex::Abs()
{
	return std::sqrt(Norm());
}

double Complex::Arg()
{
	return std :: atan2( imag , real);
}

	
Complex Complex::operator++()
{
	real++;
	imag++;
	return *this;
}

Complex Complex::operator++(int i)
{
	Complex temp(*this);
	real++;
	imag++;
	return temp;
}

Complex Complex::operator--()
{
	real-=1;
	return *this;
}

Complex Complex::operator--(int i)
{
	real-=i;
	return *this;
}


Complex::~Complex()
{
}

Complex Polar(const double leng, const double arg){
	double real=leng*cos(arg);
	double imag=leng*sin(arg);
	return Complex(real,imag);
}
double Norm(const Complex& x){
	return x.imag*x.imag+x.real*x.real;
}
double Abs(const Complex& x){
	return std::sqrt(Norm(x));
}
double Arg(const Complex& x){
	return std :: atan2( x.imag , x.real);
}
Complex operator+(const Complex& x, const Complex& y){
	return Complex(x.real+y.real, x.imag+y.imag);
}
Complex operator-(const Complex& x, const Complex& y){
	return Complex(x.real-y.real, x.imag-y.imag);
}
Complex operator*(const Complex& x, const Complex& y){
	Complex mul;
	mul.real = (x.real * y.real) - (x.imag *y.imag);
	mul.imag = (x.real * y.imag) +(x.imag *y.real);
	return mul;
}
Complex operator/(const Complex& x, const Complex& y){
	Complex div;
	div.real = ((x.real*y.real) + (x.imag*y.imag)) / (y.real*y.real + y.imag*y.imag);
	div.imag = ((x.imag*y.real) - (x.real*y.imag)) / (y.real*y.real + y.imag*y.imag);
	return div;
}
Complex operator+=(Complex& x, const Complex& y){
	x.real+=y.real;
	x.imag+=y.imag;
	return x;
}
Complex operator-=(Complex& x, const Complex& y){
	x.real-=y.real;
	x.imag-=y.imag;
	return x;
}
//~~~~~~~~~~~
Complex operator*=(Complex& x, const Complex& y){
	x=x*y;
	return x;
}
Complex operator/=(Complex& x, const Complex& y){
	x=x/y;
	return x;
}
//~~~~~~~~~~~
bool operator==(const Complex& x, const Complex& y){
	if (x.real==y.real && x.imag==y.imag)
		return true;
	else
		return false;
}
bool operator!=(const Complex& x, const Complex& y){
	if (x.real==y.real && x.imag==y.imag)
		return false;
	else
		return true;
}
ostream& operator<<(ostream& o, const Complex& x){
	o << "(" << x.real << ", " << x.imag << ")";
	return o;
}

