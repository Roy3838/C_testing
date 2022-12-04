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

typedef union {
    float f;
    struct
    {
 
        // Order is important.
        // Here the members of the union data structure
        // use the same memory (32 bits).
        // The ordering is taken
        // from the LSB to the MSB.
 
        unsigned int mantissa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
 
    } raw;
} myfloat;
 
// Function to convert a binary array
// to the corresponding integer
unsigned int convertToInt(int* arr, int low, int high)
{
    unsigned f = 0, i;
    for (i = high; i >= low; i--) {
        f = f + arr[i] * pow(2, high - i);
    }
    return f;
}


/*
                        MAIN SECTION
*/


int main(){


    static int n = 5;

    float dist(int seleccion, int n, float x[seleccion][n]){
        float x_sum = 0;

        float c[5] = {0.1, 0.2, 0.2, 0.4, 0.4};
        float A[5][4] = {{4,4,4,4},{1,1,1,1},{8,8,8,8},{6,6,6,6},{3,7,3,7}};

        for(int i = 0; i < 5; i++){
            for(int j = 0; j<n; j++){
                float div = 1/(pow(2,abs(x[seleccion][j]-A[i][j])) + c[i]);
                x_sum += div;
            }
        }
        x_sum = 1/(1+exp(-x_sum));
        return x_sum;
    }

    float sigmoid(float x){
        return 1/(1+exp(-x));
    }

    //seleccion tiene que ser numero par
    int seleccion = 800;
    float x[seleccion/2][n];
    int ciclos = 1000;
    float y_n[seleccion/2];
    float sum_y = 0;
    float cumsum[seleccion/2];
    float p_n[seleccion/2];
    int indices[seleccion];
    
    //llenar x[] linspace
    for(int i = 0; i < seleccion/2; i++){
        for(int j = 0; j < n; j++){
            x[i][j] = roy_uniform(0,10,5);
        }
    }

    // genetic algorithm to optimize function
    for(int m=1; m<ciclos; m++){

        for(int k=0; k<seleccion/2; k++){
            // for the case of NaN
            //if(-10<x[k] && x[k]<10)
            y_n[k]= dist( seleccion/2,n, x[k][n] );
            //else
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
                    // //remove NaN
                    // if(isnan(x[index])){
                    //     j--;
                    // }
                    // break;
                }
            }
            indices[i]=index;
        }

            
    float generaciones[ciclos][seleccion/2];


    // PARA P DIMENSIONES
    for(int p = 0; p<n; p++){
        
        float x_i[seleccion/2];
        memcpy(x_i, x[p], sizeof(x_i));
            /*
                            CONVERSION DE FLOAT IEEE-754 A BINARIO
            */
            void getBinary(int n, int i, int desface, int binario[32]){
            int k;
                // for (k = i - 1; k >= 0; k--) {
                //     if ((n >> k) & 1)
                //         binario[31-k] = 1;
                //     else
                //         binario[31-k] = 0;
                // }
                for (k = 0; k < i; k++) {
                    if ((n >> k) & 1)
                        //binario[31-k] = 1;
                        //binario[8-k] = 1;
                        binario[desface-k] = 1;
                    else
                        //binario[31-k] = 0;
                        //binario[8-k] = 0;
                        binario[desface-k] = 0;
                }
            }


        
            int binario[seleccion][32];
            int binario_exponente[seleccion][32];
            myfloat var[seleccion];
            for(int i = 0; i<seleccion; i++){
                var[i].f = x_i[indices[i]];
                binario[i][0]=var[i].raw.sign;
                getBinary(var[i].raw.exponent, 8, 8, binario[i]);
                getBinary(var[i].raw.mantissa, 23, 31, binario[i]);

            }


            /*
                            CRUCE DE LOS NUMEROS BINARIOS
            */
            int lalos[seleccion/2][32];
            for (int i = 0; i < seleccion/2; i++){
                int punto_cruce = rand() % 31;
                // recorre los bits
                if(rand()%2==0){
                    for(int k = 0; k<32; k++){
                        lalos[i][k]=binario[i][k];
                    }
                }
                else{
                    for(int k = 0; k<32; k++){
                        if(k<punto_cruce){
                            lalos[i][k] = binario[2*i][k];
                        }
                        else{
                            lalos[i][k] = binario[2*i+1][k];
                        }
                    }
                }

            }

            /*
                            MUTACION DE LOS NUMEROS BINARIOS
            */
            int mutaciones = seleccion/10;
            for(int i = 0; i<mutaciones; i++){
                int indice = rand() % seleccion/2;
                int bit = rand() % 32;
                if(lalos[indice][bit] == 0){
                    lalos[indice][bit] = 1;
                }
                else{
                    lalos[indice][bit] = 0;
                }

            }
            
            /*
                            CONVERSION DE BINARIO A FLOAT IEEE-754
            */
            unsigned mutacion[seleccion/2];
            myfloat vardespues[seleccion/2];
            for(int i = 0; i<seleccion/2; i++){
                mutacion[i] = convertToInt(lalos[i], 9, 31);
                vardespues[i].raw.mantissa = mutacion[i];
                mutacion[i] = convertToInt(lalos[i], 1, 8);
                vardespues[i].raw.exponent = mutacion[i];
                vardespues[i].raw.sign = 0;
            }
            for(int i = 0; i<seleccion/2; i++){
                x_i[i] = vardespues[i].f;
            }
            memcpy(x[p], x_i, sizeof(float)*seleccion/2);
            
        }
        // reemplazar los valores de x
        //memcpy(x, mutacion, sizeof(mutacion));    


    }



    return 1;
}