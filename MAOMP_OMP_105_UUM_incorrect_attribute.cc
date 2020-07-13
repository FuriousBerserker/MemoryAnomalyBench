/*
Concurrent access on an atomic counter. Inter and Intra Region.
*/
#include <stdio.h>
#define N 100000


int count(){
        int countervar = 0;
        #pragma omp parallel for private(countervar)
        for (int i=0; i<N; i++){
			#pragma omp atomic update
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
    printf("counter: %i expected: 100000\n ",countervar);
    return 0;
}