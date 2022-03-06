// Class that contains the defines the base class: Options
//
// (c) Sudhansh Dua


#ifndef Option_HPP
#define Option_HPP


#include <iostream>
using namespace std;


class Option
{
private:
	void init();
	void copy(const Option& option);

	// 'Kernel' functions for option calculations
	double CallPrice() const;						//	Call option price
	double PutPrice() const;						//	Put option price


	// Gaussian functions
	double n(double x) const;		//	Normal Probability Density function
	double N(double x) const;		//	Cumulative Probability Density function

public:
	//	Member data
	double S;			//	current stock price where we wish to price the option
	double K;			//	Strike Price
	double T;			//	time to maturity
	double r;			//	risk-free interest rate
	double sig;			//	Volatility
	double b;			//	Cost of carry
	string type;		//	"C" - call option, "P" - put option

	//	Constructors and destructor
	Option();												//	default constructor
	Option(const Option& option);							//	copy constructor
	Option(const double& S1, const double& K1, const double& T1, const double& r1,
		const double& sig1, const double& b1, const string type1);	//	constructor that accepts values
	virtual ~Option();										// destructor


	//	Assignment operator
	Option& operator = (const Option& option);


	// Functions that calculate option price and sensitivities
	double Price() const;


	// Modifier functions
	void toggle();					//	Change option type (Call to Put, Put to Call)


};

//	Global functions
double CallPrice(const double S, const double K, const double T, const double r, const double sig, const double b);
double PutPrice(const double S, const double K, const double T, const double r, const double sig, const double b);


#endif

