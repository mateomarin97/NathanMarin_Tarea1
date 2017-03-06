#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
#define N 64
#define T 1000
#define b 1.0
#define dt 0.005
#define pi 3.141592654
float inicializar(float x);
void leapfrog(float *yp,float *v);
float vder(int i,float *yp);

int main(){
  /*Inicializo la lista de las possicones y las velocidades*/
  float *yp;
  float *v;
  int i;
  
  yp=malloc(N*sizeof(float));
  v=malloc(N*sizeof(float));
  for(i=0;i<N;i++){
    v[i]=0.0;
    yp[i]=inicializar(i);
  }
  /*Ahora ejecuto leapfrog*/
  leapfrog(yp,v);

  return 0;
}

float vder(int i, float *yp){
  if(i==0 || i==N-1){
    return 0.0;
  }
  else{
    return (yp[i+1]-(2*yp[i])+yp[i-1])+b*(pow(yp[i+1]-yp[i],3.0)-pow(yp[i]-yp[i-1],3.0));
  }

}



float inicializar(float x){
  return sin(pi*(float)x/(float)(N-1));
}

void leapfrog(float *yp,float *v){
  int Nt= (int)(T/dt);
  float *vi;
  int i;
  int k;
  omp_set_num_threads(1);

  vi=malloc(N*sizeof(float));
  for(i=1;i<Nt;i++){
    /*Este for saca velocidades intermedias y posiciones finales*/
    #pragma omp parallel for private(k),shared(yp,v,vi)
       for(k=0;k<N;k++){
	 vi[k]= v[k]+(vder(k,yp)*(dt/2.0));
       }

    #pragma omp parallel for private(k),shared(yp,v,vi)
       for(k=0;k<N;k++){
	 yp[k]=yp[k]+(vi[k]*dt);
       }

    /*Este saca velocidades finales*/
    #pragma omp parallel for private(k),shared(yp,v,vi)
       for(k=0;k<N;k++){
	 v[k]=vi[k]+(vder(k,yp)*(dt/2.0));
       }
    if(i%1000==0){
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
