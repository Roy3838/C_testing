#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



double roy_uniform(double a, double b, double decimales){
    /*
    Funcion que genera un numero aleatorio uniforme entre a y b
    con una cantidad de decimales dada.
    */
    b = b*pow(10,decimales);
    a = a*pow(10,decimales);
    double r = rand() % (int)(b-a) + a;
    r=r/pow(10,decimales);
    return r;
}

int main(){

    double f_x(double ro){
    return sqrt(1-exp(-pow(ro,2)));
    };
    double montecarlo(double ro_i, double ro_f){
        //integrate using monte carlo
        int N = 100000;
        double ro[N];
        double F[N];
        double sum = 0;
        
        for (int i=0; i<N; i++){
            ro[i] = roy_uniform(ro_i,ro_f,3);
            F[i] = f_x(ro[i]);
            sum += F[i];
        }
        // calculate F(x) using E(x) expected value
        double E = (ro_f-ro_i)*sum/N;
        return E;
    }
    double ro_f=sqrt(2)*2;
    double ro_i=0;


    printf("F(x) = %f \n",montecarlo(ro_i,ro_f));

    return 0;

}