#include <stdio.h>
#include <stdlib.h>
#include <simd.h>

static inline unsigned long rpcc()                                                                                                                                          
{
    unsigned long time;
    asm("rtc %0": "=r" (time) : );
            return time;
}

int main(){

    int i;
    unsigned long st[3], ed[3];

    double *A = malloc(129 * sizeof(double));
    double *B = malloc(129 * sizeof(double));
    double *C = malloc(129 * sizeof(double));

    doublev4 A_v4, B_v4, C_v4;

    for(i = 0; i < 129; i++){

        A[i] = 0.2;
        B[i] = 0.2;

    }

    /*no simd*/
    st[0] = rpcc();
    for(i = 0; i < 128; i++){

        C[i] = A[i] * B[i];

    }
    ed[0] = rpcc();

    /*simd*/
	st[1] = rpcc();
    for(i = 0; i < 32; i++){

        simd_load(A_v4, &A[i * 4]);
        simd_load(B_v4, &B[i * 4]);
        C_v4 = simd_vmuld(A_v4, B_v4); 
        simd_store(C_v4,&C[i * 4]);

    }
    ed[1] = rpcc();

    /* non-aligned simd*/
    st[2] = rpcc();
    for(i = 0; i < 32; i++){

        simd_load(A_v4, &A[i * 4 + 1]);
        simd_load(B_v4, &B[i * 4 + 1]);
        C_v4 = simd_vmuld(A_v4, B_v4); 
        simd_store(C_v4,&C[i * 4 + 1]);

    }
    ed[2] = rpcc();


    printf("No simd %d; Aligned simd = %d; Non-aligned simd = %d"  ,ed[0] - st[0], ed[1] - st[1], ed[2] - st[2]);

    return 0;
    

}
