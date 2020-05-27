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

t_pp_bd * genPP(t_bd * pattern, t_bd * pattern2, int mmc) {

	t_pp_bd * pp;
	int i, j, z, k, a, b, c, index, offset;

	/*
	 * Allocate structures.
	 */

	pp = (t_pp_bd *) malloc(sizeof(t_pp_bd));
	pp->offsetZero.coincidences = (int *) malloc(pattern->k * sizeof(int));
	pp->offsetZero.index = (int *) malloc(pattern->v * sizeof(int));
	pp->others.coincidences = (int *) malloc(sizeof(int));
	pp->others.index = (int *) malloc(pattern->v * sizeof(int));
	pp->v = pattern->v;
	pp->k = pattern->k;
	pp->v = pattern2->v;
	pp->k = pattern2->k;



	/*
	 * My test
	 */
		
	offset = 0;
	while (offset <= mmc){
		
		z = 0;
		j = 0;
		int menor[mmc];
		memset(menor, 0, mmc*sizeof(int));
		while (z < mmc/pattern->v) {
			for (i=0; i <= pattern->k; i++){
				menor[(pattern->onSlots[i] + z*pattern->v) % mmc] = 1;
				printf("menor %d-> %d\n",j, menor[j]);
				j++;
				};
			z++;
		}

		a = 0;
		b = 0;
		int maior[mmc];
		memset(maior, 0, mmc*sizeof(int));
		while (a < mmc/pattern->v) {
			for (c=0; c < pattern2->k; c++){
				maior[((pattern2->onSlots[c] + a*pattern2->v) % mmc) + offset%mmc] = 1;
				printf("offset %d", offset);
				//printf("maior %d-> %d\n",b, maior[b]);
				b++;
				}
			a++;
		}

		for (k=0; k < mmc; k++){
			if ((menor[k] == 1) && (maior[k]==1)){
				//printf("ACHOU em %d, menor %d, maior %d\n",k, menor[k], maior[k]);
				}
		}
		offset++;
	}


	/*
	 * Assemble first case.
	 */

	for (i = 0; i < pattern->k; i++) {

		pp->offsetZero.coincidences[i] = pattern->onSlots[i];
	}
	pp->offsetZero.v = pp->v;
	pp->offsetZero.k = pp->k;

	j = 0;
	for (i = 0; i < pp->offsetZero.k; i++) {

		while(j <= pp->offsetZero.coincidences[i]) {

			pp->offsetZero.index[j++] = i;
		}
	}

	while(j < pp->v) {

		pp->offsetZero.index[j++] = 0;
	}

	/*
	 * Assemble second case.
	 */

	pp->others.coincidences[0] = 0;
	pp->others.v = pp->v;
	pp->others.k = 1;

	j = 0;
	while(j < pp->v) {

		pp->others.index[j++] = 0;
	}

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

	if (offset == 0) {
//	printf("case 1\n");
		pp_intersection = & (pp->offsetZero);
	}
	else {
//	printf("case 2\n");
		pp_intersection = & (pp->others);
	}

	/*
	 * Account for the number of slots until
	 * the first opportunity.
	 */

	if (pp_intersection->coincidences[pp_intersection->index[start]] >= start)
		t = pp_intersection->coincidences[pp_intersection->index[start]] - start;
	else 
		t = pp_intersection->v - (start - pp_intersection->coincidences[pp_intersection->index[start]]);
	attempts--;
//	printf("t1 = %lu\n", t);
	/*
	 * Account for the number of cycles.
	 */

	t += (attempts / pp_intersection->k) * pp->v;
	attempts = (attempts % pp_intersection->k);

//	printf("t2 = %lu\n", t);
	/*
	 * Account for the remainder of the attempts.
	 */

	i = pp_intersection->index[start];
	while(attempts--) {
		next_i = (i + 1) % pp_intersection->k;
//		printf("attempts = %u, i = %d, next_i = %d\n", attempts, i, next_i);
		if (next_i > i) {

			t += (pp_intersection->coincidences[next_i] - pp_intersection->coincidences[i]);
		}
		else {

			t += (pp_intersection->v - (pp_intersection->coincidences[i] - pp_intersection->coincidences[next_i]));
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


	pp = genPP(& pattern, & pattern2, mmc);

	p = start_p;
	for (j = 0; j < n_p; j++) {

		sprintf(filename, "%sbd_%.6f.txt", outputdir, p);
		output = fopen(filename, "w");
		for (i = 0; i < reps; i++) {
			start = floor(gsl_ran_flat(r, 0.0, (double) pp->v));
			t_total = 0;
			for (k = 0; k < hops; k++) {
				offset = floor(gsl_ran_flat(r, 0.0, (double) pp->v)); //PARA OFFSET RANDOM
				//offset = pp-> v -1; PARA OFFSET 1 NO BD E offset = v-1; NOS DEMAIS
				t = simulateEncounter(pp, p, start, offset);
				t_total += t;
				start = (start + offset + t + 1) % pp->v;
				fprintf(output, "%u\t", t);
			}
			fprintf(output, "%lu\n", t_total);
		}
		p += by_p;
		if (p > 1.0) p = 1.0;
		fclose(output);
	}

	free(pattern.onSlots);
	free(pattern2.onSlots);
	gsl_rng_free(r);

	return(0);
}

