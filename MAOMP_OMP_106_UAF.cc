#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    #pragma omp parallel 
    {
        #pragma omp single 
        {
                #pragma omp task 
                {
                    int a = 10;
                    printf("parent: %p\n", &a);
                    #pragma omp task shared(a)
                    {
                        sleep(2);
                        printf("child: %p\n", &a);
                        if (a > 0) {
                            printf("a = %d\n", a);
                        }
                        printf("child terminate\n");
                    }
                    printf("parent terminate\n");
                }
                printf("single terminate\n");
        }
    }

    return 0;
}