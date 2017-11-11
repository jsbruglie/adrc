#include <stdio.h>

const int C = 0;
const int R = 1;
const int P = 2;
const int I = 3;

inline int func_plus(int a, int b){
    return (a < b)? a : b;
}

inline int func_prod(int a, int b){
    if (a == C){
        if (b == C){
            return C;
        }
    } else if (a == R){
        if (b == C){
            return R;
        }
    } else if (a == P){
        if (b != I){
            return P;
        }
    }
    return I;
}

int main(){

    int exp_1[4*4*4]{I};
    int exp_2[4*4*4]{I};
    int tmp_1, tmp_2;    

    for (int a = C; a < I; a++){
        for (int b = C; b < I; b++){
            for (int c = C; c < I; c++){
                tmp_1 = func_plus(func_prod(a,b),func_prod(a,c));
                tmp_2 = func_prod(a, func_plus(b,c));
                if (tmp_1 != tmp_2)
                    printf("a:%d b:%d c:%d exp_1:%d exp_2:%d\n", a, b, c, tmp_1, tmp_2);
                exp_1[16 * a + 4 * b + c] = tmp_1;
                exp_2[16 * a + 4 * b + c] = tmp_2;
            }
        }
    }

}
