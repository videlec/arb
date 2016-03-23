/*=============================================================================

    This file is part of ARB.

    ARB is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    ARB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ARB; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2016 Pascal Molin

******************************************************************************/

#include "acb_dirichlet.h"

void
acb_dirichlet_group_dlog_precompute(acb_dirichlet_group_t G, ulong num)
{
    slong k;
    G->dlog = flint_malloc(G->num * sizeof(dlog_precomp_t));
    for (k = G->neven; k < G->num; k++)
    {
        ulong p, e, pe, a;
        p = G->primes[k];
        e = G->exponents[k];
        pe = G->primepowers[k];
        a = G->generators[k] % pe;
        dlog_precomp_modpe_init(G->dlog[k], a, p, e, pe, num);
    }
}