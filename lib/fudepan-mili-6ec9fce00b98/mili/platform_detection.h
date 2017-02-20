/*
platform_detection:
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Muñoz, Pablo Oliva FuDePAN 2012
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

#ifndef PLATFORM_DETECTION_H
#define PLATFORM_DETECTION_H

/* There is no need for namespace (NAMESPACE_BEGIN and NAMESPACE_END) */

/* OS detection
   See: http://sourceforge.net/apps/mediawiki/predef/index.php?title=Operating_Systems
*/
#define MILI_OS_LINUX       1
#define MILI_OS_WINDOWS     2
#define MILI_OS_MAC         3
#define MILI_OS_UNKNOWN     4

/* Windows */
#if   defined (WIN32)       \
   || defined (_WIN32)      \
   || defined (_WIN64)      \
   || defined (__WIN32__)   \
   || defined (__TOS_WIN__) \
   || defined (__WINDOWS__)
#    define MILI_OS MILI_OS_WINDOWS

/* Linux */
#elif defined (__linux__)   \
   || defined (linux)       \
   || defined (__linux)
#    define MILI_OS MILI_OS_LINUX

/* MAC */
#elif defined (macintosh)   \
   || defined (Macintosh)   \
   || defined (__APPLE__)   \
   || defined (__MACH__)
#    define MILI_OS MILI_OS_MAC

/* Unknown OS */
#else
#    define MILI_OS MILI_OS_UNKNOWN

#endif /* end OS Detection */

/* Compiler detection
   See: http://sourceforge.net/apps/mediawiki/predef/index.php?title=Compilers
*/
#define MILI_COMPILER_VS        1
#define MILI_COMPILER_GCC       2
#define MILI_COMPILER_ICC       3
#define MILI_COMPILER_CLANG     4
#define MILI_COMPILER_TICCS     5
#define MILI_COMPILER_UNKNOWN   6

/* Microsoft Visual C++ */
#if   defined (_MSC_VER)
#    define MILI_COMPILER MILI_COMPILER_VS

/* Intel C/C++ */
/*#elif defined (__INTEL_COMPILER)  \
   || defined (__ICC)           \
   || defined (__ECC)           \
   || defined (__ICL)
#    define MILI_COMPILER MILI_COMPILER_ICC*/

/* CLANG */
#elif defined (__clang__)
#    define MILI_COMPILER MILI_COMPILER_CLANG

/* Texas Instruments Code Composer Studio */
#elif defined (__TI_COMPILER_VERSION__)       \
    || defined (__TI_COMPILER_VERSION)
// The canonical flag seems to be __TI_COMPILER_VERSION__
// but some versions of CCS defined __TI_COMPILER_VERSION instead.
#    define MILI_COMPILER MILI_COMPILER_TICCS
// We need to include stdlib.h to get the definition of the type size_t.
// Code Composer Studio provides the file stdlib.h with that definition for the ARM compiler.
#    include "stdlib.h"

/* GCC C/C++; this actually matches any gcc-like compiler, so it's left at the bottom. */
#elif defined (__GNUC__)
#    define MILI_COMPILER MILI_COMPILER_GCC

/* Unknown compiler */
#else
#    define MILI_COMPILER MILI_COMPILER_UNKNOWN

#endif /* end Compiler detection */

/* Detection of the C++ language standard
   See: http://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html#Common-Predefined-Macros
*/
#define MILI_CXX_VERSION_CXX98 0
#define MILI_CXX_VERSION_CXX0X 1

/* GCC C/C++ */
#if defined(__GXX_EXPERIMENTAL_CXX0X__) || (__cplusplus > 199711L)
#   define MILI_CXX_VERSION MILI_CXX_VERSION_CXX0X
#else
#   define MILI_CXX_VERSION MILI_CXX_VERSION_CXX98
#endif /* end Detection of the C++ language standard */

/* Detection of exceptions' availability
 * See:
 * (GCC) http://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html
 * and
 * (ICC) http://software.intel.com/sites/products/documentation/doclib/stdxe/2013/composerxe/compiler/cpp-lin/GUID-E65FC029-9273-4CDD-8C4C-3372B9A60DC7.htm
 */
#if (MILI_COMPILER == MILI_COMPILER_GCC) || (MILI_COMPILER == MILI_COMPILER_ICC) || (MILI_COMPILER == MILI_COMPILER_CLANG)
// If we are using gcc, clang or icc, we can ask about exceptions' support (with the same flag).
#    if defined(__EXCEPTIONS)
#        define MILI_EXCEPTIONS_COMPILER_ENABLED
#    endif
#elif (MILI_COMPILER == MILI_COMPILER_TICCS)
#    undef MILI_EXCEPTIONS_COMPILER_ENABLED
// If we build using Code Composer Studio, we cannot use exceptions.
#else // On other compilers, we leave exceptions enabled by default.
// TODO: research exceptions' support flags for other compilers.
#    define MILI_EXCEPTIONS_COMPILER_ENABLED
#endif /* End detection of support for exceptions */

#endif /* PLATFORM_DETECTION_H */
