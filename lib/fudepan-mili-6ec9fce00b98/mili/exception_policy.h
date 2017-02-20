/*
exception_policy: A selector to choose error handling policies.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Pablo Oliva, Daniel Gutson, FuDePAN 2013
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt in the root directory or
    copy at http://www.boost.org/LICENSE_1_0.txt)

    MiLi IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#ifndef EXCEPTION_POLICY_H
#define EXCEPTION_POLICY_H

#include <stdint.h>
#include <cassert>

#include "platform_detection.h"
#include "generic_exception.h"

NAMESPACE_BEGIN

/**
 * @brief A policy that uses assert to validate its predicates.
 */
struct AssertionErrorPolicy
{
    /**
    * @brief Asserts that predicate is true.
    *
    * @param predicate The predicate we want to check.
    */
    static inline void checkPredicate(bool predicate)
    {
        assert(predicate);
    }
};

#ifdef MILI_EXCEPTIONS_COMPILER_ENABLED
/**
 * @brief A policy that uses assert_throw to validate its predicates.
 *
 * Only available if exceptions are supported.
 *
 * Throws ExceptionType if its predicate check fails.
 */
template <class ExceptionType>
struct ExceptionErrorPolicy
{
    /**
    * @brief Checks if predicate is true, throws ExceptionType otherwise.
    *
    * @param predicate The predicate we want to check.
    */
    static inline void checkPredicate(bool predicate)
    {
        mili::assert_throw<ExceptionType>(predicate);
    }
};
#endif

/**
 * @brief A policy that does not validate its predicates.
 */
struct DoNothingErrorPolicy
{
    /**
    * @brief Does nothing.
    */
    static inline void checkPredicate(bool /*predicate*/)
    {
    }
};


NAMESPACE_END

#endif
