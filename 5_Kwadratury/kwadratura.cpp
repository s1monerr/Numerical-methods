#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

#define FUNCTION "expand"

double func(double x){ //x^2 + 2x + 5
    double sum = 0.0;
    sum += pow(x,2);
    sum += 2*x;
    sum += 5;
    return sum;
}

double rectangleFormula(std::string fun, int n, double a, double b){ // fun - which function, n - number of sections, a, b - range
    if(fun == "sin"){
        double sum = 0.0;
        double s = (b-a)/n; // next iteration break
        for (int i = 0; i < n; i++){
            double x = a + 0.5*s;
            sum += sin(x);
            a += s;
        }
        return sum*s;
    }

    else if(fun == "expand"){
        double sum = 0.0;
        double s = (b-a)/n; // next iteration break
        for (int i = 0; i < n; i++){
            double x = a + 0.5*s;
            sum += exp(x);
            a += s;
        }
        return sum*s;
    }

    else if(fun == "function"){
        double sum = 0.0;
        double s = (b-a)/n; // next iteration break
        for (int i = 0; i < n; i++){
            double x = a + 0.5*s;
            sum += func(x);
            a += s;
        }
        return sum*s;
    }

    else    
        return -1;
}

float trapezFormula(std::string fun, int n, float a, float b){
    //double diff = (b-a)/2;
    double jump = (b-a)/n; // next iteration break
    double x = a + jump; // b in formula - for each small range
    if(fun == "sin"){
        double sum = 0.0;
        for (int i = 0; i < n; i++){
            double multi = (x-a)/2;
            sum += multi*sin(x);
            sum += multi*sin(a);
            x += jump; // next range
            a += jump;
        }
        return sum;
    }

    else if(fun == "expand"){
        double sum = 0.0;
        for (int i = 0; i < n; i++){
            double multi = (x-a)/2;
            sum += multi*exp(x);
            sum += multi*exp(a);
            a += jump;
            x += jump;
        }
        return sum;
    }

    else if(fun =="function"){
        double sum = 0.0;
        for (int i = 0; i < n; i++){
            double multi = (x-a)/2;
            sum += multi*func(x);
            sum += multi*func(a);
            a += jump;
            x += jump;
        }
        return sum;
    }

    else 
        return -1;
}

double simpsonFormula(std::string fun, int n, float a, float b){
    double jump = (b - a)/n;
    double x = a + jump; // b for each small range
    double sum = 0.0;
    if(fun == "sin"){
        for(int i = 0; i < n; i++){
        sum += ((x-a)/6)*(sin(a)+4*(sin((a+x)/2))+sin(x));
        a += jump; // next range
        x += jump;
        }
        return sum;
    }
    
    else if(fun == "expand"){
        for(int i = 0; i < n; i++){
        sum += ((x-a)/6)*(exp(a)+4*(exp((a+x)/2))+exp(x));
        a += jump; // next range
        x += jump;
        }
        return sum;
    }

    else if(fun == "function"){
        for(int i = 0; i < n; i++){
        sum += ((x-a)/6)*(func(a)+4*(func((a+x)/2))+func(x));
        a += jump; // next range
        x += jump;
        }
        return sum;
    }

    else    
        return -1;
}

void printResults(std::string fun, double result, double n, double a, double b){
    std::cout<<"Integrated function: y = ";
    if(fun=="sin")
        std::cout<<"sin(x)"<<std::endl;
    else if(fun=="function"){
        std::cout<<"x^2 + 2x + 5"<<std::endl;
    }
    else if(fun=="expand"){
        std::cout<<"exp(x)"<<std::endl;
    }

    std::cout<<"Integral: range <"<<a<<" ; "<<b<<">,  n = "<<n<<std::endl;
    std::cout<<"Result: y ~ "<<std::setprecision(6)<<result;
    std::cout<<std::endl;
}

int main(){
    const int n = 10; // number of small ranges
    const double a = 0.5; // <a,b>
    const double b = 2.5;
    double rectangle = rectangleFormula(FUNCTION, n, a, b);
    double trapez = trapezFormula(FUNCTION, n, a, b);
    double simpson = simpsonFormula(FUNCTION, n, a, b);

    std::cout<<"-------------------------"<<std::endl;
    std::cout<<"         RESULTS         "<<std::endl;
    std::cout<<"-------------------------"<<std::endl;

    std::cout<<"Rectangle formula: "<<std::endl;
    printResults(FUNCTION, rectangle, n, a, b);
    std::cout<<std::endl;

    std::cout<<"Trapezium formula: "<<std::endl;
    printResults(FUNCTION, trapez, n, a, b);
    std::cout<<std::endl;

    std::cout<<"Simpson formula: "<<std::endl;
    printResults(FUNCTION, simpson, n, a, b);

    system("pause");
    return 0;
}