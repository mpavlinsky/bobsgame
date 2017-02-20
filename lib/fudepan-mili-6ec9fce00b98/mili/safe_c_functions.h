/*
safe_c_functions.h: improves some call to C functions like std::memcpy().
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Gutson,    FuDePAN 2013
                  Lucas Besso       FuDePAN 2013
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

#ifndef SAFE_C_FUNCTIONS
#define SAFE_C_FUNCTIONS

NAMESPACE_BEGIN

#include <cstring>

template <class DEST, class SRC>
inline void safecpy(DEST* dest, const SRC* src, size_t count)
{
    struct _Validation
    {
        static void SRC_type_EqualTo_DEST(const DEST* /*dst*/)
        {
        }
    };
    _Validation::SRC_type_EqualTo_DEST(src);
    std::memcpy(dest, src, count);
}

NAMESPACE_END

#endif
