#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#define F1 "cos(x^3-2x)"
#define F2 "sin(x^2)"
#define F3 "x^3 - 5x + 3"
#define EPSILON 0.01

// Funkcja do badania zbieznosci z zadania 3
double FUN_KOLOS(double x){
    return (-0.5*(pow(x,3))+3*pow(x,2) -5);
}

// func: cos(x^3-2x)
double func1(double x){
    return cos(pow(x, 3)-2*x);
}

// sin(x^2)
double func2(double x){
    return sin(pow(x,2));
}

// tan(x^3+2)
double func3(double x){
    return pow(x,3)-5*x+3;
}


// FALSZYWA LINIA
// metoda falszywej linii, przedzial <a, b>, funckja fun
double regulaFalsi(std::string fun, double a, double b){
    int i = 0;
    double x0 = a - (func1(a)*(b-a))/(func1(b) - func1(a));
    if(fun=="f1"){
        while(fabs(func1(x0))>EPSILON){ // warunek stopu: f(xi) < 0.01
        std::cout<<"iteration: "<<i<<" :   : a = "<<a<<" :   : b = "<<b<<" :   : f(a) = "<<std::setprecision(5)<<func1(a)<<" :   : f(b) = "<<func1(b);
        std::cout<<" :   : x0 = "<<x0<<" :   : f(x0) = "<<func1(x0)<<" :   : f(a)*f(x0) = "<<func1(a)*func1(x0)<<std::endl;
            if(func1(a)*func1(x0)<0){
                b = x0;
            }
            else{
                a = x0;
            }
            x0 = a - (func1(a)*(b-a))/(func1(b) - func1(a));
           
            i++;
        }
        std::cout<<"iteration: "<<i<<" :   : a = "<<a<<" :   : b = "<<b<<" :   : f(a) = "<<std::setprecision(5)<<func1(a)<<" :   : f(b) = "<<func1(b);
        std::cout<<" :   : x0 = "<<x0<<" :   : f(x0) = "<<func1(x0)<<" :   : f(a)*f(x0) = "<<func1(a)*func1(x0)<<std::endl;
        return x0;
    }

    else if(fun == "f2"){
        while(fabs(func2(x0))>EPSILON){ // warunek stopu: f(xi) < 0.01
        std::cout<<"iteration: "<<i<<" :   : a = "<<a<<" :   : b = "<<b<<" :   : f(a) = "<<std::setprecision(5)<<func2(a)<<" :   : f(b) = "<<func2(b);
        std::cout<<" :   : x0 = "<<x0<<" :   : f(x0) = "<<func2(x0)<<" :   : f(a)*f(x0) = "<<func2(a)*func2(x0)<<std::endl;
            if(func2(a)*func2(x0)<0){
                b = x0;
            }
            else{
                a = x0;
            }
            x0 = a - (func2(a)*(b-a))/(func2(b) - func2(a));
           
            i++;
        }
        std::cout<<"iteration: "<<i<<" :   : a = "<<a<<" :   : b = "<<b<<" :   : f(a) = "<<std::setprecision(5)<<func2(a)<<" :   : f(b) = "<<func2(b);
        std::cout<<" :   : x0 = "<<x0<<" :   : f(x0) = "<<func2(x0)<<" :   : f(a)*f(x0) = "<<func2(a)*func2(x0)<<std::endl;
        return x0;
    }

    else if(fun == "f3"){
        while(fabs(func3(x0))>EPSILON){ // warunek stopu: f(xi) < 0.01
        std::cout<<"iteration: "<<i<<" :   : a = "<<a<<" :   : b = "<<b<<" :   : f(a) = "<<std::setprecision(5)<<func3(a)<<" :   : f(b) = "<<func3(b);
        std::cout<<" :   : x0 = "<<x0<<" :   : f(x0) = "<<func3(x0)<<" :   : f(a)*f(x0) = "<<func3(a)*func3(x0)<<std::endl;
            if(func3(a)*func3(x0)<0){
                b = x0;
            }
            else{
                a = x0;
            }
            x0 = a - (func3(a)*(b-a))/(func3(b) - func3(a));
           
            i++;
        }
        std::cout<<"iteration: "<<i<<" :   : a = "<<a<<" :   : b = "<<b<<" :   : f(a) = "<<std::setprecision(5)<<func3(a)<<" :   : f(b) = "<<func3(b);
        std::cout<<" :   : x0 = "<<x0<<" :   : f(x0) = "<<func3(x0)<<" :   : f(a)*f(x0) = "<<func3(a)*func3(x0)<<std::endl;
        return x0;
    }

    else if(fun == "FUN_KOLOS"){
        for(i; i < 10; i++){ // warunek stopu: f(xi) < 0.01
            if(FUN_KOLOS(a)*FUN_KOLOS(x0)<0){
                b = x0;
            }
            else{
                a = x0;
            }
            x0 = a - (FUN_KOLOS(a)*(b-a))/(FUN_KOLOS(b) - FUN_KOLOS(a));
           
            std::cout<<x0<<std::endl;
        }
        return x0;
    }

    else return -1;
}

// METODA BISEKCJI
// x0 i x1 takie, ze f(x0)*f(x1) < 0 (miedzy nimi jest miejsce zerowe)
double bisection(std::string fun, double a, double b){
    int i = 0;
    double x0 = (a+b)/2;
    if(fun=="f1"){
        while(fabs(func1(x0))>EPSILON){ // warunek stopu: f(xi) < 0.01
        std::cout<<"iteration: "<<i<<" :   : a = "<<a<<" :   : b = "<<b<<" :   : f(a) = "<<std::setprecision(5)<<func1(a)<<" :   : f(b) = "<<func1(b);
        std::cout<<" :   : x0 = "<<x0<<" :   : f(x0) = "<<func1(x0)<<" :   : f(a)*f(x0) = "<<func1(a)*func1(x0)<<std::endl;
            if(func1(a)*func1(x0)<0){
                b = x0;
            }
            else{
                a = x0;
            }
            x0 = (a+b)/2;
           
            i++;
        }
        std::cout<<"iteration: "<<i<<" :   : a = "<<a<<" :   : b = "<<b<<" :   : f(a) = "<<std::setprecision(5)<<func1(a)<<" :   : f(b) = "<<func1(b);
        std::cout<<" :   : x0 = "<<x0<<" :   : f(x0) = "<<func1(x0)<<" :   : f(a)*f(x0) = "<<func1(a)*func1(x0)<<std::endl;
        return x0;
    }

    else if(fun=="f2"){
        while(fabs(func2(x0))>EPSILON){ // warunek stopu: f(xi) < 0.01
        std::cout<<"iteration: "<<i<<" :   : a = "<<a<<" :   : b = "<<b<<" :   : f(a) = "<<std::setprecision(5)<<func2(a)<<" :   : f(b) = "<<func2(b);
        std::cout<<" :   : x0 = "<<x0<<" :   : f(x0) = "<<func2(x0)<<" :   : f(a)*f(x0) = "<<func2(a)*func2(x0)<<std::endl;
            if(func2(a)*func2(x0)<0){
                b = x0;
            }
            else{
                a = x0;
            }
            x0 = (a+b)/2;
           
            i++;
        }
        std::cout<<"iteration: "<<i<<" :   : a = "<<a<<" :   : b = "<<b<<" :   : f(a) = "<<std::setprecision(5)<<func2(a)<<" :   : f(b) = "<<func2(b);
        std::cout<<" :   : x0 = "<<x0<<" :   : f(x0) = "<<func2(x0)<<" :   : f(a)*f(x0) = "<<func2(a)*func2(x0)<<std::endl;
        return x0;
    }

    else if(fun=="f3"){
        while(fabs(func3(x0))>EPSILON){ // warunek stopu: f(xi) < 0.01
        std::cout<<"iteration: "<<i<<" :   : a = "<<a<<" :   : b = "<<b<<" :   : f(a) = "<<std::setprecision(5)<<func3(a)<<" :   : f(b) = "<<func3(b);
        std::cout<<" :   : x0 = "<<x0<<" :   : f(x0) = "<<func3(x0)<<" :   : f(a)*f(x0) = "<<func3(a)*func3(x0)<<std::endl;
            if(func3(a)*func3(x0)<0){
                b = x0;
            }
            else{
                a = x0;
            }
            x0 = (a+b)/2;
           
            i++;
        }
        std::cout<<"iteration: "<<i<<" :   : a = "<<a<<" :   : b = "<<b<<" :   : f(a) = "<<std::setprecision(5)<<func3(a)<<" :   : f(b) = "<<func3(b);
        std::cout<<" :   : x0 = "<<x0<<" :   : f(x0) = "<<func3(x0)<<" :   : f(a)*f(x0) = "<<func3(a)*func3(x0)<<std::endl;
        return x0;
    }

    else if(fun == "FUN_KOLOS"){
        for(int i = 0; i < 10; i++){ // warunek stopu: f(xi) < 0.01
            if(FUN_KOLOS(a)*FUN_KOLOS(x0)<0){
                b = x0;
            }
            else{
                a = x0;
            }
            x0 = (a+b)/2;
           
            std::cout<<x0<<std::endl;
        }
        return x0;
    }

    else
        return -1;

}

int main(){
    // std::cout<<"Solving: "<<F1<<std::endl;
    // std::cout<<"Bisection solve: "<<std::endl;
    // bisection("f1", 0, 2);
    // std::cout<<"--------------------"<<std::endl;

    // std::cout<<"Regula falsi solve: "<<std::endl;
    // regulaFalsi("f1", 0, 2);
    // std::cout<<"--------------------"<<std::endl;

    // std::cout<<"Solving: "<<F2<<std::endl;
    // std::cout<<"Bisection solve: "<<std::endl;
    // bisection("f2", 1, 2);
    // std::cout<<"--------------------"<<std::endl;

    // std::cout<<"Regula falsi solve: "<<std::endl;
    // regulaFalsi("f2", 1, 2);
    // std::cout<<"--------------------"<<std::endl;

    // std::cout<<"Solving: "<<F3<<std::endl;
    // std::cout<<"Bisection solve: "<<std::endl;
    // bisection("f3", 1, 2);
    // std::cout<<"--------------------"<<std::endl;

    // std::cout<<"Regula falsi solve: "<<std::endl;
    // regulaFalsi("f3", 1, 2);
    // std::cout<<"--------------------"<<std::endl;

    // Zbieznosc dla bisekcji
    std::cout<<"Zbieznosc dla 10 iteracji dla bisekcji: "<<std::endl;
    bisection("FUN_KOLOS", 5, 10);

    // Zbieznosc dla regula falsi
    std::cout<<"Zbieznosc dla 10 iteracji dla falszywej linii: "<<std::endl;
    regulaFalsi("FUN_KOLOS", 5, 10);

    system("pause");
    return 0;
}