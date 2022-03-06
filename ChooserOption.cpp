// Implementing the class that is defined in the header file: ChooserOption.hpp
//
// (c) Sudhansh Dua



#include "ChooserOption.hpp"
#include <string>
#include <boost/math/distributions.hpp>
#include <cmath>


using namespace std;
using namespace boost::math;


//	Gaussian functions using boost libraries
double ChooserOption::N(double x) const
{
	normal_distribution<> Standard_normal(0.0, 1.0);
	return cdf(Standard_normal, x);
}

double ChooserOption::n(double x) const
{
	normal_distribution<> Standard_normal(0.0, 1.0);
	return pdf(Standard_normal, x);
}


double ChooserOption::ChooserPrice() const
{
	return ::ChooserPrice(S, K, T, t, r, sig, b);
}


// Initialising all the default values
void ChooserOption::init()					
{
	//	Default values
	r = 0.03;
	sig = 0.2;
	K = 105;
	S = 100;			//	Default stock price 
	b = r;				//	Black - Scholes(1973) stock option model : b = r
	T = 1;				
	t = 0.5;			//	time that has passed since t = 0

}


void ChooserOption::copy(const ChooserOption& option)
{
	r = option.r;
	t = option.t;
	T = option.T;
	sig = option.sig;
	K = option.K;
	b = option.b;
	S = option.S;
}


//	Constructors and destructor
//	Default Constructor
ChooserOption::ChooserOption() : Option()
{
	init();
}

//	Copy constructor
ChooserOption::ChooserOption(const ChooserOption& option) : Option(option)
{
	copy(option);
}

//	Constructor that accepts values
ChooserOption::ChooserOption(const double& S1, const double& K1, const double& T1, const double& t1, const double& r1,
	const double& sig1, const double& b1) : Option(), S(S1), K(K1), T(T1), t(t1), r(r1), sig(sig1), b(b1) {}

//	Destructor
ChooserOption::~ChooserOption() {}


//	Assignment Operator
ChooserOption& ChooserOption::operator = (const ChooserOption& option)
{
	if (this == &option)
	{
		return *this;		//	Self-assignment check!
	}
	Option::operator = (option);
	copy(option);
	return *this;
}


// Member function that calculate the option price
double ChooserOption::Price() const
{
	return ChooserPrice();
}


// Global functions
double ChooserPrice(const double S, const double K, const double T, const double t, const double r, const double sig, const double b)
{

	double y1 = (log(S / K) + (b * T) + (sig * sig * 0.5 * t)) / (sig * sqrt(t));
	double y2 = y1 - (sig * sqrt(t));

	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));
	double d2 = d1 - (sig * sqrt(T));

	normal_distribution<> standard_normal(0.0, 1.0);

	double w = (S * exp((b - r) * T) * cdf(standard_normal, d1)) - (K * exp(-r * T) * cdf(standard_normal, d2)) - (S * exp((b - r) * T) * cdf(standard_normal, -y1)) + (K * exp(-r * T) * cdf(standard_normal, -y2));
	return w;

}

