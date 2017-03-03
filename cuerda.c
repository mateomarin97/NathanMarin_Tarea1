#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 64
#define T 100.0
#define b 1.0
#define dt 0.1
#define Nt 1000
#define pi 3.141592654
float inicializar(float x);
void leapfrog(float *yp,float *yf,float *v);
float vder(int i,	float *yp,float *yf);

int main(){
  /*Inicializo la lista de las possicones y las velocidades*/
  float *yp;
  float *yf;
  float *v;
  int i;
  yp=malloc(N*sizeof(float));
  yf=malloc(N*sizeof(float));
  v=malloc(N*sizeof(float));
  for(i=0;i<N;i++){
    v[i]=0.0;
    yp[i]=inicializar(i);
    yf[i]=0.0;
  }
  /*Ahora ejecuto leapfrog*/
  leapfrog(yp,yf,v);

  return 0;
}

float vder(int i, float *yp,float *yf){
  if(i==0 || i==N-1){
    return 0.0;
  }
  else{
    return (yp[i+1]-(2*yp[i])+yf[i-1])+b*(pow(yp[i+1]-yp[i],3.0)-pow(yp[i]-yf[i-1],3.0));
  }

}



float inicializar(float x){
  return sin(pi*(float)x/(float)(N-1));
}

void leapfrog(float *yp,float *yf,float *v){
  float *vi;
  int i;
  int k;

  vi=malloc(N*sizeof(float));
  for(i=1;i<Nt;i++){
    /*Este for saca velocidades intermedias y posiciones finales*/
    for(k=0;k<N;k++){
      vi[k]= v[k]+(vder(k,yp,yf)*(dt/2.0));
      yf[k]=yp[k]+(vi[k]*dt);
    }

    for(k=0;k<N;k++){
      yp[k]=yf[k];
    }
    /*Este saca velocidades finales*/
    for(k=0;k<N;k++){
     v[k]=vi[k]+(vder(k,yp,yf)*(dt/2.0));
    }
    if(i%10==0){
      for(k=0;k<N;k++){
        if(k==N-1){
          printf("%f \n ",yp[k]);
        }
        else{
          printf("%f ",yp[k]);
        }
      }

    }
  }
}
