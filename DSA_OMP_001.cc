/*
Counter incrementation with the reduction clause. Intra Region.
*/
#include <stdio.h>
#define N 100000

//int countervar = 0;

int count(){
    int countervar;
    #pragma omp parallel for reduction(+:countervar)
    for (int i=0; i<N; i++){
        countervar++;
    }
    return countervar;
}

int main(){
    int countervar;
    countervar = count();
    if (countervar != N) {
        printf("error observed\n");
    }
    printf("counter: %i expected: 100000\n",countervar);
    return 0;
}
