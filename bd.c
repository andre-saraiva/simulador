#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>



const gsl_rng_type * T;
gsl_rng * r;

typedef struct {

	int v;
	int k;
	int * onSlots;
} t_bd;


typedef struct {

	int v;
	int k;
	int * coincidences;
	int * index;
} t_pp_intersection;

typedef struct {

	int v;
	int k;
	t_pp_intersection offsetZero;
	t_pp_intersection others;
} t_pp_bd;

t_pp_bd * genPP(t_bd * pattern, t_bd * pattern2, int mmc, unsigned int offset) {

	t_pp_bd * pp;
	int i, j, z, w, a, b, c, d, e, f, h, k, t, q, u, r, y, x, last, index;

	/*
	 * Allocate structures.
	 */

	pp = (t_pp_bd *) malloc(sizeof(t_pp_bd));
	pp->offsetZero.coincidences = (int *) malloc(pattern->k * pattern2->k * sizeof(int));
	pp->offsetZero.index = (int *) malloc(mmc * sizeof(int));
	pp->others.coincidences = (int *) malloc(pattern->k * pattern2->k * sizeof(int));
	pp->others.index = (int *) malloc(mmc * sizeof(int));
	pp->v = pattern->v;
	pp->k = pattern->k;
	pp->v = pattern2->v;
	pp->k = pattern2->k;

	/*
	 * Creation of the MMC index for offset 0
	 */
	
	// First pattern
		
		
		a = 0;
		b = 0;
		int menor[mmc];
		memset(menor, 0, mmc*sizeof(int));
		while (a <= mmc/pattern->v) {
			for (c=0; c < pattern->k; c++){
				menor[((pattern->onSlots[c] + a*pattern->v) % mmc)] = 1;				
				}
			a++;
		}


	/*	for (int p=0; p<mmc; p++){
			printf("%d",menor[p]);
			}
		printf("\n"); */

	// Second pattern
	
		d = 0;
		e = 0;
		int maior[mmc];
		memset(maior, 0, mmc*sizeof(int));
		while (d < mmc/pattern2->v) {
			for (f=0; f < pattern2->k; f++){
				maior[((pattern2->onSlots[f] + d*pattern2->v) % mmc)] = 1;				
				e++;
				}
			d++;
		}
		
	/*	for (int p=0; p<mmc; p++){
			printf("%d",maior[p]);
			}
		printf("\n"); */
		
		

	// Comparation of pattern of offset 0
	if (offset == 0){	
		printf("if - offset = %d\n", offset);
		w=0;
		for (z=0; z < mmc; z++){
			if ((menor[z] == 1) && (maior[z]==1)){
				pp->offsetZero.coincidences[w] = z;				
				pp->offsetZero.k++;
				w++;
				}
			}
		
		for (int p=0; p<pp->offsetZero.k; p++){
			printf("offsetZero.coincidences %d= %d\n",p,pp->offsetZero.coincidences[p]);
			}
		printf("\n");
		
		j = 0;	
		pp->offsetZero.v = pp->v;
		for (i = 0; i < pp->offsetZero.k; i++) {
			while(j <= pp->offsetZero.coincidences[i]) {
				pp->offsetZero.index[j++] = pp->offsetZero.coincidences[i];
				}
			}
		
		while(j < pp->v) {
			pp->offsetZero.index[j++] = 0;
			}

		for (int p=0; p<mmc; p++){
			printf("offsetZero.index %d = %d\n",p,pp->offsetZero.index[p]);
			}
			printf("\n");
	} else {
		// Second pattern offset for different offset 0
		printf("else - offset = %d\n", offset);
		int size = sizeof(maior)/sizeof(maior[0]); 
		for (int q=0; q < offset; q++){    
			last = maior[size -1];
			for (r = size-1; r >0; r--){
				maior[r] = maior[r-1];
				}
			maior[0] = last;
			}
			
			
		for (int p=0; p<mmc; p++){
			printf("%d",menor[p]);
			}
		printf("\n");
	
		for (int p=0; p<mmc; p++){
			printf("%d",maior[p]);
			}
		printf("\n");
			
		k=0;
		for (t=0; t < mmc; t++){
			if ((menor[t] == 1) && (maior[t]==1)){
				pp->others.coincidences[k] = t;				
				pp->others.k++;
				k++;
				}
			}
			
		for (int p=0; p<pp->others.k; p++){
			printf("others.coincidences %d= %d\n",p,pp->others.coincidences[p]);
			}
		printf("\n");
	
		y = 0;	
		pp->others.v = pp->v;
		x = pp->others.coincidences[pp->others.k-1];
		for (u = 0; u <= pp->others.k; u++) {
			if (y > pp->others.coincidences[pp->others.k-1]) {
				while (x < mmc-1){
				pp->others.index[y++] = pp->others.coincidences[0];
				x++;
					}
				} else {				
			while(y <= pp->others.coincidences[u]) {
				pp->others.index[y++] = pp->others.coincidences[u];
				}
			}
		}
		
		
		while(y < pp->v) {
			pp->others.index[y++] = 0;
			}

		for (int p=0; p<mmc; p++){
			printf("others.index %d = %d\n",p,pp->others.index[p]);
			}
			printf("\n");
		};		

	return(pp);
} 


uint64_t simulateEncounter(t_pp_bd * pp, double p, unsigned int start, unsigned int offset ) {

	uint64_t t;
	unsigned int attempts;
//	unsigned int offset;
//	unsigned int start;
	int i, j, next_i;
	t_pp_intersection * pp_intersection;

	attempts = gsl_ran_geometric(r, p);
//	offset = floor(gsl_ran_flat(r, 0.0, (double) pp->v));
//	start = floor(gsl_ran_flat(r, 0.0, (double) pp->v));
//	attempts = 2; offset = 47; start = 44;
//	printf("attempts = %u, start = %u, offset = %u\n", attempts, start, offset);
	/*
	 * Test in which of the four cases the offset falls.
	 */
	printf("start = %d\n", start);
	if (offset == 0) {
		pp_intersection = & (pp->offsetZero); //aqui muda para a posição do pré processamento, tirar o if
	}
	else {
		pp_intersection = & (pp->others);
	}

	/*
	 * Account for the number of slots until
	 * the first opportunity.
	 */

	if (pp_intersection->coincidences[pp_intersection->index[start]] >= start){
		t = pp_intersection->coincidences[pp_intersection->index[start]] - start;
	} else {
		t = pp_intersection->v - (start - pp_intersection->coincidences[pp_intersection->index[start]]);
	}
	attempts--;
	printf("t1 = %lu\n", t);
	/*
	 * Account for the number of cycles.
	 */

	t += (attempts / pp_intersection->k) * pp->v;
	attempts = (attempts % pp_intersection->k);

	printf("t2 = %lu\n", t);
	/*
	 * Account for the remainder of the attempts.
	 */

	i = pp_intersection->index[start];
	while(attempts--) {
		next_i = (i + 1) % pp_intersection->k;
//		printf("attempts = %u, i = %d, next_i = %d\n", attempts, i, next_i);
		if (next_i > i) {

			t += (pp_intersection->coincidences[next_i] - pp_intersection->coincidences[i]);
			printf("t3 = %lu\n", t);
		}
		else {

			t += (pp_intersection->v - (pp_intersection->coincidences[i] - pp_intersection->coincidences[next_i]));
			printf("t4 = %lu\n", t);
		}
		i = next_i;
//		printf("tn = %lu\n", t);
	}

	return(t);
}

int main(int argc, char ** argv) {

	t_bd pattern;
	t_bd pattern2;
	t_pp_bd * pp;
	char * s_pattern;
	char * s_pattern2;
	int i, j, k;
	double start_p, by_p;
	int n_p;
	double p;
	unsigned int reps;
	unsigned int t;
	long unsigned int t_total;
	unsigned int offset;
	unsigned int start;
	unsigned int hops;
	unsigned int mmc;
	FILE * output;
	char filename[255], * outputdir;

	gsl_rng_env_setup();
	T = gsl_rng_default;
	r = gsl_rng_alloc(T);
	gsl_rng_set(r, time(NULL));

	s_pattern = argv[1];
	s_pattern2 = argv[2];
	start_p = atof(strtok(argv[3], ","));
	by_p = atof(strtok(NULL, ","));
	n_p = atoi(strtok(NULL, ","));
	reps = atoi(argv[4]);
	outputdir = argv[5];
	hops = atoi(argv[6]);
	mmc = atoi(argv[7]);

	// Parse pattern.
	pattern.v = atoi(strtok(s_pattern, ","));
 	pattern.k = atoi(strtok(NULL, ","));
	pattern.onSlots = (int *) malloc(sizeof(unsigned int) * pattern.k);
	strtok(NULL, ",");	// We dont use l.

	for (i = 0; i < pattern.k; i++) {

		pattern.onSlots[i] = atoi(strtok(NULL, ","));
	}


	pattern2.v = atoi(strtok(s_pattern2, ","));
	pattern2.k = atoi(strtok(NULL, ","));
	pattern2.onSlots = (int *) malloc(sizeof(unsigned int) * pattern2.k);
	strtok(NULL, ",");	// We dont use l.

	for (i = 0; i < pattern2.k; i++) {

		pattern2.onSlots[i] = atoi(strtok(NULL, ","));
	}

	//pp = genPP(& pattern, & pattern2, mmc, offset);

	p = start_p;
	for (j = 0; j < n_p; j++) {
		sprintf(filename, "%sbd_%.6f.txt", outputdir, p);
		output = fopen(filename, "w");
		for (i = 0; i < reps; i++) {
			start = floor(gsl_ran_flat(r, 0.0, (double) mmc));
			t_total = 0;
			for (k = 0; k < hops; k++) {
				offset = floor(gsl_ran_flat(r, 0.0, (double) mmc)); //PARA OFFSET RANDOM
				//offset = pp-> v -1; PARA OFFSET 1 NO BD E offset = v-1; NOS DEMAIS
				pp = genPP(& pattern, & pattern2, mmc, offset);
				t = simulateEncounter(pp, p, start, offset);
				t_total += t;
				start = (start + offset + t + 1) % pp->v;
				fprintf(output, "%u\t", t);
				//free(pp);
			}
			//printf("offset = %d\n", offset);
			fprintf(output, "%lu\n", t_total);
		}
		p += by_p;
		if (p > 1.0) p = 1.0;
		fclose(output);
		free(pp);
	}

	//free(pp);
	free(pattern.onSlots);
	free(pattern2.onSlots);
	gsl_rng_free(r);

	return(0);
}
