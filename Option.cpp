// Implementing the class that is defined in the header file: Option.hpp
//
// (c) Sudhansh Dua


#include "Option.hpp"
#include <cmath>
#include <boost/math/distributions.hpp>


using namespace std;
using namespace boost::math;


//	Gaussian functions using boost libraries
double Option::N(double x) const
{
	normal_distribution<> Standard_normal(0.0, 1.0);
	return cdf(Standard_normal, x);
}

double Option::n(double x) const
{
	normal_distribution<> Standard_normal(0.0, 1.0);
	return pdf(Standard_normal, x);
}

//	Kernel functions
double Option::CallPrice() const
{
	return ::CallPrice(S, K, T, r, sig, b);
}

double Option::PutPrice() const
{
	return ::PutPrice(S, K, T, r, sig, b);
}


//	Initialising all the default values
void Option::init()
{
	//	Default values
	r = 0.03;
	sig = 0.2;
	K = 100;
	S = 95;				//	Default stock price 
	T = 1;
	b = r;				//	Black - Scholes(1973) stock option model : b = r
	type = "C";			//	Call option as the default
}


void Option::copy(const Option& option)
{
	S = option.S;
	K = option.K;
	T = option.T;
	r = option.r;
	sig = option.sig;
	b = option.b;
	type = option.type;
}


//	Constructors and destructor
Option::Option()						//	Default constructor
{
	init();
}

Option::Option(const Option& option)				//	Copy constructor
{
	copy(option);
}

//	Constructor that accepts values
Option::Option(const double& S1, const double& K1, const double& T1, const double& r1,
	const double& sig1, const double& b1, const string type1) : S(S1), K(K1), T(T1), r(r1), sig(sig1), b(b1), type(type1) {}

Option::~Option() {}						//	Destructor


//	Assignment operator
Option& Option::operator = (const Option& option)
{
	if (this == &option)
	{
		return *this;
	}
	copy(option);
	return *this;
}


//	Functions that calculate option price and sensitivities
double Option::Price() const
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
void Option::toggle()				//	Change the option type
{
	type = ((type == "C") ? "P" : "C");
}


//	Global Functions
double CallPrice(const double S, const double K, const double T, const double r, const double sig, const double b)
{
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));
	double d2 = d1 - (sig * sqrt(T));
	normal_distribution<> standard_normal(0.0, 1.0);

	return (S * exp((b - r) * T) * cdf(standard_normal, d1)) - (K * exp(-r * T) * cdf(standard_normal, d2));
}

double PutPrice(const double S, const double K, const double T, const double r, const double sig, const double b)
{
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));
	double d2 = d1 - (sig * sqrt(T));
	normal_distribution<> standard_normal(0.0, 1.0);

	return (K * exp(-r * T) * cdf(standard_normal, -d2)) - (S * exp((b - r) * T) * cdf(standard_normal, -d1));
}
