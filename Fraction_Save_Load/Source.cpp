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

	friend ofstream& operator<<(ofstream& os, Fraction& f);//для загрузки в файл
	friend ifstream& operator>>(ifstream& is, Fraction& f);//для выгрузки из файла

	friend void SaveData(Fraction& f);//загрузка в файл
	friend void LoadData(Fraction& f);//выгрузка из файлa
};

int main()
{
	Fraction f1(7, 4);
	Fraction f2(1, 3);
	Fraction f3;
	f3 = f1 + f2;
	f3.print();
	SaveData(f1);
	SaveData(f2);
	SaveData(f3);
	
	Fraction f4;
	LoadData(f4);
	f4.print();

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

ofstream& operator<<(ofstream& os, Fraction& f)
{
	f.Exam();
	if (f.intPart > 0) os << f.intPart << "(" << f.c << "/" << f.z << ")" << endl;
	else os << "(" << f.c << "/" << f.z << ")" << endl;

	return os;
}

ifstream& operator>>(ifstream& is, Fraction& f)
{
	//isdigit()//находит цифры
	//ispunct(s2[0]) != 0 //находит скобки
	string temp;
	string buf[3];
	
		getline(is, temp);
		//анализируем получившуюся строку
		if (ispunct(temp[0]) != 0)//если первый символ скобка
		{
			int i = 1;
			while (isdigit(temp[i]) != 0)
				buf[0] += temp[i++];
			int j = i + 1;
			while (isdigit(temp[j]) != 0)
				buf[1] += temp[j++];
			f.c = stoi(buf[0]);
			f.z = stoi(buf[1]);
		}
		else if (isdigit(temp[0]) != 0)
		{
			int i = 0;
			while (isdigit(temp[i]) != 0)
				buf[0] = temp[i++];
			int j = i + 1;
			while (isdigit(temp[j]) != 0)
				buf[1] += temp[j++];
			int k = j + 1;
			while (isdigit(temp[k]) != 0)
				buf[2] += temp[k++];
			f.intPart = stoi(buf[0]);
			f.c = stoi(buf[1]);
			f.z = stoi(buf[2]);
		}
	

	return is;
}

void SaveData(Fraction& f)
{
	string filename = "1.txt";
	ofstream os(filename, ios::app);
	os << f;
	os.close();
}

void LoadData(Fraction& f)
{
	string filename = "1.txt";
	ifstream is(filename);
	is >> f;
	is.close();
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


