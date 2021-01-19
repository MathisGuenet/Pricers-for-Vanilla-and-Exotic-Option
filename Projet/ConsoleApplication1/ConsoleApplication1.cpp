// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "BS.h"
#include "CRR.h"
#include "RandomPaths.h"
#include "Option.h"

void refineRandomPaths(double r, double sigma, double s0, double steps, AsianOption& option)
{
    double totalWalks = 0;
    double nbWalks = 800;
    totalWalks = totalWalks + nbWalks;
    RandomPaths paths1 = RandomPaths(nbWalks, r, sigma, s0, steps, option);
    double currentEstimation = paths1.pricerPathDependent(option);
    std::cout << "1ere estimation (800 paths) : ";
    std::cout <<  currentEstimation<< std::endl;
   
    nbWalks = 1500;
    totalWalks = totalWalks + nbWalks;
    RandomPaths paths2 = RandomPaths(nbWalks, r, sigma, s0, steps, option);
    currentEstimation = (currentEstimation*(double(totalWalks - nbWalks)/double(totalWalks))) + paths2.pricerPathDependent(option)*(double(nbWalks)/double(totalWalks));
    std::cout << "2nd estimation (1500 paths) : ";
    std::cout << currentEstimation << std::endl;
  
    nbWalks = 1000;
    totalWalks = totalWalks + nbWalks;
    RandomPaths paths3 = RandomPaths(nbWalks, r, sigma, s0, steps, option);
    currentEstimation = (currentEstimation * (double(totalWalks - nbWalks)/double(totalWalks)))+paths2.pricerPathDependent(option)*(double(nbWalks) / double(totalWalks));
    std::cout << "3eme estimation (1000 paths) : ";
    std::cout << currentEstimation << std::endl;
}

void refineRandomPaths(double r, double sigma, double s0, double steps, EuropeanOption& option)
{
    double totalWalks = 0;
    double nbWalks = 200;
    totalWalks = totalWalks + nbWalks;
    RandomPaths paths1 = RandomPaths(nbWalks, r, sigma, s0, steps, option);
    double currentEstimation = paths1.pricerPathDependent(option);
    std::cout << "1ere estimation (200 paths) : ";
    std::cout << currentEstimation << std::endl;

    nbWalks = 800;
    totalWalks = totalWalks + nbWalks;
    RandomPaths paths2 = RandomPaths(nbWalks, r, sigma, s0, steps, option);
    currentEstimation = (currentEstimation * (double(totalWalks - nbWalks) / double(totalWalks))) + paths2.pricerPathDependent(option) * (double(nbWalks) / double(totalWalks));
    std::cout << "2nd estimation (800 paths) : ";
    std::cout << currentEstimation << std::endl;

    nbWalks = 500;
    totalWalks = totalWalks + nbWalks;
    RandomPaths paths3 = RandomPaths(nbWalks, r, sigma, s0, steps, option);
    currentEstimation = (currentEstimation * (double(totalWalks - nbWalks) / double(totalWalks))) + paths2.pricerPathDependent(option) * (double(nbWalks) / double(totalWalks));
    std::cout << "3eme estimation (500 paths) : ";
    std::cout << currentEstimation << std::endl;
}

void europeanCallPricer(double s0, double r, double sigma, EuropeanCall& europeanCall, double up, double down)
{
    std::cout << "Pricers for European call" << std::endl;
    std::cout << std::endl;
    std::cout << "Blacksholes closed form : ";
    BS bs = BS(r, sigma, s0);
    std::cout << bs.pricerBS(europeanCall) << std::endl;
    std::cout << std::endl;

    std::cout << "Monte Carlo Pricer (random paths) : " << std::endl;
    int steps = 15;
    refineRandomPaths(r, sigma, s0, steps, europeanCall);
    std::cout << std::endl;

    std::cout << "binomial Model (closed form) : ";
    CRR crr = CRR(europeanCall._t, r, s0, up, down);
    std::cout << crr.pricerClosedFormula(europeanCall) << std::endl;
    std::cout << std::endl;

    std::cout << "binomial Model (CRR) : ";
    std::cout << crr.pricer(europeanCall) << std::endl;
    crr.Display();
    std::cout << std::endl;

    std::cout << "binomial Model (CRR with blacksholes approximation,  steps = 100) : ";
    steps = 100;
    CRR crrBs = CRR(steps, europeanCall._t, r, s0, sigma, true);
    std::cout << crrBs.pricer(europeanCall);
    std::cout << std::endl;
}

void europeanPutPricer(double s0, double r, double sigma, EuropeanPut& europeanPut, double up, double down)
{
    std::cout << "Pricers for European Put" << std::endl;
    std::cout << std::endl;
    std::cout << "Blacksholes closed form : ";
    BS bs = BS(r, sigma, s0);
    std::cout << bs.pricerBS(europeanPut) << std::endl;
    std::cout << std::endl;

    std::cout << "Monte Carlo Pricer (random paths) : " << std::endl;
    int steps = 15;
    refineRandomPaths(r, sigma, s0, steps, europeanPut);
    std::cout << std::endl;

    std::cout << "binomial Model (closed form) : ";
    CRR crr = CRR(europeanPut._t, r, s0, up, down);
    std::cout << crr.pricerClosedFormula(europeanPut) << std::endl;
    std::cout << std::endl;

    std::cout << "binomial Model (CRR) : ";
    std::cout << crr.pricer(europeanPut) << std::endl;
    crr.Display();
    std::cout << std::endl;

    std::cout << "binomial Model (CRR with blacksholes approximation, steps = 100) : ";
    steps = 100;
    CRR crrBs = CRR(steps, europeanPut._t, r, s0, sigma, true);
    std::cout << crrBs.pricer(europeanPut);
    std::cout << std::endl;
}

void europeanDigitalCallPricer(double s0, double r, double sigma, EuropeanDigitalCall& europeanDigitalCall, double up, double down)
{
    std::cout << "Pricers for European digital call" << std::endl;
    std::cout << std::endl;

    std::cout << "Monte Carlo Pricer (random paths) : " << std::endl;
    int steps = 15;
    refineRandomPaths(r, sigma, s0, steps, europeanDigitalCall);
    std::cout << std::endl;

    std::cout << "binomial Model (closed form) : ";
    CRR crr = CRR(europeanDigitalCall._t, r, s0, up, down);
    std::cout << crr.pricerClosedFormula(europeanDigitalCall) << std::endl;
    std::cout << std::endl;

    std::cout << "binomial Model (CRR) : ";
    std::cout << crr.pricer(europeanDigitalCall) << std::endl;
    std::cout << std::endl;

    std::cout << "binomial Model (CRR with blacksholes approximation, steps = 100) : ";
    steps = 100;
    CRR crrBs = CRR(steps, europeanDigitalCall._t, r, s0, sigma, true);
    std::cout << crrBs.pricer(europeanDigitalCall);
    std::cout << std::endl;
}

void europeanDigitalPutPricer(double s0,double r, double sigma, EuropeanDigitalPut& europeanDigitalPut, double up, double down)
{
    std::cout << "Pricers for European digital put" << std::endl;
    std::cout << std::endl;

    std::cout << "Monte Carlo Pricer (random paths) : " << std::endl;
    int steps = 15;
    refineRandomPaths(r, sigma, s0, steps, europeanDigitalPut);
    std::cout << std::endl;

    std::cout << "binomial Model (closed form) : ";
    CRR crr = CRR(europeanDigitalPut._t, r, s0, up, down);
    std::cout << crr.pricerClosedFormula(europeanDigitalPut) << std::endl;
    std::cout << std::endl;

    std::cout << "binomial Model (CRR) : ";
    std::cout << crr.pricer(europeanDigitalPut) << std::endl;
    std::cout << std::endl;

    std::cout << "binomial Model (CRR with blacksholes approximation, steps = 100) : ";
    steps = 100;
    CRR crrBs = CRR(steps, europeanDigitalPut._t, r, s0, sigma, true);
    std::cout << crrBs.pricer(europeanDigitalPut);
    std::cout << std::endl;
}

void americanCallPricer(double s0, double r, double sigma, AmericanCall& americanCall, double up, double down)
{
    std::cout << "Pricers for American call" << std::endl;
    std::cout << std::endl;

    std::cout << "binomial Model (CRR) : ";
    CRR crr = CRR(americanCall._t, r, s0, up, down);
    std::cout << crr.pricer(americanCall) << std::endl;
    std::cout << std::endl;

    std::cout << "binomial Model (CRR with blacksholes approximation, steps = 100) : ";
    int steps = 100;
    CRR crrBs = CRR(steps, americanCall._t, r, s0, sigma, true);
    std::cout << crrBs.pricer(americanCall);
    std::cout << std::endl;
}

void americanPutPricer(double s0, double r, double sigma, AmericanPut& americanPut, double up, double down)
{
    std::cout << "Pricers for American put" << std::endl;
    std::cout << std::endl;

    std::cout << "binomial Model (CRR) : ";
    CRR crr = CRR(americanPut._t, r, s0, up, down);
    std::cout << crr.pricer(americanPut) << std::endl;
    std::cout << std::endl;

    std::cout << "binomial Model (CRR with blacksholes approximation, steps = 100) : ";
    int steps = 100;
    CRR crrBs = CRR(steps, americanPut._t, r, s0, sigma, true);
    std::cout << crrBs.pricer(americanPut);
    std::cout << std::endl;
}

void asianCallPricer(double s0, double r, double sigma, AsianCall& asianCall)
{
    std::cout << "Pricers for Asian call" << std::endl;
    std::cout << std::endl;

    std::cout << "Monte Carlo Pricer (random paths) : " << std::endl;
    int steps = 15;
    refineRandomPaths(r, sigma, s0, steps, asianCall);
    std::cout << std::endl;
}

void asianPutPricer(double s0, double r, double sigma, AsianPut& asianPut)
{
    std::cout << "Pricers for Asian Put" << std::endl;
    std::cout << std::endl;

    std::cout << "Monte Carlo Pricer (random paths) : " << std::endl;
    int steps = 15;
    refineRandomPaths(r, sigma, s0, steps, asianPut);
    std::cout << std::endl;
}



int main()
{
    double s0 = 100;
    double K = 101;
    double r = 0.01;
    double sigma = 0.1;
    double maturity = 10;
    
    //for CRR model only
    double up = 1.05;
    double down = 1 / 1.05;
    
    
    EuropeanCall europeanCall(K, maturity);
    EuropeanPut europeanPut(K, maturity);
    EuropeanDigitalCall europeanDigitalCall(K, maturity);
    EuropeanDigitalPut europeanDigitalPut(K, maturity);
    AsianCall asianCall(K, maturity);
    AsianPut asianPut(K, maturity);
    AmericanCall americanCall(K, maturity);
    AmericanPut americanPut(K, maturity);


    bool continuer = true;
    std::string choice = "";
    while (continuer = true)
    {
        char option;
        char type;
        std::cout << "Veuillez choisir l'option : \n Tapez 1 Pour European. \n Tapez 2 pour European Digital \n Tapez 3 pour American \n Tapez 4 pour Asian " << std::endl << std::endl;
        std::cin >> option;
        std::cout << "Veuillez choisir le type de l'option : \n Tapez 1 pour Call \n Tapez 2 pour Put" << std::endl << std::endl;
        std::cin >> type;
        switch (option)
        {
        case '1':
            switch (type)
            {
            case '1':
                europeanCallPricer(s0, r, sigma, europeanCall, up, down);
                std::cout << std::endl << std::endl;
                break;

            case '2':
                europeanPutPricer(s0, r, sigma, europeanPut, up, down);
                std::cout << std::endl << std::endl;
                break;
            default:
                std::cout << "This option doesn't exist :)" << std::endl << std::endl;
                break;
            }

            break;


        case '2':
            switch (type)
            {
            case '1':
                europeanDigitalCallPricer(s0, r, sigma, europeanDigitalCall, up, down);
                std::cout << std::endl << std::endl;
                break;

            case '2':
                europeanDigitalPutPricer(s0, r, sigma, europeanDigitalPut, up, down);
                std::cout << std::endl << std::endl;
                break;
            default:
                std::cout << "This option doesn't exist :)" << std::endl << std::endl;
                break;
            }

            break;


        case '3':
            switch (type)
            {
            case '1':
                americanCallPricer(s0, r, sigma, americanCall, up, down);
                std::cout << std::endl << std::endl;
                break;

            case '2':
                americanPutPricer(s0, r, sigma, americanPut, up, down);
                std::cout << std::endl << std::endl;
                break;
            default:
                std::cout << "This option doesn't exist :)" << std::endl << std::endl;
                break;
            }

            break;


        case '4':
            switch (type)
            {
            case '1':
                asianCallPricer(s0, r, sigma, asianCall);
                std::cout << std::endl << std::endl;
                break;

            case '2':
                asianPutPricer(s0, r, sigma, asianPut);
                std::cout << std::endl << std::endl;
                break;
            default:
                std::cout << "This option doesn't exist :)" << std::endl << std::endl;
                break;
            }

            break;

        default:
            std::cout << "This option doesn't exist :)" << std::endl << std::endl;
            break;

        }
        std::cout << ("Do you want to price another option ? (YES/NO) ") << std::endl;
        std::cin >> choice;
        if (choice == "NO")
        {
            continuer = false;
            break;
        }

    }
    
}
