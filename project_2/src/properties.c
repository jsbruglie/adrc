#include <stdio.h>
#include <stdlib.h>

#define C 0
#define R 1 
#define P 2
#define I 3

int matrix[3][4] = {
    {P, P, P, I},
    {R, I, I, I},
    {C, I, I, I}
};
 
inline int plus(int a, int b){
    return (a < b)? a : b;
}

inline int prod(int a, int b){
    return matrix[a][ b];    
}

inline int implies(int a, int b){
    return (!a || (a && b));
}

int main(){

    int tmp_1, tmp_2;    

    // Left distributivity
    // c prod ( a plus b ) = (c prod a ) plus (c prod b)
    for (int a = C; a < I; a++){
        for (int b = C; b < I; b++){
            for (int c = C; c < I; c++){
                tmp_1 = prod(c, plus(a,b));
                tmp_2 = plus(prod(c,a), prod(c, b));
                if (tmp_1 != tmp_2){
                    printf("a:%d b:%d c:%d exp_1:%d exp_2:%d\n", a, b, c, tmp_1, tmp_2);
                    printf("Left distributivity not verified\n");
                    exit(1);
                }
            }
        }
    }
    
    // Left isotonicity
    // a < b implies (c prod a) < (c prod b)
    for (int a = C; a < I; a++){
        for (int b = C; b < I; b++){
            for (int c = C; c < I; c++){
                tmp_1 = prod(c,a);
                tmp_2 = prod(c,b);
                if (!implies((a <= b),(tmp_1 <= tmp_2))){
                    printf("a:%d b:%d c:%d exp_1:%d exp_2:%d\n", a, b, c, tmp_1, tmp_2);
                    printf("Left isotonicity not verified\n");
                    exit(1);
                }
            }
        }
    }

    // Dijkstra sufficient property
    // (a prod (b1 prod c)) plus (a prod (b2 prod c)) =
    //  = a prod ((b1 prod c) plus (b2 prod c))
    for (int a = C; a < I; a++){
        for (int b1 = C; b1 < I; b1++){
            for (int b2 = C; b2 < I; b2++){
                for (int c = C; c < I; c++){
                    tmp_1 = plus(prod(a,prod(b1,c)),prod(a,prod(b2,c)));
                    tmp_2 = prod(a, plus(prod(b1,c),prod(b2,c)));
                    if (tmp_1 != tmp_2){
                        printf("a:%d b1:%d b2:%d c:%d\n", a, b1, b2, c);
                        printf("Dijkstra property not verified\n");
                        exit(1);
                    }
                }
            }
        }
    }
    printf("All properties verified\n");
}