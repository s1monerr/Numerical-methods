#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

#define FUNCTION "expand"

double func(double x){ //x^2 + 2x + 5
    double sum = 0.0;
    sum += pow(x,2);
    sum += 2*x;
    sum += 5;
    return sum;
}

// ti factor function
double ti(double a, double b, double x){
    return (a+b)/2+((b-a)/2)*x;
}

// Main alghoritm. fun - function type, nodes - number of nodes
double integralGauss(double a, double b, std::string fun, int nodes){ 
    double sum = 0.0; // temp sum variable
    
    if(nodes == 2){// 2 nodes case
        double *nodes = new double[2];
        nodes[0] = -sqrt(3)/3;
        nodes[1] = -nodes[0];

        if(fun == "sin"){
            for(int i = 0; i < 2; i++){
                sum += sin(ti(a,b,nodes[i]));
            }
            sum *= (b-a)/2;
            delete[] nodes;
            return sum;
        }

        else if(fun == "expand"){
            for(int i = 0; i < 2; i++){
                sum += exp(ti(a,b,nodes[i]));
            }
            sum *= (b-a)/2;
            delete[] nodes;
            return sum;
        }

        else if(fun == "func"){
            for(int i = 0; i < 2; i++){
                sum += func(ti(a,b,nodes[i]));
            }
            sum *= (b-a)/2;
            delete[] nodes;
            return sum;
        }
    } 

    else if(nodes == 4){
        double *nodes = new double[4];
        nodes[0] = -0.861136;
        nodes[1] = -0.339981;
        nodes[2] = 0.339981;
        nodes[3] = 0.861136;

        double *heights = new double[4]; // wagi
        heights[0] = 0.347855;
        heights[1] = 0.652145;
        heights[2] = 0.652145;
        heights[3] = 0.347855;

        if(fun == "sin"){
            for(int i = 0; i < 4; i++){
                sum += heights[i]*sin(ti(a,b,nodes[i]));
            }
            sum *= (b-a)/2;
            delete[] nodes;
            delete[] heights;
            return sum;
        }

        else if(fun == "expand"){
            for(int i = 0; i < 4; i++){
                sum += heights[i]*exp(ti(a,b,nodes[i]));
            }
            sum *= (b-a)/2;
            delete[] nodes;
            delete[] heights;
            return sum;
        }

        else if(fun == "func"){
            for(int i = 0; i < 4; i++){
                sum += heights[i]*func(ti(a,b,nodes[i]));
            }
            sum *= (b-a)/2;
            delete[] nodes;
            delete[] heights;
            return sum;
        }
    }
}

int main(){
    std::cout<<"function: sin(x)"<<std::endl;
    std::cout<<"2 nodes: "<<std::endl;
    std::cout<<"result = "<<integralGauss(0.5,2.5,"sin",2)<<std::endl;

    std::cout<<"4 nodes: "<<std::endl;
    std::cout<<"result = "<<integralGauss(0.5,2.5,"sin",4)<<std::endl<<std::endl;

    std::cout<<"function: expand(x)"<<std::endl;
    std::cout<<"2 nodes: "<<std::endl;
    std::cout<<"result = "<<integralGauss(0.5,5,"expand",2)<<std::endl;

    std::cout<<"4 nodes: "<<std::endl;
    std::cout<<"result = "<<integralGauss(0.5,5,"expand",4)<<std::endl<<std::endl;

    std::cout<<"function: quadratic: x^2x+5"<<std::endl;
    std::cout<<"2 nodes: "<<std::endl;
    std::cout<<"result = "<<integralGauss(0.5,5,"func",2)<<std::endl;

    std::cout<<"4 nodes: "<<std::endl;
    std::cout<<"result = "<<integralGauss(0.5,5,"func",4)<<std::endl;

    system("pause");
}

