#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <malloc.h>
#include <complex.h>
/*
NO CUAJO VOY A HACERLO EN PYTHON
*/


double complex gauss(double complex x,double complex y,double complex w0){
    return cexp(-(cpow(x,2)+cpow(y,2))/cpow(w0,2));
}

double complex interferencia_gauss(double complex x,double complex y,double complex w0,double complex phi){
    // if return = A+B
    // double complex A = cexp(I*phi*x)*gauss(x,y,w0);
    // double complex B = exp(-I*phi*x)*gauss(x,y,w0);
    return cexp(I*phi*x)*gauss(x,y,w0)+exp(-I*phi*x)*gauss(x,y,w0);
}

double complex vortex(double complex x, double complex y, double complex w0, double complex l){
    // if return = A*B*C
    // double complex A = cpow(csqrt(cpow(x,2) + cpow(y,2)), cabs(l));
    // double complex B = cexp(-(cpow(x,2) + cpow(y,2))/cpow(w0,2));
    // double complex C = cexp(I*l*atan2(y,x));
    return  cpow(csqrt(cpow(x,2) + cpow(y,2)), cabs(l))*cexp(-(cpow(x,2) + cpow(y,2))/cpow(w0,2))*cexp(I*l*atan2(y,x));
}


int main(){

    //inicializamos constantes
    double w0=1;
    double x_max = 3*w0;
    double a= 0.75*w0;
    int puntos = 512;
    int N = 256;
    //in MATLAB
    //xs = xmax*(2/puntos)*(-puntos/2:puntos/2-1);
    // in C
    double xs[puntos];
    for(int i = 0; i<puntos; i++){
        xs[i] = x_max*(2/puntos)*(-puntos/2+i);
    }

    //hacaer un meshgrid
    //double complex X = repmat(xs,N,1);
    
    //call gauss function and print result
    // double complex result = gauss(x,y,w0);
    // double complex vortexresult = vortex(x,y,w0,1.0 + 1.0*I);
    // double complex interferenceresult = interferencia_gauss(x,y,w0,1.0 + 1.0*I);

    // make a complex number matrix 
    double complex matrix[3][3];

    // printf("result is : %f + %f*I\n",creal(result),cimag(result));
    // printf("vortex result is : %f + %f*I\n",creal(vortexresult),cimag(vortexresult));
    // printf("interferencia result is : %f + %f*I",creal(interferenceresult),cimag(interferenceresult));

    return 0;
}