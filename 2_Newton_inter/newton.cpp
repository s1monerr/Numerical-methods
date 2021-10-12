#include <iostream>
#include <fstream>
#include <iomanip>

long double differ(long double, long double, long double, long double);
long double countPolynomial(long double, long double, long double, long double *);
void printResults(int , long double *, long double *, long double, long double);

long double differ(long double y1, long double y2, long double xk, long double x0){ 
    return (y2 - y1)/(xk - x0);
}

long double countPolynomial(long double factor, long double p, long double index, long double *x){ // count polynomial sum for each element. p is interpolated point, x are nodes
    long double result = factor; // single element sum. Start -> factor of index
    for(int i = 0; i < index; i++){
        result *= (p - x[i]); // ex. index = 2: b[2](x-x0)(x-x1)
    }

    return result;
}

void printResults(int count, long double *x, long double *y, long double p, long double result){
std::cout<<"RESULTS:"<<std::endl<< "Number of nodes is "<<count<<std::endl;

        for (int i = 0; i<count; i++){
            std::cout<<"Node "<<i+1<<std::setprecision(5)<<" : ("<<x[i]<<", "<<y[i]<<")"<<std::endl;
        }

        std::cout<<std::endl;
        std::cout<<"Interpolated point: x = "<<std::setprecision(5)<<p<<" : f(x) ~ "<<result<<std::endl;
        std::cout<<std::endl;
}


int main(){

    // INPUT
    std::fstream read("data_newton.txt");

    int count = 0; // node counter

    if(read.is_open()){  // if file is opened correctly

        read >> count; // read number of nodes

        long double *x = new long double[count];
        long double *y = new long double[count]; // dynamically allocated arrays

        for(int i = 0;i<count; i++){ // read nodes and values
            read >> x[i];
            read >> y[i];
        }

        long double *factors = new long double[count]; // main array of polynomial factors
        long double *tab = new long double[count]; // temp array of polynomial factors

        for(int i = 0; i < count; i++){
            tab[i] = y[i]; // first iteration - tab values are node values
        }


        // *** MAIN FACTORS LOOP - COUNTING FACTOR VALUES *** //

        for(int i = 1; i < count; i++){ // main loop
            for(int j = 0; j<=count - i; j++){ // small loop - arrays are overwritten. Counting factors 
                tab[j] = differ(tab[j],tab[j+1], x[j+i],x[j]); // count the difference. x[i+j] is xk in formula, x[j] is x0 in formula
            }
            factors[i] = tab[0]; // main factors array -> tab[0] -> first value from temp array
        }

        factors[0] = y[0]; // first factor is first node value

        long double p; // interpolation pointt from user
        std::cout<<"Put in interpolation point: "<<std::endl;
        std::cin>>p;
        long double result = 0.0; // interpolation result variable

        // COUNT INTERPOLATION SUM
        for(int i = 0; i<count; i++){
            result += countPolynomial(factors[i], p, i, x);
        }


        // PRINTING RESULTS
        std::cout<<"POLYNOMIAL FACTORS: b =  "<<std::endl;
        for(int i = 0; i<count; i++){
            std::cout<<"b["<<i<<"] = "<<std::setprecision(2)<<factors[i]<<std::endl;
        }

        printResults(count,x,y,p,result);

        delete[]tab;
        delete[] factors;
        delete[] x;
        delete[] y;

        system("pause");
    }
    
    return 0;
}