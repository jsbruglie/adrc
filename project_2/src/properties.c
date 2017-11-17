#include <stdio.h>
#include <stdlib.h>

#define C 0
#define R 1 
#define P 2
#define I 3

int matrix[4][4] = {
    {C, I, I, I},
    {R, I, I, I},
    {P, P, P, I},
    {I, I, I, I}
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

    printf("Verifying the following properties\n\
    \t- Left distributivity\n\
    \t- Left isotonicity\n\
    \t- Right isotonicity\n\
    \t- Global optimum from local optimum\n");

    // Left distributivity
    // c prod (a plus b) = (c prod a) plus (c prod b)
    for (int a = C; a <= I; a++){
        for (int b = C; b <= I; b++){
            for (int c = C; c <= I; c++){
                tmp_1 = prod(c, plus(a,b));
                tmp_2 = plus(prod(c,a), prod(c, b));
                if (tmp_1 != tmp_2){
                    printf("a:%d b:%d c:%d exp_1:%d exp_2:%d\n", a, b, c, tmp_1, tmp_2);
                    printf("Left distributivity not verified\n");
                    break;
                }
            }
        }
    }

    // Right distributivity
    // (a plus b) prod c = (a prod c) plus (b prod c)
    for (int a = C; a <= I; a++){
        for (int b = C; b <= I; b++){
            for (int c = C; c <= I; c++){
                tmp_1 = prod(plus(a,b), c);
                tmp_2 = plus(prod(a,c), prod(b, c));
                if (tmp_1 != tmp_2){
                    printf("a:%d b:%d c:%d exp_1:%d exp_2:%d\n", a, b, c, tmp_1, tmp_2);
                    printf("Right distributivity not verified\n");
                    break;
                }
            }
        }
    }
    
    // Left isotonicity
    // a <= b implies (c prod a) <= (c prod b)
    for (int a = C; a <= I; a++){
        for (int b = C; b <= I; b++){
            for (int c = C; c <= I; c++){
                tmp_1 = prod(c,a);
                tmp_2 = prod(c,b);
                if (!implies((a <= b),(tmp_1 <= tmp_2))){
                    printf("a:%d b:%d c:%d exp_1:%d exp_2:%d\n", a, b, c, tmp_1, tmp_2);
                    printf("Left isotonicity not verified\n");
                    break;
                }
            }
        }
    }

    // Right isotonicity
    // a <= b implies (a prod c) <= (b prod c)
    for (int a = C; a <= I; a++){
        for (int b = C; b <= I; b++){
            for (int c = C; c <= I; c++){
                tmp_1 = prod(a,c);
                tmp_2 = prod(b,c);
                if (!implies((a <= b),(tmp_1 <= tmp_2))){
                    printf("a:%d b:%d c:%d exp_1:%d exp_2:%d\n", a, b, c, tmp_1, tmp_2);
                    printf("Right isotonicity not verified\n");
                    break;
                }
            }
        }
    }

    // Dijkstra sufficient property
    //  Idea: global optimum can be calculated as an extension of the local optimum
    // (a prod (b1 prod c)) plus (a prod (b2 prod c)) =
    //  = a prod ((b1 prod c) plus (b2 prod c))
    for (int a = C; a <= I; a++){
        for (int b1 = C; b1 <= I; b1++){
            for (int b2 = C; b2 <= I; b2++){
                for (int c = C; c <= I; c++){
                    tmp_1 = plus(prod(a,prod(b1,c)),prod(a,prod(b2,c)));
                    tmp_2 = prod(a, plus(prod(b1,c),prod(b2,c)));
                    if (tmp_1 != tmp_2){
                        printf("a:%d b1:%d b2:%d c:%d\n", a, b1, b2, c);
                        printf("Dijkstra property not verified\n");
                        break;
                    }
                }
            }
        }
    }
}