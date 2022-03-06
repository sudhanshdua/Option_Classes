//	Class that represents solutions to Barrier options
//
//	(c) Sudhansh Dua


#ifndef BarrierOption_HPP
#define BarrierOption_HPP

#include "Option.hpp"
#include <string>
using namespace std;


class BarrierOption : public Option
{
private:
	// 'Kernel' functions for option calculations
	double DownAndOutCallBarrier() const;					//	Price of a down-n-out barrier call option
	double DownAndOutPutBarrier() const;					//	Price of a down-n-out barrier put option
	double DownAndInCallBarrier() const;					//	Price of a down-n-in barrier call option
	double DownAndInPutBarrier() const;					//	Price of a down-n-in barrier put option
	double UpAndOutCallBarrier() const;					//	Price of a up-n-out barrier call option
	double UpAndOutPutBarrier() const;					//	Price of a up-n-out barrier put option
	double UpAndInCallBarrier() const;					//	Price of a up-n-in barrier call option
	double UpAndInPutBarrier() const;					//	Price of a up-n-in barrier put option

	void init();								// Initialise all default values
	void copy(const BarrierOption& option);					//	copies all values

public:
	//	Member data
	double T;			//	Time to expiry
	double H;			//	Barrier
	double cr;			//	Cash Rebate
	double r;			//	risk-free interest rate
	double sig;			//	Volatility
	double K;			//	Strike Price
	double S;			//	current stock price
	double b;			//	Cost of carry
	string type;			//	"C" - call option, "P" - put option
	string InOrOut;			//	"In" - In barrier, "Out" - out barrier


	//	Constructors and the destructor
	BarrierOption();										//	default constructor
	BarrierOption(const BarrierOption& option);							//	Copy constructor
	BarrierOption(const double& S1, const double& H1, const double& K1, const double& cr1, const double& T1, const double& r1,
		const double& sig1, const double& b1, const string type1, const string InOrOut1);	//	constructor that accepts values
	~BarrierOption();										//	destructor


	//	Assignment operator
	BarrierOption& operator = (const BarrierOption& option);


	// Functions that calculate the option price
	double Price() const;


	// Modifier functions
	void toggle();					//	Change option type (Call to Put, Put to Call)

};

//	Global Functions
double DownAndOutCallBarrier(const double S, const double H, const double K, const double cr, const double T, const double r, const double sig, const double b, const string type, const string InOrOut);
double DownAndOutPutBarrier(const double S, const double H, const double K, const double cr, const double T, const double r, const double sig, const double b, const string type, const string InOrOut);
double DownAndInCallBarrier(const double S, const double H, const double K, const double cr, const double T, const double r, const double sig, const double b, const string type, const string InOrOut);
double DownAndInPutBarrier(const double S, const double H, const double K, const double cr, const double T, const double r, const double sig, const double b, const string type, const string InOrOut);
double UpAndOutCallBarrier(const double S, const double H, const double K, const double cr, const double T, const double r, const double sig, const double b, const string type, const string InOrOut);
double UpAndOutPutBarrier(const double S, const double H, const double K, const double cr, const double T, const double r, const double sig, const double b, const string type, const string InOrOut);
double UpAndInCallBarrier(const double S, const double H, const double K, const double cr, const double T, const double r, const double sig, const double b, const string type, const string InOrOut);
double UpAndInPutBarrier(const double S, const double H, const double K, const double cr, const double T, const double r, const double sig, const double b, const string type, const string InOrOut);

#endif
