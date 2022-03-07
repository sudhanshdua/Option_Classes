// Class that represents solutions to digital options
//
// (c) Sudhansh Dua
//
//	The digital options pay $1 at expiration if the option is In-the-money.
//	The payoff from a call is 0 if S < K and 1, if S > K.
//	The payoff from a put is 0 if S > K and 1 if S < K.


#ifndef DigitalOption_HPP
#define DigitalOption_HPP

#include "Option.hpp"
#include <string>
using namespace std;

class DigitalOption : public Option
{
private:
	// 'Kernel' functions for option calculations
	double CallPrice() const;								//	Price of a digital call option
	double PutPrice() const;								//	Price of a digital put option


	void init();											// Initialise all default values
	void copy(const DigitalOption& option);					//	copies all values

public:
	//	Member data
	double T;			//	Time to expiry
	double r;			//	risk-free interest rate
	double sig;			//	Volatility
	double K;			//	Strike Price
	double S;			//	current stock price
	double b;			//	Cost of carry
	string type;		//	"C" - call option, "P" - put option



	//	Constructors and the destructor
	DigitalOption();												//	default constructor
	DigitalOption(const DigitalOption& option);						//	Copy constructor
	DigitalOption(const double& S1, const double& K1, const double& T1, const double& r1,
		const double& sig1, const double& b1, const string type1);	//	constructor that accepts values
	~DigitalOption();												//	destructor


	//	Assignment operator
	DigitalOption& operator = (const DigitalOption& option);


	// Functions that calculate the option price
	double Price() const;


	// Modifier functions
	void toggle();					//	Change option type (Call to Put, Put to Call)

};

//	Global Functions
double DigitalCallPrice(const double S, const double K, const double T, const double r, const double sig, const double b, const string type);
double DigitalPutPrice(const double S, const double K, const double T, const double r, const double sig, const double b, const string type);

#endif


