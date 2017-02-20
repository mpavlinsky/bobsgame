#include "stdafx.h"
/*
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Hugo Arregui, FuDePAN 2011
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

    This is a test file.
*/

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <queue>
#include "mili/mili.h"

using namespace mili;

TEST(ContainerUtilsTest, vector)
{
    std::vector<int> v;
    insert_into(v, 1);
    ASSERT_EQ(1, find(v, 1));
    ASSERT_FALSE(contains(v, 2));
}

struct MapTest: public ::testing::Test
{
    void SetUp()
    {
        m["hello"] = "good bye";
        m["Bonjour"] = "au revoir";
        m["ハロー"] = "さようなら";
        m["hola"] = "adios";
        m["buenas"] = "adios";
    }
    std::map<std::string, std::string> m;
};

TEST_F(MapTest, contains)
{
    ASSERT_FALSE(contains(m, "nothing"));
}

TEST_F(MapTest, remove_first_from)
{
    ASSERT_TRUE(remove_first_from(m, "au revoir"));
}

TEST_F(MapTest, remove_all_from)
{
    ASSERT_TRUE(remove_all_from(m, "adios"));
}

TEST_F(MapTest, found)
{
    EXPECT_EQ("good bye", find(m, "hello"));
    EXPECT_EQ("good bye", *find(m, "hello", std::nothrow));
}

TEST_F(MapTest, not_found)
{
    ASSERT_THROW(find(m, "world"), ElementNotFound);
}

TEST(ContainerUtilsTest, queue)
{
    std::queue<int> myqueue;
    insert_into(myqueue, 100);
    insert_into(myqueue, 100);
}

TEST(ContainerUtilsTest, listContains)
{
    std::list<int> myList ;
    insert_into(myList, 1);
    insert_into(myList, 2);
    insert_into(myList, 3);

    EXPECT_TRUE(contains(myList, 2));
    EXPECT_FALSE(contains(myList, 5));
}

struct SpecList : public std::list<int>
{
    int aboveN(const int n)
    {
        int result = 0;
        for (std::list<int>::iterator i = this->begin(); i != this->end(); ++i)
        {
            if (*i > n)
            {
                ++result;
            }
        }
        return result;
    }
};

TEST(ContainerUtilsTest, derivedlist)
{
    SpecList myList;

    insert_into(myList, 1);
    insert_into(myList, 2);
    insert_into(myList, 3);
    EXPECT_EQ(true, contains(myList, 1));
    EXPECT_EQ(1, find(myList, 1));
    EXPECT_EQ(1, *find(myList, 1, std::nothrow));
    EXPECT_TRUE(remove_first_from(myList, 2));
    EXPECT_TRUE(remove_all_from(myList, 1));
    EXPECT_EQ(1, myList.aboveN(1));
}

struct SpecMap: public std::map<char, int>
{
};

TEST(ContainerUtilsTest, derivedMap)
{
    SpecMap myMap;

    myMap.insert(std::pair<char, int>('a', 1));
    myMap.insert(std::pair<char, int>('b', 2));
    myMap.insert(std::pair<char, int>('c', 3));
    myMap.insert(std::pair<char, int>('d', 1));
    EXPECT_EQ(true, contains(myMap, 'a'));
    EXPECT_EQ(1, find(myMap, 'a'));
    EXPECT_EQ(1, *find(myMap, 'a', std::nothrow));
    EXPECT_TRUE(remove_first_from(myMap, 2));
    EXPECT_TRUE(remove_all_from(myMap, 1));

}

TEST(ContainerUtilsTest, stringContains)
{
    const std::string longText =
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
        "Aenean luctus porttitor accumsan. "
        "Duis ornare auctor nisl, vel gravida nunc viverra quis.";

    const std::string beginning = "Lorem ipsum";
    const std::string middle = "tus por";
    const std::string end = "viverra quis.";
    const std::string notPresent = "Pugliese Pugliese Pugliese";

    EXPECT_TRUE(contains(longText, beginning));
    EXPECT_TRUE(contains(longText, middle));
    EXPECT_TRUE(contains(longText, end));
    EXPECT_FALSE(contains(longText, notPresent));
}

#if MILI_CXX_VERSION == MILI_CXX_VERSION_CXX0X

struct UMapTest: public ::testing::Test
{
    void SetUp()
    {
        m["hello"] = "good bye";
        m["Bonjour"] = "au revoir";
        m["ハロー"] = "さようなら";
        m["hola"] = "adios";
        m["buenas"] = "adios";
    }
    std::unordered_map<std::string, std::string> m;
};

TEST_F(UMapTest, contains)
{
    ASSERT_FALSE(contains(m, "nothing"));
}

TEST_F(UMapTest, remove_first_from)
{
    ASSERT_TRUE(remove_first_from(m, "au revoir"));
}

TEST_F(UMapTest, remove_all_from)
{
    ASSERT_TRUE(remove_all_from(m, "adios"));
}

TEST_F(UMapTest, found)
{
    EXPECT_EQ("good bye", find(m, "hello"));
    EXPECT_EQ("good bye", *find(m, "hello", std::nothrow));
}

TEST_F(UMapTest, not_found)
{
    ASSERT_THROW(find(m, "world"), ElementNotFound);
}

TEST(USetTest, general)
{
    std::unordered_set<int> s;
    insert_into(s, 1);
    insert_into(s, 2);
    EXPECT_EQ(1, find(s, 1));
    EXPECT_EQ(1, *find(s, 1, std::nothrow));
    EXPECT_FALSE(contains(s, 3));
    EXPECT_TRUE(remove_first_from(s, 1));
}

TEST(SetTest, general)
{
    std::set<std::string> s;
    insert_into(s, "asd");
    insert_into(s, "asd2");
    EXPECT_EQ("asd", find(s, "asd"));
    EXPECT_EQ("asd", *find(s, "asd", std::nothrow));
    EXPECT_FALSE(contains(s, "asdffff"));
    EXPECT_TRUE(remove_first_from(s, "asd"));
}

#endif