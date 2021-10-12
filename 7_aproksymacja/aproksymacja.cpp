#include <iostream>
#include <iomanip>
#include <cmath>

#define COUNT 8 // number of nodes
#define DEGREE 1 // polynomial degree
#define EPSILON 0.0000001 // gauss equation epsilon


template <typename T> void swap(T& a, T& b) {
	T buf = a;
	a = b;
	b = buf;
}


void printResults(int deg, int count, double *nodes, double *values, double *results, double *aprox){    
    std::cout<<"RESULTS: "<<std::endl<<std::endl;;
    std::cout<<"Number of nodes: "<<count<<std::endl;
    for(int i = 0; i<count; i++){
        std::cout<<"Node "<<i<<": "<<"("<<nodes[i]<<", "<<values[i]<<")"<<std::endl;
    }

    for(int i = 0; i < deg+1; i++){
        std::cout<<"a"<<i<<" = "<<std::setprecision(4)<<results[i]<<std::endl;
    }

    std::cout<<"Aproximated values in nodes:"<<std::endl;
    for (int i = 0; i < count; i++){
        std::cout<<"f("<<nodes[i]<<")"<<" = "<<aprox[i]<<std::endl;
    }
    
}

// calculate aproximated values
void calcAproximate(int count, int deg, double *nodes, double *results, double *aproxValues){
    for(int i = 0; i < count; i++){
        aproxValues[i] = results[0]+results[1]*nodes[i];
    }
}

// degree - stopien wielomianu, weigth - funkcja wagowa, values - f(xi), vectorG - Gkj, vectorF - Fk
void aproximate(int count, int degree, double weigth, double *nodes, double *values, double **vectorG, double *vectorF){
    // count vectorG
    for(int i = 0; i < degree+1; i++){ // degree+1 - ilosc pochodnych dla stopnia wielomianu aproksymacyjnego
        for(int j = 0; j < degree+1; j++){
                for(int m = 0; m < count; m++){
                    vectorG[i][j] += pow(nodes[m],i)*pow(nodes[m], j)*weigth;
                }
        }
    }

    // count vectorF
    for(int i = 0; i < degree+1; i++){ // degree+1 - ilosc pochodnych dla stopnia wielomianu aproksymacyjnego
                for(int m = 0; m < count; m++){
                    vectorF[i] += pow(nodes[m],i)*values[m]*weigth;
                }
    }
}



// GAUSS
bool gaussMatrix(double **factors, int n, int begin){

    if(begin+1==n){ // recursion break condition - entire matrix is done
       return true; 
    }
    
    int maxIndex = begin;
    double maxValue = fabs(factors[begin][begin]);

    // ALGHORITM - find row with max value
    for(int i = begin; i<n;i++){
        if(fabs(factors[i][begin]>maxValue)){
            maxIndex = i;
            maxValue = factors[i][begin];
        }
    }
    
    if(maxIndex != begin){ // if first component isnt the biggest
        for(int i = begin; i <= n; i++){
            swap(factors[begin][i],factors[maxIndex][i]); // swap entire row
        }
    }


    //GAUSS ALGHORITM - TRIANGLE MATRIX - start from second row (index 1)
    for(int i = begin+1; i<n; i++){ // row loop
        const double multiplier = factors[i][begin]/factors[begin][begin]; // const multiplier for entire row - a[1][0]
            for(int j = begin; j <= n; j++){ // column loop
            factors[i][j] -= multiplier*factors[begin][j]; // ex. a[1][0] = a[1][0]/a[0][0]*a[0][0] (entire row 1) 
            if(factors[i][j]<EPSILON&&factors[i][j]>-EPSILON){ // double mistakes
                factors[i][j] = 0.0;
            }
        }
    }

    gaussMatrix(factors, n, ++begin); // recursion -> with [n-1][n-1] matrix
}


void calcSolution(double **factors, int size, double *results){
    size--; // array counted from 0 

    for(int i = size; i>=0; i--){
        double tempSum = 0.0;
        for(int j = i; j < size; j++){
            tempSum += results[j+1]*factors[i][j+1]; // calculate sum of non-counted factors
        }    

        results[i] = (factors[i][size+1] - tempSum)/factors[i][i]; // calculate result[i]
    }
}


int main(){
    // nodes
    double *nodes = new double[COUNT]{1,2,3,4,5,6,7,8};
    double *values = new double[COUNT]{2,4,3,5,6,9,11,11};
    
    double **G = new double*[DEGREE+1];
    for(int i = 0; i<DEGREE+1; i++){
        G[i] = new double[DEGREE+1];
    }

    double *F = new double[DEGREE+1];

    aproximate(COUNT, DEGREE, 1, nodes, values, G, F);

    double **factors = new double*[DEGREE+1];
    for(int i = 0; i<DEGREE+1; i++){
        factors[i] = new double[DEGREE+2];
    }

    for(int i = 0; i < DEGREE+1; i++){
        for(int j = 0; j < DEGREE + 2; j++){
            if(j!=DEGREE+1){
                factors[i][j]=G[i][j];
            }
            else{    
                factors[i][j] = F[i];
            }
        }
    }

    double *results = new double[DEGREE+1];

    gaussMatrix(factors, DEGREE+1, 0);
    calcSolution(factors, DEGREE+1, results);

    // Aproximate values in nodes
    double *aproximateVaules = new double[COUNT];
    calcAproximate(COUNT, DEGREE, nodes, results, aproximateVaules);

    printResults(DEGREE, COUNT, nodes, values, results, aproximateVaules);
    system("pause");
    return 0;
}