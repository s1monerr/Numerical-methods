// Temat projektu - rozkład LU 
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#define PATH "data.txt"

void printMatrix(int n, double **matrix){
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            std::cout<<std::setprecision(3)<<matrix[i][j]<<" | ";
        }
        std::cout<<std::endl;
    }
}

// L matrix - daigonals = 1
void diagonalL(int n, double**matrix){
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j)
                matrix[i][j] = 1;
        }
    }
}

// reseting matrix
void zeroMatrix(int n, double **matrix){
    for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrix[i][j] = 0;
        }
    }
}

// calculate U matrix factors
// mi, mj - main iterators; matA, matL, matU - A, U and L matrices 
void uCalc(int mi, int mj, double **matA, double **matL, double **matU){
    double tempSum = 0;
    for(int i = 0; i < mj; i++){
        tempSum += matL[mi][i]*matU[i][mj];
    }
    matU[mi][mj] = matA[mi][mj] - tempSum;
}

// calculate L matrix factors
void lCalc(int mi, int mj, double **matA, double **matL, double **matU){
    double tempSum = 0;
    for(int i = 0; i < mj; i++){
        tempSum += matL[mi][i]*matU[i][mj];
    }
    matL[mi][mj] = (1/matU[mj][mj])*(matA[mi][mj]-tempSum);
}

// main LU Doolitle alghoritm
// n - equations counter, A - matrixA, L , U - matrix L and U
void LUfactorization(int n, double **A, double **L, double **U){
    //reset L and U matrices
    zeroMatrix(n, L);
    zeroMatrix(n, U);
    diagonalL(n, L); // 1 od L diagonal

    for(int j = 0; j < n; j++){ // first - iterate rows
        for(int i = 0; i < n; i++){ // fast loop - rows
            if(i <= j){ // i =< j -> upper diagonal, calculate u factors
                uCalc(i, j, A, L, U);
            }
            else if(i > j){ // i > j -> bottom diagonal, calculate u factors
                lCalc(i, j, A, L, U);
            }
        }
    }
}

// matA - matrix A, matB - matrixB
void readFile(std::string file, int &n, double **matA, double *matB){
    std::fstream read(file);
    if(read.is_open()){  // if file is opened correctly
    read >> n;
        for(int i = 0; i < n; i++){ // read matrix
            for(int j = 0; j < n; j++){
                read >> matA[i][j];
            }
            read >> matB[i];
        }
    }

    else{
        std::cout<<"Unable to open file."<<std::endl;
        return;
    }
}

void printInitial(double **factors, double *matB, int size){
        std::cout<<"-------------------------"<<std::endl;
        std::cout<<"      INITIAL SYSTEM     "<<std::endl;
        std::cout<<"-------------------------"<<std::endl;
        // print initial matrix
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if(j==size){
                    std::cout<<" |";
                }
                std::cout<<std::setprecision(3)<<factors[i][j]<<"    ";
            }
            std::cout<<"|   "<<matB[i]<<std::endl; // wolny wyraz
        }
}

void equationSolve(int n, double **A, double *X, double *B){
        // LU factorization
        double **L = new double*[n]; // matrix L
        for(int i = 0; i < n; i++){
            L[i] = new double[n];
        }

        double **U = new double*[n]; // matrix U
        for(int i = 0; i < n; i++){
            U[i] = new double[n];
        }
        std::cout<<"=================="<<std::endl;
        std::cout<<"Matrix A after LU decomposition: "<<std::endl;
        LUfactorization(n, A, L, U);
        std::cout<<"=================="<<std::endl<<"L: "<<std::endl;
        printMatrix(n, L);
        std::cout<<"=================="<<std::endl<<"U: "<<std::endl;
        printMatrix(n, U);

        // vector Y
        // L x Y = B
        double *Y = new double[n];
        // calculate Y solutions
        for(int i = 0; i < n; i++){ // row iterator
            int j = 0; // column iterator
            double tempSum = 0.0; // temp equation sum for each row
            while(j <= i){// if lower diagonal
                    if(i == j){ // if i == j => L[i][j] = 1
                        Y[i] = B[i]-tempSum;
                    }
                    else{
                        tempSum += Y[j]*L[i][j];
                    }
                j++;
            }
        }
        // vector X
        // U x X = Y
        for(int i = n-1; i >= 0; i--){ // row iterator, go upwards (matrixU)
            int j = n-1; // column iterator
            double tempSum = 0.0; // temp equation sum for each row
            // Calculate X results
            while(j >= i){// if upper diagonal
                    if(i == j){
                        X[i] = (Y[i]-tempSum)/U[i][j];
                    }
                    else{
                        tempSum += X[j]*U[i][j];
                    }
                j--;
            }
        }
        delete[] Y;
        delete[] U;
        delete[] L;
}

void printResults(int size, double *results){
    std::cout<<std::endl;
    std::cout<<"-------------------------"<<std::endl;
    std::cout<<"         RESULTS         "<<std::endl;
    std::cout<<"-------------------------"<<std::endl;

    std::cout<<std::endl;
    std::cout<<"Equation system solution: "<<std::endl;
    for(int i = 0; i < size; i++){
        std::cout<<std::setprecision(4)<<"x"<<i+1<<" = "<<results[i]<<", ";
    }
    std::cout<<std::endl;
}

int main(){
    // file input
    std::fstream read(PATH);
    int count = 0;

    if(read.is_open()){
        read >> count;
        double **matrixA = new double*[count]; // main equation matrix

        // matrix A
        for(int i = 0; i < count; i++){ 
            matrixA[i] = new double[count];
        }

        double *matrixB = new double[count]; // matrixB - macierz wyrazow wonych

        readFile(PATH, count, matrixA, matrixB);

        double *results = new double[count];
        
        // equation solving
        printInitial(matrixA, matrixB, count);

        equationSolve(count, matrixA, results, matrixB);

        printResults(count, results);
        
        system("pause");
        return 0;
    }
    
    else{
        std::cout<<"Error: Can't open file. "<<std::endl;
        system("pause");
        return -1;
    }
}