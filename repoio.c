#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int roy_uniform(int low, int high, int iterations) {
    double a = pow(7,5);
    double m = pow(2,31)-1;

    double x_0 = fmod(470211272 /(a),m);
    double x[iterations];
    x[0] = x_0;
    double u_x[iterations];
    u_x[0] = x_0;

    //Se generan los numeros aleatorios uniformes
    for(int i = 1; i < iterations; i++) {
        x[i] = fmod(a*x[i-1],m);
        u_x[i] = (double)x[i]/m;
    }
    // escalar entre low y high
    u_x[iterations] = low + (high-low)*u_x[iterations];

    return u_x[iterations];
}

double f_x(double x, double y){
    double primerarg= pow(x,2) + pow(y,2);
    double segundoarg = pow(sin(x),2) + pow(sin(y),2);
    return  primerarg + 25*segundoarg;
}

int main(){
    // Simulated Annealing
    double seed = 10;
    int range= 10;
    double x_0 = rand()%range -5;
    double y_0 = rand()%range -5;
    double p_0[] = {x_0,y_0};
    double T_0 = 100;
    double T_min = 0.01;
    double p_1[] = {p_0[0] ,p_0[1]};
    int L = 100;
    while(T_0 > T_min){
        T_0=0.9*T_0;
        printf("El minimo es: %f , %f \n",p_0[0],p_0[1]);
        for(int i = 0; i<L; i++){
            double x_1 = (rand()%100)*0.01;
            double y_1 = (rand()%100)*0.01;
            double p_1[] = {p_0[0] + x_1 ,p_0[1] + y_1};
            if (f_x(p_1[0],p_1[1]) < f_x(p_0[0],p_0[1])){
                p_0[0] = p_1[0];
                p_0[1] = p_1[1];
            }
            // else{
            //     double r = (rand()%100)*0.01;
            //     double e = exp((f_x(p_0[0],p_0[1])-f_x(p_1[0],p_1[1]))/T_0);
            //     if (r < e){
            //         p_0[0] = p_1[0];
            //         p_0[1] = p_1[1];
            //     }
            // }

            }




        }


    return 0;
}









