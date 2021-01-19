#pragma once
#include <vector>
#include <iostream>

class Option
{
public :
	Option(double k, double t);
	

public :
	double _k;
	double _t;
};

class EuropeanOption:public Option
{
public :
	virtual double payOff(double St) = 0;
protected:
	EuropeanOption(double k, double t);
};

class AsianOption :public Option
{
public :
	virtual double payOff(std::vector<double> path) = 0;
protected:
	AsianOption(double k, double t);
};

class AmericanOption :public Option
{
protected:
	AmericanOption(double k, double t);
};

class EuropeanCall : public EuropeanOption
{
public:
	EuropeanCall(double k, double t);
	double payOff(double St) override;
};

class EuropeanPut : public EuropeanOption
{
public:
	EuropeanPut(double k, double t);
	double payOff(double St) override;
};

class EuropeanDigitalCall: public EuropeanOption
{
public:
	EuropeanDigitalCall(double k, double t);
	double payOff(double St) override;
};

class EuropeanDigitalPut : public EuropeanOption
{
public:
	EuropeanDigitalPut(double k, double t);
	double payOff(double St) override;
};

class AsianCall:public AsianOption
{
public :
	AsianCall(double k, double t);
	double payOff(std::vector<double> path) override;
};

class AsianPut :public AsianOption
{
public:
	AsianPut(double k, double t);
	double payOff(std::vector<double> path) override;
};

class AmericanCall:public AmericanOption
{
public:
	AmericanCall(double k, double t);

};

class AmericanPut :public AmericanOption
{
public:
	AmericanPut(double k, double t);
};




