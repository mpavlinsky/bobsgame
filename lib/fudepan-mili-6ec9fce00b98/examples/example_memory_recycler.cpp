#include "stdafx.h"
/*
memory_recycler: A minimal library for doing type-safe bitwise operations.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Leonardo Boquillon, FuDePAN 2015
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

    This is a example file
*/

#include <iostream>
#include "mili/mili.h"


// Recyclable Types must inherit from mili::RecyclabeType
class RType : public mili::RecyclabeType<RType>
{
public:

    RType() = delete;

    RType(int a, int b)
        : _a(a),
          _b(b)
    {}

    int getA()
    {
        return _a;
    }

    int getB()
    {
        return _b;
    }

    // Recyclable Types must overload new/delete operators
    static void* operator new(std::size_t /*size*/)
    {
        return RecyclabeType<RType>::allocateMemory();
    }

    static void operator delete(void* memory)
    {
        RecyclabeType<RType>::deleteMemory(memory);
    }


private:
    int _a;
    int _b;
};


int main()
{
    for (int i = 0; i < 100; ++i)
    {
        for (int j = 0; j < 100; ++j)
        {
            RType* ptr = new RType(i, j);
            std::cout << ptr->getA() << " " << ptr->getB() << std::endl;
            delete ptr;
        }
    }

    return 0;
}