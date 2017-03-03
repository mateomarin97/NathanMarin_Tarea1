#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define T 40.0
#define rho 10.0
#define L 100.0
#define Np 1000
#define h 0.1001001
#define dimy 100000000
#define dimv 1000
#define c2 4.0
#define h2 0.01002003
#define dt 0.002
float inicializar(float x);
void leapfrog(float *y,float *v);
float vder(int i,float *y);

int main(){
  /*Inicializo la lista de las possicones y las velocidades*/
  float *y;
  float *v;
  int i;
  y=malloc(dimy*sizeof(float));
  v=malloc(dimv*sizeof(float));
  for(i=0;i<dimv;i++){
    v[i]=0.0;
    y[i]=inicializar(h*i);
  }
  /*Ahora ejecuto leapfrog*/
  leapfrog(y,v);
  /*Imprimo los datos*/
  int k;
  for(k=0;k<(dimy/dimv);k++){
    if(k%500==0){
      for(i=0;i<dimv;i++){
	if(i%dimv==999){
	  printf("%f \n",y[(k*dimv)+i]);
	}
	else{
	  printf("%f ",y[(k*dimv)+i]);
	}
      }
    }
  }
  
  return 0;
}

float vder(int i, float *y){
  if(i%dimv==0 || i%dimv==999){
    return 0.0;
  }
  else{
    return (c2/h2)*(y[i+1]-(2*y[i])+y[i-1]);
  }

}



float inicializar(float x){
  if(x<=0.8*L){
    return (float)(1.25*x)/L;
  }
  else{
    return 5.0*(1-(x/L));
  }
}

void leapfrog(float *y,float *v){
  float *vi;
  int i;
  int k;

  vi=malloc(dimv*sizeof(float));
  for(i=1;i<(dimy/dimv);i++){
    /*Este for saca velocidades intermedias y posiciones finales*/
    for(k=0;k<dimv;k++){
      vi[k]= v[k]+(vder(((i-1)*dimv)+k,y)*(dt/2.0));
      y[(i*dimv)+k]=y[((i-1)*dimv)+k]+(vi[k]*dt);
    }
    /*Este saca velocidades finales*/
    for(k=0;k<dimv;k++){
     v[k]=vi[k]+(vder((i*dimv)+k,y)*(dt/2.0));
    }
    
  }
}
