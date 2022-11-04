#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(){
    double S0 = 997;
    double I0 = 3;
    double R0 = 0;
    double B = 0.25;
    double G = 0.05;
    double T = 100;
    double dt = 0.1;
    int NT = T/dt;
    double N = 1000;

    // time vector linspace
    double t[NT];
    for (int i=0; i<NT; i++){
        t[i] = i*dt;
    }

    //initialize the vectors
    double S[NT];
    double I[NT];
    double R[NT];

    //initial conditions
    S[0] = S0;
    I[0] = I0;
    R[0] = R0;


    //iterate using finite diferences
    for (int i=0; i<NT-1; i++){
        S[i+1]=S[i]*(-B*I[i]/N*dt + 1);
        I[i+1]=I[i]*(B*S[i]/N*dt - G*dt + 1);
        R[i+1]=G*I[i]*dt + R[i];
    }

    //Plotting FML :(

    //PLOTTING DE LA FRECUENCIA RELATIVA A TRAVES DEL TIEMPO
        FILE *fpPuntos=fopen("puntos1.txt","w"); // se crea un archivo de texto para guardar los valores del dado
        for (int i=1; i<N; i++){
            if (i%1==0){
                fprintf(fpPuntos,"%f %f \n",t[i],S[i]);
            }
        }
        fclose(fpPuntos);
        FILE *fp2Puntos=fopen("puntos2.txt","w"); // se crea un archivo de texto para guardar los valores del dado
        for (int i=1; i<N; i++){
            if (i%1==0){
                fprintf(fpPuntos,"%f %f \n",t[i],I[i]);
            }
        }
        fclose(fp2Puntos);
        FILE *fp3Puntos=fopen("puntos3.txt","w"); // se crea un archivo de texto para guardar los valores del dado
        for (int i=1; i<N; i++){
            if (i%1==0){
                fprintf(fpPuntos,"%f %f \n",t[i],R[i]);
            }
        }

    // plot both files with gnuplot
    FILE *fp = popen("gnuplot -persist", "w");
    fprintf(fp, "plot \"puntos1.txt\" with lines, \"puntos2.txt\" with lines, \"puntos3.txt\" with lines \n");
    


    return 0;
}