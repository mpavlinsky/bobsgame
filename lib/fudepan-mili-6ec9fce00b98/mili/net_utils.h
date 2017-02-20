/*
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

#ifndef NET_UTILS_H
#define NET_UTILS_H


#include <stdint.h>
#include <arpa/inet.h>

NAMESPACE_BEGIN

union int64Handler
{
    int64_t u64;
    struct
    {
        int32_t high32;
        int32_t low32;
    };
};

inline int16_t hton(const int16_t value)
{
    return static_cast<int16_t>(htons(static_cast<uint16_t>(value)));
}

inline uint16_t hton(const uint16_t value)
{
    return htons(value);
}

inline int32_t hton(const int32_t value)
{
    return static_cast<int32_t>(htonl(static_cast<uint32_t>(value)));
}

inline uint32_t hton(const uint32_t value)
{
    return htonl(value);
}

inline int64_t hton(const int64_t value)
{
    int64Handler input;
    input.u64 = value;

    input.high32 = hton(input.high32);
    input.low32 = hton(input.low32);

    std::swap(input.high32, input.low32);

    return input.u64;
}

inline uint64_t hton(const uint64_t value)
{
    return static_cast<uint64_t>(hton(static_cast<int64_t>(value)));
}

/** Network to host **/

inline int16_t ntoh(const int16_t value)
{
    return static_cast<int16_t>(ntohs(static_cast<uint16_t>(value)));
}

inline uint16_t ntoh(const uint16_t value)
{
    return ntohs(value);
}

inline int32_t ntoh(const int32_t value)
{
    return static_cast<int32_t>(ntohl(static_cast<uint32_t>(value)));
}

inline uint32_t ntoh(const uint32_t value)
{
    return ntohl(value);
}

inline int64_t ntoh(const int64_t value)
{
    int64Handler input;
    input.u64 = value;

    input.high32 = ntoh(input.high32);
    input.low32 = ntoh(input.low32);

    std::swap(input.high32, input.low32);

    return input.u64;
}

inline uint64_t ntoh(const uint64_t value)
{
    return static_cast<uint64_t>(ntoh(static_cast<int64_t>(value)));
}

NAMESPACE_END

#endif