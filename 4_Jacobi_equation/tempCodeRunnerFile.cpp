
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