/*
* Copyright (c) 2017 , LAIN
* All rights reserved
*
* name : Stack.h
* contents : TOP SECRET
*
* developed by Comcx
* created time : 
*
*
*/

#ifndef FRACTION_H
#define FRACTION_H

class Fraction{

private:
	int up;
	int down;
	
public:
	//Fraction();
	Fraction( int up=0 , int down=1 );
	Fraction( double num );
	~Fraction(){};

	void Show(char flag = 'f');
	int getUp(){return this->up;};
	int getDown(){return this->down;};
	void Reduction();

	Fraction operator+ ( Fraction Frac );
	Fraction operator+ ( int num );
	Fraction operator- ( Fraction Frac );
	Fraction operator- ( int num );
	Fraction operator* ( Fraction Frac );
	Fraction operator* ( int num );
	Fraction operator/ ( Fraction Frac );
	Fraction operator/ ( int num );
	friend std::ostream & operator<< (std::ostream & os , Fraction & frac);
	friend Fraction operator+ (int num , Fraction & frac);
	friend Fraction operator- (int num , Fraction & frac);
	friend Fraction operator* (int num , Fraction & frac);
	friend Fraction operator/ (int num , Fraction & frac);

};






#endif//FRACTION_H