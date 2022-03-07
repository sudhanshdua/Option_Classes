// Implementing the class that is defined in the header file: Option.hpp
//
// (c) Sudhansh Dua


#include "EuropeanOption.hpp"
#include <cmath>
#include <boost/math/distributions.hpp>

using namespace std;
using namespace boost::math;


//	Gaussian functions using boost libraries
double EuropeanOption::N(double x) const
{
	normal_distribution<> Standard_normal(0.0, 1.0);
	return cdf(Standard_normal, x);
}

double EuropeanOption::n(double x) const
{
	normal_distribution<> Standard_normal(0.0, 1.0);
	return pdf(Standard_normal, x);
}

//	Kernel functions
double EuropeanOption::CallPrice() const
{
	return ::CallPrice(S, K, T, r, sig, b);
}

double EuropeanOption::PutPrice() const
{
	return ::PutPrice(S, K, T, r, sig, b);
}

double EuropeanOption::CallDelta() const
{
	return ::CallDelta(S, K, T, r, sig, b);
}

double EuropeanOption::PutDelta() const
{
	return ::PutDelta(S, K, T, r, sig, b);
}

double EuropeanOption::CallGamma() const
{
	return ::CallGamma(S, K, T, r, sig, b);
}

double EuropeanOption::PutGamma() const
{
	return ::PutGamma(S, K, T, r, sig, b);
}

double EuropeanOption::CallVega() const
{
	return ::CallVega(S, K, T, r, sig, b);
}

double EuropeanOption::PutVega() const
{
	return ::PutVega(S, K, T, r, sig, b);
}

double EuropeanOption::CallTheta() const
{
	return ::CallTheta(S, K, T, r, sig, b);
}

double EuropeanOption::PutTheta() const
{
	return ::PutTheta(S, K, T, r, sig, b);
}

double EuropeanOption::CallRho() const
{
	return ::CallRho(S, K, T, r, sig, b);
}

double EuropeanOption::PutRho() const
{
	return ::PutRho(S, K, T, r, sig, b);
}

double EuropeanOption::CallCoc() const
{
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));
	return T * S * exp((b - r) * T) * N(d1);
}

double EuropeanOption::PutCoc() const
{
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));
	return -T * S * exp((b - r) * T) * N(-d1);
}


//	Initialising all the default values
void EuropeanOption::init()
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


void EuropeanOption::copy(const EuropeanOption& option)
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
EuropeanOption::EuropeanOption() : Option()						//	Default constructor
{
	init();
}

EuropeanOption::EuropeanOption(const EuropeanOption& option) : Option(option)		//	Copy constructor
{
	copy(option);
}

//	Constructor that accepts values
EuropeanOption::EuropeanOption(const double& S1, const double& K1, const double& T1, const double& r1,
	const double& sig1, const double& b1, const string type1) : Option(), S(S1), K(K1), T(T1), r(r1), sig(sig1), b(b1), type(type1) {}

EuropeanOption::~EuropeanOption() {}							//	Destructor


//	Assignment operator
EuropeanOption& EuropeanOption::operator = (const EuropeanOption& option)
{
	if (this == &option)
	{
		return *this;
	}
	Option::operator = (option);
	copy(option);
	return *this;
}


//	Functions that calculate option price and sensitivities
double EuropeanOption::Price() const
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

double EuropeanOption::Delta() const
{
	if (type == "C")
	{
		return CallDelta();
	}
	else
	{
		return PutDelta();
	}
}

double EuropeanOption::Gamma() const
{
	if (type == "C")
	{
		return CallGamma();
	}
	else
	{
		return PutGamma();
	}
}

double EuropeanOption::Vega() const
{
	if (type == "C")
	{
		return CallVega();
	}
	else
	{
		return PutVega();
	}
}

double EuropeanOption::Theta() const
{
	if (type == "C")
	{
		return CallTheta();
	}
	else
	{
		return PutTheta();
	}
}

double EuropeanOption::Rho() const
{
	if (type == "C")
	{
		return CallRho();
	}
	else
	{
		return PutRho();
	}
}


//	Functions that calculates the Cost of carry
double EuropeanOption::Coc() const
{
	if (type == "C")
	{
		return CallCoc();
	}
	else
	{
		return PutCoc();
	}
}


// Modifier functions
void EuropeanOption::toggle()				//	Change the option type
{
	type = ((type == "C") ? "P" : "C");
}


//	Global Functions
double CallDelta(const double S, const double K, const double T, const double r, const double sig, const double b)
{
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));

	normal_distribution<> standard_normal(0.0, 1.0);
	return exp((b - r) * T) * cdf(standard_normal, d1);

}

double PutDelta(const double S, const double K, const double T, const double r, const double sig, const double b)
{

	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));
	normal_distribution<> standard_normal(0.0, 1.0);
	return exp((b - r) * T) * (cdf(standard_normal, d1) - 1.0);
}


double CallGamma(const double S, const double K, const double T, const double r, const double sig, const double b)
{
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));
	double d2 = d1 - (sig * sqrt(T));
	normal_distribution<> standard_normal(0.0, 1.0);
	return (pdf(standard_normal, d1) * exp((b - r) * T)) / (S * sig * sqrt(T));
}

double PutGamma(const double S, const double K, const double T, const double r, const double sig, const double b)
{
	return CallGamma(S, K, T, r, sig, b);
}


double CallVega(const double S, const double K, const double T, const double r, const double sig, const double b)
{
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));
	normal_distribution<> standard_normal(0.0, 1.0);
	return (S * sqrt(T) * exp((b - r) * T) * pdf(standard_normal, d1));
}


double PutVega(const double S, const double K, const double T, const double r, const double sig, const double b)
{
	return CallVega(S, K, T, r, sig, b);
}


double CallTheta(const double S, const double K, const double T, const double r, const double sig, const double b)
{
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));
	double d2 = d1 - (sig * sqrt(T));
	normal_distribution<> standard_normal(0.0, 1.0);
	double t1 = (S * sig * exp((b - r) * T) * pdf(standard_normal, d1)) / (2 * sqrt(T));
	double t2 = ((b - r) * S * exp((b - r) * T) * cdf(standard_normal, d1));
	double t3 = (r * K * exp(-r * T) * cdf(standard_normal, d1));
	return -(t1 + t2 + t3);
}

double PutTheta(const double S, const double K, const double T, const double r, const double sig, const double b)
{
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));
	double d2 = d1 - (sig * sqrt(T));
	normal_distribution<> standard_normal(0.0, 1.0);
	double t1 = (S * sig * exp((b - r) * T) * pdf(standard_normal, d1)) / (2 * sqrt(T));
	double t2 = ((b - r) * S * exp((b - r) * T) * cdf(standard_normal, d1));
	double t3 = (r * K * exp(-r * T) * cdf(standard_normal, d1));
	return t2 + t3 - t1;
}


double CallRho(const double S, const double K, const double T, const double r, const double sig, const double b)
{
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));
	double d2 = d1 - (sig * sqrt(T));
	normal_distribution<> standard_normal(0.0, 1.0);
	if (b != 0.0)
	{
		return T * K * exp(-r * T) * cdf(standard_normal, d2);
	}
	else
	{
		return -T * CallPrice(S, K, T, r, sig, b);
	}
}

double PutRho(const double S, const double K, const double T, const double r, const double sig, const double b)
{
	double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));
	double d2 = d1 - (sig * sqrt(T));
	normal_distribution<> standard_normal(0.0, 1.0);
	if (b != 0.0)
	{
		return T * K * exp(-r * T) * cdf(standard_normal, -d2);
	}
	else
	{
		return -T * PutPrice(S, K, T, r, sig, b);
	}
}
