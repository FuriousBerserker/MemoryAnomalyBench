#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define C 512


int *a;
int *b;


int init(){
    for(int i=0; i<C; i++){
        a[i]=0;
        b[i]=1;
    }
    // c[5] = 1;
    // b[5] = 1;
    // a[5] = 1;
        return 0;
}

void lastpriv() {
    int i=0;

    #pragma omp parallel for
    for (i=0; i<C-1; i++)
        a[i] = b[i] + b[i];
    printf("%d\n", i);
    a[i]=b[i];
}


int check(){
    bool test = false;
    for(int i=0; i<C; i++){
        if (i == C - 1) {
            if (a[i] != 1) {
                printf("a[%d] = %d\n", i, a[i]);
                test = true;
            }
        } else {
            if (a[i] != 2) {
                printf("a[%d] = %d\n", i, a[i]);
                test = true;
            }
        }
    }
    printf("Memory Access Issue visible: %s\n",test ? "true" : "false");
    return 0;
}

int main(){
    a = new int[C];
    b = new int[C];
    init();
    lastpriv();
    check();
    delete[] a;
    delete[] b;
    return 0;
}