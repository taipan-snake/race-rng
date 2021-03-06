#ifndef RNG_H
#define RNG_H

#include <stdint.h>

/* ----- struct definitions ----- */

/* Parameters for an rng function */
typedef struct rng_params_t_ {
    uint64_t a;
    uint64_t b;
} rng_params_t;

/* Arguments passed into the loop rng function */
typedef struct loop_f_args_t_ {
    // a pointer to the random number
    uint64_t *num;

    // the parameters for the function
    rng_params_t *rng_params;

    // the number of loops
    int num_loops;

    // the rng function to call - paramters match rng_f
    void (*fn) (uint64_t *, rng_params_t *rng_params);
} loop_f_args_t;

/* Configuration for the rng */
typedef struct rng_config_t_ {
    // number of threads
    int num_threads;

    // number of loops for each thread
    int num_loops;

    // starting random number
    uint64_t init_random;

    // array of rng parameters, should be 1 per thread
    rng_params_t *rng_params;
} rng_config_t;

/* ----- function forward declarations ----- */

/* 
 * The main rng function. The default function is a simple PRNG
 * using bitshifts and bitwise AND, inspired by xorshift
 *
 * The PRNG function be changed if you define your own function
 * with the same parameters, and define which function to use
 * in loop_f
 *
 * @param num a pointer to the random number to be modified
 * @param rng_params the parameters to use for this PRNG
 */
void rng_f(uint64_t *num, rng_params_t *rng_params);

/* 
 * Loops the rng function
 *
 * @param args an element of type loop_f_args_t defining arguments
 */
void *loop_f(void *args);

/*
 * The main rng function with a config
 *
 * @return the random number
 * @param config the configuration for this rng
 */
uint64_t rng_config(rng_config_t *config);

/*
 * The main rng function - call this to make a new random number!
 * Calls rng(rng_config_t) with a default config
 *
 * @return the random number
 */
uint64_t rng();

#endif /* RNG_H */
