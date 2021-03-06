/*
 * Check: a unit test framework for C
 * Copyright (C) 2001, 2002 Arien Malec
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */
/*
#ifndef MONEY_H
#define MONEY_H

typedef struct Money Money;

Money *money_create(int amount, char *currency);
int money_amount(Money * m);
char *money_currency(Money * m);
void money_free(Money * m);

#endif // MONEY_H 
*/

// PATCH Test
int test_cve_2015_3417();
int test_cve_2015_0205(int *input);
int test_cve_2017_12613(int input);
int test_cve_2017_7862(int height, int width);
int test_cve_2018_12459(int bits_per_raw_sample, int studio_profile);
int test_cve_2018_14395(int channels);
int test_cve_2019_9433();
