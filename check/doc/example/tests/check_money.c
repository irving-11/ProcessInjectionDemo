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

#include <config.h>
#include <stdlib.h>
#include <stdint.h>
#include <check.h>
#include "../src/money.h"

/*
Money *five_dollars;

void setup(void)
{
    five_dollars = money_create(5, "USD");
}

void teardown(void)
{
    money_free(five_dollars);
}

START_TEST(test_money_create)
{
    ck_assert_int_eq(money_amount(five_dollars), 5);
    ck_assert_str_eq(money_currency(five_dollars), "USD");
}
END_TEST
*/

// PATCH Test
START_TEST(test_cve_1)
{
    ck_assert_int_eq(test_cve_2015_3417(), 1);
}
END_TEST

START_TEST(test_cve_2)
{
    ck_assert_int_eq(test_cve_2015_0205((int *)1), 1);
    ck_assert_int_eq(test_cve_2015_0205((int *)0), 0);
}
END_TEST

START_TEST(test_cve_3)
{
    ck_assert_int_eq(test_cve_2017_12613(-1), 1);
    // ck_assert_int_eq(test_cve_2017_12613(11), 0);//??? figure out !!!
    ck_assert_int_eq(test_cve_2017_12613(12), 1);
}
END_TEST

START_TEST(test_cve_4)
{
    ck_assert_int_eq(test_cve_2017_7862(1, 2), 1);
    ck_assert_int_eq(test_cve_2017_7862(2, 1), 1);
    ck_assert_int_eq(test_cve_2017_7862(1, 1), 0);
}
END_TEST

START_TEST(test_cve_5)
{
    ck_assert_int_eq(test_cve_2018_12459(1, 0), 1);
    ck_assert_int_eq(test_cve_2018_12459(2, 0), 1);
    ck_assert_int_eq(test_cve_2018_12459(1, 1), 0);
}
END_TEST

START_TEST(test_cve_6)
{
    ck_assert_int_eq(test_cve_2018_14395(0), 1);
    ck_assert_int_eq(test_cve_2018_14395(1), 0);
}
END_TEST

START_TEST(test_cve_7)
{
    ck_assert_int_eq(test_cve_2019_9433(), 1);
}
END_TEST

// START_TEST(test_money_create_neg)
// {
//     Money *m = money_create(-1, "USD");

//     ck_assert_msg(m == NULL,
//                   "NULL should be returned on attempt to create with "
//                   "a negative amount");
// }
// END_TEST

// START_TEST(test_money_create_zero)
// {
//     Money *m = money_create(0, "USD");

//     if (money_amount(m) != 0)
//     {
//         ck_abort_msg("Zero is a valid amount of money");
//     }
// }
// END_TEST

Suite * money_suite(void)
{
    Suite *s;
    TCase *tc_core;
    // TCase *tc_limits;

    s = suite_create("Money");

    /* Core test case */
    tc_core = tcase_create("Core");

    // tcase_add_checked_fixture(tc_core, setup, teardown);
    // tcase_add_test(tc_core, test_money_create);
    tcase_add_test(tc_core, test_cve_1);
    tcase_add_test(tc_core, test_cve_2);
    tcase_add_test(tc_core, test_cve_3);
    tcase_add_test(tc_core, test_cve_4);
    tcase_add_test(tc_core, test_cve_5);
    tcase_add_test(tc_core, test_cve_6);
    tcase_add_test(tc_core, test_cve_7);
    suite_add_tcase(s, tc_core);

    // /* Limits test case */
    // tc_limits = tcase_create("Limits");

    // tcase_add_test(tc_limits, test_money_create_neg);
    // tcase_add_test(tc_limits, test_money_create_zero);
    // suite_add_tcase(s, tc_limits);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = money_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

