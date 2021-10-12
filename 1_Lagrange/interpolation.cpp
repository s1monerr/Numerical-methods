#include <iostream>
#include <iomanip>
#include <fstream>

int main(){

    double *x = new double[1000];
    double *y = new double[1000]; // node arrays

    // *** NODES INPUT - read from file *** //


    std::fstream read("data.txt");

    int count = 0; // node counter

    if(read.is_open()){  // if file is opened correctly

        read >> count; // at first -> read number of nodes
        
        for(int i = 0;i<count; i++){ // read nodes and values
            read >> x[i];
            read >> y[i];
        }
    }

    read.close();

    // *** INTERPOLATION POINT FROM USER ***  //
    std::cout<<"Put in interpolation point: "<<std::endl;
    double p;
    std::cin>>p; 

    double result = 0.0;

    // *** CREATING INTERPOLATION POLYNOMIAL SUM *** //
    for(int i = 0; i<count; i++){
    double sum = 1.0; // temp sum 

        for(int j = 0; j<count; j++){   
            if(j!=i){
                sum *= (p-x[j])/(x[i] - x[j]); // adding quotient if (i!=j)
            }
        }

        result += (sum*y[i]); // every quotient multiplied by value i
    }

    std::cout<<"RESULTS:"<<std::endl<< "number of nodes is "<<count<<std::endl;

    for (int i = 0; i<count; i++){
        std::cout<<"Node "<<i<<" : ("<<x[i]<<", "<<y[i]<<")"<<std::endl;
    }

    std::cout<<std::endl;
    std::cout<<"Interpolated point: x = "<<std::setprecision(4)<<p<<" : f(x) ~ "<<result<<std::endl;
    std::cout<<std::endl;

    system("pause");

    return 0;
}