// 
//
// (c) Sudhansh Dua


#ifndef EuropeanOption_HPP
#define EuropeanOption_HPP


#include "Option.hpp"
#include <iostream>
using namespace std;


class EuropeanOption: public Option
{
private:
	void init();
	void copy(const EuropeanOption& option);

	// 'Kernel' functions for option calculations
	double CallPrice() const;				//	Call option price
	double PutPrice() const;				//	Put option price
	double CallDelta() const;				//	Call option delta
	double PutDelta() const;				//	Put option delta
	double CallGamma() const;				//	Call option gamma
	double PutGamma() const;				//	Put option gamma
	double CallVega() const;				//	Call option vega
	double PutVega() const;					//	Put option vega
	double CallTheta() const;				//	Call option theta
	double PutTheta() const;				//	Put option theta
	double CallRho() const;					//	Call option rho
	double PutRho() const;					//	Put option rho
	double CallCoc() const;					//	Call cost of carry
	double PutCoc() const;					//	Put cost of carry	


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
	string type;			//	"C" - call option, "P" - put option

	//	Constructors and destructor
	EuropeanOption();							//	default constructor
	EuropeanOption(const EuropeanOption& option);				//	copy constructor
	EuropeanOption(const double& S1, const double& K1, const double& T1, const double& r1,
		const double& sig1, const double& b1, const string type1);	//	constructor that accepts values
	virtual ~EuropeanOption();						// destructor


	//	Assignment operator
	EuropeanOption& operator = (const EuropeanOption& option);


	// Functions that calculate option price and sensitivities
	double Price() const;
	double Delta() const;
	double Gamma() const;
	double Vega() const;
	double Theta() const;
	double Rho() const;
	double Coc() const;


	// Modifier functions
	void toggle();					//	Change option type (Call to Put, Put to Call)


};

//	Global functions
double CallDelta(const double S, const double K, const double T, const double r, const double sig, const double b);
double PutDelta(const double S, const double K, const double T, const double r, const double sig, const double b);
double CallGamma(const double S, const double K, const double T, const double r, const double sig, const double b);
double PutGamma(const double S, const double K, const double T, const double r, const double sig, const double b);
double CallVega(const double S, const double K, const double T, const double r, const double sig, const double b);
double PutVega(const double S, const double K, const double T, const double r, const double sig, const double b);
double CallTheta(const double S, const double K, const double T, const double r, const double sig, const double b);
double PutTheta(const double S, const double K, const double T, const double r, const double sig, const double b);
double CallRho(const double S, const double K, const double T, const double r, const double sig, const double b);
double PutRho(const double S, const double K, const double T, const double r, const double sig, const double b);

#endif

