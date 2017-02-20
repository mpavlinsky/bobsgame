#include "stdafx.h"
/*
example_safe_c_functions: examples of usage for functions defined in c_call_improved.h.
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

    This is an example file.
*/

#include "mili/mili.h"

int main()
{
    char pepe[10];
    char juan[15];
//    int maria[10];

//    mili::safecpy(&pepe, juan, 10);   // it doesn't compile
//    mili::safecpy(pepe, &juan, 10);   // it doesn't compile

//    mili::safecpy(maria, juan, 10);   // it doesn't compile: maria type is different of juan type
//    mili::safecpy(juan, maria, 10);   // it doesn't compile: maria type is different of juan type

    mili::safecpy(pepe, juan, 10);   // it compiles
}
