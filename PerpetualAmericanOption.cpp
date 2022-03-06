// Implementing the class that is defined in the header file: PerpetualAmericanOption.hpp
//
// (c) Sudhansh Dua


#include "PerpetualAmericanOption.hpp"
#include <string>
#include <boost/math/distributions.hpp>
#include <cmath>
#include <vector>


using namespace std;
using namespace boost::math;


double PerpetualAmericanOption::CallPrice() const
{
	return ::PerpetualCall(S, K, r, sig, b);
}

double PerpetualAmericanOption::PutPrice() const
{
	return ::PerpetualPut(S, K, r, sig, b);
}

void PerpetualAmericanOption::init()		// Initialising all the default values
{
	//	Default values
	r = 0.03;
	sig = 0.2;
	K = 105;
	S = 100;				//	Default stock price 
	b = r;					//	Black - Scholes(1973) stock option model : b = r

	type = "C";				//	Call option as the default
}

void PerpetualAmericanOption::copy(const PerpetualAmericanOption& option)
{
	r = option.r;
	sig = option.sig;
	K = option.K;
	b = option.b;
	type = option.type;
	S = option.S;
}


//	Constructors and destructor
//	Default Constructor
PerpetualAmericanOption::PerpetualAmericanOption()
{
	init();
}

//	Copy constructor
PerpetualAmericanOption::PerpetualAmericanOption(const PerpetualAmericanOption& option)
{
	copy(option);
}

//	Constructor that accepts values
PerpetualAmericanOption::PerpetualAmericanOption(const double& S1, const double& K1, const double& r1,
	const double& sig1, const double& b1, const string type1) : S(S1), K(K1), r(r1), sig(sig1), b(b1), type(type1) {}

//	Destructor
PerpetualAmericanOption::~PerpetualAmericanOption() {}


//	Assignment Operator
PerpetualAmericanOption& PerpetualAmericanOption::operator = (const PerpetualAmericanOption& option)
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
double PerpetualAmericanOption::Price() const
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
void PerpetualAmericanOption::toggle()				//	Change the option type
{
	type = ((type == "C") ? "P" : "C");
}

// Global functions
double PerpetualCall(const double S, const double K, const double r, const double sig, const double b)
{
	double y1 = 0.5 - (b / (sig * sig)) + sqrt(pow(((b / (sig * sig)) - 0.5), 2) + (2 * r / (sig * sig)));

	if (y1 == 1.0)
	{
		return S;
	}
	double C = (K / (y1 - 1)) * pow(((y1 - 1) / y1) * (S / K), y1);

	return C;
}


double PerpetualPut(const double S, const double K, const double r, const double sig, const double b)
{
	double y2 = 0.5 - (b / (sig * sig)) - sqrt(pow(((b / (sig * sig)) - 0.5), 2) + (2 * r / (sig * sig)));

	if (y2 == 1.0)
	{
		return S;
	}
	double P = (K / (1 - y2)) * pow(((y2 - 1) / y2) * (S / K), y2);

	return P;
}

