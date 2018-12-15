#include <stdio.h>
#include <gmp.h>

int talvez_primo(const mpz_t a, const mpz_t n, const mpz_t n1, unsigned int t, const mpz_t q){
  mpz_t nmod2, apqmodn;
  mpz_inits(nmod2, apqmodn, NULL);

  if(mpz_cmp(a, n) == 0) return 1;

  if(mpz_cmp_ui(n, 1) < 0) return 0;
  if(mpz_cmp_ui(n, 4) < 0) return 1;

  mpz_fdiv_r_ui(nmod2, n, 2);
  if(mpz_cmp_ui(nmod2, 0) == 0) return 0;

  mpz_powm(apqmodn, a, q, n);

  if(mpz_cmp_ui(apqmodn, 1) == 0 || mpz_cmp(apqmodn, n1) == 0) return 1;

  for(unsigned int i = 0; i < (t - 1); i++){
    mpz_powm_ui(apqmodn, apqmodn, 2, n);
    if(mpz_cmp_ui(apqmodn, 1) == 0) return 0;
    if(mpz_cmp(apqmodn, n1) == 0) return 1;
  }

  return mpz_cmp(apqmodn, n1) == 0;
}

int provavelmente_primo(const mpz_t n, unsigned int iter, gmp_randstate_t rnd){
  mpz_t n1, q, a, qmod2;
  mpz_inits(n1, q, a, qmod2, NULL);

  mpz_sub_ui(n1, n, 1);
  mpz_set(q, n1);

  unsigned int t = 0;

  mpz_fdiv_r_ui(qmod2, q, 2);
  while(mpz_cmp_ui(qmod2, 0) == 0){
    t++;
    mpz_tdiv_q_ui(q, q, 2);
    mpz_fdiv_r_ui(qmod2, q, 2);
  }

  for(unsigned int i = 0; i < iter; i++){
    mpz_urandomm(a, rnd, n);
    mpz_add_ui(a, a, 1);
    if(talvez_primo(a, n, n1, t, q) == 0) return 0;
  }

  return 1;
}

void primo_aleatorio(mpz_t r, unsigned int b, gmp_randstate_t rnd){
  mpz_t cr, rndmax;
  mpz_inits(cr, rndmax, NULL);

  mpz_set_ui(rndmax, 2);

  do{
    mpz_set_ui(r, 0);
    mpz_setbit(r, 0);
    mpz_setbit(r, b - 1);

    for(int i = 1; i < b - 1; i++){
      mpz_urandomm(cr, rnd, rndmax);
      if(mpz_cmp_ui(cr, 1) == 0) mpz_setbit(r, i);
    }
  }while(!provavelmente_primo(r, 20, rnd));

  mpz_clears(cr, rndmax, NULL);
}
