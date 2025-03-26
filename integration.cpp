
#include<iostream>
#include<cmath>
using namespace std;
double f(double x){
    return x*x;
}
double trap(double y[],double h){

    double sum=0;
    for(int i=1;i<36;i++){
        sum+=2*y[i];
    }
    return (h/2)*(y[0]+sum+y[36]);
}
double simpson1_3(double y[],double h){
    double sum1=0;
    double sum2=0;
    for(int i=1;i<36;i++){
        if(i%2==0){
            sum1+=2*y[i];
        }
        else{
            sum2+=4*y[i];
        }
    }
    return (h/3)*(y[0]+sum1+sum2+y[36]);
}
double simpson3_8(double y[],double h){
    double sum1=0;
    double sum2=0;
    for(int i=1;i<36;i++){
        if(i%3==0){
            sum1+=2*y[i];
        }
        else{
            sum2+=3*y[i];
        }
    }
    return (3*h/8)*(y[0]+sum1+sum2+y[36]);
}
