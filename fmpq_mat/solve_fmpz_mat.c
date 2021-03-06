/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2014 Alex J. Best

******************************************************************************/

#include "fmpq_mat.h"

int
fmpq_mat_solve_fmpz_mat(fmpq_mat_t X, const fmpz_mat_t A, const fmpz_mat_t B)
{
    int success = 1;
    fmpz_t tmp;
    fmpz_mat_t X_Z;

    fmpz_init(tmp);
    fmpz_mat_init(X_Z, X->r, X->c);

    if (X->r < 25)                 /* small matrices use solve */
    {
        success = fmpz_mat_solve(X_Z, tmp, A, B);
        if (success)
            fmpq_mat_set_fmpz_mat_div_fmpz(X, X_Z, tmp);
    }
    else                        /* larger matrices use dixon */
    {
        success = fmpz_mat_solve_dixon(X_Z, tmp, A, B);
        if (success)
            fmpq_mat_set_fmpz_mat_mod_fmpz(X, X_Z, tmp);
    }

    fmpz_clear(tmp);
    fmpz_mat_clear(X_Z);

    return success;
}
