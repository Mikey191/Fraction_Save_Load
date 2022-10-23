#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Fraction
{
private:
	int c;
	int z;
	int intPart;
public:
	Fraction(int intPart, int c, int z): intPart{ intPart }, c{ c }, z{ z }{}
	Fraction(int c, int z): Fraction(0, c, z){}
	Fraction():Fraction(0,0,0){}
	Fraction operator+(Fraction& f);
	Fraction operator+(int value);
	friend Fraction operator+(int value, Fraction& f);

	Fraction operator-(Fraction& f);
	Fraction operator-(int value);
	friend Fraction operator-(int value, Fraction& f);

	Fraction operator*(Fraction& f);
	Fraction operator*(int value);
	friend Fraction operator*(int value, Fraction& f);

	Fraction operator/(Fraction& f);
	Fraction operator/(int value);
	friend Fraction operator/(int value, Fraction& f);
	void print(); //{ cout << "(" << c << "/" << z << ")"; }

	Fraction& RightFraction();
	Fraction& IntegerPart();
	Fraction& Exam();
	
	void SaveData();
	void LoadData();
};

int main()
{
	Fraction f1(7, 4);
	Fraction f2(1, 3);
	Fraction f3;
	f3 = f1 + f2;
	f3.print();

	return 0;
}

Fraction Fraction::operator+(Fraction& f)
{
	Fraction temp;
	temp.c = this->c * f.z + f.c * this->z;
	temp.z = this->z * f.z;

	return temp;
}

Fraction Fraction::operator+(int value)
{
	Fraction temp;
	temp.c = this->z * value + this->c;
	temp.z = this->z;

	return temp;
}

Fraction operator+(int value, Fraction& f)
{
	Fraction temp;
	temp.c = f.z * value + f.c;
	temp.z = f.z;

	return temp;
}

Fraction Fraction::operator-(Fraction& f)
{
	Fraction temp;
	temp.c = this->c * f.z - f.c * this->z;
	temp.z = this->z * f.z;

	return temp;
}

Fraction Fraction::operator-(int value)
{
	Fraction temp;
	temp.c = this->c - this->z * value;
	temp.z = this->z;

	return temp;
}

Fraction operator-(int value, Fraction& f)
{
	Fraction temp;
	temp.c = f.z * value - f.c;
	temp.z = f.z;

	return temp;
}

Fraction Fraction::operator*(Fraction& f)
{
	Fraction temp;
	temp.c = this->c * f.c;
	temp.z = this->z * f.z;

	return temp;
}

Fraction Fraction::operator*(int value)
{
	Fraction temp;
	temp.c = this->c * value;
	temp.z = this->z;

	return temp;
}

Fraction operator*(int value, Fraction& f)
{
	Fraction temp;
	temp.c = f.c * value;
	temp.z = f.z;

	return temp;
}

Fraction Fraction::operator/(Fraction& f)
{
	Fraction temp;
	temp.c = this->c * f.z;
	temp.z = this->z * f.c;

	return temp;
}

Fraction Fraction::operator/(int value)
{
	Fraction temp;
	temp.c = this->c;
	temp.z = this->z * value;

	return temp;
}

Fraction operator/(int value, Fraction& f)
{
	Fraction temp;
	temp.c = f.c;
	temp.z = f.z * value;

	return temp;
}

Fraction& Fraction::RightFraction()
{
	//Fraction temp;
	int NOD;
	int c1 = this->c;
	int z1 = this->z;
	while (c1 != 0 && z1 != 0)
	{
		if (c1 > z1)
			c1 = c1 % z1;
		else
			z1 = z1 % c1;
	}
	NOD = c1 + z1;
	this->c = this->c / NOD;
	this->z = this->z / NOD;

	return *this;
}

Fraction& Fraction::IntegerPart()
{
	//Fraction temp;
	this->intPart = this->c / this->z;
	if (this->intPart > 0)
	{
		this->c = this->c - this->intPart * this->z;
		this->z = this->z;
	}
	return *this;
}

Fraction& Fraction::Exam()
{
	this->RightFraction();
	if (this->c > this->z) this->IntegerPart();
	else return *this;
	return *this;
}

void Fraction::print()
{
	this->Exam();
	if (this->intPart > 0) cout << this->intPart << "(" << this->c << "/" << this->z << ")";
	else cout << "(" << this->c << "/" << this->z << ")";
}


