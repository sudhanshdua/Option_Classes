//	Objective: To implement the option class that is defined in the header file: AsianGeometricOption.hpp
//
// (c) Sudhansh Dua

#include "AsianGeometricOption.hpp"
#include <string>
#include <boost/math/distributions.hpp>
#include <cmath>

using namespace std;
using namespace boost::math;


double AsianGeometricOption::CallPrice() const
{
	return ::AsianGeometricCallPrice(S, K, T, r, sig, b, type);
}

double AsianGeometricOption::PutPrice() const
{
	return ::AsianGeometricPutPrice(S, K, T, r, sig, b, type);
}


void AsianGeometricOption::init()					// Initialising all the default values
{
	//	Default values
	T = 0.25;
	r = 0.05;
	sig = 0.2;
	K = 85;
	S = 80;			
	b = 0.08;			

	type = "C";			//	Call option as the default

}

void AsianGeometricOption::copy(const AsianGeometricOption& option)
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
AsianGeometricOption::AsianGeometricOption() : Option()
{
	init();
}

//	Copy constructor
AsianGeometricOption::AsianGeometricOption(const AsianGeometricOption& option) : Option(option)
{
	copy(option);
}

//	Constructor that accepts values
AsianGeometricOption::AsianGeometricOption(const double& S1, const double& K1, const double& T1, const double& r1, const double& sig1,
	const double& b1, const string type1) : Option(), S(S1), K(K1), T(T1), r(r1), sig(sig1), b(b1), type(type1) {}

//	Destructor
AsianGeometricOption::~AsianGeometricOption() {}


//	Assignment Operator
AsianGeometricOption& AsianGeometricOption::operator = (const AsianGeometricOption& option)
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
double AsianGeometricOption::Price() const
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
void AsianGeometricOption::toggle()								//	Change the option type
{
	type = ((type == "C") ? "P" : "C");
}

// Global Functions
double AsianGeometricCallPrice(const double S, const double K, const double T, const double r, const double sig, const double b, const string type)
{
	double sig_adj = sig / sqrt(3);						//	adjusted volatility 
	double b_adj = 0.5 * (b - ((sig * sig) / 6));		//	adjusted cost-of-carry

	double d1 = (log(S / K) + (b_adj + (sig_adj * sig_adj * 0.5)) * T) / sig_adj * sqrt(T);
	double d2 = d1 - sig_adj * sqrt(T);

	normal_distribution<> standard_normal(0.0, 1.0);
	return ((S * exp((b_adj - r) * T) * cdf(standard_normal, d1)) - (K * exp(-r * T) * cdf(standard_normal, d2)));
}

double AsianGeometricPutPrice(const double S, const double K, const double T, const double r, const double sig, const double b, const string type)
{
	double sig_adj = sig / sqrt(3);						//	adjusted volatility 
	double b_adj = 0.5 * (b - ((sig * sig) / 6));		//	adjusted cost-of-carry

	double d1 = (log(S / K) + (b_adj + (sig_adj * sig_adj * 0.5)) * T) / sig_adj * sqrt(T);
	double d2 = d1 - sig_adj * sqrt(T);

	normal_distribution<> standard_normal(0.0, 1.0);
	return ((K * exp(-r * T) * cdf(standard_normal, -d2)) - (S * exp((b_adj - r) * T) * cdf(standard_normal, -d1)));
}

