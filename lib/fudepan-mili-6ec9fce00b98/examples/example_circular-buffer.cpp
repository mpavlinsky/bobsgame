#include "stdafx.h"
/*
circular_buffer: An example of usage of circular buffer.
    This file is part of the MiLi Minimalistic Library.


    Copyright (C) Pablo Oliva, Franco Riberi, FuDePAN 2009
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

#include <iostream>
#include "mili/mili.h"

using namespace mili;
using namespace std;

int main()
{
    std::cout << "Build a Circular Buffer of 4 ints; by default, "
              "its error policies will be to use assertions." << std::endl;
    CircBuffer<int, 4u> cBuf;
    CircBuffer<int, 4u> dst;

    std::cout << "IsEmpty " << cBuf.isEmpty() << std::endl;
    std::cout << "Enqueue 0 " << std::endl;
    cBuf.queue(0);
    std::cout << "IsEmpty " << cBuf.isEmpty() << std::endl;
    std::cout << "Enqueue 1 " << std::endl;
    cBuf.queue(1);
    std::cout << "Enqueue 2 " << std::endl;
    cBuf.queue(2);
    std::cout << "IsFull " << cBuf.isFull() << std::endl;
    std::cout << "Enqueue 3 " << std::endl;
    cBuf.queue(3);
    std::cout << "IsFull " << cBuf.isFull() << std::endl;

    std::cout << "Source Buffer Available  " << cBuf.available() << std::endl;
    std::cout << "Destination Buffer Available  " << dst.available() << std::endl;

    std::cout << "Move from source to destination; amount of moves " << dst.moveFrom(cBuf) << std::endl;

    std::cout << "Source Buffer Available  " << cBuf.available() << std::endl;
    std::cout << "Destination Buffer Available  " << dst.available() << std::endl;

    return 0;
}

