// laba6.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
using namespace std;
class Rch
{

public:
	int chis, znam;
	friend ostream&  operator <<(ostream& os, const Rch&a);
	void Evklid()
	{
		int k;
		if (chis > znam)
		{
			k = chis;
		}
		else
		{
			k = znam;
		}
		for (int i = 2; i <= k+1; i++)
		{
			if (chis%i == 0 && znam%i == 0)
			{
				chis = chis / i;
				znam = znam / i;
			}
		}
	}
	Rch  operator *(const Rch& a) const
	{
		Rch temp;
		temp.chis = chis*a.chis;
		temp.znam = znam*a.znam;
		temp.Evklid();
		return temp;
	}
	Rch  operator *(const int a) const
	{
		Rch temp;
		temp.chis = chis*a;
		temp.znam = znam;
		temp.Evklid();
		return temp;
	}
	Rch  operator +(const Rch& a) const
	{
		Rch temp;
		if (chis==0)
		{
			temp.chis = a.chis;
			temp.znam = a.znam;
		}
		else
		{
			temp.chis = chis*a.znam + a.chis*znam;
			temp.znam = znam*a.znam;
			temp.Evklid();
		}
		return temp;
	}

};
ostream&  operator <<(ostream& os, const Rch&a)
{
	os << a.chis << "/" << a.znam << " ";
	return os;
}
template <typename Z >
class matrix {
	Z** T;
	int M;
	int N;
public:
	matrix(int m, int n) : T(NULL), M(m), N(n)
	{
		T = new Z*[M];
		for (int i = 0; i < M; i++)
		{
			T[i] = new Z[N];
			for (int j = 0; j < N; j++)
				T[i][j] = Z();
		}
	}
	Z& operator () (int i, int j)
	{
		return T[i][j];
	}

	template<typename Z>
	friend ostream&  operator <<(ostream& os, const matrix<Z>&a);
	template <typename Z >
	matrix<Z>  operator*(const matrix<Z>& a) const 
	{
		matrix<Z> U(M, a.N);

		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < a.N; j++)
			{
				for (int t = 0; t < N; t++)
				{
					U(i, j) = U(i, j) + T[i][t] * a.T[t][j];
				}
			}
		}
		return U;
	}
	
	matrix  operator ~() const
	{
		matrix U(N, M);

		for (int i = 0; i<N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				U(i, j) = T[j][i];
			}
		}
		return U;
	}
	matrix &  operator *(const int a) const
	{

		matrix U(M, N);

		for (int i = 0; i<M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				U(i, j) = T[i][j]*a;
			}
		}
		return U;
	}
	matrix  operator |(const matrix& a) const 
	{

		matrix U(M, N + a.N);

		for (int i = 0; i<M; i++)
		{
			for (int j = 0; j < N + a.N; j++)
			{
				if (j < N)
				{
					U(i, j) = T[i][j];
				}
				else
				{
					U(i, j) = a.T[i][j - N];
				}
			}
		}
		return U;
	}
	class iterator {
		matrix* Ma;
		size_t c;
	public:
		iterator(matrix* a, size_t b) : Ma(a), c(b) {};

		iterator& operator++() {
			c++;
			return *this;
		}

		Z& operator*() {
			return Ma->e[c];
		}

		Z* operator->() {
			return &(Ma->e[c]);
		}

		bool operator !=(const iterator& it) {
			return !(*this == it);
		}

		bool operator ==(const iterator& it) {
			return (c == it.c);
		}
	};
	iterator begin() {
		return iterator(this, 0);
	}

	iterator end() {
		return iterator(this, N*M);
	}
};
template <typename Z >
ostream&  operator <<(ostream& os, const matrix<Z> &a)
{
	for (int i = 0; i < a.M; i++)
	{
		for (int j = 0; j <a.N; j++)
			os << a.T[i][j] << " ";
		cout << endl;
	}
	cout << endl << endl;
	return os;
}	
template<template <class> class cont, typename Z, typename X>
cont<X> caster(cont<Z> a) {
	cont<X> b(m.n, m.m);
	for (int i = 0; i < n*m; i++) b.e[i] = static_cast<X>(a.e[i]);
	return b;
}


int main()
{
	int n;
	matrix<Rch> M(5, 6);
	matrix<Rch> L(5, 6);
	matrix<Rch> K(6, 5);
	matrix<Rch> O(5, 5);
	matrix<int> N(5, 5);
	Rch  *r;
	r = new Rch[30];
	for (int i = 0; i < 30; i++)
	{
		r[i].chis = rand() % 10 + 1;
		r[i].znam = rand() % 10 + 1;
		r[i].Evklid();
	}
for (int i = 0; i < 5; i++)
{
	for (int j = 0; j < 6; j++)
	{
		M(i, j) = r[i*6 + j];
	}
}

	cout << M;
	cout << "umnozhenie na chislo\n";
	L = M * 7;
	cout << L;
	cout << "transponirovanie\n";
	K = ~M;
	cout << K;
	cout << "kon'uktinaciya\n";
	L = L | M;
	cout << L;
	cout << "umnozhenie \n";
	O = M*K;
	cout << O;
	cout << "intovaya\n";
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			N(i, j) = rand() % 9;
		}
	}
	cout << N;
	system("pause");
	return 0;
}