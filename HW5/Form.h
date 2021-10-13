#ifndef __FORM_H__
#define __FORM_H__
using namespace std;
#include <sstream>

class Bound_form; // Form plus value

class Form{
	friend ostream& operator<<(ostream&, const Bound_form&);

	int prc;		//precision
	int fmt;		//general, scientific, fixed

	public:
		Form(int p = 6):prc(p), fmt(0){}	//預定precision = 6
		Bound_form operator()(double d);   // make a Bound_form for *this and d
		Form& scientific(){
			fmt = ios_base::scientific;
			return *this;
		}
		Form& fixed(){
			fmt = ios_base::fixed;
			return *this;
		}
		Form& precision(int p){
			prc = p;
			return *this;
		}

};



struct Bound_form{
	const Form& f;
	double val;
	Bound_form(const Form& ff, double v):f(ff),val(v){}
};

ostream& operator<<(ostream& os, const Bound_form& bf){
	ostringstream s;
	s.precision(bf.f.prc);
	s.setf(bf.f.fmt, ios_base::floatfield);
	s << bf.val;
	return os << s.str();
}

Bound_form Form::operator()(double d) {
	return Bound_form(*this, d); 
}

#endif



