// polimorfizmo testas.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class Polimorfizmas {
private:
	int x;
	double y;
public:
	bool setx(int);
	int getx();
	bool sety(double);
	double gety();

	Polimorfizmas();
	~Polimorfizmas();
	int funkcija(int);
	int funkcija(double);
	double funkcija(int, double);
	double funkcija(double, int);
};

Polimorfizmas::Polimorfizmas() {
	x = 1;
	y = 3.14;
}

Polimorfizmas::~Polimorfizmas() {
}

bool Polimorfizmas::setx(int x) {
	this->x = x;
	return true;
}

int Polimorfizmas::getx() {
	return x;
}

bool Polimorfizmas::sety(double y) {
	this->y = y;
	return true;
}

double Polimorfizmas::gety() {
	return y;
}

int Polimorfizmas::funkcija(int x) {
	return x * x;
}

int Polimorfizmas::funkcija(double y) {
	return 1;
}

double Polimorfizmas::funkcija(int x, double y) {
	return y - x;
}

double Polimorfizmas::funkcija(double y, int x) {
	return (x * y) - 1;
}

int main()
{
	Polimorfizmas objektasTestavimui;
	cout << objektasTestavimui.funkcija(5) << endl; // imetam sveika skaiciu
	cout << objektasTestavimui.funkcija(5.56) << endl; // imetam realu skaiciu
	cout << objektasTestavimui.funkcija(1, 2.46) << endl;	// duodam viena sveika skaiciu, o kita realuji
	cout << objektasTestavimui.funkcija(1.11, 2) << endl;	// duodam viena realuji skaiciu, o kita sveika
	// funkcija kvieciama skirtinga priklausomai nuo iejimo - tai POLIMORFIZMAS
    return 0;
}
