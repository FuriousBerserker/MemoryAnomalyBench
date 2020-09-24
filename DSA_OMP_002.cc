/*
Matrix Vector multiplication without application errors.
*/


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define C 512


int *a;
int *b;
int *c;


int init(){
    for(int i=0; i<C; i++){
        for(int j=0; j<C; j++){
            b[j+i*C]=1;
        }
        a[i]=1;
        // c[i]=0;
    }
    // c[5] = 1;
    // b[5] = 1;
    // a[5] = 1;
        return 0;
}


int Mult(){
    #pragma omp parallel for
    for(int i=0; i<C; i++){
        for(int j=0; j<C; j++){
            c[i]+=b[j+i*C]*a[j];
        }
    }
    return 0;
}

int check(){
    bool test = false;
    for(int i=0; i<C; i++){
        if(c[i]!=C){
            test = true;
        }
    }
    printf("Memory Access Issue visible: %s\n",test ? "true" : "false");
    return 0;
}

int main(){
    a = new int[C];
    b = new int[C*C];
    c = new int[C];
    init();
    Mult();
    check();
    delete[] a;
    delete[] b;
    delete[] c;
    return 0;
}
