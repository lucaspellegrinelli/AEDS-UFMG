#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

void gera_chaves(mpz_t n, mpz_t e, mpz_t d, gmp_randstate_t rnd){
  mpz_t p, q, tot, pm1, qm1, totgcde;
  mpz_inits(p, q, tot, pm1, qm1, totgcde, NULL);

  mpz_urandomb(p, rnd, 2048);
  mpz_urandomb(q, rnd, 2048);

  mpz_sub_ui(pm1, p, 1);
  mpz_sub_ui(qm1, q, 1);

  mpz_mul(n, p, q);
  mpz_mul(tot, pm1, qm1);

  mpz_set_ui(e, 65537);

  mpz_gcd(totgcde, e, tot);
  while(mpz_cmp_ui(totgcde, 1) != 0){
    mpz_add_ui(e, e, 2);
    mpz_gcd(totgcde, e, tot);
  }

  mpz_invert(d, e, n);
  mpz_clears(p, q, tot, pm1, qm1, totgcde, NULL);
}

void codifica(mpz_t r, const char *str){
  mpz_t indval, posval;
  mpz_inits(indval, posval, NULL);

  mpz_set_ui(indval, 1);

  for(int i = 0; str[i] != '\0'; i++){
    mpz_mul_ui(posval, indval, (unsigned int)str[i]);
    mpz_add(r, r, posval);
    mpz_mul_ui(indval, indval, 256);
  }

  mpz_clears(indval, posval);
}

char *decodifica(const mpz_t n){
  char *out = malloc(501 * sizeof(char));

  mpz_t currn, currc;
  mpz_inits(currn, currc, NULL);

  mpz_set(currn, n);

  int txtIndex = 0;
  while(mpz_cmp_ui(currn, 0) != 0){
    mpz_fdiv_r_ui(currc, currn, 256);
    out[txtIndex++] = (char)mpz_get_ui(currc);
    mpz_tdiv_q_ui(currn, currn, 256);
  }

  for(; txtIndex < 501; txtIndex++) out[txtIndex] = '\0';

  mpz_clears(currn, currc);
  return out;
}

void criptografa(mpz_t C, const mpz_t M, const mpz_t n, const mpz_t e){
  mpz_powm(C, M, e, n);
}

void descriptografa(mpz_t M, const mpz_t C, const mpz_t n, const mpz_t d){
  mpz_powm(M, C, d, n);
}
