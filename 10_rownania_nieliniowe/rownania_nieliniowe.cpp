#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#define F1 "-x^3 + 10x + 5"
#define F2 "x^3 + 5x + 3"
#define F3 "-2x^3 +x^2 - 3x + 3"
#define EPSILON 0.00001

// Funkcja x^2 - 2 => x = sqrt2
double FUN_1(double x){
    return (pow(x, 2) - 2);
}

// Funkcja: x^2 - 10, zad. 3
double FUN_KOLOS(double x){
    return(pow(x,2)-10);
}

// Zadanie 3 oraz 1: analiza zbieznosci i miejsce zerowe
double FUN_KOLOS_ZBIEZNOSC(double x){
    return (-0.5*(pow(x,3))+3*pow(x,2) -5);
}

// pochodna z zadania 3 do metody stycznych
double ZBIEZNOSC_INTEGRAL(double x){
    return (-1.5*(pow(x, 2)+6*x));
}

double FUN_KOLOS_INTEGRAL(double x){
    return (-3*pow(x, 2)+4);
}

// func: -x^3 + 10x + 5
double func1(double x){
    //return(-pow(x, 3)+10*x+5);
    return (pow(x, 3) - 20);
}

// integral(func1) : -3x^2 + 10
double integralFunc1(double x){
   // return(-3*pow(x,2)+10);
   return 3*pow(x, 2);
}

// x^3 + 5x + 3
double func2(double x){
    return(pow(x, 3)+5*x+3);
}

// integral: func2
double integralFunc2(double x){
    return(3*pow(x, 2) + 5);
}

// -2x^3 +x^2 - 3x + 3
double func3(double x){
    return(-2*pow(x,3)+ pow(x,2)-3*x+3);
}

// integral : func3
double integralFunc3(double x){
    return(-6*x +2*x - 3);
}

//  x0 - punkt startowy, iterations - iteracje do stopu
// STYCZNE
double tangentMethod(std::string fun, double x0, int iterations){

    if(fun == "f1"){
        // iteration 0
        double *x = new double[iterations]; // wektor iteracji rozwiazania
        x[0] = x0 - (func1(x0)/integralFunc1(x0));

        std::cout<<"Iteration 0. x[i] = "<<x[0]<<" , ";
        std::cout<<", f[x[i]] = "<<func1(x[0])<<std::endl;
        
        // main alghoritm, from i = 1
        for(int i = 1; i < iterations ; i++){
            x[i] = x[i-1] - (func1(x[i-1])/(integralFunc1(x[i-1])));
            std::cout<<"Iteration "<<i<<". x[i] = "<<x[i]<<" , ";
            std::cout<<"f[x[i]] = "<<func1(x[i])<<std::endl;
        }
        return x[iterations];
    }

    else if(fun == "f2"){
        // iteration 0
        double *x = new double[iterations]; // wektor iteracji rozwiazania
        x[0] = x0 - (func2(x0)/integralFunc2(x0));

        std::cout<<"Iteration 0. x[i] = "<<x[0]<<"  , ";
        std::cout<<"f[x[i]] = "<<func2(x[0])<<std::endl;
        
        // main alghoritm, from i = 1
        for(int i = 1; i < iterations ; i++){
            x[i] = x[i-1] - (func2(x[i-1])/(integralFunc2(x[i-1])));
            std::cout<<"Iteration "<<i<<". x[i] = "<<x[i]<<" , ";
            std::cout<<"f[x[i]] = "<<func2(x[i])<<std::endl;
        }
        return x[iterations];
    }

    else if(fun == "f3"){
        // iteration 0
        double *x = new double[iterations]; // wektor iteracji rozwiazania
        x[0] = x0 - (func3(x0)/integralFunc3(x0));

        std::cout<<"Iteration 0. x[i] = "<<x[0]<<"  ,  ";
        std::cout<<"f[x[i]] = "<<func3(x[0])<<std::endl;
        
        // main alghoritm, from i = 1
        for(int i = 1; i < iterations ; i++){
            x[i] = x[i-1] - (func3(x[i-1])/(integralFunc3(x[i-1])));
            std::cout<<"Iteration "<<i<<". x[i] = "<<x[i]<<" , ";
            std::cout<<"f[x[i]] = "<<func3(x[i])<<std::endl;
        }
        return x[iterations];
    }

    else if(fun == "FUN_KOLOS"){
        // iteration 0
        double *x = new double[iterations]; // wektor iteracji rozwiazania
        x[0] = x0 - (FUN_KOLOS(x0)/FUN_KOLOS_INTEGRAL(x0));

        std::cout<<"Iteration 0. x[i] = "<<x[0]<<"  ,  ";
        std::cout<<"f[x[i]] = "<<FUN_KOLOS(x[0])<<std::endl;
        
        // main alghoritm, from i = 1
        for(int i = 1; i < iterations ; i++){
            x[i] = x[i-1] - (FUN_KOLOS(x[i-1])/(FUN_KOLOS_INTEGRAL(x[i-1])));
            std::cout<<"Iteration "<<i<<". x[i] = "<<x[i]<<" , ";
            std::cout<<"f[x[i]] = "<<FUN_KOLOS(x[i])<<std::endl;
        }
        return x[iterations];
    }

    else if(fun =="KOLOS_ZBIEZNOSC"){
        // iteration 0
        double *x = new double[iterations]; // wektor iteracji rozwiazania
        x[0] = x0 - (FUN_KOLOS_ZBIEZNOSC(x0)/ZBIEZNOSC_INTEGRAL(x0));

        std::cout<<"Iteration 0. x[i] = "<<x[0]<<"  ,  ";
        std::cout<<"f[x[i]] = "<<FUN_KOLOS_ZBIEZNOSC(x[0])<<std::endl;
        
        // main alghoritm, from i = 1
        for(int i = 1; i < 10 ; i++){
            x[i] = x[i-1] - (FUN_KOLOS_ZBIEZNOSC(x[i-1])/(ZBIEZNOSC_INTEGRAL(x[i-1])));
            std::cout<<x[i]<<std::endl;
        }
        return x[iterations];
    }

    return -1;
}

// analityczna pochodna dla metody siecznych
double secantIntegral(std::string fun, double xnow, double xprev){
    if(fun == "f1"){
        return (func1(xnow) - func1(xprev))/(xnow - xprev);
    }
    else if(fun == "f2"){
        return(func2(xnow) - func2(xprev))/(xnow - xprev);
    }
    else if(fun == "f3"){
        return(func3(xnow) - func3(xprev))/(xnow - xprev);
    }
    else if(fun == "FUN_KOLOS"){
        return (FUN_KOLOS(xnow) - FUN_KOLOS(xprev))/(xnow - xprev);
    }
    else if(fun == "KOLOS_ZBIEZNOSC"){
        return (FUN_KOLOS_ZBIEZNOSC(xnow) - FUN_KOLOS_ZBIEZNOSC(xprev))/(xnow - xprev);
    }
}

// SIECZNE
// metoda siecznych. x0 - punkt startowy, iterations - iteracje do stopu
double secantMethod(std::string fun, double x0, int iterations){
    if(fun == "f1"){
        double *x = new double[iterations];
 
        x[0] = x0-0.1 - func1(x0-0.1)/secantIntegral(fun, x0-0.1, x0);

        std::cout<<"Iteration 0. x[i] = "<<x[0]<<" , ";
        std::cout<<"f[x[i]] = "<<func1(x[0])<<std::endl;

        for(int i = 1; i < iterations; i++){
            if(i == 1){
                x[i] = x[0] - func1(x[0])/secantIntegral(fun, x[0], x0-0.1);
            }
            else{
            x[i] = x[i-1] - func1(x[i-1])/secantIntegral(fun, x[i-1], x[i-2]);
            }
            std::cout<<"Iteration "<<i<<". x[i] = "<<x[i]<<" , ";
            std::cout<<"f[x[i]] = "<<func1(x[i])<<std::endl;
        }
    }

    else if (fun == "f2"){
        double *x = new double[iterations];
 
        x[0] = x0-0.1 - func2(x0-0.1)/secantIntegral(fun, x0-0.1, x0);

        std::cout<<"Iteration 0. x[i] = "<<x[0]<<"  ,  ";
        std::cout<<"f[x[i]] = "<<func2(x[0])<<std::endl;

        for(int i = 1; i < iterations; i++){
            if(i == 1){
                x[i] = x[0] - func2(x[0])/secantIntegral(fun, x[0], x0-0.1);
            }
            else{
            x[i] = x[i-1] - func2(x[i-1])/secantIntegral(fun, x[i-1], x[i-2]);
            }
            std::cout<<"Iteration "<<i<<". x[i] = "<<x[i]<<" , ";
            std::cout<<"f[x[i]] = "<<func2(x[i])<<std::endl;
        }
    }

    else if(fun == "f3"){
        double *x = new double[iterations];
 
        x[0] = x0-0.1 - func3(x0-0.1)/secantIntegral(fun, x0-0.1, x0);

        std::cout<<"Iteration 0. x[i] = "<<x[0]<<"  ,  ";
        std::cout<<"f[x[i]] = "<<func3(x[0])<<std::endl;

        for(int i = 1; i < iterations; i++){
            if(i == 1){
                x[i] = x[0] - func3(x[0])/secantIntegral(fun, x[0], x0-0.1);
            }
            else{
            x[i] = x[i-1] - func3(x[i-1])/secantIntegral(fun, x[i-1], x[i-2]);
            }
            std::cout<<"Iteration "<<i<<". x[i] = "<<x[i]<<" , ";
            std::cout<<"f[x[i]] = "<<func3(x[i])<<std::endl;
        }
    }

    else if(fun == "FUN_KOLOS"){
        double *x = new double[iterations];
        
        //std::cout<<"HEEELLOO"<<secantIntegral(fun, x0-0.1, x0)<<std::endl;
        x[0] = x0-0.1 - FUN_KOLOS(x0-0.1)/secantIntegral(fun, x0-0.1, x0);

        std::cout<<"Iteration 0. x[i] = "<<x[0]<<"  ,  ";
        std::cout<<"f[x[i]] = "<<FUN_KOLOS(x[0])<<std::endl;

        int i = 0;
        // Warunek stopu: y[i] < EPSILON
        while(FUN_KOLOS(x[i])>EPSILON){
            i++;
            if(i == 1){
                x[i] = x[0] - FUN_KOLOS(x[0])/secantIntegral(fun, x[0], x0-0.1);
            }
            else{
            x[i] = x[i-1] - FUN_KOLOS(x[i-1])/secantIntegral(fun, x[i-1], x[i-2]);
            }
            std::cout<<"Iteration "<<i<<". x[i] = "<<x[i]<<" , ";
            std::cout<<"f[x[i]] = "<<FUN_KOLOS(x[i])<<std::endl;
        }
    }

    else if(fun == "KOLOS_ZBIEZNOSC"){
        double *x = new double[iterations];

        x[0] = x0-0.1 - FUN_KOLOS_ZBIEZNOSC(x0-0.1)/secantIntegral(fun, x0-0.1, x0);

        std::cout<<"Iteration 0. x[i] = "<<x[0]<<"  ,  ";
        std::cout<<"f[x[i]] = "<<FUN_KOLOS_ZBIEZNOSC(x[0])<<std::endl;
        // Warunek stopu: y[i] < EPSILON
        for(int i = 1; i < 10; i++){
            if(i == 1){
                x[i] = x[0] - FUN_KOLOS_ZBIEZNOSC(x[0])/secantIntegral(fun, x[0], x0-0.1);
            }
            else{
            x[i] = x[i-1] - FUN_KOLOS_ZBIEZNOSC(x[i-1])/secantIntegral(fun, x[i-1], x[i-2]);
            }
            std::cout<<x[i]<<std::endl;
        }
    }

    return -1;
}

int main(){
    // std::cout<<"Solving: "<<F1<<std::endl;
    // std::cout<<"Tangent solve: "<<std::endl;
    // tangentMethod("f1", 6,5);
    // std::cout<<"--------------------"<<std::endl;

    // std::cout<<"Secant solve: "<<std::endl;
    // secantMethod("f1", 6, 5);

    // std::cout<<"--------------------"<<std::endl;
    // std::cout<<"--------------------"<<std::endl;

    // std::cout<<"Solving: "<<F2<<std::endl;
    // std::cout<<"Secant solve: "<<std::endl;
    // secantMethod("f2", 6, 8);
    // std::cout<<"--------------------"<<std::endl;
    // std::cout<<"Tangent solve: "<<std::endl;
    // tangentMethod("f2", 6, 8);

    //  std::cout<<"--------------------"<<std::endl;
    // std::cout<<"--------------------"<<std::endl;

    // std::cout<<"Solving: "<<F3<<std::endl;
    // std::cout<<"Secant solve: "<<std::endl;
    // secantMethod("f3", 6, 8);
    // std::cout<<"--------------------"<<std::endl;
    // std::cout<<"Tangent solve: "<<std::endl;
    // tangentMethod("f3", 6, 8);

    /*
    // ZADANIE 1
    // PUNKT STARTOWY: 3, 4 ITERACJE
    std::cout<<"Punkt x = 7 przedzialu jako punkt poczatkowy."<<std::endl;
    std::cout<<"Rozwiazanie metoda stycznych:"<<std::endl;
    tangentMethod("KOLOS_ZBIEZNOSC", 7, 4);
    */
    // ZADANIE 2
    // std::cout<<"Solving: x^2 - 10"<<std::endl;
    // std::cout<<"Tangent solve: "<<std::endl;
    // std::cout<<secantMethod("FUN_KOLOS", -5, 100)<<std::endl;

    // // BADANIE ZBIEZNOSCI
    // // 100 iteracji - nieuzywany parametr, bo zmodyfikowano funkcje tak, by bylo 10 iteracji
    // std::cout<<"Zbieznosc dla 10 iteracji dla siecznych: "<<std::endl;
    // secantMethod("KOLOS_ZBIEZNOSC", 5, 100);

    // std::cout<<"Zbieznosc dla 10 iteracji dla stycznych: "<<std::endl;
    // tangentMethod("KOLOS_ZBIEZNOSC", 5, 100);
    tangentMethod("f1", 2, 10);
    
    system("pause");
    return 0;
}