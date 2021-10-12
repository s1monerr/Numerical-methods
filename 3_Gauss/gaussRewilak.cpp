#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

bool gaussMatrix_1(double **, int, int);
bool gaussMatrixPivot(double **, int, int);
void printInitial(double **, int);
void printResults(double **, int, double);
void calcSolution(double **, int, double *);
#define EPSILON 0.0000001

template <typename T> void swap(T& a, T& b) {
	T buf = a;
	a = b;
	b = buf;
}

void printMatrix(int n, double** matrix){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            std::cout<<matrix[i][j]<<"   ";
        }
        std::cout<<std::endl;
    }
}

bool gaussMatrix_1(double ** factors, int n, int begin){

    if(begin == n){
        return true; // program runned succesfully
    }

    // if 0 on diagonal
    if(factors[begin][begin]==0){
        std::cout<<"Value 0 in matrix["<<begin<<"]["<<begin<<"]. Closing program."<<std::endl;
        return false; // break function
    }

    // GAUSS ALGHORITM - start from second row (index 1)
    for(int i = begin+1; i<n; i++){ // row loop
        const double multiplier = factors[i][begin]/factors[begin][begin]; // const multiplier for entire row - a[1][0]
            for(int j = begin; j <= n; j++){ // column loop
            factors[i][j] -= multiplier*factors[begin][j]; // ex. a[1][0] = a[1][0]/a[0][0]*a[0][0] (entire row 1) 
            if(factors[i][j]<EPSILON&&factors[i][j]>-EPSILON){ // double mistakes
                factors[i][j] = 0.0;
            }
        }
    }

    gaussMatrix_1(factors, n, ++begin);
}

bool gaussMatrixPivot(double **factors, int n, int begin){
    if(begin == n){
        return true; // program runned succesfully
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

    // if 0 on diagonal
    if(factors[begin][begin]==0){
        std::cout<<"Value 0 in matrix["<<begin<<"]["<<begin<<"]. Closing program."<<std::endl;
        return false; // break function
    }

    // GAUSS ALGHORITM - start from second row (index 1)
    for(int i = begin+1; i<n; i++){ // row loop
        const double multiplier = factors[i][begin]/factors[begin][begin]; // const multiplier for entire row - a[1][0]
            for(int j = begin; j <= n; j++){ // column loop
            factors[i][j] -= multiplier*factors[begin][j]; // ex. a[1][0] = a[1][0]/a[0][0]*a[0][0] (entire row 1) 
            if(factors[i][j]<EPSILON&&factors[i][j]>-EPSILON){ // double mistakes
                factors[i][j] = 0.0;
            }
        }
    }

    gaussMatrixPivot(factors, n, ++begin);
}

// Full - find max value, swap entire row & column
// swaps - tablica potrzebna, bo sa zamieniane kolumny - czyli kolejnosc rozwiazan x1, x2, ... xn jest zmieniona
bool gaussMatrixFull(double **factors, int n, int begin, int *swaps){ 
    if(begin == n){
        return true; // program runned succesfully
    }

    int maxIndexi = begin;
    int maxIndexj = begin;
    double maxValue = fabs(factors[begin][begin]);

    // Wybor pelny - znajduje komorke z najwieksza wartoscia
    for(int i = begin; i < n; i++){ // rzedy
        for(int j = begin; j < n; j++){ // kolumny
        if(fabs(factors[i][j]>maxValue)){
            maxIndexi = i;
            maxIndexj = j;
            maxValue = factors[i][j];
            }
        }
    }

        for(int i = 0; i <= n; i++){
            swap(factors[i][begin],factors[i][maxIndexi]); // zamien kolumne
        }

        for(int i = begin; i <= n; i++){
            swap(factors[begin][i],factors[maxIndexj][i]); // zamien rzad
        }
        swap(swaps[begin], swaps[maxIndexj]); // swaps - zmiana kolumny to zmiana indeksu w wektorze rozwiazan

    // if 0 on diagonal
    if(factors[begin][begin]==0){
        std::cout<<"Value 0 in matrix["<<begin<<"]["<<begin<<"]. Closing program."<<std::endl;
        return false; // break function
    }

    // GAUSS ALGHORITM - start from second row (index 1)
    for(int i = begin+1; i<n; i++){ // row loop
        const double multiplier = factors[i][begin]/factors[begin][begin]; // const multiplier for entire row - a[1][0]
            for(int j = begin; j <= n; j++){ // column loop
            factors[i][j] -= multiplier*factors[begin][j]; // ex. a[1][0] = a[1][0]/a[0][0]*a[0][0] (entire row 1) 
            if(factors[i][j]<EPSILON&&factors[i][j]>-EPSILON){ // double mistakes
                factors[i][j] = 0.0;
            }
        }
    }

    gaussMatrixFull(factors, n, ++begin, swaps);
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
        
        double **factors = new double*[count]; // dynamically allocated 2d matrix of factors

        for(int i = 0; i<=count; i++){ // <= - factors is [x][x+1] matrix - last column is column of const.
            factors[i] = new double[count+1];
        }

        for(int i = 0; i<count; i++){ // read factors
            for(int j = 0; j<=count; j++){
                read >> factors[i][j];
            }
        }

        int *swaps = new int[count]; // tablica zmian zmiennych 
        for(int i = 0; i < count; i++){
            swaps[i] = i;
        }

        printInitial(factors, count);
        double *results = new double[count]; // results array

        // if(gaussMatrix_1(factors, count, 0)){
        //     calcSolution(factors, count, results);
        //     printResults(factors, count, results);
        //  }

        // Solution
        if(gaussMatrixFull(factors, count, 0, swaps)){
            calcSolution(factors, count, results);
            for(int i = 0; i < count; i++){
                std::cout<<"swaps "<<i<<" = "<<swaps[i]<<std::endl;
            }
            // zamiana kolejnosci rozwiazan - swaps
            double *resultsBufor = new double[count]; // bufor - do zmiany kolejnosci wynikow
            resultsBufor = results;
            
            // for(int i = 0; i < count; i++){
            //             results[swaps[i]] = resultsBufor[i];
            // }
            printResults(factors, count, results);
        }
    }

    system("pause");
    return 0;
}