#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double integral_locoshona(double x){
	double f_x=pow(x-1,2);
	return f_x;

}

double * num_aleatorios(int x_0, int x_1,int a, int m ,int s,int iterations){
    /*
    x_0 : valor minimo
    x_1 : valor maximo
    a : multiplicador
    m : modulo
    s : semilla
    iterations : numero de iteraciones
    */

    //Numero de iteraciones generadas por el PRNG
    int x[iterations];
    x[0] = s;
    double u_x[iterations];
    u_x[0] = s;
    // using malloc function
    double *u = (double*)malloc(iterations * sizeof(double));
    //Se generan los numeros aleatorios uniformes
    for(int i = 1; i < iterations; i++) {
        x[i] = (a*x[i-1])%m;
        u_x[i] = (double)x[i]/m;
    }
    for(int i = 0; i < iterations; i++) {
        // escalar a x_0 a x_1
        u[i] = u_x[i] * (x_1 - x_0) + x_0;
    }
    return u;

}


int main(){
    /*

    GENERADOR DE NUMEROS ALEATORIOS UNIFORMES
    
    */

    int iterations = 1000;
    //PRNG number generator parameters
    int a = pow(7,5);
    int m = pow(2,31)-1;
    int s = 470211272/(a)%m;
    
    // se generan los numeros aleatorios uniformes
    double *u = num_aleatorios(2,3,a,m,s,iterations);
    // se generan otros numeros aleatorios uniformes
    double *v = num_aleatorios(2,3,a,m,s,iterations);

    // Se va a tener una integral y se van a aventar numeros aleatorios 
    
    int cantidad_puntos = 0;
    for(int k = 0; k<iterations/2; k++){
	    if (integral_locoshona(u[k]) > u[k*2])
	    {
		    cantidad_puntos++;
	    }

    }
    printf("puntos %i", cantidad_puntos);




    /*

    SECCION DE PLOTTING

    */
    
    // Se crea el archivo de texto para guardar los datos de la distribucion exponencial
    FILE *fpPuntos=fopen("data/montecarlo.txt","w");
    for (int i=1; i<iterations; i++){
        if (i%1==0){
            fprintf(fpPuntos,"%f %f \n",u[i], v[i]);
        }
    }
    fclose(fpPuntos);

    // // Se grafican las dos distribuciones en un mismo plot
    // FILE *fp = popen("gnuplot -persist", "w");
    // fprintf(fp, "binwidth=0.1 \n bin(x,width)=width*floor(x/width) \n");
    // fprintf(fp, "plot 'data/exp.txt' using (bin($1,binwidth)):(1.0) smooth freq with boxes\n");   
    // fprintf(fp, "replot 'data/gamma.txt' using (bin($1,binwidth)):(1.0) smooth freq with boxes\n");


    return 0;
}

