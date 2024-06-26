/** @file
 * @brief Xapian-specific test helper functions and macros.
 */
/* Copyright 1999,2000,2001 BrightStation PLC
 * Copyright 2002,2003,2007,2008,2015,2023 Olly Betts
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#ifndef XAPIAN_INCLUDED_TESTUTILS_H
#define XAPIAN_INCLUDED_TESTUTILS_H

#include "testsuite.h"
#include <xapian.h>

// ######################################################################
// Useful display operators

std::ostream &operator<<(std::ostream &os,
			 const std::vector<Xapian::docid> &ints);

// ######################################################################
// Useful comparison operators

// Test that the weights and docids in two mset ranges are the same.
bool
mset_range_is_same(const Xapian::MSet &mset1, unsigned int first1,
		   const Xapian::MSet &mset2, unsigned int first2,
		   unsigned int count);

// Test that the weights and docids in the mset and an array are the same.
bool
mset_range_is_same(const Xapian::MSet& mset, unsigned int first,
		   const std::pair<Xapian::docid, double> to_compare[],
		   unsigned int count);

// Test that the weights in two mset ranges are the same, ignoring docids.
bool
mset_range_is_same_weights(const Xapian::MSet &mset1, unsigned int first1,
			   const Xapian::MSet &mset2, unsigned int first2,
			   unsigned int count);

bool operator==(const Xapian::MSet &first, const Xapian::MSet &second);

inline bool operator!=(const Xapian::MSet &first, const Xapian::MSet &second)
{
    return !(first == second);
}

void mset_expect_order(const Xapian::MSet &A,
		       Xapian::docid d1 = 0, Xapian::docid d2 = 0,
		       Xapian::docid d3 = 0, Xapian::docid d4 = 0,
		       Xapian::docid d5 = 0, Xapian::docid d6 = 0,
		       Xapian::docid d7 = 0, Xapian::docid d8 = 0,
		       Xapian::docid d9 = 0, Xapian::docid d10 = 0,
		       Xapian::docid d11 = 0, Xapian::docid d12 = 0);

void test_mset_order_equal(const Xapian::MSet &mset1,
			   const Xapian::MSet &mset2);

// ######################################################################
// Useful test macros

/// Check MSet M has size S.
#define TEST_MSET_SIZE(M, S) TEST_AND_EXPLAIN(((M).size() == (S)), \
	"MSet '" STRINGIZE(M) "' is not of expected size: was '" << \
	(M).size() << "' expected '" << (S) << "':\n" << \
	"Full mset was:\n" << (M))

/// Helper macro.
#define TEST_EXCEPTION_(TYPE, CODE, EXACT, FAIL_TO_THROW_ACTION) \
    do { \
	expected_exception = STRINGIZE(TYPE); \
	if (strncmp(expected_exception, "Xapian::", \
		    CONST_STRLEN("Xapian::")) == 0) { \
	    expected_exception += CONST_STRLEN("Xapian::"); \
	} \
	try { \
	    CODE; \
	    FAIL_TO_THROW_ACTION; \
	} catch (const TYPE& xap_ex_obj_) { \
	    if (EXACT) { \
		if (strcmp(expected_exception, xap_ex_obj_.get_type()) != 0) { \
		    FAIL_TEST("Caught subclass " << xap_ex_obj_.get_type() << \
			      " of expected " << expected_exception); \
		} \
	    } \
	} \
	expected_exception = NULL;\
    } while (0)

#define DEFAULT_FAIL_TO_THROW_ACTION_ \
    FAIL_TEST("Expected " << expected_exception << " not thrown")

/// Check that CODE throws Xapian exception derived from TYPE.
#define TEST_EXCEPTION_BASE_CLASS(TYPE, CODE) \
    TEST_EXCEPTION_(TYPE, CODE, false, DEFAULT_FAIL_TO_THROW_ACTION_)

/// Check that CODE throws exactly Xapian exception TYPE.
#define TEST_EXCEPTION(TYPE, CODE) \
    TEST_EXCEPTION_(TYPE, CODE, true, DEFAULT_FAIL_TO_THROW_ACTION_)

/** Check that CODE throws Xapian exception derived from TYPE.
 *
 *  Variant with custom fail-to-throw action.
 */
#define TEST_EXCEPTION_BASE_CLASS3(TYPE, CODE, FAIL_TO_THROW_ACTION) \
    TEST_EXCEPTION_(TYPE, CODE, false, FAIL_TO_THROW_ACTION)

/** Check that CODE throws exactly Xapian exception TYPE.
 *
 *  Variant with custom fail-to-throw action.
 */
#define TEST_EXCEPTION3(TYPE, CODE, FAIL_TO_THROW_ACTION) \
    TEST_EXCEPTION_(TYPE, CODE, true, FAIL_TO_THROW_ACTION)

#endif // XAPIAN_INCLUDED_TESTUTILS_H
