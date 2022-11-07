#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Acumulada de la distribucion Exponencial
double F_x_exp_inv(double u,double lambda) {
    return -log(1-u)/lambda;
}

// Acumulada de la distribucion Gamma
double F_x_gamma_inv(double u,double k,double theta) {
    double x = 0;
    for (int i=0; i<k; i++) {
        x += F_x_exp_inv(u,theta);
    }
    return x;
}

int main(){
    /*

    GENERADOR DE NUMEROS ALEATORIOS UNIFORMES
    
    */

    //PRNG number generator parameters
    int a = pow(7,5);
    int m = pow(2,31)-1;
    int x_0 = 470211272/(a)%m;
    //Numero de iteraciones generadas por el PRNG
    int iterations = 1000;
    int x[iterations];
    x[0] = x_0;
    double u_x[iterations];
    u_x[0] = x_0;
    
    //Se generan los numeros aleatorios uniformes
    for(int i = 1; i < iterations; i++) {
        x[i] = (a*x[i-1])%m;
        u_x[i] = (double)x[i]/m;
    }
    

    /*

    Se usan los numeros aleatorios uniformes y se distribuyen de manera F_X_inv(x), 
    que es la funcion acumulada de la distribucion exponencial.

    */


    double lambda = 1;
    double k=1;
    double theta=2;
    double u[iterations];
    double x_exp[iterations];
    double x_gamma[iterations];
    // Se convierte el rango u_x de [-1,1] a [0,1]
    for(int i = 0; i < iterations; i++) {
        u[i] = (u_x[i]+1)/2;
    }

    // Se distribuyen los numeros aleatorios en la distribucion exponencial
    for(int i = 1; i < iterations; i++) {
        x_exp[i] = F_x_exp_inv(u[i] ,lambda);
    }

    // Se distribuyen los numeros aleatorios en la distribucion gamma
    for(int i = 1; i < iterations; i++) {
        x_gamma[i] = F_x_gamma_inv(u[i],k,theta);
    }

    /*

    SECCION DE PLOTTING

    */
    
    // Se crea el archivo de texto para guardar los datos de la distribucion exponencial
    FILE *fpPuntos=fopen("data/exp.txt","w");
    for (int i=1; i<iterations; i++){
        if (i%1==0){
            fprintf(fpPuntos,"%f \n",x_exp[i]);
        }
    }
    fclose(fpPuntos);
    
    // Se crea el archivo de texto para guardar los datos de la distribucion gamma
    FILE *fp2Puntos=fopen("data/gamma.txt","w");
    for (int i=1; i<iterations; i++){
        if (i%1==0){
            fprintf(fp2Puntos,"%f \n",x_gamma[i]);
        }
    }
    fclose(fp2Puntos);

    // Se grafican las dos distribuciones en un mismo plot
    FILE *fp = popen("gnuplot -persist", "w");
    fprintf(fp, "binwidth=0.1 \n bin(x,width)=width*floor(x/width) \n");
    fprintf(fp, "plot 'data/exp.txt' using (bin($1,binwidth)):(1.0) smooth freq with boxes\n");   
    fprintf(fp, "replot 'data/gamma.txt' using (bin($1,binwidth)):(1.0) smooth freq with boxes\n");


    return 0;
}
