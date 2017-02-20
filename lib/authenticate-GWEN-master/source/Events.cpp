//
// GWEN
// Copyright (c) 2013-2015 James Lammlein
// Copyright (c) 2010 Facepunch Studios
//
// This file is part of GWEN.
//
// MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "Gwen.h"
#include "Gwen/Events.h"

namespace Gwen
{
namespace Event
{

Handler::~Handler()
{
    _CleanLinks();
}

void Handler::RegisterCaller(Caller* caller)
{
    _callers.push_back(caller);
}

void Handler::UnregisterCaller(Caller* caller)
{
    _callers.remove(caller);
}

Handler::Handler()
{
}

void Handler::_CleanLinks()
{
    /// Remove the link from all callers.
    auto begin = _callers.begin();
    while (begin != _callers.end())
    {
        Caller* caller = *begin;
        UnregisterCaller(caller);
        caller->RemoveHandler(this);
        begin = _callers.begin();
    }
}

Caller::Caller()
{
}

Caller::~Caller()
{
    _CleanLinks();
}

void Caller::Call(Controls::Base* control)
{
    for (auto i = _handlers.begin(); i != _handlers.end(); ++i)
    {
        HandlerInstance& handler_instance = *i;
        if (handler_instance._function)
        {
            (handler_instance._object->*handler_instance._function)(control);
        }

        if (handler_instance._function_blank)
        {
            (handler_instance._object->*handler_instance._function_blank)();
        }
    }
}

void Caller::RemoveHandler(Event::Handler* object)
{
    object->UnregisterCaller(this);

    auto i = _handlers.begin();
    while (i != _handlers.end())
    {
        HandlerInstance& handler_instance = *i;
        if (handler_instance._object == object)
        {
            i = _handlers.erase(i);
        }
        else
        {
            ++i;
        }
    }
}

void Caller::_CleanLinks()
{
    for (auto i = _handlers.begin(); i != _handlers.end(); ++i)
    {
        HandlerInstance& handler_instance = *i;
        handler_instance._object->UnregisterCaller(this);
    }
    _handlers.clear();
}

void Caller::_AddInternal(Event::Handler* object, Handler::FunctionBlank function)
{
    HandlerInstance handler_instance;
    handler_instance._function_blank = function;
    handler_instance._object = object;

    _handlers.push_back(handler_instance);

    object->RegisterCaller(this);
}

void Caller::_AddInternal(Event::Handler* object, Handler::Function function)
{
    HandlerInstance handler_instance;
    handler_instance._function = function;
    handler_instance._object = object;

    _handlers.push_back(handler_instance);

    object->RegisterCaller(this);
}

Caller::HandlerInstance::HandlerInstance() :
    _function_blank(nullptr),
    _function(nullptr),
    _object(nullptr)
{
}

}; // namespace Event

}; // namespace Gwen
