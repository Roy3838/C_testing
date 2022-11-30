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

    float f(float r){
        float d = 0.0;
        return (1+cos(12*sqrt(pow(r+d,2))))/(0.5*(pow(r+d,2)) +2 );
    }

    float sigmoid(float x){
        return 1/(1+exp(-x));
    }

    //timing variables
    clock_t start, end;

    //seleccion tiene que ser numero par
    int seleccion = 800;
    float x[seleccion/2];
    int ciclos = 1000;
    float y_n[seleccion/2];
    float sum_y = 0;
    float cumsum[seleccion/2];
    float p_n[seleccion/2];
    int indices[seleccion];
    float generaciones[ciclos][seleccion/2];
    start = clock();

    //llenar x[] linspace
    for(int i = 0; i < seleccion/2; i++){
        x[i] = roy_uniform(-3,3,3);
        generaciones[0][i] = x[i];
    }

    // genetic algorithm to optimize function
    for(int m=1; m<ciclos; m++){

        for(int k=0; k<seleccion/2; k++){
            // for the case of NaN
            if(-10<x[k] && x[k]<10)
                y_n[k]= f( x[k] );
            else
                y_n[k] = 0;
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
                    if(isnan(x[index])){
                        j--;
                    }
                    break;
                }
            }
            indices[i]=index;
        }

        
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
        void getBinaryexp(int n, int i, int binario[32]){
            int k;
                for (k = 0; k < i; k++) {
                    if ((n >> k) & 1)
                        binario[8-k] = 1;
                    else
                        binario[8-k] = 0;
                }
        }

       
        int binario[seleccion][32];
        int binario_exponente[seleccion][32];
        myfloat var[seleccion];
        for(int i = 0; i<seleccion; i++){
            var[i].f = x[indices[i]];
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
            // if(i==3){
            //     // print for debugging
            //     printf("punto de cruce: %d\n", punto_cruce);
            //     for(int k = 0; k<32; k++){
            //         printf("%d", binario[2*i][k]);
            //         }
            //     printf("\n");
            //     for(int k = 0; k<32; k++){
            //         printf("%d", binario[2*i+1][k]);
            //         }
            //     printf("\n");
            //     for(int k = 0; k<32; k++){
            //         printf("%d", lalos[i][k]);
            //         }
            //     printf("\n");
            // }

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
            x[i] = vardespues[i].f;
        }
        memcpy(generaciones[m], x, sizeof(float)*seleccion/2);
        

        // reemplazar los valores de x
        //memcpy(x, mutacion, sizeof(mutacion));    


    }
    // print time
    end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("time: %f\n", time_spent);


    FILE *faba = fopen("data/mijo_lalo.csv", "w");
    for(int k = 0; k<ciclos; k++){
        if(k%10==0){
            for (int i = 0; i < seleccion/2; i++){
                fprintf(faba, "%f ,", generaciones[k][i]);
            }
            fprintf(faba, "\n");
        }
    }
    fclose(faba);



    return 1;
}