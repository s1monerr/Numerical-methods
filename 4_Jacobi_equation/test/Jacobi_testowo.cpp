#include <iostream>
#include <fstream>
#include <cmath>
#include "../algorytmy.h" // biblioteka z definicja funkcji swap
#include <iomanip>

#define DATA "data.txt"


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

void readFile(std::string file, int &n, double **factors){
    std::fstream read(file);
    if(read.is_open()){  // if file is opened correctly
    read >> n;
        for(int i = 0; i<n; i++){ // read factors
            for(int j = 0; j<=n; j++){
                read >> factors[i][j];
            }
        }
    }

    else{
        std::cout<<"Unable to open file."<<std::endl;
        return;
    }
}

void jacobiSolver(double** factors, double* results, int n){
    for(int i = 0; i < n; i++){ // MAIN ITERATOR  
    std::cout<<" MAAAIN LOOOP. i = "<<i<<std::endl<<std::endl;  
        for(int j = 0; j < n; j++){ // rows 
            const double divider = factors[j][j]; // divider is factor from solved variable
           // std::cout<<" DIVIDER = "<<divider<<std::endl;
            std::cout<<"j = "<<j<<" results[j] = "<<results[j]<<std::endl;
           // std::cout<<"factors[j][n] = "<<factors[j][n]<<std::endl;
            results[j] += factors[j][n]; // result += consant value (last in each row) 

            for(int k = 0; k < n; k++){ // colums (variables)

                if(k!=j){
                    std::cout<<"iteration: k =  "<<k<<" results[k] = "<<results[k]<<"results[j] = "<<results[j]<<" odejmuje factors[i][j] = "<<factors[i][j]*results[k]<<std::endl;
                    results[j] -= factors[i][j]*results[k];
                    std::cout<<"k = "<<k<<" results[j] = "<<results[j]<<std::endl;
                }
            }
            results[i] /= divider; // divide by divider
        }
        
        std::cout<<"Iteration = "<<i<<", equations: "<<std::endl;
        for(int p = 0; p<n; p++){
            std::cout<<"results "<<p<<" = "<<results[p]<<"      ";
        }
        std::cout<<std::endl<<std::endl;
    }
}

int main(){
    // file input
    std::fstream read(DATA);
    int count = 0;
    if(read.is_open()){
        read >> count;
        double **factors = new double*[count]; // dynamically allocated 2d matrix of factorsW

        for(int i = 0; i<=count; i++){ // <= - factors is [x][x+1] matrix - last column is column of const.
            factors[i] = new double[count+1];
        }

        readFile(DATA, count, factors);
        printInitial(factors, count);

        double *results = new double[count];
        for(int i = 0; i<count; i++){
            results[i] = 0; // first iteration - results 0
        }

        jacobiSolver(factors, results, count);
    }

}