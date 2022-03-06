// Class that defines the derived class: Perpetual American Options
//
// (c) Sudhansh Dua


#ifndef PerpetualAmericanOption_HPP
#define PerpetualAmericanOption_HPP


#include "Option.hpp"
#include <string>
using namespace std;


class PerpetualAmericanOption : public Option
{
private:
	// 'Kernel' functions for option calculations
	double CallPrice() const;					//	Price of a call option
	double PutPrice() const;					//	Price of a put option
	void init();							// 	Initialise all default values
	void copy(const PerpetualAmericanOption& option);		//	copies all values

public:
	//	Member data
	double r;			//	risk-free interest rate
	double sig;			//	Volatility
	double K;			//	Strike Price
	double S;			//	current stock price
	double b;			//	Cost of carry
	string type;			//	"C" - call option, "P" - put option


	//	Constructors and the destructor
	PerpetualAmericanOption();						//	default constructor
	PerpetualAmericanOption(const PerpetualAmericanOption& option);		//	Copy constructor
	PerpetualAmericanOption(const double& S1, const double& K1, const double& r1,
		const double& sig1, const double& b1, const string type1);	//	constructor that accepts values
	~PerpetualAmericanOption();						//	destructor

	//	Assignment operator
	PerpetualAmericanOption& operator = (const PerpetualAmericanOption& option);

	// Functions that calculate the option price
	double Price() const;

	// Modifier functions
	void toggle();					//	Change option type (Call to Put, Put to Call)

};

//	Global Functions

double PerpetualCall(const double S, const double K, const double r, const double sig, const double b);
double PerpetualPut(const double S, const double K, const double r, const double sig, const double b);

#endif

