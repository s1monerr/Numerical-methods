#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

#define DATA "data.txt"
#define EPSILON 0.0001


void printInitial(double **factors, int size){
        std::cout<<"-------------------------"<<std::endl;
        std::cout<<"      INITIAL SYSTEM     "<<std::endl;
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

void printResults(double **factors, int size, double *results, int steps){
    std::cout<<std::endl;
    std::cout<<"-------------------------"<<std::endl;
    std::cout<<"         RESULTS         "<<std::endl;
    std::cout<<"-------------------------"<<std::endl;

    std::cout<<std::endl;
    std::cout<<"Equation system solution: "<<std::endl;
    for(int i = 0; i < size; i++){
        std::cout<<std::setprecision(5)<<"x"<<i+1<<" = "<<results[i]<<", ";
    }
    // std::cout<<std::endl<<"Solved in "<<steps<<" steps."<<std::endl;
    std::cout<<std::endl;
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

void printMatrix(int n, double** matrix){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            std::cout<<matrix[i][j]<<"   ";
        }
        std::cout<<std::endl;
    }
}

// U+L matrix function
double** matrixUL(int n, double** matrix){
    double** UL = new double*[n]; // to return
    for(int i = 0; i < n; i++){
        UL[i] = new double[n];
        for(int j = 0; j < n; j++){
            if(j == i)
                UL[i][j] = 0;
            else
                UL[i][j] = matrix[i][j];
        }
    }
    return UL;
}

// D ^(-1) function
double **reverseDiagonal(int n, double** matrix){
    double** D = new double*[n]; // to return
    for(int i = 0; i < n; i++){
        D[i] = new double[n];
        for(int j = 0; j < n; j++){
            if(j == i)
                D[i][j] = 1/matrix[i][j];
            else
                D[i][j] = 0;
        }
    }
    return D;
}

double* multiMatrix(double **m1, double *vec, int n){ // multiply NxN matrix by vector
    
    double *fin = new double[n];

    for (int i = 0; i < n; i++){
        double temp = 0.0;
        for(int j = 0; j < n; j++){
            temp += m1[i][j]*vec[j];
        }
        fin[i] = temp;
    }
    return fin;
}

double** multiMatrix(double **m1, double **m2, int n){ // multiply NxN by NxN matrix

    double **fin = new double*[n];
    for(int i = 0; i < n; i++){
        fin[i] = new double[n];
    }

    for(int i = 0 ; i < n; i++){ // rows
        for(int j = 0; j < n; j++){ // columns
        fin[i][j] = 0;
            for(int k = 0; k < n; k++){
                fin[i][j] += m1[i][k]*m2[k][j];
            }   
        }
    }
    return fin;
}

double* addVectors(double *vec1, double *vec2, int n){ // add 2 vectors 3D
    double *fin = new double[n];
    for(int i = 0; i < n; i++){
        fin[i] = 0;
        fin[i] = vec1[i]+vec2[i];
    }
    return fin;
}

bool weaklyDominant(double **matrix, int size){ // if weakly dominant diagonal matrix
    bool result = true; // boolean flag
    // 1st condition: V |aii| >= sum of row
    for(int i = 0; i < size; i++){ // rows
        double tempSum = 0.0; // temp sum or each row
        for(int j = 0; j < size; j++){ // columns
            if(i!=j)
                tempSum += fabs(matrix[i][j]);
        }
        if(fabs(matrix[i][i]<tempSum)){ // 1st condition is not true - return false
            std::cout<<"Matrix A is not weakly diagonal dominant."<<std::endl;
            return !result;
        }
    }

    // 2st condition -  for at least one i |aii| > sum of row
     for(int i = 0; i < size; i++){ // rows
        double tempSum = 0.0; // temp sum or each row
        for(int j = 0; j < size; j++){ // columns
            if(i!=j)
                tempSum += fabs(matrix[i][j]);
        }
        if(fabs(matrix[i][i]>tempSum)){ // 1st and 2nd condition is true - return true
            std::cout<<"Matrix A is weakly diagonal dominant."<<std::endl;
            return result;
        }
    }

    // 1st condition true, 2nd condition false - return false
    std::cout<<"Matrix A is not weakly diagonal dominant."<<std::endl;
    return !result;

}

// |x(i+1) - x(i)| < epsilon 
bool stopCondition(double *vec1, double *vec2, double epsilon, int size){ // epsilon condition function
    for(int i = 0; i < size; i++){
        if(fabs(vec1[i] - vec2[i])>epsilon) // false: |x(i+1) - x(i)| > epsilon
            return false;
    }
    
    return true; // // true: |x(i+1) - x(i)| < epsilon
}

// Kolokwium nr 1 - warunek stopu. vec1 - x(i), vec2 - x(i+1)
bool stopConditionKolokwium(double *vec1, double *vec2, double epsilon, int size){
    double tempSum = 0.0;
    for(int i = 0; i < size; i++){
        tempSum += (vec2[i] - vec1[i])*(vec2[i] - vec1[i]); // suma (X(i+1) - X(i))^2
    }
    if(sqrt(tempSum) < epsilon)
        return true;
    else
        return false;
}

// *** MAIN JACOBI ALGHORITM, b = const values, results = x vector ***//
bool jacobiSolution(double **D, double **LU, double *results, double **A, double *b, int size, int iterations){ 
    // count only if matrix is weakly diagonal dominant
    // if(!weaklyDominant(A, size)){
    //     std::cout<<"Cannot solve equation system. "<<std::endl;
    //     return false;
    // }

    double **negativeRevMatrix = new double*[size]; // -D^(-1) - temp matrix
    for(int i = 0; i < size; i++){
        negativeRevMatrix[i] = new double[size];
    }
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(D[i][j]!=0)
                negativeRevMatrix[i][j] = -1.0*D[i][j];
            else
                negativeRevMatrix[i][j] = 0.0;
        }
    }
    // tempMatrix - // -D^(-1)*(L+U) - const for all iterations
    double **tempMatrix = new double*[size];
    for(int j = 0; j < size; j++){
        tempMatrix[j] = new double[size];
    }
    tempMatrix = multiMatrix(negativeRevMatrix, LU, size); // -D^(-1)*(L+U)
    double *lastResults = new double[size]; // last results temp vector - for stop condition
    int stepsCounter = 0; // steps counter
    for(int i = 0; i < size; i++){
        lastResults[i] = results[i]+1; // +1 - don't stop at first iteration
    }
    
    // MAIN ALGHORITM    
    for(int i = 0; i < iterations&&!stopConditionKolokwium(results, lastResults, EPSILON, size); i++){
        
        for(int i = 0; i < size; i++){ // count last iteration results
            lastResults[i] = results[i];
        }

        double *tempVector1 = new double[size];
        tempVector1 = multiMatrix(tempMatrix, results, size); // -D^(-1)*(L+U)*x (results = x vector)
        
        double *tempVector2 = new double[size];
        tempVector2 = multiMatrix(D, b, size); // D^(-1)*b
        
        double *finalVector = new double[size];
        finalVector = addVectors(tempVector1, tempVector2, size); // -D^(-1)*(L+U)*x + D^(-1)*b

        // new results = finalVector
        for(int j = 0; j < size; j++){
            results[j] = finalVector[j];
        }
        std::cout<<"Iteration "<<i<<std::endl;
        for(int k = 0; k < size; k++){
            std::cout<<"x["<<k<<"] = "<<results[k]<<std::endl;
        }
        
        delete[] finalVector;
        delete[] tempVector1;
        delete[] tempVector2;
        stepsCounter++;
        
    }
    delete[] tempMatrix;
    delete[] lastResults;
    std::cout<<"Solved in "<<stepsCounter<<" steps. "<<std::endl;
    return true;
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
        // for(int i = 0; i<count; i++){
        //     results[i] = 0; // first iteration - results 0
        // }
        results[0] = 1;
        results[1] = 1;
        results[2] = 2;
        results[3] = 2;

        double **UL = new double*[count]; // U+L matrix
        for(int i = 0; i<=count; i++){ 
            UL[i] = new double[count];
        }

        double **D = new double*[count]; // U+L matrix
        for(int i = 0; i<=count; i++){ 
            D[i] = new double[count];
        }

        double *b = new double[count]; // const expression vector
        for(int i = 0; i < count; i++){
            b[i] = factors[i][count];
        }

        // count D and U+L matrices
        D = reverseDiagonal(count, factors);
        UL = matrixUL(count, factors);
        std::cout<<std::endl<<"U + L matrix: "<<std::endl;
        printMatrix(count, UL);
        std::cout<<std::endl<<"Diagonal reversed matrix: "<<std::endl;
        printMatrix(count, D);

        // user input - number of iterations
        std::cout<<"Put in max number of iterations. "<<std::endl;
        int iterations;
        std::cin>>iterations;
        if(jacobiSolution(D, UL, results, factors, b, count, iterations))
            printResults(factors, count, results, iterations);
    }
    system("pause");
}