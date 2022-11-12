#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <malloc.h>

double roy_uniform(double a, double b, double decimales){
    /*
    Funcion que genera un numero aleatorio uniforme entre a y b
    con una cantidad de decimales dada.
    */
    b = b*pow(10,decimales);
    a = a*pow(10,decimales);
    int r = rand() % (int)(b-a) + a;
    double m=(double)r/pow(10,decimales);
    return m;
}

double f_x_y(double x, double y){
    int d = 0;
    return  pow(x+d,2) + pow(y+d,2) + 25*(pow(sin(x+d),2) + pow(sin(y+d),2));

}

double *repoios_recocidos(double alpha, int L, double T_0, double T_min, int seed){
    //dynamically allocate memory using malloc()
    double *ret = (double *)malloc(2 * sizeof(double));

    // Simulated Annealing
    srand(seed);
    double x_0 = roy_uniform(-50,50,5);
    double y_0 = roy_uniform(-50,50,5);
    double p_0[] = {x_0,y_0};

    double p_1[] = {p_0[0] ,p_0[1]};
    // double alpha = 0.99;
    // int L = 100;
    // double T_0 = 389;
    // double T_min = 0.01;

    while(T_0 > T_min){
        T_0=alpha*T_0;
        for(int i = 0; i<L; i++){
            // double x_1 = (rand()%10000)*0.0001 - 0.5; // = uniform(-0.5,0.5) pero con 0.01 
            // double y_1 = (rand()%10000)*0.0001 - 0.5;
            double x_1 = roy_uniform(-0.5,0.5,5);
            double y_1 = roy_uniform(-0.5,0.5,5);
            double p_1[] = {p_0[0] + x_1 ,p_0[1] + y_1};
            double valor_p_1 = f_x_y(p_1[0],p_1[1]);
            double valor_p_0 = f_x_y(p_0[0],p_0[1]);
            
            if (valor_p_1 < valor_p_0){
                p_0[0] = p_1[0];
                p_0[1] = p_1[1];
            }
            else{
                double r = roy_uniform(0,1,2); // numero aleatorio entre 0 y 1
                double e = exp((valor_p_0 - valor_p_1)/T_0); // e^(-deltaE/T)
                if (r < e){ // si el numero aleatorio es menor que e^(-deltaE/T)
                    p_0[0] = p_1[0]; // se acepta el nuevo punto
                    p_0[1] = p_1[1];
                }
            }

            }

        }
    
    ret[0] = p_0[0];
    ret[1] = p_0[1];
    return ret;
}

int main(){
    double alpha = 0.99;
    double L = 1000;
    double T_0 = 300.0;
    double T_min = 0.001;
    // int p_0 = {0,0};
    // printf("El minimo es: %f , %f \n",p_0[0],p_0[1]);
    for(int i =1; i<10; i++){
        double *p_0 = repoios_recocidos(alpha,L,T_0,T_min,i);
        printf("El minimo es: %f , %f \n",p_0[0],p_0[1]);
    }

    return 0;
}





