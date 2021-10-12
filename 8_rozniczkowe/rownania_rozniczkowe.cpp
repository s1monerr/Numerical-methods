#include <iostream>
#include <iomanip>
#include <cmath>

#define FUN1 "x^2+y"
#define FUN2 "x+y"

double func(double x, double y){ // x^2 + y
    return x*x + y;
}

double func2(double x, double y){ // x + y
    return x+y;
}

double FUN_KOLOS(double y){
    return -0.005*(y-50);
}

double euler(std::string fun, double a, double b, int n, double begin, double node){ // begin - warunek poczatkowy, node - punkt dla ktorego sie liczy
    double h = (b-a)/n;
    double *x = new double[n+1];
    double *y = new double[n+1]; // n+1 iterations

    if(fun == "x^2+y"){
        int i = 0;
        // Euler iteration
        while(true){
            if(i != 0){
                x[i] = x[i-1] + h;
                y[i] = y[i-1]+h*func(x[i-1], y[i-1]);
            }

            else if(i == 0){
                x[i] = 0;
                y[i] = begin;
            }

            if(i==n){
                break;
            }
            i++;
        }
        double toReturn = y[n];
        delete[] x;
        delete[] y;
        return toReturn;
    }

    else if(fun == "x+y"){
        int i = 0;
        // Euler iteration
        while(true){
            if(i != 0){
                x[i] = x[i-1] + h;
                y[i] = y[i-1]+h*func2(x[i-1], y[i-1]);
            }

            else if(i == 0){
                x[i] = 0;
                y[i] = begin;
            }

            if(i==n){
                break;
            }
            i++;
        }
        double toReturn = y[n];
        delete[] x;
        delete[] y;
        return toReturn;
    }

    else if(fun == "FUN_KOLOS"){
        int i = 0;
        // Euler iteration
        while(true){
            if(i != 0){
                x[i] = x[i-1] + h;
                y[i] = y[i-1]+h*FUN_KOLOS(y[i-1]);
            }

            else if(i == 0){
                x[i] = 0;
                y[i] = begin;
            }

            if(i==n){
                break;
            }
            i++;
        }
        double toReturn = y[n];
        delete[] x;
        delete[] y;
        return toReturn;
    }

    else if(fun == "x+y"){
        int i = 0;
        // Euler iteration
        while(true){
            if(i != 0){
                x[i] = x[i-1] + h;
                y[i] = y[i-1]+h*func2(x[i-1], y[i-1]);
            }

            else if(i == 0){
                x[i] = 0;
                y[i] = begin;
            }

            if(i==n){
                break;
            }
            i++;
        }
        double toReturn = y[n];
        delete[] x;
        delete[] y;
        return toReturn;
    }

    else  // wrong function
        return -1;
}

double RKfunc_1(double x, double y, double h){
    double k1 = func(x,y);
    double k2 = func(x+h, y+h*k1);
    return (k1+k2)/2;
}

double RKfunc_2(double x, double y, double h){
    double k1 = func2(x,y);
    double k2 = func2(x+h, y+h*k1);
    return (k1+k2)/2;
}

double RKfunc4_1(double x, double y, double h){
    double k1 = func(x, y);
    double k2 = func(x+h/2, y+h*k1/2);
    double k3 = func(x+h/2, y+h*k2/2);
    double k4 = func(x+h, y+h*k3);
    //std::cout<<"HERERE "<<(k1+2*k2+2*k3+k4)/6<<std::endl;
    return (k1+2*k2+2*k3+k4)/6;
}

double RKfunc4_2(double x, double y, double h){
    double k1 = func2(x, y);
    double k2 = func2(x+h/2, y+h*k1/2);
    double k3 = func2(x+h/2, y+h*k2/2);
    double k4 = func2(x+h, y+h*k3);
    return (k1+2*k2+2*k3+k4)/6;
}

double RK2(std::string fun, double a, double b, int n, double begin, double node){ // RungeKutty 2 rzedu
    double h = (b-a)/n;
    double *x = new double[n+1];
    double *y = new double[n+1];

    if(fun == "x^2+y"){
        int i = 0;

        while(true){
            if(i != 0){
                x[i] = x[i-1] + h;
                y[i] = y[i-1]+h*RKfunc_1(x[i-1],y[i-1],h);
            }

            else if(i == 0){
                x[i] = 0;
                y[i] = begin;
            }

            if(i == n){
                break;
            }
            i++;
        }
        double toReturn = y[n];
        delete[] x;
        delete[] y;
        return toReturn;
    }
    
    else if(fun == "x+y"){
        int i = 0;
        while(true){
            if(i != 0){
                x[i] = x[i-1] + h;
                y[i] = y[i-1]+h*RKfunc_2(x[i-1],y[i-1],h);
            }

            else if(i == 0){
                x[i] = 0;
                y[i] = begin;
            }
            if(i == n){
                break;
            }
            i++;
        }
        double toReturn = y[n];
        delete[] x;
        delete[] y;
        return toReturn;       
    }

    else  // wrong function
        return -1;
}

double RK4(std::string fun, double a, double b, int n, double begin, double node){ // RungeKutty 2 rzedu
    double h = (b-a)/n;
    double *x = new double[n+1];
    double *y = new double[n+1];

    if(fun=="x^2+y"){
        int i = 0;
        while(true){
            if(i != 0){
                x[i] = x[i-1] + h;
                y[i] = y[i-1]+h*RKfunc4_1(x[i-1],y[i-1],h);
            }

            else if(i == 0){
                x[i] = 0;
                y[i] = begin;
            }
            if(i == n){
                break;
            }
            i++;
        }
        double toReturn = y[n];
        delete[] x;
        delete[] y;
        return toReturn;
    }

    else if(fun == "x+y"){
        int i = 0;
        while(true){
            if(i != 0){
                x[i] = x[i-1] + h;
                y[i] = y[i-1]+h*RKfunc4_2(x[i-1],y[i-1],h);
            }

            else if(i == 0){
                x[i] = 0;
                y[i] = begin;
            }
            if(i == n){
                break;
            }
            i++;
        }
        double toReturn = y[n];
        delete[] x;
        delete[] y;
        return toReturn;
    }
}

void printInfo(std::string fun, int n, double val, double a, double b){
    std::cout<<"*************************"<<std::endl;
    std::cout<<"Solving: ' = "<<fun<<std::endl<<"with terms: y(0) = "<<std::setprecision(5)<<val<<", step n = "<<n<<", h = "<<(a+b)/n<<std::endl;
    std::cout<<"Calculating solution: y'(x) for x = "<<b<<std::endl;
}

int main(){
    // printInfo(FUN1, 3, 0.1, 0, 0.3);
    // std::cout<<"Euler result: ";
    // std::cout<<euler(FUN1, 0, 0.3, 3, 0.1, 0.3)<<std::endl;
    // std::cout<<"RK2 result: ";
    // std::cout<<RK2(FUN1, 0, 0.3, 3, 0.1, 0.3)<<std::endl;
    // std::cout<<"RK4 result: ";
    // std::cout<<RK4(FUN1, 0, 0.3, 3, 0.1, 0.3)<<std::endl<<std::endl;

    // printInfo(FUN1, 10, 0.1, 0, 1);
    // std::cout<<"Euler result: "<<std::endl;
    // std::cout<<euler(FUN1, 0, 1, 10, 0.1, 1)<<std::endl;
    // std::cout<<"RK2 result: "<<std::endl;
    // std::cout<<RK2(FUN1, 0, 1, 10, 0.1, 1)<<std::endl;
    // std::cout<<"RK4 result: "<<std::endl;
    // std::cout<<RK4(FUN1, 0, 1, 10, 0.1, 1)<<std::endl;

    // printInfo(FUN2, 10, 0.1, 0, 1);
    // std::cout<<"Euler result: "<<std::endl;
    // std::cout<<euler(FUN2, 0, 1, 10, 0.1, 1)<<std::endl;
    // std::cout<<"RK2 result: "<<std::endl;
    // std::cout<<RK2(FUN2, 0, 1, 10, 0.1, 1)<<std::endl;
    // std::cout<<"RK4 result: "<<std::endl;
    // std::cout<<RK4(FUN2, 0, 1, 10, 0.1, 1)<<std::endl;

    std::cout<<"Rozwiazanie rownania metoda Eulera: "<<euler("FUN_KOLOS", 0, 60, 60, 500, 60)<<std::endl;

    // ponizej 100 kelwinow
    // iteracja po i - po kazdej sekundzie
    // wynik: 439/440 sekund
    for(int i = 0; i < 500; i++){
    std::cout<<"Euler solve: i = "<<i<<",  "<<euler("FUN_KOLOS", 0, i, i, 500, i)<<std::endl;
    }

    system("pause");
    return 0;
}