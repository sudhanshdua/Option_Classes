// Class that defines the derived class: Chooser Option
//
// (c) Sudhansh Dua
//
// A simple chooser option gives the holder the right to choose whether the option is to be a standard call or put after a time t, 
// with strike K and time to maturity T.


#ifndef ChooserOption_HPP
#define ChooserOption_HPP


#include "Option.hpp"
#include <iostream>
using namespace std;


class ChooserOption : public Option
{
private:
	// 'Kernel' functions for option calculations
	double ChooserPrice() const;			//	Price of the option
	void init();					// 	Initialise all default values
	void copy(const ChooserOption& option);		//	copies all values


	// Gaussian functions
	double n(double x) const;			//	Normal Probability Density function
	double N(double x) const;			//	Cumulative Probability Density function


public:
	//	Member data
	double t;			//	time that has passed since t = 0
	double T;			//  	time to maturity
	double r;			//	risk-free interest rate
	double sig;			//	Volatility
	double K;			//	Strike Price
	double S;			//	current stock price where we wish to price the option
	double b;			//	Cost of carry
	


	//	Constructors and the destructor
	ChooserOption();					//	default constructor
	ChooserOption(const ChooserOption& option);		//	Copy constructor
	ChooserOption(const double& S1, const double& K1, const double& T1, const double& t1, const double& r1,
		const double& sig1, const double& b1);		//	constructor that accepts values
	~ChooserOption();					//	destructor

	//	Assignment operator
	ChooserOption& operator = (const ChooserOption& option);

	// Functions that calculate the option price
	double Price() const;

};

//	Global Functions
double ChooserPrice(const double S, const double K, const double T, const double t, const double r, const double sig, const double b);

#endif
