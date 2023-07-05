#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

float sigmoidf(float x){
    return 1.f/(1.f + expf(-x));
}
// Or-gate
float train[][3] = {
    {0,0,1},
    {0,1,1},
    {1,0,1},
    {1,1,0},
};

#define train_count (sizeof(train))/sizeof(train[0]) 

float rand_float(void){
    return (float)rand()/(float)RAND_MAX;
}

float cost(float w1, float w2, float b){
    float result = 0.0f;

    for(size_t i=0;i<train_count;i++){
        float x1 = train[i][0];
        float x2 = train[i][1];
        float y = sigmoidf(x1*w1+x2*w2+b);
        float d = y-train[i][2];
        result+=d*d;
    }
    return result /=train_count;
}

int main(){
    // srand(69);
    srand(time(0));
    float eps = 1e-1;
    float rate = 1e-1;
    float w1  = rand_float();
    float w2  = rand_float();
    float b  = rand_float();

    printf("w1 = %f,w2 = %f\n",w1,w2);

    for(int i=0;i<1000*1000;i++){
        float c = cost(w1,w2,b);
        float dw1 = (cost(w1+eps,w2,b)-c)/eps;
        float dw2 = (cost(w1,w2+eps,b)-c)/eps;
        float db = (cost(w1,w2,b+eps)-c)/eps;
        // printf("%f\n",dcost);
        w1 -= rate*dw1;
        w2 -= rate*dw2;
        b -= rate*db;
        printf("cost = %f, w1 = %f, w2= %f, b= %f\n",cost(w1,w2,b),w1,w2,b);
    }
    printf("---------------\n");
    printf("w1: %f,w2: %f, cost: %f, b:%f\n",w1,w2,cost(w1,w2,b),b);

    for(size_t i=0;i<2;i++){
        for(size_t j=0;j<2;j++){
            printf("%zu | %zu = %f\n",i,j,sigmoidf(i*w1+j*w2+b));
        }
    }

    return 0;
}