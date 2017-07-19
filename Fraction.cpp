
#include <iostream>
#include "Fraction.h"

void Fraction::Show( char flag )
{
	Fraction::Reduction();                                   //约分
	if ( this->up == 0 && this->down != 0)					//判断分子是否为零
	{                                                      //
		std::cout << this->up;                            //
		return;                                          //
	}                                                   //
	                                                   //
	                                                  //
	if ( this->down < 0 )                            //处理符号
	{
		this->up *= -1;
		this->down *= -1;
	}

	if( flag == 'f' )
	{
		switch(this->down)
		{
		case 1:
			std::cout << this->up;
			break;
		case 0:
			std::cerr << "NaN";
			break;
		default:
			std::cout << this->up << "/" << this->down;
		}
	}

	else if( flag == 'r' )
	{
		switch(this->down)
		{
		case 1:
			std::cout << this->up;
			break;
		case 0:
			std::cerr << "NaN";
			break;
		default:
			std::cout << double(this->up) / double(this->down);
		}


	}
	
	
	
	
}


inline Fraction::Fraction( int up , int down )
{
	this->up = up;
	this->down = down;
}


Fraction::Fraction( double num )
{

}


Fraction Fraction::operator+ ( Fraction Frac )
{
	Fraction Result;
	Result.down = this->down * Frac.down;
	Result.up = this->up*Frac.down + Frac.up*this->down;
	return Result;
}

Fraction Fraction::operator+ ( int num )
{
	Fraction Result;
	Result.up = this->up + num*this->down;
	Result.down = this->down;
	return Result;

}


Fraction Fraction::operator- ( Fraction Frac )
{
	Fraction Result;
	Result.down = this->down * Frac.down;
	Result.up = this->up*Frac.down - Frac.up*this->down;
	return Result;
}

Fraction Fraction::operator-( int num )
{
	Fraction Result;
	Result.up = this->up - num*this->down;
	Result.down = this->down; 
	return Result;

}


Fraction Fraction::operator* ( Fraction Frac )
{
	Fraction Result;
	Result.down = this->down * Frac.down;
	Result.up = this->up * Frac.up;
	return Result;
}

Fraction Fraction::operator*( int num )
{
	Fraction Result;
	Result.up = this->up * num;
	Result.down = this->down; 
	return Result;

}


Fraction Fraction::operator/ ( Fraction Frac )
{
	Fraction Result;
	Result.down = this->down * Frac.up;
	Result.up = this->up * Frac.down;
	return Result;
}

Fraction Fraction::operator/( int num )
{
	Fraction Result;
	Result.up = this->up;
	Result.down = this->down * num; 
	return Result;
}



void Fraction::Reduction()
{
	if (this->down == 0 || this->up == 0)
		return;

	int up = std::max(this->up , this->down);
	int down = std::min(this->up , this->down);
	int left = up % down;

	while (left != 0)
	{
		up = down;
		down = left;
		left = up % down;
	}

	this->up /= down;
	this->down /= down;
	
}



std::ostream & operator<< ( std::ostream & os , Fraction & frac )
{
	frac.Reduction();                                                //约分
	int up = frac.getUp();
	int down = frac.getDown();
	if ( up == 0 && down != 0)					                  //判断分子是否为零
	{                                                            //
		os << up;                                               //
		return os;                                             //
	}                                                   //
	                                                   //
	                                                  //
	if ( down < 0 )                                  //处理符号
	{
		up *= -1;
		down *= -1;
	}
	
	switch(down)
	{
	case 1:
		os << up;
		break;
	case 0:
		os << "NaN";
		break;
	default:
		os << up << "/" << down;
	}
	
	return os;
}




Fraction operator+ (int num , Fraction & frac)
{
	Fraction Result;
	Result = frac + num;
	return Result;
}

Fraction operator- (int num , Fraction & frac)
{
	Fraction Result;
	Result = frac - num;
	return Result;
}

Fraction operator* (int num , Fraction & frac)
{
	Fraction Result;
	Result = frac * num;
	return Result;
}
Fraction operator/ (int num , Fraction & frac)
{
	Fraction Result;
	Result = frac / num;
	return Result;
}












