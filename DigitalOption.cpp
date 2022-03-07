//	Objective: To implement the option class that is defined in the header file: DigitalOption.hpp
//
// (c) Sudhansh Dua

#include "DigitalOption.hpp"
#include <string>
#include <boost/math/distributions.hpp>
#include <cmath>

using namespace std;
using namespace boost::math;


double DigitalOption::CallPrice() const
{
	return ::DigitalCallPrice(S, K, T, r, sig, b, type);
}

double DigitalOption::PutPrice() const
{
	return ::DigitalPutPrice(S, K, T, r, sig, b, type);
}


void DigitalOption::init()					// Initialising all the default values
{
	//	Default values
	T = 1;
	r = 0.08;
	sig = 0.25;
	K = 100;
	S = 100;			//	Default stock price 
	b = r;				//	Black - Scholes(1973) stock option model : b = r

	type = "C";			//	Call option as the default

}

void DigitalOption::copy(const DigitalOption& option)
{
	T = option.T;
	r = option.r;
	sig = option.sig;
	K = option.K;
	b = option.b;
	type = option.type;
	S = option.S;
}

//	Constructors and destructor
//	Default Constructor
DigitalOption::DigitalOption() : Option()
{
	init();
}

//	Copy constructor
DigitalOption::DigitalOption(const DigitalOption& option) : Option()
{
	copy(option);
}

//	Constructor that accepts values
DigitalOption::DigitalOption(const double& S1, const double& K1, const double& T1, const double& r1, const double& sig1,
	const double& b1, const string type1) : Option(), S(S1), K(K1), T(T1), r(r1), sig(sig1), b(b1), type(type1) {}

//	Destructor
DigitalOption::~DigitalOption() {}


//	Assignment Operator
DigitalOption& DigitalOption::operator = (const DigitalOption& option)
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
double DigitalOption::Price() const
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
void DigitalOption::toggle()								//	Change the option type
{
	type = ((type == "C") ? "P" : "C");
}

// Global Functions
double DigitalCallPrice(const double S, const double K, const double T, const double r, const double sig, const double b, const string type)
{
	double d = (log(S / K) + (b - (sig * sig * 0.5)) * T) / (sig * sqrt(T));
	normal_distribution<> standard_normal(0.0, 1.0);
	return (exp(-r * T) * cdf(standard_normal, d));
}

double DigitalPutPrice(const double S, const double K, const double T, const double r, const double sig, const double b, const string type)
{
	double d = (log(S / K) + (b - (sig * sig * 0.5)) * T) / (sig * sqrt(T));
	normal_distribution<> standard_normal(0.0, 1.0);
	return (exp(-r * T) * cdf(standard_normal, -d));
}

