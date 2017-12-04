#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#define bb 0.2497
#define bd 5.16
#define ad 0.3105
#define ah 64.3
#define PI 3.141592

main(){

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
//	printf("%f %f\n", x_obs[i], y_obs[i]);
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

float my_model(x_obs, Mb, Md, Mh){
	float factor1 = (sqrt(Mb)*x_obs)/(pow((pow(x_obs, 2)+pow(bb, 2)), 3/4));
	float factor2 = (sqrt(Md)*x_obs)/pow((pow(x_obs, 2)+pow((bd+ad), 2)), 3/4);
	float factor3 = (sqrt(Mh))/(pow((pow(x_obs, 2)+pow(ah, 2)), 1/4));
	return factor1 + factor2 + factor3;
}

double gaussrand()
{
	static double U, V;
	static int phase = 0;
	double Z;

	if(phase == 0) {
		U = (rand() + 1.) / (RAND_MAX + 2.);
		V = rand() / (RAND_MAX + 1.);
		Z = sqrt(-2 * log(U)) * sin(2 * PI * V);
	} else
		Z = sqrt(-2 * log(U)) * cos(2 * PI * V);

	phase = 1 - phase;

	return Z;
}

int n_iter = 1000;

float *Mb_walk = malloc(n_iter*sizeof(float));
float *Md_walk = malloc(n_iter*sizeof(float));
float *Mh_walk = malloc(n_iter*sizeof(float));
float *l_walk = malloc(n_iter*sizeof(float));

Mb_walk[0] = 100*gaussrand()+3500;
Md_walk[0] = 100*gaussrand()+3500;
Mh_walk[0] = 100*gaussrand()+3500;

//printf("%f\n", Mb_walk[0]);
//printf("%f\n", Md_walk[0]);
//printf("%f\n", Mh_walk[0]);

float y_init = my_model(x_obs, Mb_walk[0], Md_walk[0], Mh_walk[0]);


l_walk[0] = likelihood(y_obs, y_init);
//printf("%f\n", l_walk[0]);


//int n_iter = 10000;
float *Mb_prime = malloc(n_iter*sizeof(float));
float *Md_prime = malloc(n_iter*sizeof(float));
float *Mh_prime = malloc(n_iter*sizeof(float));

for(i=0;i<n_iter;i++){
	Mb_prime[i] = 100*gaussrand()+3500;
	Md_prime[i] = 100*gaussrand()+3500;
	Mh_prime[i] = 100*gaussrand()+3500;

	float y_init = my_model(x_obs, Mb_walk[i], Md_walk[i], Mh_walk[i]);
	float y_prime = my_model(x_obs, Mb_prime, Md_prime, Mh_prime);

	float l_prime = likelihood(y_obs, y_prime);
    float l_init = likelihood(y_obs, y_init);

	float alpha = l_prime/l_init;
	if(alpha>=1.0){
		for(i=0;i<n_iter;i++)
{
			Mb_walk[i] = Mb_prime[i];
			Md_walk[i] = Md_prime[i];
			Mh_walk[i] = Mh_prime[i];
			l_walk[i] = l_prime;
}
}
	else{
		float beta = drand48();
		if(beta<=alpha){
			for(i=0;i<n_iter;i++)
{
				Mb_walk[i] = Mb_prime[i];
				Md_walk[i] = Md_prime[i];
				Mh_walk[i] = Mh_prime[i];
				l_walk[i] = l_prime;
}
}
		else{
			for(i=0; i<n_iter;i++){
			Mb_walk[i] = Mb_walk[i];
			Md_walk[i] = Md_walk[i];
			Mh_walk[i] = Mh_walk[i];
			l_walk[i] = l_init;
}
}
}
			printf("%f\n", Mb_walk[i]);
			printf("%f\n", Md_walk[i]);
			printf("%f\n", Mh_walk[i]);
}

}//ultimate
