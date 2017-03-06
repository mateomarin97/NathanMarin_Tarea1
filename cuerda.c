#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
#define N 64
#define T 100
#define b 1.0
#define dt 0.005
#define pi 3.141592654
float inicializar(float x);
void leapfrog(float *yp,float *v);
float vder(int i,float *yp);
float A(int k, float *yp);
float Ap(int k, float *v);
float w2(int k);

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

float A(int k, float *yp){
  float suma=0;
  int i;
  for(i=0;i<N;i++){
    suma+= yp[i]*sin((i*k*pi)/(float)(N+1));
  }
  return pow(2.0/(N+1),0.5)*suma;
  
}

float Ap(int k, float *v){
  float suma=0;
  int i;
  for(i=0;i<N;i++){
    suma+= v[i]*sin((i*k*pi)/(float)(N+1));
  }
  return pow(2.0/(N+1),0.5)*suma;

}
/*Funcion omega al cuadrado*/
float w2(int k){
  return 4.0*pow(sin((k*pi)/((2.0*N)+2.0)),2.0);

}


void leapfrog(float *yp,float *v){
  int Nt= (int)(T/dt);
  float *vi;
  int i;
  int k;
  int modulo = (int)(Nt/1000);
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
    if(i%modulo==0){
      printf("%f ",(pow(Ap(1,v),2.0)+w2(1)*pow(A(1,yp),2.0))/2.0);
      printf("%f ",(pow(Ap(2,v),2.0)+w2(2)*pow(A(2,yp),2.0))/2.0);
      printf("%f \n ",(pow(Ap(3,v),2.0)+w2(3)*pow(A(3,yp),2.0))/2.0);
	

    }
  }
}
