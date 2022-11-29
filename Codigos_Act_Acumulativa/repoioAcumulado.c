#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <malloc.h>
#include <string.h>

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
    return  -(1+cos(12*sqrt(pow(x,2)+pow(y,2))))/(0.5*(pow(x,2)+pow(y,2)) +2 );
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
    double chochosgil[] = {p_0[0],p_0[1]};
    double valorchochosgil = 1000000;
    // double T_min = 0.01;
    double x_1 = 0;
    double y_1 = 0;
    double valor_p_1 = 0;
    double valor_p_0 = 0;
    
    while(T_0 > T_min){
        T_0=alpha*T_0;
        memcpy(p_0, chochosgil, sizeof(p_0));
        valorchochosgil = f_x_y(chochosgil[0],chochosgil[1]);
        for(int i = 0; i<L; i++){
            // double x_1 = (rand()%10000)*0.0001 - 0.5; // = uniform(-0.5,0.5) pero con 0.01 
            // double y_1 = (rand()%10000)*0.0001 - 0.5;
            x_1 = roy_uniform(-0.5,0.5,5);
            y_1 = roy_uniform(-0.5,0.5,5);
            p_1[0] = p_0[0] + x_1;
            p_1[1] = p_0[1] + y_1;
            //memcpy(p_1, p_0, sizeof(p_0));
            valor_p_1 = f_x_y(p_1[0],p_1[1]);
            valor_p_0 = f_x_y(p_0[0],p_0[1]);
            
            if (valor_p_1 < valor_p_0){
                p_0[0] = p_1[0];
                p_0[1] = p_1[1];
                if(valor_p_1<valorchochosgil){
                    chochosgil[0] = p_1[0];
                    chochosgil[1] = p_1[1];
                    valorchochosgil = valor_p_1;
                }
                
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
    /*
    PARAMETROS DAN 85.4% de exitos
    double alpha = 0.99;
    double L = 1000;
    double T_0 = 300.0;
    double T_min = 0.001;
    */
    double alpha = 0.9;
    double L = 5000;
    double T_0 = 150.0;
    double T_min = 0.00001;


    // int p_0 = {0,0};
    // printf("El minimo es: %f , %f \n",p_0[0],p_0[1]);
    int time_seed= time(NULL);
    int contador_exitos = 0;
    int ciclos = 100;
    for(int i =0; i<ciclos; i++){
        double *p_0 = repoios_recocidos(alpha,L,T_0,T_min,i*time_seed);
        printf("El minimo es: %f , %f \n",p_0[0],p_0[1]);
        if (p_0[0] < 0.1 && p_0[0] > -0.1 && p_0[1] < 0.1 && p_0[1] > -0.1){
            contador_exitos++;
        }
    }
    printf("El numero de exitos es: %d \n",contador_exitos);
    printf("el total de ciclos es: %d \n",ciclos);

    return 0;
}





