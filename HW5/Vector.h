#ifndef __VECTOR_H__
#define __VECTOR_H__
#include <iostream>
#include "Trace.h"
using namespace std;

template<class T> class Vector{		//general  vector type
	T* v;
	int sz;
	int count;
	public:
		Vector(){
			TRACE(dummy, "vector<T>::vector(int)");
		}
		Vector(int size){
			TRACE(dummy, "vector<T>::vector(int)");
			sz = size;
			v = new T[sz];
			count++;
			cout << "count = " << count << endl;
		}
		~Vector(){
			TRACE(dummy, "vector<T>::~vector");
			cout << "count = " << count << endl;
			count--;
		}
		T& elem(int i){ return v[i]; }
		T& operator[](int i){ return v[i]; }
};

static int countV;
template<> class Vector<void*>{		// specialized for any pointer
	void** p;
	public:
		Vector(){
			TRACE(dummy, "vector<void*>::vector(int)");
		}
		Vector(int size){
			TRACE(dummy, "vector<void*>::vector(int)");
			p = new void*[size];
			countV++;
			cout << "count = " << countV << endl;
		}
		~Vector(){
			TRACE(dummy, "vector<void*>::~vector");
			cout << "count = " << countV << endl;
			countV--;
		}
		void*& elem(int i){ return p[i]; }
		void*& operator[](int i){
			return p[i];
		}
};

template<class T> class Vector<T*>: private Vector<void*>{	// specialized for void*
	int count;
	public:
		typedef Vector<void*> Base;
		Vector():Base(){
			TRACE(dummy, "vector<T*>::vector(int)");
		}
		~Vector(){
			TRACE(dummy, "vector<T*>::~vector");
		}
		explicit Vector(int i):Base(i){
			TRACE(dummy, "vector<T*>::vector(int)");
		}
		T*& elem(int i){
			static T* t = (T*)Base::elem(i);
			return t;
		}
		T*&operator[](int i){
			static T* t = (T*) Base::operator[](i);
			return t;
		}
};


#endif



