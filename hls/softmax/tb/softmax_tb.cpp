#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "softmax.h"

struct Rmse
{
	int num_sq;
	float sum_sq;
	float error;

	Rmse(){ num_sq = 0; sum_sq = 0; error = 0; }

	float add_value(OUTP_TYPE d_n)
	{
		num_sq++;
		sum_sq += (float)(d_n*d_n);
		error = sqrtf(sum_sq / num_sq);
		return error;
	}
};

Rmse rmse;

INPT_TYPE In[SFMX_SIZE], Out[SFMX_SIZE];

int main()
{
	int r,c;
	OUTP_TYPE gold;
	FILE *fp;
	fp = fopen("input.dat", "r");
	for(r=0; r < SFMX_SIZE; ++r) {
		fscanf(fp, "%f\n", &In[r]);
	}
	fclose(fp);

	//Perform Bit Reverse
	softmax(In, Out);

	fp = fopen("out.gold.dat", "r");
	for (r = 0; r < SFMX_SIZE; ++r) {
	  fscanf(fp, "%f\n", &gold);
	  rmse.add_value(Out[r] - gold);
	}
	fclose(fp);

	// printing error results
	printf("----------------------------------------------\n");
	printf("   RMSE ");
	printf("%0.15f\n", rmse.error);
	printf("----------------------------------------------\n");

	if (rmse.error > 0.1) {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "FAIL: Output DOES NOT match the golden output\n");
		fprintf(stdout, "*******************************************\n");
		return 1;
	}else {
		fprintf(stdout, "*******************************************\n");
		fprintf(stdout, "PASS: The output matches the golden output!\n");
		fprintf(stdout, "*******************************************\n");
		return 0;
	}
}
