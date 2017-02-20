/*
VariantsSet: A minimal library that implements a set of variables of heterogenic types.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Ezequiel S. Velez
                  Daniel Gutson, FuDePAN 2010
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

#ifndef VARIANTS_SET_H
#define VARIANTS_SET_H

#include <string>
#include <map>
#include "generic_exception.h"


NAMESPACE_BEGIN

/** @brief Exceptions for VariantSet. */
struct VariantsSetExceptionHierarchy {};
typedef mili::GenericException<VariantsSetExceptionHierarchy> VariantsSetException;

DEFINE_SPECIFIC_EXCEPTION_TEXT(BadElementName, VariantsSetExceptionHierarchy, "Element not found");
DEFINE_SPECIFIC_EXCEPTION_TEXT(BadElementType, VariantsSetExceptionHierarchy, "Conversion failed");

typedef std::string ElementName;

class VariantsSet
{
    typedef std::string ElementValue;
    typedef std::map<ElementName, ElementValue> VariantsContainer;

    /** @brief Container to store the elements. */
    VariantsContainer _elements;

public:

    /* typedef to simulate STL */
    typedef VariantsContainer::iterator iterator;
    typedef VariantsContainer::const_iterator const_iterator;
    typedef VariantsContainer::value_type value_type;
    typedef VariantsContainer::reference reference;
    typedef VariantsContainer::const_reference const_reference;

    /* Returns a const_iterator pointing to the beginning of the VariantsSet. */
    const_iterator begin() const
    {
        return _elements.begin();
    }

    /* Returns a const_iterator pointing to the end of the VariantsSet. */
    const_iterator end() const
    {
        return _elements.end();
    }

    /* Returns a iterator pointing to the beginning of the VariantsSet. */
    iterator begin()
    {
        return _elements.begin();
    }
    /* Returns a iterator pointing to the end of the VariantsSet. */
    iterator end()
    {
        return _elements.end();
    }

    /* returns the element called name */
    /* Throwing version only available if exceptions are allowed.*/
#   ifdef MILI_EXCEPTIONS_COMPILER_ENABLED
    template <class T>
    T get_element(const ElementName& name) const throw (BadElementType, BadElementName)
    {
        const ElementValue* const strElement = find(_elements, name, std::nothrow);
        if (strElement == NULL)
            throw BadElementName(name);

        T element;
        // TODO use mili::assert_throw<BadElementType, name>(strElement == nullptr). It depends on issue99
        if (!from_string<T>(*strElement, element))
            throw BadElementType(name);
        return element;
    }

    template <class T>
    void get_element(const ElementName& name, T& element) const throw (BadElementType, BadElementName)
    {
        const ElementValue* const strElement = find(_elements, name, std::nothrow);
        if (strElement == NULL)
            throw BadElementName(name);

        if (!from_string<T>(*strElement, element))
            throw BadElementType(name);
    }
#   endif //MILI_EXCEPTIONS_COMPILER_ENABLED

    /* get_element, nothrow versions */
    template <class T>
    bool get_element(const ElementName& name, T& element, const std::nothrow_t&) const
    {
        bool found = false;
        const T* const strElement = find(_elements, name, std::nothrow);
        if (strElement != NULL)
            found = from_string<T>(*strElement, element);
        return found;
    }

    /* inserts the element in the VariantsSet. */
    template <class T>
    void insert(const ElementName& name, const T& element)
    {
        _elements[name] = to_string(element);
    }

    bool empty() const
    {
        return _elements.empty();
    }

    void erase(const ElementName& name) throw (BadElementName)
    {
        const const_iterator it = _elements.find(name);
        if (it != _elements.end())
            _elements.erase(name);
        else
            throw BadElementName(name);
    }

    void clear()
    {
        _elements.clear();
    }

    size_t size() const
    {
        return _elements.size();
    }

    VariantsSet()
        : _elements()
    {}
};

NAMESPACE_END

#endif
