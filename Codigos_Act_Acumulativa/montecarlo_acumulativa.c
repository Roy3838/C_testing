#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <complex.h>



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

    double complex f_x(double y, double w){
        return 1/csqrt(2*3.141592) * 1/(3.141592 * (1 + cpow(y,2))) * (cexp(I*w*y));
    };

    double montecarlo(double y_i, double y_f, double w,int N, double y[N]){
        //integrate using monte carlo 
        double complex sum = 0;
        double complex Y[N];
        double y_linspace[N];
        // fill y_linspace

        for (int i=0; i<N; i++){
            Y[i] = f_x(y[i],w);
            sum += Y[i];
        }
        // calculate F(x) using E(x) expected value
        double complex E = (y_f-y_i)*sum/N;
        return E;
    }
    int N = 260000;       
    int N_w = 1000;
    double complex w[N_w];
    double w_i = -2;
    double w_f = 2;
    double w_step = (w_f-w_i)/(N_w-1);
    double w_linspace[N_w];
    double y [N];
    double y_i = -100;
    double y_f = 100;

    for (int i=0; i<N; i++){
        y[i] = roy_uniform(y_i,y_f,3);
    }

    if(1){
        for(int i = 0; i<N_w; i++){
            w_linspace[i] = w_i + i*w_step;
            w[i] = montecarlo(y_i,y_f,w_i+i*w_step,N, y);
            printf("%d\n",i);
        }
        


        FILE *fpPuntos=fopen("data/monte_img.csv","w"); // se crea un archivo de texto para guardar los valores del dado

        //printf("integration result is %f + %fi", creal(res), cimag(res));
        for(int i = 0; i<N_w; i++){
            fprintf(fpPuntos,"%f, %f \n", w_linspace[i], creal(w[i]));
        }
    
    }
    // else{
    //     printf("valor : %f", montecarlo(-100,100,0));
    // }
    return 0;

}