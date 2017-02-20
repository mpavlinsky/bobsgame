/*
string_utils: A minimal library with string utilities.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Gutson, FuDePAN 2009
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

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <ctype.h>
#include <errno.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>
#include <limits>

#include "generic_exception.h"

NAMESPACE_BEGIN

class StringUtilsExceptionHierarchy {};
typedef GenericException <StringUtilsExceptionHierarchy> StringUtilsException;
DEFINE_SPECIFIC_EXCEPTION_TEXT(ConversionFailed, StringUtilsException, "Conversion error occurred: input failed.");


template <class NORMALIZER>
struct normalized_string : std::string
{
    class normalized_char
    {
        NORMALIZER normalize;
        std::string::value_type& c;
    public:
        normalized_char(std::string::value_type& c)
            : c(c)
        {}

        normalized_char(const normalized_char& other)
            : c(other.c)
        {}

        operator std::string::value_type() const
        {
            return c;
        }

        normalized_char& operator = (std::string::value_type other)
        {
            c = normalize(other);
            return *this;
        }

        bool operator == (std::string::value_type other) const
        {
            return c == normalize(other);
        }

        bool operator != (std::string::value_type other) const
        {
            return c != normalize(other);
        }

        // TODO: implement ++, --, +=, -=, etc.
    };

    void normalize()
    {
        NORMALIZER normalize;
        const size_t max = size();
        for (size_t i = 0; i < max; i++)
            std::string::operator[](i) = normalize(std::string::operator[](i));
    }

    normalized_string()
        : std::string()
    {}

    normalized_string(const normalized_string<NORMALIZER>& other)
        : std::string(other)
    {}

    normalized_string(const std::string& str)
        : std::string(str)
    {
        normalize();
    }

    normalized_string(const char* cstr)
        : std::string(cstr)
    {
        normalize();
    }

#define SELF_NORMALIZED_OP(op)                                                              \
    normalized_string<NORMALIZER>& operator op (const normalized_string<NORMALIZER>& other) \
    {                                                                                       \
        std::string::operator op (other);                                                   \
        return *this;                                                                       \
    }                                                                                       \
                                                                                            \
    normalized_string<NORMALIZER>& operator op (const std::string& other)                   \
    {                                                                                       \
        std::string::operator op (other);                                                   \
        normalize();                                                                        \
        return *this;                                                                       \
    }                                                                                       \
                                                                                            \
    normalized_string<NORMALIZER>& operator op (const char* cstr)                           \
    {                                                                                       \
        std::string::operator op (cstr);                                                    \
        normalize();                                                                        \
        return *this;                                                                       \
    }                                                                                       \
                                                                                            \
    normalized_string<NORMALIZER>& operator op (char c)                                     \
    {                                                                                       \
        std::string::operator op (NORMALIZER(c));                                           \
        return *this;                                                                       \
    }

    SELF_NORMALIZED_OP( =);
    SELF_NORMALIZED_OP( +=);

    normalized_string<NORMALIZER> operator + (const normalized_string<NORMALIZER>& other) const
    {
        normalized_string<NORMALIZER> tmp(*this);
        return (tmp += other);
    }

    normalized_string<NORMALIZER> operator + (const std::string& other) const
    {
        normalized_string<NORMALIZER> tmp(*this);
        return (tmp += other);
    }

    normalized_string<NORMALIZER> operator + (char c) const
    {
        normalized_string<NORMALIZER> tmp(*this);
        return (tmp += c);
    }

#define BOOL_NORMALIZED_OP(op)                                          \
    bool operator op (const normalized_string<NORMALIZER>& other) const \
    {                                                                   \
        return static_cast<const std::string&>(*this) op (other);       \
    }                                                                   \
                                                                        \
    bool operator op (const char* s) const                              \
    {                                                                   \
        return (*this) op normalized_string<NORMALIZER>(s);             \
    }                                                                   \
                                                                        \
    bool operator op (const std::string& s) const                       \
    {                                                                   \
        return *this op normalized_string<NORMALIZER>(s);               \
    }

    BOOL_NORMALIZED_OP( ==);
    BOOL_NORMALIZED_OP( !=);
    BOOL_NORMALIZED_OP( <);
    BOOL_NORMALIZED_OP( <=);
    BOOL_NORMALIZED_OP( >=);
    BOOL_NORMALIZED_OP( >);

    //using std::string::operator [];

    normalized_char operator[](size_t index)
    {
        return normalized_char(std::string::operator[](index));
    }

    normalized_char operator[](size_t index) const
    {
        return normalized_char(std::string::operator[](index));
    }

    std::string::size_type find(const normalized_string<NORMALIZER>& other) const
    {
        return std::string::find(other);
    }

    std::string::size_type find(const std::string& str) const
    {
        return find(normalized_string<NORMALIZER>(str));
    }

    std::string::size_type find(const char* cstr) const
    {
        return find(normalized_string<NORMALIZER>(cstr));
    }

    std::string::size_type find(std::string::value_type v) const
    {
        return std::string::find(NORMALIZER(v));
    }

};

struct TO_UPPER_FUNCTOR
{
    int operator()(int c) const
    {
        return toupper(c);
    }
};

struct TO_LOWER_FUNCTOR
{
    int operator()(int c) const
    {
        return tolower(c);
    }
};

typedef normalized_string<TO_UPPER_FUNCTOR> ustring;
typedef normalized_string<TO_LOWER_FUNCTOR> lstring;

inline std::string tolower(const std::string& s)
{
    return lstring(s);
}

inline std::string toupper(const std::string& s)
{
    return ustring(s);
}

template <class T> inline size_t size(const T& t)
{
    return t.size();
}

inline size_t size(const char* cstr)
{
    return std::strlen(cstr);
}

template <class S, class B>
inline bool begins_with(const S& s, const B& beginning)
{
    // TODO: improve
    return s.find(beginning) == 0;
}

template <class S, class E>
inline bool ends_with(const S& s, const E& ending)
{
    // TODO: improve
    const typename S::size_type position = s.find(ending);
    if (position == S::npos)
        return false;
    else
        return (s.size() - position) == size(ending);
}

static const unsigned int INT_CHAR_AMOUNT = 21u;
static const unsigned int FLOAT_CHAR_AMOUNT = 33u;
static const unsigned int DOUBLE_CHAR_AMOUNT = 33u;
static const unsigned int LONG_DOUBLE_CHAR_AMOUNT = 45u;

template <class Number>
inline std::string to_string(Number n)
{
    std::stringstream ss;
    ss << n;
    return ss.str();
}

template<>
inline std::string to_string(short int a)
{
    char cStr[INT_CHAR_AMOUNT];
    snprintf(cStr, INT_CHAR_AMOUNT, "%hd", a);
    return cStr;
}

template<>
inline std::string to_string(unsigned short int a)
{
    char cStr[INT_CHAR_AMOUNT];
    snprintf(cStr, INT_CHAR_AMOUNT, "%hu", a);
    return cStr;
}

template<>
inline std::string to_string(int a)
{
    char cStr[INT_CHAR_AMOUNT];
    snprintf(cStr, INT_CHAR_AMOUNT, "%d", a);
    return cStr;
}

template<>
inline std::string to_string(unsigned int a)
{
    char cStr[INT_CHAR_AMOUNT];
    snprintf(cStr, INT_CHAR_AMOUNT, "%u", a);
    return cStr;
}

template<>
inline std::string to_string(long int a)
{
    char cStr[INT_CHAR_AMOUNT];
    snprintf(cStr, INT_CHAR_AMOUNT, "%ld", a);
    return cStr;
}

template<>
inline std::string to_string(unsigned long int a)
{
    char cStr[INT_CHAR_AMOUNT];
    snprintf(cStr, INT_CHAR_AMOUNT, "%lu", a);
    return cStr;
}

template<>
inline std::string to_string(long long int a)
{
    char cStr[INT_CHAR_AMOUNT];
    snprintf(cStr, INT_CHAR_AMOUNT, "%lld", a);
    return cStr;
}

template<>
inline std::string to_string(unsigned long long int a)
{
    char cStr[INT_CHAR_AMOUNT];
    snprintf(cStr, INT_CHAR_AMOUNT, "%llu", a);
    return cStr;
}

template<>
inline std::string to_string(float f)
{
    char cStr[FLOAT_CHAR_AMOUNT];
    // %.14e is the maximum amount of decimal if
    // the number is written in scientific notation.
    snprintf(cStr, FLOAT_CHAR_AMOUNT, "%.14e", f);
    return cStr;
}

template<>
inline std::string to_string(double d)
{
    char cStr[DOUBLE_CHAR_AMOUNT];
    // %.23e is the maximum amount of decimal if
    // the number is written in scientific notation
    snprintf(cStr, DOUBLE_CHAR_AMOUNT, "%.23e", d);
    return cStr;
}

template<>
inline std::string to_string(long double ld)
{
    char cStr[LONG_DOUBLE_CHAR_AMOUNT];
    // %.34Le is the maximum amount of decimal if
    // the number is written in scientific notation that
    // snprintf supports.
    snprintf(cStr, LONG_DOUBLE_CHAR_AMOUNT, "%.34Le", ld);
    return cStr;
}


template <class T>
inline T from_string(const std::string& str)
{
    T value;
    std::stringstream ss(str);
    assert_throw<ConversionFailed>(ss >> value);
    return value;
}

template <class T>
inline bool from_string(const std::string& str, T& value)
{
    std::stringstream ss(str);
    return (ss >> value);
}


inline bool _isUnsigned(const std::string& str)
{
    return not str.empty() && str.front() != '-';
}

template <class T>
inline bool _strtoul(const std::string& str, T& value)
{
    bool success = false;
    if (_isUnsigned(str))
    {
        char* endptr;
        value = static_cast<T>(strtoul(str.c_str(), &endptr, 0));
        success = *endptr == '\0';
    }
    return success;
}

template <class T>
inline bool _strtol(const std::string& str, T& value)
{
    char* endptr;
    value = static_cast<T>(strtol(str.c_str(), &endptr, 0));
    return not str.empty() && *endptr == '\0';
}

template <class T>
inline bool _strtoull(const std::string& str, T& value)
{
    bool success = false;
    if (_isUnsigned(str))
    {
        char* endptr;
        value = static_cast<T>(strtoull(str.c_str(), &endptr, 0));
        success = *endptr == '\0';
    }
    return success;
}

template <class T>
inline bool _strtoll(const std::string& str, T& value)
{
    char* endptr;
    value = static_cast<T>(strtoll(str.c_str(), &endptr, 0));
    return not str.empty() && *endptr == '\0';
}



/* string to unsigned short int */

template<>
inline unsigned short int from_string(const std::string& str)
{
    unsigned short int value = 0u;
    const bool success = _strtoul<unsigned short int>(str, value);
    assert_throw<ConversionFailed>(success);
    return value;
}

template <>
inline bool from_string(const std::string& str, unsigned short int& value)
{
    return _strtoul<unsigned short int>(str, value);
}


/* string to short int */

template<>
inline short int from_string(const std::string& str)
{
    short int value = 0;
    const bool success = _strtol<short int>(str, value);
    assert_throw<ConversionFailed>(success);
    return value;
}

template <>
inline bool from_string(const std::string& str, short int& value)
{
    return _strtol<short int>(str, value);
}


/* string to unsigned int */

template<>
inline unsigned int from_string(const std::string& str)
{
    unsigned int value = 0u;
    const bool success = _strtoul<unsigned int>(str, value);
    assert_throw<ConversionFailed>(success);
    return value;
}

template <>
inline bool from_string(const std::string& str, unsigned int& value)
{
    return _strtoul<unsigned int>(str, value);
}


/* string to int */

template <>
inline int from_string(const std::string& str)
{
    int value = 0;
    const bool success = _strtol<int>(str, value);
    assert_throw<ConversionFailed>(success);
    return value;
}

template <>
inline bool from_string(const std::string& str, int& value)
{
    return _strtol<int>(str, value);
}


/* string to unsigned long int */

template<>
inline unsigned long int from_string(const std::string& str)
{
    unsigned long int value = 0ul;
    const bool success = _strtoul<unsigned long int>(str, value);
    assert_throw<ConversionFailed>(success);
    return value;
}

template <>
inline bool from_string(const std::string& str, unsigned long int& value)
{
    return _strtoul<unsigned long int>(str, value);
}


/* string to long int */

template<>
inline long int from_string(const std::string& str)
{
    long int value = 0l;
    const bool success = _strtol<long int>(str, value);
    assert_throw<ConversionFailed>(success);
    return value;
}

template <>
inline bool from_string(const std::string& str, long int& value)
{
    return _strtol<long int>(str, value);
}


/* string to unsigned long long int */

template<>
inline unsigned long long int from_string(const std::string& str)
{
    unsigned long long int value = 0ull;
    const bool success = _strtoull<unsigned long long int>(str, value);
    assert_throw<ConversionFailed>(success);
    return value;
}

template <>
inline bool from_string(const std::string& str, unsigned long long int& value)
{
    return _strtoull<unsigned long long int>(str, value);
}


/* string to long long int */

template<>
inline long long int from_string(const std::string& str)
{
    long long int value = 0ll;
    const bool success = _strtoll<long long int>(str, value);
    assert_throw<ConversionFailed>(success);
    return value;
}

template <>
inline bool from_string(const std::string& str, long long int& value)
{
    return _strtoll<long long int>(str, value);
}


/* string to float */

template <>
inline bool from_string(const std::string& str, float& value)
{
    char* endptr;
    value = strtof(str.c_str(), &endptr);
    return not str.empty() && *endptr == '\0';
}

template<>
inline float from_string(const std::string& str)
{
    float value = 0.f;
    const bool success = from_string(str, value);
    assert_throw<ConversionFailed>(success);
    return value;
}


/* string to double */

template <>
inline bool from_string(const std::string& str, double& value)
{
    char* endptr;
    value = strtod(str.c_str(), &endptr);
    return not str.empty() && *endptr == '\0';
}

template<>
inline double from_string(const std::string& str)
{
    double value;
    const bool success = from_string(str, value);
    assert_throw<ConversionFailed>(success);
    return value;
}


/* string to long double */

template <>
inline bool from_string(const std::string& str, long double& value)
{
    char* endptr;
    value = strtold(str.c_str(), &endptr);
    return not str.empty() && *endptr == '\0';
}


template<>
inline long double from_string(const std::string& str)
{
    long double value = 0.;
    const bool success = from_string(str, value);
    assert_throw<ConversionFailed>(success);
    return value;
}


/* Special case: string -> string */

template <>
inline std::string from_string<std::string>(const std::string& s)
{
    return s;
}

template <>
inline bool from_string<std::string>(const std::string& s, std::string& t)
{
    t = s;
    return true;
}

/* to_number is obsolete. from_string should be used instead. */
template <class Number>
inline Number to_number(const std::string& s)
{
    return from_string<Number>(s);
}

template <class Number>
inline bool to_number(const std::string& s, Number& n)
{
    return from_string(s, n);
}

// Remove tabs and whitespaces at both sides
inline std::string trim(const std::string& s)
{
    std::string text(s);

    const std::string::size_type positionStart = text.find_first_not_of(" \t");
    text.erase(0, positionStart);
    const std::string::size_type positionEnd = text.find_last_not_of(" \t");
    text.erase(positionEnd + 1);

    return text;
}

struct StringNotFound : std::exception {};

/* Throwing version only available if exceptions are allowed.*/
#ifdef MILI_EXCEPTIONS_COMPILER_ENABLED
inline std::string::size_type ensure_found(std::string::size_type found) throw(StringNotFound)
{
    if (found != std::string::npos)
        return found;
    else
        throw StringNotFound();
}
#endif //MILI_EXCEPTIONS_COMPILER_ENABLED

inline std::string::size_type ensure_found(std::string::size_type found, std::string::size_type default_value)
{
    if (found != std::string::npos)
        return found;
    else
        return default_value;
}

struct Count_
{
    explicit Count_(size_t count) :
        _count(count)
    {
    }

    const size_t _count;
};

struct Pos_
{
    explicit Pos_(size_t pos) :
        _pos(pos)
    {
    }

    const size_t _pos;
};

inline std::string substr(const std::string& str, const Pos_& start, const Count_& count)
{
    return str.substr(start._pos, count._count);
}

inline std::string substr(const std::string& str, const Pos_& start, const Pos_& end)
{
    return str.substr(start._pos, end._pos - start._pos + 1);
}

NAMESPACE_END

#endif
