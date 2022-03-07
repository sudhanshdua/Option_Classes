//	Objective: To implement the option class that is defined in the header file: DigitalOption.hpp
//
// (c) Sudhansh Dua

#include "AssetOrNothingOption.hpp"
#include <string>
#include <boost/math/distributions.hpp>
#include <cmath>

using namespace std;
using namespace boost::math;


double AssetOrNothingOption::CallPrice() const
{
	return ::AoNCallPrice(S, K, T, r, sig, b, type);
}

double AssetOrNothingOption::PutPrice() const
{
	return ::AoNPutPrice(S, K, T, r, sig, b, type);
}


void AssetOrNothingOption::init()					// Initialising all the default values
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

void AssetOrNothingOption::copy(const AssetOrNothingOption& option)
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
AssetOrNothingOption::AssetOrNothingOption() : Option()
{
	init();
}

//	Copy constructor
AssetOrNothingOption::AssetOrNothingOption(const AssetOrNothingOption& option) : Option(option)
{
	copy(option);
}

//	Constructor that accepts values
AssetOrNothingOption::AssetOrNothingOption(const double& S1, const double& K1, const double& T1, const double& r1, const double& sig1,
	const double& b1, const string type1) : Option(), S(S1), K(K1), T(T1), r(r1), sig(sig1), b(b1), type(type1) {}

//	Destructor
AssetOrNothingOption::~AssetOrNothingOption() {}


//	Assignment Operator
AssetOrNothingOption& AssetOrNothingOption::operator = (const AssetOrNothingOption& option)
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
double AssetOrNothingOption::Price() const
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
void AssetOrNothingOption::toggle()								//	Change the option type
{
	type = ((type == "C") ? "P" : "C");
}

// Global Functions
double AoNCallPrice(const double S, const double K, const double T, const double r, const double sig, const double b, const string type)
{
	double d = (log(S / K) + (b + (sig * sig * 0.5)) * T) / (sig * sqrt(T));
	normal_distribution<> standard_normal(0.0, 1.0);
	return (S * exp(-r * T) * cdf(standard_normal, d));
}

double AoNPutPrice(const double S, const double K, const double T, const double r, const double sig, const double b, const string type)
{
	double d = (log(S / K) + (b + (sig * sig * 0.5)) * T) / (sig * sqrt(T));
	normal_distribution<> standard_normal(0.0, 1.0);
	return (S * exp(-r * T) * cdf(standard_normal, -d));
}

