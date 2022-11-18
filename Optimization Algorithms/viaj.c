#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

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

int main(){
    static int ciudades = 100;

    // Metodo que regresa la distancia total recorrida por el viajero
    double dist(int ciudades, double ps[2][ciudades]){
        double distancia = 0;
        //inicializamos variables para iterar sobre memoria fija
        double x1=ps[0][0];
        double y1=ps[1][0];
        double x2=ps[0][1];
        double y2=ps[1][1];
        double x=pow(x2-x1,2);
        double y=pow(y2-y1,2);
        distancia = sqrt(x+y);
        for (int i = 1; i < ciudades; i++){
            x1=ps[0][i];
            y1=ps[1][i];
            x2=ps[0][i+1];
            y2=ps[1][i+1];
            x=pow(x2-x1,2);
            y=pow(y2-y1,2);
            distancia = distancia + sqrt(x+y);
        }
        //distancia entre primer y ultimo punto
        x1=ps[0][ciudades];
        y1=ps[1][ciudades];
        x2=ps[0][0];
        y2=ps[1][0];
        x=pow(x2-x1,2);
        y=pow(y2-y1,2);
        distancia = distancia + sqrt(x+y);
        return distancia;
    }

    /*
                    Metodo modifica la matrix dada para que sea un acomodo vecino al pasado
    */
    void vecindad(int ciudades, double ps[2][ciudades]){
        int index_swaps=1;
        for(int v=1; v<=index_swaps; v++){   
            //random index swap
            int i = rand() % (int)(ciudades-1) ;
            int j = rand() % (int)(ciudades-1) ;
            //asegurarse que j y i son diferentes
            while (i == j){
                j = rand() % (int)(ciudades-1) + 1;
            }
            double tempx=ps[0][i];
            double tempy=ps[1][i];
            ps[0][i]=ps[0][j];
            ps[1][i]=ps[1][j];
            ps[0][j]=tempx;
            ps[1][j]=tempy;
    }
    }

    // PARAMETROS DEL METODO RECOCIDO
    double alpha = 0.95;
    int L = 5000;
    double T_0 = 300;
    double T_min = 0.000000001;

    double ps[2][ciudades];
    srand(time(NULL));
    clock_t start, end;
    double cpu_time_used;

    /*
                                    PARTE DE GENERAR LOS DATOS DE LAS CIUDADES
    */

    // Se generan ciudades en numeros random de -2 a 2
    for (int i = 0; i < ciudades; i++){
        ps[0][i] = roy_uniform(-2,2,6);
        ps[1][i] = roy_uniform(-2,2,6);
    }

    // Salvar los datos iniciales para poder graficarlos
    FILE *f = fopen("data/ps.csv", "w");
    for (int i = 0; i < ciudades; i++){
        fprintf(f, "%f, %f\n", ps[0][i], ps[1][i]);
    }
    fclose(f);
    
    /*
                                                    RECOCIDO SIMULADO
    */


    // la memoria de las matrices tiene que ser estatica
    double ps_0[2][ciudades];
    double ps_1[2][ciudades];
    double ps_m[2][ciudades];
    double min_dist = 20000;
    // ps_0=ps;
    double eval_0 = 0;
    double eval_1 = 0;
    
    memcpy(ps_m, ps, sizeof(ps));
    double t_i=T_0;
    int iter=0;
    int boltzmann=0;

    start=clock();
    while(T_0 > T_min){
        T_0=alpha*T_0;
        iter++;
        if (iter%10==0){
            printf("iter: %d, T_0: %f, min_dist: %f b_g: %d\n", iter, T_0*1000, min_dist, boltzmann);
        }
        //
        memcpy(ps_0, ps_m, sizeof(ps));
        for(int i = 0; i<L; i++){
            //crear ps_1
            memcpy(ps_1, ps_0, sizeof(ps));
            //evaluar ps_0
            eval_0=dist(ciudades,ps_0);
            //crear vecindad
            vecindad(ciudades, ps_1);
            //evaluar vecindad
            eval_1=dist(ciudades,ps_1);
            
            if (eval_1 < eval_0){
                memcpy(ps_0, ps_1, sizeof(ps));
                if (eval_1 < min_dist){
                    min_dist = eval_1;
                    memcpy(ps_m, ps_1, sizeof(ps));
                }
            }
            
            else{
                double r = roy_uniform(0,1,2);
                double delta = eval_1 - eval_0;
                double prob = exp(-delta/T_0);
                if (r < prob){
                    memcpy(ps_0, ps_1, sizeof(ps));
                }

                }
            }

            }
    printf("Distancia: %f \n", dist(ciudades,ps_m));

    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tiempo: %f segundos\n", cpu_time_used);

    // Guardar resultados finales
    FILE *fooba = fopen("data/ps2.csv", "w");
    for (int i = 0; i < ciudades; i++){
        fprintf(fooba, "%f, %f\n", ps_0[0][i], ps_0[1][i]);
    }
    fclose(fooba);
    FILE *fp = popen("/usr/bin/python \"/home/jay/c_aber/Optimization Algorithms/viajeroplotter.py\"", "w");
    return 0;
}

    


    


