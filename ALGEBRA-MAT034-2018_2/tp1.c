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

		mpz_clear(qa);
		mpz_clear(qb);
	}

	mpz_clears(ta, tb, a0, a1, b0, b1, q, NULL);
}

int inverso_modular(mpz_t r, const mpz_t a, const mpz_t n){
	mpz_t g, x, y;
	mpz_inits(g, x, y, NULL);
	mdc_estendido(g, x, y, a, n);

	int out = mpz_cmp_ui(g, 1) == 0;

	mpz_clears(g, x, y, NULL);

	return out;
}

void exp_binaria(mpz_t r, const mpz_t b, const mpz_t e, const mpz_t n){
	mpz_t xmodp, exp, base, rx, bb, expmod2;
	mpz_inits(xmodp, exp, base, rx, bb, expmod2, NULL);

	mpz_set(exp, e);
	mpz_set(base, b);

	mpz_set_ui(r, 1);
	mpz_fdiv_r(xmodp, base, n);

	while(mpz_cmp_ui(exp, 0) > 0){
		mpz_fdiv_r_ui(expmod2, exp, 2);
		if(mpz_cmp_ui(expmod2, 1) == 0){
			mpz_mul(rx, r, base);
			mpz_fdiv_r(r, rx, n);
		}

		mpz_tdiv_q_ui(exp, exp, 2);
		mpz_mul(bb, base, base);
		mpz_fdiv_r(base, bb, n);
	}

	mpz_clears(xmodp, exp, base, rx, bb, expmod2, NULL);
}
