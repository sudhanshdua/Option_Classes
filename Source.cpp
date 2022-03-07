// Testing the exotic option classes
//
// (c) Sudhansh Dua

// Base class
#include "Option.hpp"

// Derived Classes
#include "EuropeanOption.hpp"
#include "PerpetualAmericanOption.hpp"
#include "ChooserOption.hpp"
#include "BarrierOption.hpp"
#include "DigitalOption.hpp"
#include "AssetOrNothingOption.hpp"
#include "CashOrNothingOption.hpp"
#include "AsianGeometricOption.hpp"

#include <iostream>
#include <iomanip>
using namespace std;


int main()
{	
	
	////////////////////////////		Chooser Option		///////////////////////////////
	// Chooser Option parameters
	double S_1 = 50.0;
	double K_1 = 50.0;
	double T_1 = 0.5;
	double t = 0.25;
	double r_1 = 0.08;
	double sig_1 = 0.25;
	double b_1 = r_1;
	ChooserOption option_1(S_1, K_1, T_1, t, r_1, sig_1, b_1);
	double price_1 = option_1.Price();
	cout << "Simple Chooser Option price:\t" << setprecision(10) << setprecision(10) << price_1 << endl;	// 6.1071
	cout << "\n";

	//////////////////////////////////////////		Barrier Options		//////////////////////////////////////
	// Down-Barrier option parameters (S >= H)
	double S_2 = 100.0;
	double K_2 = 100.0;
	double H = 100.0;
	double cr = 3;
	double T_2 = 0.5;
	double r_2 = 0.08;
	double sig_2 = 0.25;
	double b_2 = 0.04;
	BarrierOption option_2(S_2, H, K_2, cr, T_2, r_2, sig_2, b_2, "P", "In");
	BarrierOption option_3(S_2, H, K_2, cr, T_2, r_2, sig_2, b_2, "C", "In");
	BarrierOption option_4(S_2, H, K_2, cr, T_2, r_2, sig_2, b_2, "P", "Out");
	BarrierOption option_5(S_2, H, K_2, cr, T_2, r_2, sig_2, b_2, "C", "Out");

	double price_2 = option_2.Price();
	double price_3 = option_3.Price();
	double price_4 = option_4.Price();
	double price_5 = option_5.Price();

	cout << "Down and in put barrier price: \t" << setprecision(10) << price_2 << endl;		// 5.9085
	cout << "Down and in call barrier price: \t" << setprecision(10) << price_3 << endl;	// 7.8494
	cout << "Down and out put barrier price: \t" << setprecision(10) << price_4 << endl;	// 3.0
	cout << "Down and out call barrier price: \t" << setprecision(10) << price_5 << endl;	// 3.0

	// Up-Barrier option parameters (S < H)
	double H_2 = 105.0;

	BarrierOption option_6(S_2, H_2, K_2, cr, T_2, r_2, sig_2, b_2, "P", "In");
	BarrierOption option_7(S_2, H_2, K_2, cr, T_2, r_2, sig_2, b_2, "C", "In");
	BarrierOption option_8(S_2, H_2, K_2, cr, T_2, r_2, sig_2, b_2, "P", "Out");
	BarrierOption option_9(S_2, H_2, K_2, cr, T_2, r_2, sig_2, b_2, "C", "Out");

	double price_6 = option_6.Price();
	double price_7 = option_7.Price();
	double price_8 = option_8.Price();
	double price_9 = option_9.Price();

	cout << "Up and in put barrier price: \t" << setprecision(10) << price_6 << endl;		// 3.3721
	cout << "Up and in call barrier price: \t" << setprecision(10) << price_7 << endl;		// 8.4482
	cout << "Up and out put barrier price: \t" << setprecision(10) << price_8 << endl;		// 5.4932
	cout << "Up and out call barrier price: \t" << setprecision(10) << price_9 << endl;		// 2.3580
	cout << "\n";


	////////////////////////////		Digital Option		///////////////////////////////
	// Digital Option parameters
	double S_3 = 100.0;
	double K_3 = 80.0;
	double T_3 = 0.75;
	double r_3 = 0.06;
	double sig_3 = 0.35;
	double b_3 = 0;		//	constant dividend yield = risk-free rate
	DigitalOption option_10(S_3, K_3, T_3, r_3, sig_3, b_3, "P");

	double price_10 = option_10.Price();

	cout << "Digital Put option price: \t" << setprecision(10) << price_10 << endl;		// 0.26710
	cout << "\n";


	///////////////////////////////////		Asset-Or-Nothing Option		//////////////////////////////////
	// AssetOrNothing Option parameters
	double S_4 = 70.0;
	double K_4 = 65.0;
	double T_4 = 0.5;
	double r_4 = 0.05;
	double sig_4 = 0.27;
	double b_4 = 0.02;		//	constant dividend yield = 0.07

	AssetOrNothingOption option_11(S_4, K_4, T_4, r_4, sig_4, b_4, "P");
	double price_11 = option_11.Price();
	cout << "Asset-or-nothing option price: \t" << setprecision(10) << price_11 << endl;	// 20.2069
	cout << "\n";


	////////////////////////////		Cash-or-nothing Option		///////////////////////////////
	// Cash-or-nothing Option parameters
	double S_5 = 100.0;
	double K_5 = 80.0;
	double T_5 = 0.75;
	double r_5 = 0.06;
	double sig_5 = 0.35;
	double b_5 = 0;		//	constant dividend yield = risk-free rate
	double cr_2 = 10;
	CashOrNothingOption option_12(S_5, K_5, cr_2, T_5, r_5, sig_5, b_5, "P");

	double price_12 = option_12.Price();

	cout << "Cash-or-nothing Put option price: \t" << setprecision(10) << price_12 << endl;		// 2.6710
	cout << "\n";
	

	////////////////////////////////////		Asian Geometric Option			///////////////////////////////
	// Asian Geometric option parameters
	// Cash-or-nothing Option parameters
	double S_6 = 80.0;
	double K_6 = 85.0;
	double T_6 = 0.25;
	double r_6 = 0.05;
	double sig_6 = 0.2;
	double b_6 = 0.08;

	Option option_13(S_6, K_6, T_6, r_6, sig_6, b_6, "P");

	double price_13 = option_13.Price();

	cout << "Asian continuous Geometric Put option price: \t" << setprecision(10) << price_13 << endl;		// 5.2186
	cout << "\n";
	

	////////////////////////////		European Option		///////////////////////////////
	// European Option parameters
	double S_7 = 60.0;
	double K_7 = 65.0;
	double T_7 = 0.25;
	double r_7 = 0.08;
	double sig_7 = 0.3;
	double b_7 = r_7;		//	constant dividend yield = risk-free rate

	EuropeanOption option_14(S_7, K_7, T_7, r_7, sig_7, b_7, "C");
	EuropeanOption option_15(S_7, K_7, T_7, r_7, sig_7, b_7, "P");

	double price_14 = option_14.Price();
	double price_15 = option_15.Price();

	cout << "European Call option price: \t" << setprecision(10) << price_14 << endl;		// 2.13337
	cout << "European Put option price: \t" << setprecision(10) << price_15 << endl;		// 5.84628
	cout << "\n";


	///////////////////////////////////////		Perpetual American Option		////////////////////////////////
	// Perpetual American Option parameters
	double S_8 = 110.0;
	double K_8 = 100.0;
	double r_8 = 0.1;
	double sig_8 = 0.1;
	double b_8 = 0.02;		//	constant dividend yield = risk-free rate

	PerpetualAmericanOption option_16(S_8, K_8, r_8, sig_8, b_8, "C");
	PerpetualAmericanOption option_17(S_8, K_8, r_8, sig_8, b_8, "P");

	double price_16 = option_16.Price();
	double price_17 = option_17.Price();

	cout << "Perpetual American Call option price: \t" << setprecision(10) << price_16 << endl;		// 18.50349988
	cout << "Perpetual American Put option price: \t" << setprecision(10) << price_17 << endl;		// 3.031060383
	cout << "\n";

}