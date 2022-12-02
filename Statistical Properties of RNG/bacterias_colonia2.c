
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(){
    int N = 100000000;
    double pVal[20];

    for(int i = 0; i < 20; i++) {
        pVal[i] = (int) pow(2,i);
    }

    double probVal[20];
    for(int i = 0; i < 20; i++) {
        probVal[i] = pow(0.5,i);
    }

    return 0;
}
