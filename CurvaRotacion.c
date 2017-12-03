#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

main(){
//Constantes:

#define bb 0.2497
#define bd 5.16
#define ad 0.3105
#define ah 64.3

FILE* data;
data = fopen("RadialVelocities.dat", "r");
int len = 300;
float *x = malloc(len*sizeof(float)); // x_obs
float *y = malloc(len*sizeof(float)); // y_obs
float *x_obs = malloc(len*sizeof(float)); 
float *y_obs = malloc(len*sizeof(float));

int i;
for(i=0;i<300;i++)
{
	fscanf(data, "%f %f\n", &x[i], &y[i]);
	x_obs[i]=x[i];
	y_obs[i]=y[i];
	printf("%f %f\n", x_obs[i], y_obs[i]);
}
fclose(data);

float likelihood(y_obs, y_model){
	float sum = 0.0;
	float chi_squared = 0.0;
	for(i=0;i<len;i++){
	sum+=pow((y_obs-y_model), 2);
	}
	chi_squared = (1.0/2.0)*sum;
	return exp(-chi_squared);
}

float my_model(x_obs, )

}
