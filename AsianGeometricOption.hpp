// Class that represents solutions to AsianGeometric options
//
// (c) Sudhansh Dua
//
//	The Asian Geometric continous average-rate options 


#ifndef AsianGeometricOption_HPP
#define AsianGeometricOption_HPP

#include "Option.hpp"
#include <string>
using namespace std;

class AsianGeometricOption : public Option
{
private:
	// 'Kernel' functions for option calculations
	double CallPrice() const;								//	Price of a AsianGeometric call option
	double PutPrice() const;								//	Price of a AsianGeometric put option


	void init();											// Initialise all default values
	void copy(const AsianGeometricOption& option);			//	copies all values

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
	AsianGeometricOption();												//	default constructor
	AsianGeometricOption(const AsianGeometricOption& option);						//	Copy constructor
	AsianGeometricOption(const double& S1, const double& K1, const double& T1, const double& r1,
		const double& sig1, const double& b1, const string type1);	//	constructor that accepts values
	~AsianGeometricOption();												//	destructor


	//	Assignment operator
	AsianGeometricOption& operator = (const AsianGeometricOption& option);


	// Functions that calculate the option price
	double Price() const;


	// Modifier functions
	void toggle();					//	Change option type (Call to Put, Put to Call)

};

//	Global Functions
double AsianGeometricCallPrice(const double S, const double K, const double T, const double r, const double sig, const double b, const string type);
double AsianGeometricPutPrice(const double S, const double K, const double T, const double r, const double sig, const double b, const string type);

#endif


