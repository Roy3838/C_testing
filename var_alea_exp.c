// Python Code
    
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//Me mame no podia importar math con debugger asi que hice mi propio pow
int Pow( double a , int b ){  
    double power = 1;
    for (int i = 1 ; i<=b ; ++i) {  
        power = power * a ;
    }
    return power ;
}

double F_x(double x, double lambda) {
    return 1 - exp(-lambda*x);
}

double F_x_inv(double u,double lambda) {
    return -log(1-u)/lambda;
}


int main(){
    //PRNG number generator
    int a = Pow(7,5);
    int m = Pow(2,31)-1;
    int x_0 = 470211272/(a)%m;
    int iterations = 100;
    int x[iterations];
    x[0] = x_0;
    double u_x[iterations];
    u_x[0] = x_0;

    for(int i = 1; i < iterations; i++) {
        x[i] = (a*x[i-1])%m;
        u_x[i] = (double)x[i]/m;
    }

    // usar numeros aleatorios uniformes y hacerlos con distribucion exponencial

    double lambda = 1;
    double u[iterations];
    double x_exp[iterations];

    for(int i = 0; i < iterations; i++) {
        u[i] = u_x[i];
        x_exp[i] = F_x_inv(u[i],lambda);
        printf("exp =%f \n",x_exp[i]);
    }

    return 0;
}
