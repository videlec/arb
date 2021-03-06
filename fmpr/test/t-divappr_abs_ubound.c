/*
    Copyright (C) 2013 Fredrik Johansson

    This file is part of Arb.

    Arb is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include "fmpr.h"

int main()
{
    slong iter;
    flint_rand_t state;

    flint_printf("divappr_abs_ubound....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 10000 * arb_test_multiplier(); iter++)
    {
        fmpr_t a, b, c, d;
        slong prec;

        fmpr_init(a);
        fmpr_init(b);
        fmpr_init(c);
        fmpr_init(d);

        fmpr_randtest_special(a, state, 2 + n_randint(state, 200), 100);
        fmpr_randtest_special(b, state, 2 + n_randint(state, 200), 100);
        fmpr_randtest_special(c, state, 2 + n_randint(state, 200), 100);
        fmpr_randtest_special(d, state, 2 + n_randint(state, 200), 100);
        prec = 2 + n_randint(state, 200);

        fmpr_div(c, a, b, prec, FMPR_RND_UP);
        fmpr_abs(c, c);

        fmpr_divappr_abs_ubound(d, a, b, prec);

        if (fmpr_cmp(c, d) > 0)
        {
            flint_printf("FAIL:\n");
            fmpr_printd(a, prec / 3.32); flint_printf("\n");
            fmpr_printd(b, prec / 3.32); flint_printf("\n");
            fmpr_printd(c, prec / 3.32); flint_printf("\n");
            fmpr_printd(d, prec / 3.32); flint_printf("\n");
            flint_abort();
        }

        fmpr_clear(a);
        fmpr_clear(b);
        fmpr_clear(c);
        fmpr_clear(d);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}

