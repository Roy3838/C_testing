#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
/*
                        HELPER METHODS SECTION
*/


float roy_uniform(float a, float b, float decimales){
    /*
    Funcion que genera un numero aleatorio uniforme entre a y b
    con una cantidad de decimales dada.
    */
    b = b*pow(10,decimales);
    a = a*pow(10,decimales);
    int r = rand() % (int)(b-a) + a;
    return (float)r/pow(10,decimales);
}
 
// Function to convert a binary array
// to the corresponding integer


/*
                        MAIN SECTION
*/


int main(){

    float f(float x, float y){
        //eggshell function
        int d=0;
        return pow(x+d,2) + pow(y+d,2) + 25*(pow(sin(x+d),2) + pow(sin(y+d),2));
    }

    float sigmoid(float x){
        return 1/(1+exp(x-3));
    }



    //seleccion tiene que ser numero par
    int seleccion = 1000;
    int dimensiones = 2;
    float x[seleccion/2][dimensiones];
    int ciclos = 1000;
    float y_n[seleccion/2];
    float sum_y = 0;
    float cumsum[seleccion/2];
    float p_n[seleccion/2];
    int indices[seleccion];
    float generaciones[ciclos][seleccion/2][dimensiones];
    // create a uniform distribution of x and y
    for (int i = 0; i < seleccion/2; i++){
        for (int j = 0; j < dimensiones; j++){
            x[i][j] = roy_uniform(-10, 10, 2);
        }
    }


    for(int m=1; m<ciclos; m++){

        for(int k=0; k<seleccion/2; k++){
            // for the case of NaN
            y_n[k]= sigmoid( f( x[k][0], x[k][1] ));
            if(k==0)
                cumsum[k] = y_n[k];
            else
                cumsum[k] = cumsum[k-1] + y_n[k];
        }

        // el cumsum
        for(int m=0; m<seleccion/2; m++){
            p_n[m] = cumsum[m]/cumsum[seleccion/2-1];
        }

        float eval = 0;
        int index = 0;
        /*
                        OBTENER LOS INDICES DE LA ACUMULADA DE LA DISTRIBUCION
        */

        for(int i = 0; i<seleccion; i++){
            eval= roy_uniform(0,1,5);
            for(int j = 0; j<seleccion; j++){
                if(p_n[j] > eval){
                    index = j;
                    //remove NaN
                    if(isnan(x[index][0] + x[index][1])){
                        j--;
                    }
                    break;
                }
            }
            indices[i]=index;
        }

        /*
                        CREAR LA NUEVA POBLACION
        */
       float hijos [seleccion/2][dimensiones];
       for(int i =0 ; i<seleccion/2; i++){
            for(int j = 0; j<dimensiones; j++){
                float papa1=x[indices[2*i]][j];
                float papa2=x[indices[2*i + 1]][j];
                if(papa1 - papa2 < 1 && papa1 - papa2 > -1){
                    hijos[i][j] = papa1;
                }
                else{
                    if(papa1 > papa2){
                        hijos[i][j] = roy_uniform(x[indices[2*i + 1]][j], x[indices[2*i]][j], 2);
                    }
                    else
                        hijos[i][j] = roy_uniform(x[indices[2*i]][j], x[indices[2*i + 1]][j], 2);
                    
                    }
                }
            
        }

        /*
                        MUTACION
        */
        for(int i =0 ; i<seleccion/2; i++){
            if(rand()%2 ==0){
                for(int j = 0; j<dimensiones; j++){
                    x[i][j] = x[i][j] + roy_uniform(-0.1, 0.1, 2);
                }
            }
        }

        /*
                        GUARDAR LA GENERACION
        */
        for(int i =0 ; i<seleccion/2; i++){
            for(int j = 0; j<dimensiones; j++){
                generaciones[m][i][j] = x[i][j];
            }
        }

    }

        

    

    // FILE *faba = fopen("data/lalomijo.csv", "w");
    // for(int k = 0; k<ciclos; k++){
    //     if(k%10==0){
    //         for (int i = 0; i < seleccion/2; i++){
    //             fprintf(faba, "%f ,", generaciones[k][i]);
    //         }
    //         fprintf(faba, "\n");
    //     }
    // }
    // fclose(faba);



    return 1;
}