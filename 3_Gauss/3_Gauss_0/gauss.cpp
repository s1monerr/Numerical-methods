#include <iostream>
#include <fstream>
#include <cmath>
#include "../algorytmy.h" // biblioteka z definicja funkcji swap
#include <iomanip>
#define EPSILON 0.0000001

bool gaussMatrix(double **, int *, int);
void printResults(double **, int, double);
void printInitial(double **, int);
void calcSolution(double **, int);

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

void printResults(double **factors, int size, double *results){
    std::cout<<std::endl;
    std::cout<<"-------------------------"<<std::endl;
    std::cout<<"         RESULTS         "<<std::endl;
    std::cout<<"-------------------------"<<std::endl;
    std::cout<<"TRANSFORMATED MATRIX: "<<std::endl<<std::endl;

    for(int i = 0; i < size; i++){
        for(int j = 0; j<= size; j++){
            if(j==size){
                std::cout<<" |";
            }
            std::cout<<std::setprecision(3)<<factors[i][j]<<"    ";
        }
        std::cout<<std::endl;
    }

    std::cout<<std::endl;
    std::cout<<"Equation system solution: "<<std::endl;
    for(int i = 0; i < size; i++){
        std::cout<<std::setprecision(4)<<"x"<<i+1<<" = "<<results[i]<<", ";
    }
    std::cout<<std::endl;
}

void printInitial(double **factors, int size){
        std::cout<<"-------------------------"<<std::endl;
        std::cout<<"      INITIAL MATRIX     "<<std::endl;
        std::cout<<"-------------------------"<<std::endl;
        // print initial matrix
        for(int i = 0; i < size; i++){
            for(int j = 0; j<= size; j++){
                if(j==size){
                    std::cout<<" |";
                }
                std::cout<<std::setprecision(3)<<factors[i][j]<<"    ";
            }
            std::cout<<std::endl;
        }
}

int main(){

    std::fstream read("data.txt");

    int count = 0; // equations counter

    if(read.is_open()){  // if file is opened correctly
    
        read >> count; //  read number of equations
        
        double **factors = new double*[count]; // dynamically allocated 2d matrix of factorsW

        for(int i = 0; i<=count; i++){ // <= - factors is [x][x+1] matrix - last column is column of const.
            factors[i] = new double[count+1];
        }

        for(int i = 0; i<count; i++){ // read factors
            for(int j = 0; j<=count; j++){
                read >> factors[i][j];
            }
        }
        
        printInitial(factors, count);
        // main counting
        if(gaussMatrix(factors, count, 0)){ // if matrix is solved correctly

        double *results = new double[count]; // results array
        calcSolution(factors, count, results);

        printResults(factors, count, results);
        delete[] results;
        }

        delete[] factors;
    }

    read.close();
    system("pause");
    return 0;
}