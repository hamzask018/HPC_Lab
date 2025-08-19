#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;

int main(){
 int n = 10000000;
 int scalar =  5;
 vector<int> vec(n,1);
 vector<int> result(n,0);

 double start , end;
 //seq

 start = omp_get_wtime();
 for(int i = 0;i<n;i++){
    result[i] = vec[i] + scalar;
 }
 end = omp_get_wtime();
 double seq_time = (end-start);
 cout<<" Sequential Time: "<<(end-start)<<endl;

 //Parallel static schedule 
 int chunk_size[] = {1,5,10,20,50,100};

 for(auto chunk :chunk_size){
    start = omp_get_wtime();
    #pragma omp parallel for schedule(static,chunk)
    for(int i = 0;i<n;i++){
        result[i] = vec[i] + scalar;
    }
    end = omp_get_wtime();
    double static_time = end-start;
    cout<<"Static schedule chunks "<<chunk<<" Time: "<<static_time<< " | Speed up: " << seq_time / static_time<<endl;
 }

 // Parallel Dynamic schedule
 for(auto chunk :chunk_size){
    start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic , chunk)
    for(int i = 0;i<n;i++){
        result[i] = vec[i] + scalar;
    }
    end = omp_get_wtime();
    double static_time = end-start;
    cout<<"Dynamic schedule chunks: "<<chunk<<" Time: "<<static_time<< " | Speed up: " << seq_time / static_time<<endl;
 }

//Parallel with the nowait

start = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp for nowait
        for(int i = 0;i<n/2;i++){
            result[i] = vec[i] + scalar;
        }
        #pragma omp for nowait
        for(int i = n/2;i<n;i++){
            result[i] = vec[i] + scalar;
        }
    }

  end  = omp_get_wtime();

  double nowait_time = end - start;

  cout<<" No wait Time: "<<nowait_time<< " | Speed up: " << seq_time / nowait_time<<endl;

  return 0; 

    
}
