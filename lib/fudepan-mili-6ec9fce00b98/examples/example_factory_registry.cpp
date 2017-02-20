#include "stdafx.h"
/*
factory_registry: A simple way to registry derived classes without .h file
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Leandro Ramos, FuDePAN 2012
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

#include<iostream>
#include<string>
#include"mili/mili.h"

/* This example was written in one file for simplicity but it could write in separete files */

//! Speaker interface .h

struct Speaker
{
    virtual void saySomething() = 0;
    virtual ~Speaker(){}
};

//! End of speaker interface file

//! Hello.cpp file


class Hello: public Speaker
{
    virtual void saySomething();
};

void Hello::saySomething()
{
    std::cout << "Hello" << std::endl;
}

REGISTER_FACTORIZABLE_CLASS(Speaker, Hello, std::string, "Hello");

//! End of Hello.cpp

//! Goodbye.cpp


class Goodbye: public Speaker
{
    virtual void saySomething();
};

void Goodbye::saySomething()
{
    std::cout << "Goodbye" << std::endl;
}

REGISTER_FACTORIZABLE_CLASS(Speaker, Goodbye, std::string, "Goodbye");

//! End of Goodbye.cpp


class CustomizableSpeaker
{
public: 
    CustomizableSpeaker(bool polite);
    virtual ~CustomizableSpeaker(){};
    virtual void saySomething() = 0;

protected:
    const bool _polite;
};

CustomizableSpeaker::CustomizableSpeaker(bool polite):
    _polite(polite)
{    
}


struct CustomizableHello : CustomizableSpeaker
{
    CustomizableHello(bool polite);
    virtual void saySomething();
};

CustomizableHello::CustomizableHello(bool polite):
    CustomizableSpeaker(polite)
{    
}

void CustomizableHello::saySomething()
{
    std::cout << (_polite ? "Good morning" : "Hello") << std::endl;
}
REGISTER_FACTORIZABLE_CLASS_WITH_ARG(CustomizableSpeaker, CustomizableHello, std::string, "CustomizableHello", bool);

struct CustomizableGoodbye : CustomizableSpeaker
{
    CustomizableGoodbye(bool polite);
    virtual void saySomething();
};

CustomizableGoodbye::CustomizableGoodbye(bool polite):
    CustomizableSpeaker(polite)
{    
}

void CustomizableGoodbye::saySomething()
{
    std::cout << (_polite ? "Farewell" : "Goodbye") << std::endl;
}
REGISTER_FACTORIZABLE_CLASS_WITH_ARG(CustomizableSpeaker, CustomizableGoodbye, std::string, "CustomizableGoodbye", bool);


//! Main file
int main()
{
    std::string className;
    Speaker* speaker;
    mili::Factory<std::string,Speaker>::KeyIterator it(mili::FactoryRegistry<Speaker, std::string>::getConstructibleObjectsKeys());

    std::cout << "Which speaker would you like?" << std::endl;
    std::cin >> className;
    speaker = mili::FactoryRegistry<Speaker, std::string>::new_class(className);
    while(!it.end())
    {
        std::cout << *(it) << std::endl;
        it++;
    }
    if (speaker == NULL)
    {
        std::cout << "Speaker " << className << " doesn't exist" << std::endl;
    }
    else
    {
        speaker->saySomething();
        delete speaker;
    }

    CustomizableSpeaker* customSpeaker;

    std::cout << "\nPolite Speakers: " << std::endl;

    customSpeaker = mili::FactoryRegistry<CustomizableSpeaker, std::string, bool>::new_class("CustomizableHello", true);
    customSpeaker->saySomething();
    delete customSpeaker;

    customSpeaker = mili::FactoryRegistry<CustomizableSpeaker, std::string, bool>::new_class("CustomizableGoodbye", true);
    customSpeaker->saySomething();
    delete customSpeaker;

    std::cout << "\nNon polite Speakers: " << std::endl;
        
    customSpeaker = mili::FactoryRegistry<CustomizableSpeaker, std::string, bool>::new_class("CustomizableHello", false);
    customSpeaker->saySomething();
    delete customSpeaker;

    customSpeaker = mili::FactoryRegistry<CustomizableSpeaker, std::string, bool>::new_class("CustomizableGoodbye", false);
    customSpeaker->saySomething();
    delete customSpeaker;

    
    return 0;
}
