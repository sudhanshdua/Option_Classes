//	Objective: To implement the option class that is defined in the header file: GapOption.hpp
//
// (c) Sudhansh Dua

#include "GapOption.hpp"
#include <string>
#include <boost/math/distributions.hpp>
#include <cmath>

using namespace std;
using namespace boost::math;


double GapOption::CallPrice() const
{
	return ::GapCallPrice(S, K1, K2, T, r, sig, b, type);
}

double GapOption::PutPrice() const
{
	return ::GapPutPrice(S, K1, K2, T, r, sig, b, type);
}


void GapOption::init()					// Initialising all the default values
{
	//	Default values
	T = 0.5;
	r = 0.09;
	sig = 0.2;
	K1 = 50;
	K2 = 57;
	S = 50;				//	Default stock price 
	b = r;				//	Black - Scholes(1973) stock option model : b = r

	type = "C";			//	Call option as the default

}

void GapOption::copy(const GapOption& option)
{
	T = option.T;
	r = option.r;
	sig = option.sig;
	K1 = option.K1;
	K2 = option.K2;
	b = option.b;
	type = option.type;
	S = option.S;
}

//	Constructors and destructor
//	Default Constructor
GapOption::GapOption() : Option()
{
	init();
}

//	Copy constructor
GapOption::GapOption(const GapOption& option) : Option(option)
{
	copy(option);
}

//	Constructor that accepts values
GapOption::GapOption(const double& S1, const double& K1, const double& K2, const double& T1, const double& r1, const double& sig1,
	const double& b1, const string type1) : Option(), S(S1), K1(K1), K2(K2), T(T1), r(r1), sig(sig1), b(b1), type(type1) {}

//	Destructor
GapOption::~GapOption() {}


//	Assignment Operator
GapOption& GapOption::operator = (const GapOption& option)
{
	if (this == &option)
	{
		return *this;		//	Self-assignment check!
	}
	Option::operator = (option);
	copy(option);
	return *this;
}


// Functions that calculate the option price
double GapOption::Price() const
{
	if (type == "C")
	{
		return CallPrice();
	}
	else
	{
		return PutPrice();
	}
}


// Modifier functions
void GapOption::toggle()								//	Change the option type
{
	type = ((type == "C") ? "P" : "C");
}

// Global Functions
double GapCallPrice(const double S, const double K1, const double K2, const double T, const double r, const double sig, const double b, const string type)
{
	double d1 = (log(S / K1) + (b + (sig * sig * 0.5)) * T) / (sig * sqrt(T));
	double d2 = d1 - (sig * sqrt(T));
	normal_distribution<> standard_normal(0.0, 1.0);

	return (S * exp((b - r) * T) * cdf(standard_normal, d1)) - (K2 * exp(-r * T) * cdf(standard_normal, d2));
}

double GapPutPrice(const double S, const double K1, const double K2, const double T, const double r, const double sig, const double b, const string type)
{
	double d1 = (log(S / K1) + (b + (sig * sig * 0.5)) * T) / (sig * sqrt(T));
	double d2 = d1 - (sig * sqrt(T));
	normal_distribution<> standard_normal(0.0, 1.0);

	return (K2 * exp(-r * T) * cdf(standard_normal, -d2)) - (S * exp((b - r) * T) * cdf(standard_normal, -d1));
}

