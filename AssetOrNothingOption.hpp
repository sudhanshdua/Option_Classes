// Class that represents solutions to Asset or Nothing options
//
// (c) Sudhansh Dua
//
//  At expiration, the asset-or-nothing call option pays 0 if S < K and S if S > K. 
//	Similarly, a put option pays 0 if S > Kand S if S < K.


#ifndef AssetOrNothingOption_HPP
#define AssetOrNothingOption_HPP

#include "Option.hpp"
#include <string>
using namespace std;

class AssetOrNothingOption : public Option
{
private:
	// 'Kernel' functions for option calculations
	double CallPrice() const;								//	Price of a asset-or-nothing call option
	double PutPrice() const;								//	Price of a asset-or-nothing put option


	void init();											//  Initialise all default values
	void copy(const AssetOrNothingOption& option);			//	copies all values

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
	AssetOrNothingOption();												//	default constructor
	AssetOrNothingOption(const AssetOrNothingOption& option);			//	Copy constructor
	AssetOrNothingOption(const double& S1, const double& K1, const double& T1, const double& r1,
		const double& sig1, const double& b1, const string type1);		//	constructor that accepts values
	~AssetOrNothingOption();											//	destructor


	//	Assignment operator
	AssetOrNothingOption& operator = (const AssetOrNothingOption& option);


	// Functions that calculate the option price
	double Price() const;


	// Modifier functions
	void toggle();					//	Change option type (Call to Put, Put to Call)

};

//	Global Functions
double AoNCallPrice(const double S, const double K, const double T, const double r, const double sig, const double b, const string type);
double AoNPutPrice(const double S, const double K, const double T, const double r, const double sig, const double b, const string type);

#endif


