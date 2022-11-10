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

double f_x(double x, double y){

    int d = 0;
    double primerarg= pow(x+d,2) + pow(y+d,2);
    double segundoarg = pow(sin(x+d),2) + pow(sin(y+d),2);
    return  primerarg + 25*segundoarg;

}


int main(){
    // Simulated Annealing
    double seed = 10;
    int range= 100;
    clock_t start, end;
    double cpu_time_used;
    // change rand() seed dependent of time
    srand(time(NULL));
    double x_0 = roy_uniform(-50,50,2);
    double y_0 = roy_uniform(-50,50,2);
    double p_0[] = {x_0,y_0};
    double T_0 = 389;
    double T_min = 0.00001;
    double p_1[] = {p_0[0] ,p_0[1]};
    int resolucion = 1000;
    
    // guardar la trayectoria
    double x[100000];
    double y[100000];
    int contador = 0;

    int L = 1000;
    printf("El inicial es: %f , %f \n",p_0[0],p_0[1]);
    start = clock();

    while(T_0 > T_min){
        T_0=0.875*T_0;
        for(int i = 0; i<L; i++){
            // double x_1 = (rand()%10000)*0.0001 - 0.5; // = uniform(-0.5,0.5) pero con 0.01 
            // double y_1 = (rand()%10000)*0.0001 - 0.5;
            double x_1 = roy_uniform(-0.5,0.5,3);
            double y_1 = roy_uniform(-0.5,0.5,3);
            double p_1[] = {p_0[0] + x_1 ,p_0[1] + y_1};
            double valor_p_1 = f_x(p_1[0],p_1[1]);
            double valor_p_0 = f_x(p_0[0],p_0[1]);
            
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
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("%f seconds \n",cpu_time_used);

    printf("Cero en : %f , %f \n",p_0[0],p_0[1]);
    printf("iteraciones : %d \n",contador);

    

    
    



    return 0;
}









