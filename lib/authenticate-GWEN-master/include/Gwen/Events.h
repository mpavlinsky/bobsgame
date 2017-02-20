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

#pragma once

#include "Gwen/Structures.h"

#include <list>

namespace Gwen
{

namespace Controls
{

// Forward declarations
class Base;

}; // namespace Controls

namespace Event
{

// Forward declarations
class Caller;

/// \brief This class represents a base class for classes wanting to receieve events.
class Handler
{
public:
    /// \brief A blank callback function.
    typedef void (Handler::*FunctionBlank)();

    /// \brief A callback function containing the control.
    typedef void (Handler::*Function)(Controls::Base* control);

    /// \brief Destructor.
    virtual ~Handler();

    /// \brief Registers a caller with this handler.
    void RegisterCaller(Caller* caller);

    /// \brief Unregisters a caller with this handler.
    void UnregisterCaller(Caller* caller);

protected:
    /// \brief Constructor.
    Handler();

    /// \brief A helper function to clean links.
    void _CleanLinks();

    /// \brief The callers.
    std::list<Caller*> _callers;
};

/// \brief This class stores the information to send events.
class Caller
{
public:
    /// \brief Constructor.
    Caller();

    /// \brief Destructor.
    virtual ~Caller();

    /// \brief Call the callback.
    void Call(Controls::Base* control);

    /// \brief Adds a blank function callback.
    template <typename T>
    void Add(Event::Handler* object, void (T::*function)())
    {
        _AddInternal(object, static_cast<Handler::FunctionBlank>(function));
    }

    /// \brief Adds a function callback.
    template <typename T>
    void Add(Event::Handler* object, T function)
    {
        _AddInternal(object, static_cast<Handler::Function>(function));
    }

    /// \brief Removes a handler.
    void RemoveHandler(Event::Handler* object);

protected:
    /// \brief A helper function to clean links.
    void _CleanLinks();

    /// \brief Adds a blank function callback.
    void _AddInternal(Event::Handler* object, Handler::FunctionBlank function);

    /// \brief Adds a function callback.
    void _AddInternal(Event::Handler* object, Handler::Function function);

    /// \brief This class represents an instance of a handler.
    struct HandlerInstance
    {
        /// \brief Constructor.
        HandlerInstance();

        /// \brief The blank function.
        Handler::FunctionBlank _function_blank;

        /// \brief The function.
        Handler::Function _function;

        /// \brief The object.
        Event::Handler* _object;
    };

    /// \brief The handlers.
    std::list<HandlerInstance> _handlers;
};

}; // namespace Event

}; // namespace Gwen
