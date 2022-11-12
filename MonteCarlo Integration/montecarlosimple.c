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
    int steps = 100;
    double F[steps];
    double ro[steps];
    double dominio[steps];
    //linspace ro
    double delta = (ro_f-ro_i)/steps;
    for (int i=1; i<steps; i++){
        ro[i] = ro_i + i*delta;
        dominio[i] = (double)i*2/steps;
        F[i] = montecarlo(ro_i,ro[i]);
    }
    printf("compute over");
    /*
    PLOT F[ro] vs ro
    */
    //PLOTTING DE LA FRECUENCIA RELATIVA A TRAVES DEL TIEMPO
    FILE *fpPuntos=fopen("data/monte_carlo.txt","w"); // se crea un archivo de texto para guardar los valores del dado
    for (int i=0; i<100; i++){
            fprintf(fpPuntos,"%f %f \n", dominio[i],F[i]);
    }
    fclose(fpPuntos);
    FILE *fp = popen("gnuplot -persist", "w");
    // set gnuplot figure properties
    fprintf(fp, "set title \"Monte Carlo Integration\"\n");
    fprintf(fp, "set xlabel \"r\"\n");
    fprintf(fp, "set ylabel \"F(r)\"\n");
    fprintf(fp, "plot \"data/monte_carlo.txt\" with lines\n");   
    

    return 0;

}