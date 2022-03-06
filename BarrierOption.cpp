//	Objective: To implement the option class that is defined in the header file: PerpetualAmericanOption.hpp

#include "BarrierOption.hpp"
#include <string>
#include <boost/math/distributions.hpp>
#include <cmath>

using namespace std;
using namespace boost::math;


double BarrierOption::DownAndOutCallBarrier() const
{
	return ::DownAndOutCallBarrier(S, H, K, cr, T, r, sig, b, type, InOrOut);
}

double BarrierOption::DownAndOutPutBarrier() const
{
	return ::DownAndOutPutBarrier(S, H, K, cr, T, r, sig, b, type, InOrOut);
}

double BarrierOption::DownAndInCallBarrier() const
{
	return ::DownAndInCallBarrier(S, H, K, cr, T, r, sig, b, type, InOrOut);
}

double BarrierOption::DownAndInPutBarrier() const
{
	return ::DownAndInPutBarrier(S, H, K, cr, T, r, sig, b, type, InOrOut);
}

double BarrierOption::UpAndOutCallBarrier() const
{
	return ::UpAndOutCallBarrier(S, H, K, cr, T, r, sig, b, type, InOrOut);
}

double BarrierOption::UpAndOutPutBarrier() const
{
	return ::UpAndOutPutBarrier(S, H, K, cr, T, r, sig, b, type, InOrOut);
}

double BarrierOption::UpAndInCallBarrier() const
{
	return ::UpAndInCallBarrier(S, H, K, cr, T, r, sig, b, type, InOrOut);
}

double BarrierOption::UpAndInPutBarrier() const
{
	return ::UpAndInPutBarrier(S, H, K, cr, T, r, sig, b, type, InOrOut);
}


void BarrierOption::init()		// Initialising all the default values
{
	//	Default values
	T = 1;
	H = 105;			
	cr = 3;
	r = 0.08;
	sig = 0.25;
	K = 100;
	S = 100;			//	Default stock price 
	b = r;				//	Black - Scholes(1973) stock option model: b = r (i.e. non-dividend paying stock)

	type = "C";			//	Call option as default
	InOrOut = "In";			//	In Barrier as default
}

void BarrierOption::copy(const BarrierOption& option)
{
	H = option.H;
	T = option.T;
	InOrOut = option.InOrOut;
	cr = option.cr;
	r = option.r;
	sig = option.sig;
	K = option.K;
	b = option.b;
	type = option.type;
	S = option.S;
}

//	Constructors and destructor
//	Default Constructor
BarrierOption::BarrierOption() : Option()
{
	init();
}

//	Copy constructor
BarrierOption::BarrierOption(const BarrierOption& option) : Option()
{
	copy(option);
}

//	Constructor that accepts values
BarrierOption::BarrierOption(const double& S1, const double& H1, const double& K1, const double& cr1, const double& T1, const double& r1, const double& sig1, 
	const double& b1, const string type1, const string InOrOut1) : Option(), S(S1), H(H1), K(K1), cr(cr1), T(T1), r(r1), sig(sig1), b(b1), type(type1), InOrOut(InOrOut1) {}

//	Destructor
BarrierOption::~BarrierOption() {}

//	Assignment Operator
BarrierOption& BarrierOption::operator = (const BarrierOption& option)
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
double BarrierOption::Price() const
{
	if (S >= H)
	{ 							// Down Barrier

		if (InOrOut == "In")						// Down and in barrier
		{ 

			if (type == "C")
			{												// Down and in call barrier
				return DownAndInCallBarrier();
			}
			else
			{												// Down and in put barrier
				return DownAndInPutBarrier();
			}
		}
		else
		{								// Down and out barrier
			if (type == "C")
			{												// Down and out call barrier
				return DownAndOutCallBarrier();
			}
			else
			{												// Down and out put barrier
				return DownAndOutPutBarrier();
			}
		}
	}

	else
	{							// Up Barrier

		if (InOrOut == "In")
		{								// Up and in barrier

			if (type == "C")
			{												// Up and in call barrier
				return UpAndInCallBarrier();
			}
			else
			{												// Up and in put barrier
				return UpAndInPutBarrier();
			}
		}
		else
		{								// Up and out barrier
			if (type == "C")
			{												// Up and out call barrier
				return UpAndOutCallBarrier();
			}
			else
			{												// Up and out put barrier
				return UpAndOutPutBarrier();
			}
		}
	}
}


// Modifier functions
void BarrierOption::toggle()				//	Change the option type
{
	type = ((type == "C") ? "P" : "C");
}



// Global Functions

double DownAndOutCallBarrier(const double S, const double H, const double K, const double cr, const double T, const double r, const double sig, const double b, const string type, const string InOrOut)
{
	double ita = 1;
	double phi = 1;

	double mu = (b - (sig * sig * 0.5)) / (sig * sig);
	double psi = sqrt((mu * mu) + (2 * r / (sig * sig)));
	double x1 = (log(S / K) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double x2 = (log(S / H) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double y1 = (log(H * H / (S * K)) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double y2 = (log(H / S)) / (sig * sqrt(T)) + ((1 + mu) * sig * sqrt(T));
	double z = (log(H / S) / (sig * sqrt(T))) + (psi * sig * sqrt(T));

	normal_distribution<> standard_normal(0.0, 1.0);
	double A = (phi * S * exp((b - r) * T) * cdf(standard_normal, phi * x1)) - (phi * K * exp(-r * T) * cdf(standard_normal, phi * (x1 - (sig * sqrt(T)))));
	double B = (phi * S * exp((b - r) * T) * cdf(standard_normal, phi * x2)) - (phi * K * exp(-r * T) * cdf(standard_normal, phi * (x2 - (sig * sqrt(T)))));
	double C = (phi * S * pow(H / S, 2 * (mu + 1)) * exp((b - r) * T) * cdf(standard_normal, ita * y1)) - (phi * K * exp(-r * T) * (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y1 - (sig * sqrt(T))))));
	double D = (phi * S * pow(H / S, 2 * (mu + 1)) * exp((b - r) * T) * cdf(standard_normal, ita * y2)) - (phi * K * exp(-r * T) * (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y2 - (sig * sqrt(T))))));
	double E = (cr * exp(-r * T) * ((cdf(standard_normal, ita * (x2 - (sig * sqrt(T))))) - (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y2 - (sig * sqrt(T)))))));
	double F = (cr * ((pow(H / S, mu + psi) * cdf(standard_normal, ita * z)) + (pow(H / S, mu - psi) * cdf(standard_normal, ita * (z - (2 * psi * sig * sqrt(T)))))));

	if (K > H)
	{
		return A - C + F;
	}
	else
		return B - D + F;
}


double DownAndOutPutBarrier(const double S, const double H, const double K, const double cr, const double T, const double r, const double sig, const double b, const string type, const string InOrOut)
{
	double ita = 1;
	double phi = -1;

	double mu = (b - (sig * sig * 0.5)) / (sig * sig);
	double psi = sqrt((mu * mu) + (2 * r / (sig * sig)));
	double x1 = (log(S / K) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double x2 = (log(S / H) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double y1 = (log(H * H / (S * K)) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double y2 = (log(H / S)) / (sig * sqrt(T)) + ((1 + mu) * sig * sqrt(T));
	double z = (log(H / S) / (sig * sqrt(T))) + (psi * sig * sqrt(T));

	normal_distribution<> standard_normal(0.0, 1.0);
	double A = phi * S * exp((b - r) * T) * cdf(standard_normal, phi * x1) - phi * K * exp(-r * T) * cdf(standard_normal, phi * (x1 - (sig * sqrt(T))));
	double B = phi * S * exp((b - r) * T) * cdf(standard_normal, phi * x2) - phi * K * exp(-r * T) * cdf(standard_normal, phi * (x2 - (sig * sqrt(T))));
	double C = (phi * S * pow(H / S, 2 * (mu + 1)) * exp((b - r) * T) * cdf(standard_normal, ita * y1)) - (phi * K * exp(-r * T) * (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y1 - (sig * sqrt(T))))));
	double D = (phi * S * pow(H / S, 2 * (mu + 1)) * exp((b - r) * T) * cdf(standard_normal, ita * y2)) - (phi * K * exp(-r * T) * (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y2 - (sig * sqrt(T))))));
	double E = (cr * exp(-r * T) * ((cdf(standard_normal, ita * (x2 - (sig * sqrt(T))))) - (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y2 - (sig * sqrt(T)))))));
	double F = (cr * ((pow(H / S, mu + psi) * cdf(standard_normal, ita * z)) + (pow(H / S, mu - psi) * cdf(standard_normal, ita * (z - (2 * psi * sig * sqrt(T)))))));

	if (K > H)
	{
		return A - B + C - D + F;
	}
	else
		return F;
}


double DownAndInCallBarrier(const double S, const double H, const double K, const double cr, const double T, const double r, const double sig, const double b, const string type, const string InOrOut)
{
	double ita = 1;
	double phi = 1;

	double mu = (b - (sig * sig * 0.5)) / (sig * sig);
	double psi = sqrt((mu * mu) + (2 * r / (sig * sig)));
	double x1 = (log(S / K) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double x2 = (log(S / H) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double y1 = (log(H * H / (S * K)) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double y2 = (log(H / S)) / (sig * sqrt(T)) + ((1 + mu) * sig * sqrt(T));
	double z = (log(H / S) / (sig * sqrt(T))) + (psi * sig * sqrt(T));

	normal_distribution<> standard_normal(0.0, 1.0);
	double A = phi * S * exp((b - r) * T) * cdf(standard_normal, phi * x1) - phi * K * exp(-r * T) * cdf(standard_normal, phi * (x1 - (sig * sqrt(T))));
	double B = phi * S * exp((b - r) * T) * cdf(standard_normal, phi * x2) - phi * K * exp(-r * T) * cdf(standard_normal, phi * (x2 - (sig * sqrt(T))));
	double C = (phi * S * pow(H / S, 2 * (mu + 1)) * exp((b - r) * T) * cdf(standard_normal, ita * y1)) - (phi * K * exp(-r * T) * (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y1 - (sig * sqrt(T))))));
	double D = (phi * S * pow(H / S, 2 * (mu + 1)) * exp((b - r) * T) * cdf(standard_normal, ita * y2)) - (phi * K * exp(-r * T) * (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y2 - (sig * sqrt(T))))));
	double E = (cr * exp(-r * T) * ((cdf(standard_normal, ita * (x2 - (sig * sqrt(T))))) - (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y2 - (sig * sqrt(T)))))));
	double F = (cr * ((pow(H / S, mu + psi) * cdf(standard_normal, ita * z)) + (pow(H / S, mu - psi) * cdf(standard_normal, ita * (z - (2 * psi * sig * sqrt(T)))))));

	if (K > H)
	{
		return C + E;
	}
	else
		return A - B + D + E;

}


double DownAndInPutBarrier(const double S, const double H, const double K, const double cr, const double T, const double r, const double sig, const double b, const string type, const string InOrOut)
{
	double ita = 1;
	double phi = -1;

	double mu = (b - (sig * sig * 0.5)) / (sig * sig);
	double psi = sqrt((mu * mu) + (2 * r / (sig * sig)));
	double x1 = (log(S / K) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double x2 = (log(S / H) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double y1 = (log(H * H / (S * K)) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double y2 = (log(H / S)) / (sig * sqrt(T)) + ((1 + mu) * sig * sqrt(T));
	double z = (log(H / S) / (sig * sqrt(T))) + (psi * sig * sqrt(T));

	normal_distribution<> standard_normal(0.0, 1.0);
	double A = phi * S * exp((b - r) * T) * cdf(standard_normal, phi * x1) - phi * K * exp(-r * T) * cdf(standard_normal, phi * (x1 - (sig * sqrt(T))));
	double B = phi * S * exp((b - r) * T) * cdf(standard_normal, phi * x2) - phi * K * exp(-r * T) * cdf(standard_normal, phi * (x2 - (sig * sqrt(T))));
	double C = (phi * S * pow(H / S, 2 * (mu + 1)) * exp((b - r) * T) * cdf(standard_normal, ita * y1)) - (phi * K * exp(-r * T) * (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y1 - (sig * sqrt(T))))));
	double D = (phi * S * pow(H / S, 2 * (mu + 1)) * exp((b - r) * T) * cdf(standard_normal, ita * y2)) - (phi * K * exp(-r * T) * (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y2 - (sig * sqrt(T))))));
	double E = (cr * exp(-r * T) * ((cdf(standard_normal, ita * (x2 - (sig * sqrt(T))))) - (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y2 - (sig * sqrt(T)))))));
	double F = (cr * ((pow(H / S, mu + psi) * cdf(standard_normal, ita * z)) + (pow(H / S, mu - psi) * cdf(standard_normal, ita * (z - (2 * psi * sig * sqrt(T)))))));

	if (K > H)
	{
		return B - C + D + E;
	}
	else
		return A + E;
}


double UpAndOutCallBarrier(const double S, const double H, const double K, const double cr, const double T, const double r, const double sig, const double b, const string type, const string InOrOut)
{
	double ita = -1;
	double phi = 1;

	double mu = (b - (sig * sig * 0.5)) / (sig * sig);
	double psi = sqrt((mu * mu) + (2 * r / (sig * sig)));
	double x1 = (log(S / K) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double x2 = (log(S / H) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double y1 = (log(H * H / (S * K)) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double y2 = (log(H / S)) / (sig * sqrt(T)) + ((1 + mu) * sig * sqrt(T));
	double z = (log(H / S) / (sig * sqrt(T))) + (psi * sig * sqrt(T));

	normal_distribution<> standard_normal(0.0, 1.0);
	double A = phi * S * exp((b - r) * T) * cdf(standard_normal, phi * x1) - phi * K * exp(-r * T) * cdf(standard_normal, phi * (x1 - (sig * sqrt(T))));
	double B = phi * S * exp((b - r) * T) * cdf(standard_normal, phi * x2) - phi * K * exp(-r * T) * cdf(standard_normal, phi * (x2 - (sig * sqrt(T))));
	double C = (phi * S * pow(H / S, 2 * (mu + 1)) * exp((b - r) * T) * cdf(standard_normal, ita * y1)) - (phi * K * exp(-r * T) * (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y1 - (sig * sqrt(T))))));
	double D = (phi * S * pow(H / S, 2 * (mu + 1)) * exp((b - r) * T) * cdf(standard_normal, ita * y2)) - (phi * K * exp(-r * T) * (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y2 - (sig * sqrt(T))))));
	double E = (cr * exp(-r * T) * ((cdf(standard_normal, ita * (x2 - (sig * sqrt(T))))) - (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y2 - (sig * sqrt(T)))))));
	double F = (cr * ((pow(H / S, mu + psi) * cdf(standard_normal, ita * z)) + (pow(H / S, mu - psi) * cdf(standard_normal, ita * (z - (2 * psi * sig * sqrt(T)))))));

	if (K > H)
	{
		return F;
	}
	else
		return A - B + C - D + F;

}


double UpAndOutPutBarrier(const double S, const double H, const double K, const double cr, const double T, const double r, const double sig, const double b, const string type, const string InOrOut)
{
	double ita = -1;
	double phi = -1;

	double mu = (b - (sig * sig * 0.5)) / (sig * sig);
	double psi = sqrt((mu * mu) + (2 * r / (sig * sig)));
	double x1 = (log(S / K) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double x2 = (log(S / H) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double y1 = (log(H * H / (S * K)) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double y2 = (log(H / S)) / (sig * sqrt(T)) + ((1 + mu) * sig * sqrt(T));
	double z = (log(H / S) / (sig * sqrt(T))) + (psi * sig * sqrt(T));

	normal_distribution<> standard_normal(0.0, 1.0);
	double A = phi * S * exp((b - r) * T) * cdf(standard_normal, phi * x1) - phi * K * exp(-r * T) * cdf(standard_normal, phi * (x1 - (sig * sqrt(T))));
	double B = phi * S * exp((b - r) * T) * cdf(standard_normal, phi * x2) - phi * K * exp(-r * T) * cdf(standard_normal, phi * (x2 - (sig * sqrt(T))));
	double C = (phi * S * pow(H / S, 2 * (mu + 1)) * exp((b - r) * T) * cdf(standard_normal, ita * y1)) - (phi * K * exp(-r * T) * (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y1 - (sig * sqrt(T))))));
	double D = (phi * S * pow(H / S, 2 * (mu + 1)) * exp((b - r) * T) * cdf(standard_normal, ita * y2)) - (phi * K * exp(-r * T) * (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y2 - (sig * sqrt(T))))));
	double E = (cr * exp(-r * T) * ((cdf(standard_normal, ita * (x2 - (sig * sqrt(T))))) - (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y2 - (sig * sqrt(T)))))));
	double F = (cr * ((pow(H / S, mu + psi) * cdf(standard_normal, ita * z)) + (pow(H / S, mu - psi) * cdf(standard_normal, ita * (z - (2 * psi * sig * sqrt(T)))))));

	if (K > H)
	{
		return B - D + F;
	}
	else
		return A - C + F;
}


double UpAndInCallBarrier(const double S, const double H, const double K, const double cr, const double T, const double r, const double sig, const double b, const string type, const string InOrOut)
{
	double ita = -1;
	double phi = 1;

	double mu = (b - (sig * sig * 0.5)) / (sig * sig);
	double psi = sqrt((mu * mu) + (2 * r / (sig * sig)));
	double x1 = (log(S / K) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double x2 = (log(S / H) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double y1 = (log(H * H / (S * K)) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double y2 = (log(H / S)) / (sig * sqrt(T)) + ((1 + mu) * sig * sqrt(T));
	double z = (log(H / S) / (sig * sqrt(T))) + (psi * sig * sqrt(T));

	normal_distribution<> standard_normal(0.0, 1.0);
	double A = phi * S * exp((b - r) * T) * cdf(standard_normal, phi * x1) - phi * K * exp(-r * T) * cdf(standard_normal, phi * (x1 - (sig * sqrt(T))));
	double B = phi * S * exp((b - r) * T) * cdf(standard_normal, phi * x2) - phi * K * exp(-r * T) * cdf(standard_normal, phi * (x2 - (sig * sqrt(T))));
	double C = (phi * S * pow(H / S, 2 * (mu + 1)) * exp((b - r) * T) * cdf(standard_normal, ita * y1)) - (phi * K * exp(-r * T) * (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y1 - (sig * sqrt(T))))));
	double D = (phi * S * pow(H / S, 2 * (mu + 1)) * exp((b - r) * T) * cdf(standard_normal, ita * y2)) - (phi * K * exp(-r * T) * (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y2 - (sig * sqrt(T))))));
	double E = (cr * exp(-r * T) * ((cdf(standard_normal, ita * (x2 - (sig * sqrt(T))))) - (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y2 - (sig * sqrt(T)))))));
	double F = (cr * ((pow(H / S, mu + psi) * cdf(standard_normal, ita * z)) + (pow(H / S, mu - psi) * cdf(standard_normal, ita * (z - (2 * psi * sig * sqrt(T)))))));

	if (K > H)
	{
		return A + E;
	}
	else
		return B - C + D + E;

}


double UpAndInPutBarrier(const double S, const double H, const double K, const double cr, const double T, const double r, const double sig, const double b, const string type, const string InOrOut)
{
	double ita = -1;
	double phi = -1;

	double mu = (b - (sig * sig * 0.5)) / (sig * sig);
	double psi = sqrt((mu * mu) + (2 * r / (sig * sig)));
	double x1 = (log(S / K) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double x2 = (log(S / H) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double y1 = (log(H * H / (S * K)) / (sig * sqrt(T))) + ((1 + mu) * sig * sqrt(T));
	double y2 = (log(H / S)) / (sig * sqrt(T)) + ((1 + mu) * sig * sqrt(T));
	double z = (log(H / S) / (sig * sqrt(T))) + (psi * sig * sqrt(T));

	normal_distribution<> standard_normal(0.0, 1.0);
	double A = phi * S * exp((b - r) * T) * cdf(standard_normal, phi * x1) - phi * K * exp(-r * T) * cdf(standard_normal, phi * (x1 - (sig * sqrt(T))));
	double B = phi * S * exp((b - r) * T) * cdf(standard_normal, phi * x2) - phi * K * exp(-r * T) * cdf(standard_normal, phi * (x2 - (sig * sqrt(T))));
	double C = (phi * S * pow(H / S, 2 * (mu + 1)) * exp((b - r) * T) * cdf(standard_normal, ita * y1)) - (phi * K * exp(-r * T) * (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y1 - (sig * sqrt(T))))));
	double D = (phi * S * pow(H / S, 2 * (mu + 1)) * exp((b - r) * T) * cdf(standard_normal, ita * y2)) - (phi * K * exp(-r * T) * (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y2 - (sig * sqrt(T))))));
	double E = (cr * exp(-r * T) * ((cdf(standard_normal, ita * (x2 - (sig * sqrt(T))))) - (pow(H / S, 2 * mu) * cdf(standard_normal, ita * (y2 - (sig * sqrt(T)))))));
	double F = (cr * ((pow(H / S, mu + psi) * cdf(standard_normal, ita * z)) + (pow(H / S, mu - psi) * cdf(standard_normal, ita * (z - (2 * psi * sig * sqrt(T)))))));

	if (K > H)
	{
		return A - B + D + E;
	}
	else
		return C + E;
}

