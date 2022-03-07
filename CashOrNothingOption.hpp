// Class that represents solutions to CashOrNothing options
//
// (c) Sudhansh Dua
//
//	The cash-or-nothing options pay an amount CR at expiration if the option is in-the-money.
//	The payoff from a call is 0 if S < K and CR, if S > K.
//	The payoff from a put is 0 if S > Kand CR if S < K.


#ifndef CashOrNothingOption_HPP
#define CashOrNothingOption_HPP

#include "Option.hpp"
#include <string>
using namespace std;

class CashOrNothingOption : public Option
{
private:
	// 'Kernel' functions for option calculations
	double CallPrice() const;								//	Price of a CashOrNothing call option
	double PutPrice() const;								//	Price of a CashOrNothing put option


	void init();											// Initialise all default values
	void copy(const CashOrNothingOption& option);			//	copies all values

public:
	//	Member data
	double cr;			//	Cash Rebate
	double T;			//	Time to expiry
	double r;			//	risk-free interest rate
	double sig;			//	Volatility
	double K;			//	Strike Price
	double S;			//	current stock price
	double b;			//	Cost of carry
	string type;		//	"C" - call option, "P" - put option


	//	Constructors and the destructor
	CashOrNothingOption();												//	default constructor
	CashOrNothingOption(const CashOrNothingOption& option);				//	Copy constructor
	CashOrNothingOption(const double& S1, const double& K1, const double& cr1, const double& T1, const double& r1,
		const double& sig1, const double& b1, const string type1);		//	constructor that accepts values
	~CashOrNothingOption();												//	destructor


	//	Assignment operator
	CashOrNothingOption& operator = (const CashOrNothingOption& option);


	// Functions that calculate the option price
	double Price() const;


	// Modifier functions
	void toggle();					//	Change option type (Call to Put, Put to Call)

};

//	Global Functions
double CashOrNothingCallPrice(const double S, const double K, const double cr, const double T, const double r, const double sig, const double b, const string type);
double CashOrNothingPutPrice(const double S, const double K, const double cr, const double T, const double r, const double sig, const double b, const string type);

#endif

