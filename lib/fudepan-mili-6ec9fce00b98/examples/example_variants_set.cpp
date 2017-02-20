#include "stdafx.h"
/*
example_variants_set: An example that uses MiLi's Variants Set.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Ezequiel S. Velez, FuDePAN 2010
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

int main()
{
    VariantsSet variantSet;
    int ie = 0;
    std::string is;
    float f;
    ElementName str = "greeting";
    variantSet.insert("number", 3);
    variantSet.insert(str, "hello");
    variantSet.insert("temperature", 0.1f);

    try
    {
        variantSet.get_element("number", ie);
        std::cout << "number: " << ie << std::endl;

        variantSet.get_element(str, is);
        std::cout << "greeting: " << is << std::endl;
        std::cout << "greeting: " << variantSet.get_element<std::string>(str) << std::endl;
        variantSet.get_element("float", f);
    }
    catch (const BadElementName&)
    {
        std::cerr << "Bad Element Name!" << std::endl;
    }
    catch (const BadElementType&)
    {
        std::cerr << "BadElementType!" << std::endl;
    }

    variantSet.erase("temperature");
    std::cout << "size: " << variantSet.size() << std::endl;
    return 0;
}
