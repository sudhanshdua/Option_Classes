// Class that represents solutions to Gap options
//
// (c) Sudhansh Dua
//
//	The Gap options has the following payoff: 
//	->	call:	0 if S < K1	and	S — K2 if S > X1,
//	->	put:	0 if S > K1 and K2 — S if S < X1


#ifndef GapOption_HPP
#define GapOption_HPP

#include "Option.hpp"
#include <string>
using namespace std;

class GapOption : public Option
{
private:
	// 'Kernel' functions for option calculations
	double CallPrice() const;								//	Price of a Gap call option
	double PutPrice() const;								//	Price of a Gap put option


	void init();											// Initialise all default values
	void copy(const GapOption& option);						//	copies all values

public:
	//	Member data
	double T;			//	Time to expiry
	double r;			//	risk-free interest rate
	double sig;			//	Volatility
	double K1;			//	Strike Price-1
	double K2;			//	Strike Price-2 : the pay-off strike 
	double S;			//	current stock price
	double b;			//	Cost of carry
	string type;		//	"C" - call option, "P" - put option



	//	Constructors and the destructor
	GapOption();												//	default constructor
	GapOption(const GapOption& option);						//	Copy constructor
	GapOption(const double& S1, const double& K1, const double& K2, const double& T1, const double& r1,
		const double& sig1, const double& b1, const string type1);	//	constructor that accepts values
	~GapOption();												//	destructor


	//	Assignment operator
	GapOption& operator = (const GapOption& option);


	// Functions that calculate the option price
	double Price() const;


	// Modifier functions
	void toggle();					//	Change option type (Call to Put, Put to Call)

};

//	Global Functions
double GapCallPrice(const double S, const double K1, const double K2, const double T, const double r, const double sig, const double b, const string type);
double GapPutPrice(const double S, const double K1, const double K2, const double T, const double r, const double sig, const double b, const string type);

#endif


