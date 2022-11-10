// def f(x,y):
//     return x**2 + y**2 + 25*(np.sin(x)**2 + np.sin(y)**2)

// def annealing(T_0, L, delta_uniforme):

//     """ COMPUTING THE OPTIMIZATION PATH """
//     x_0=rd.uniform(-5,5)
//     y_0=rd.uniform(-5,5)
//     p_0=np.array([x_0,y_0])
//     T_0_i=T_0
//     p_1=p_0
//     ciclos=0
//     contador_boltzmann=0
//     contador_zi_cuajo=0


//     while (T_0>0.01):
//         T_0=T_0*0.99
//         #print(p_1)
//         # make color change according to temperature RED -> BLUE
//         color=(T_0/T_0_i,0,1-T_0/T_0_i)
//         plt.plot(p_0[0],p_0[1],'ro',color=color)
//         for i in range(L):
//             ciclos+=1
//             p_1=[rd.uniform(-0.1,0.1)+p_0[0],rd.uniform(-0.1,0.1)+p_0[1]]
//             if (f(p_1[0],p_1[1])<f(p_0[0],p_0[1])):
//                 contador_zi_cuajo+=1
//                 p_0=p_1
//             # if not Boltzmann Gibbz
//             else:
//                 if (rd.uniform(0,1)<np.exp(-f(p_1[0],p_1[1])/T_0)):
//                     contador_boltzmann+=1
//                     p_0=p_1
    
//     return(np.abs(p_1))

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// in C
double f(double x, double y){
    return pow(x,2) + pow(y,2) + 25*(pow(sin(x),2) + pow(sin(y),2));
}

int main(){
    // COMPUTING THE OPTIMIZATION PATH
    double x_0 = rand()%100*0.01;
    double y_0 = rand()%100*0.01;
    double p_0[] = {x_0,y_0};
    double T_0 = 100;
    double T_min = 0.1;
    double p_1[] = {p_0[0] ,p_0[1]};
    int L = 100;

    while(T_0 > 0.1){
        T_0 = T_0*0.99;
        for(int i = 0; i < L; i++){
            p_1[0] = rand()%100*0.01 + p_0[0];
            p_1[1] = rand()%100*0.01 + p_0[1];
            if(f(p_1[0],p_1[1]) < f(p_0[0],p_0[1])){
                p_0[0] = p_1[0];
                p_0[1] = p_1[1];
            }
            else{
                if(rand()%100*0.01 < exp(-f(p_1[0],p_1[1])/T_0)){
                    p_0[0] = p_1[0];
                    p_0[1] = p_1[1];
                }
            }
        }
        printf("p_0 = (%f,%f)", p_0[0],p_0[1]);
    }

    return 0;
}