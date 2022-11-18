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
    static int ciudades = 100;
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

    void vecindad(int ciudades, double ps[2][ciudades]){
        int index_swaps=1;
        for(int v=1; v<=index_swaps; v++){   
            //random index swap
            int i = rand() % (int)(ciudades-1) ;
            int j = rand() % (int)(ciudades-1) ;
            // make sure i and j are different
            while (i == j){
                j = rand() % (int)(ciudades-1) + 1;
            }
            //printf("i: %d, j: %d \n", i, j);
            double tempx=ps[0][i];
            double tempy=ps[1][i];
            ps[0][i]=ps[0][j];
            ps[1][i]=ps[1][j];
            ps[0][j]=tempx;
            ps[1][j]=tempy;
        // make ps_1 equal to ps
        // for (int i = 0; i < ciudades; i++){
        //     ps_1[0][i] = ps[0][i];
        //     ps_1[1][i] = ps[1][i];
        // }
    }
    }
    
    double alpha = 0.95;
    int L = 2000;
    double T_0 = 3;
    double T_min = 0.0000001;
    // test the vecindad method SI FUNCIONO ALV " :D "- Copilot
    // double a[2][8] = {{1,2,3,4,5,6,7,8},{1,2,3,4,5,6,7,8}};
    // vecindad(8,a);

    
    double ps[2][ciudades];
    //se generan las ciudades en un circulo
    // for (int i = 0; i < ciudades; i++){
    //     ps[0][i] = cos(2*3.1416*i/ciudades);
    //     ps[1][i] = sin(2*3.1416*i/ciudades);
    // }

    // se generan ciudades en numeros random de -2 a 2
    for (int i = 0; i < ciudades; i++){
        ps[0][i] = roy_uniform(-2,2,6);
        ps[1][i] = roy_uniform(-2,2,6);
    }

    // save ps[0] in a file to plot using python
    FILE *f = fopen("data/ps.csv", "w");
    for (int i = 0; i < ciudades; i++){
        fprintf(f, "%f, %f\n", ps[0][i], ps[1][i]);
    }
    fclose(f);
    

    double ps_0[2][ciudades];
    double ps_1[2][ciudades];
    double ps_n[2][ciudades];
    double ps_m[2][ciudades];
    double min_dist = 20000;
    // ps_0=ps;
    double eval_0 = 0;
    double eval_1 = 0;
    
    memcpy(ps_m, ps, sizeof(ps));
    double t_i=T_0;
    
    while(T_0 > T_min){
        T_0=alpha*T_0;
        printf("percentage: %f \n", 100-(T_0/t_i));
        memcpy(ps_0, ps_m, sizeof(ps));
        for(int i = 0; i<L; i++){
            memcpy(ps_1, ps_0, sizeof(ps));
            eval_0=dist(ciudades,ps_0);
            // check if vecindad method does what it is supposed to do
            //printf("ps_0: %f, %f, %f, %f, %f \n" , ps_0[0][0], ps_0[1][0], ps_0[0][1], ps_0[1][1], ps_0[0][2]);
            vecindad(ciudades, ps_1);
            //printf("ps_0: %f, %f, %f, %f, %f \n" , ps_0[0][0], ps_0[1][0], ps_0[0][1], ps_0[1][1], ps_0[0][2]);
            eval_1=dist(ciudades,ps_1);
            
            if (eval_1 < eval_0){
                // copy array in a memory efficient way
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
                if (r < prob){ // si el numero aleatorio es menor que e^(-deltaE/T)
                    memcpy(ps_0, ps_1, sizeof(ps));
                }

                }
            }

            }
    printf("distancia: %f \n", dist(ciudades,ps_0));


    FILE *fooba = fopen("data/ps2.csv", "w");
    for (int i = 0; i < ciudades; i++){
        fprintf(fooba, "%f, %f\n", ps_0[0][i], ps_0[1][i]);
    }
    fclose(fooba);
    return 0;
}

    


    


