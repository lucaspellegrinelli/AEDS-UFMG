
#include <stdio.h>
#include <gmp.h>

void mdc_estendido(mpz_t g, mpz_t x, mpz_t y, const mpz_t a, const mpz_t b){
	mpz_t ta, tb, a0, a1, b0, b1, q;

	mpz_inits(q, ta, tb, a0, a1, b0, b1, NULL);
	mpz_set_ui(a0, 1);
	mpz_set_ui(a1, 0);
	mpz_set_ui(b0, 0);
	mpz_set_ui(b1, 1);

	mpz_set(ta, a);
	mpz_set(tb, b);

	while(1){
		mpz_t qa, qb;
		mpz_inits(qa, qb, NULL);

		mpz_fdiv_q(q, ta, tb);
		mpz_fdiv_r(ta, ta, tb);

		mpz_mul(qa, q, a1);
		mpz_mul(qb, q, b1);

		mpz_sub(a0, a0, qa);
		mpz_sub(b0, b0, qb);

		if(mpz_cmp_ui(ta, 0) == 0){
			mpz_set(g, tb);
			mpz_set(x, a1);
			mpz_set(y, b1);
			return;
		}

		mpz_fdiv_q(q, tb, ta);
		mpz_fdiv_r(tb, tb, ta);

		mpz_mul(qa, q, a0);
		mpz_mul(qb, q, b0);

		mpz_sub(a1, a1, qa);
		mpz_sub(b1, b1, qb);

		if(mpz_cmp_ui(tb, 0) == 0){
			mpz_set(g, ta);
			mpz_set(x, a0);
			mpz_set(y, b0);
			return;
		}
	}
}

int inverso_modular(mpz_t r, const mpz_t a, const mpz_t n){

}

int main(){
	mpz_t g, x, y, a, b;
  mpz_inits(g, x, y, a, b, NULL);

  mpz_set_ui(a, 2345);
  mpz_set_ui(b, 554);

  mdc_estendido(g, x, y, a, b);

  gmp_printf ("a = %Zd\nb = %Zd\nGCD: %Zd\nx: %Zd\ny: %Zd\n", a, b, g, x, y);
  return 0;
}