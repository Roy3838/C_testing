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



int main(){
    
    double dist(double ps[2][4]){
        double dist = 0;
        dist = sqrt(pow((ps[1][0]-ps[0][0]),2)+pow((ps[1][1]-ps[0][1]),2));
        for (int i = 1; i < ciudades; i++){
            dist = dist + sqrt(pow(ps[i][0]-ps[i+1][0],2)+pow(ps[i][1]-ps[i+1][1],2));
        }
        return dist;
    }

    double vecindad(double ps[2][4]){
        //random index swap
        int i = rand() % (int)(ciudades-1) + 1;
        int j = rand() % (int)(ciudades-1) + 1;
        double tempx=ps[0][i];
        double tempy=ps[1][i];
        ps[0][i]=ps[0][j];
        ps[1][i]=ps[1][j];
        ps[0][j]=tempx;
        ps[1][j]=tempy;
        return ps;
    }
    
    double alpha = 0.99;
    int L = 100;
    double T_0 = 389;
    double T_min = 0.01;


    static int ciudades = 4;
    double ps[2][ciudades];
    //se generan las ciudades en un circulo
    for (int i = 0; i < ciudades; i++){
        ps[0][i] = cos(2*3.1416*i/ciudades);
        ps[1][i] = sin(2*3.1416*i/ciudades);
    }

    double ps_0[2][ciudades];
    double ps_1[2][ciudades];
    ps_0=ps;
    
    while(T_0 > T_min){
        T_0=alpha*T_0;
        for(int i = 0; i<L; i++){
            ps_1 = ps_0
            double eval_0=dist(ps_0);
            ps_1 = vecindad(ps_1);
            double eval_1=dist(ps_1);
            
            if (eval_1<eval_0){
                // copy array in a memory efficient way
                memcpy(ps_0, ps_1, sizeof(ps_0));
            }
            // else{
                
            //     if (r < e){ // si el numero aleatorio es menor que e^(-deltaE/T)
                    
            //     }
            // }

            }

        }
    
    return 0;
}

