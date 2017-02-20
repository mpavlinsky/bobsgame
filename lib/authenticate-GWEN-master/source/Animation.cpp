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
#include "Gwen/Animation.h"

#include "Gwen/Utility.h"

namespace Gwen
{
namespace Animation
{

/// \brief The animations.
static std::map<Controls::Base*, std::list<Animation*>> _animations;

Animation::Animation()
{
}

Animation::~Animation()
{
}

bool Animation::GetFinished()
{
    return false;
}

void Add(Controls::Base* control, Animation* animation)
{
    animation->_control = control;
    _animations[control].push_back(animation);
}

void Cancel(Controls::Base* control)
{
    auto animations = _animations.find(control);
    if (animations != _animations.end())
    {
        auto animations_per_control = animations->second;
        auto animation = animations_per_control.begin();
        if (animation != animations_per_control.end())
        {
            do
            {
                delete(*animation);
            }
            while (++animation != animations_per_control.end());
        }

        _animations.erase(animations);
    }
}

void Think()
{
    auto animations = _animations.begin();
    if (animations != _animations.end())
    {
        do
        {
            auto animations_per_control = animations->second.begin();
            if (animations_per_control != animations->second.end())
            {
                do
                {
                    Animation* animation = *animations_per_control;
                    animation->Think();
                    if (animation->GetFinished())
                    {
                        animations_per_control = animations->second.erase(animations_per_control);
                        delete animation;
                    }
                    else
                    {
                        ++animations_per_control;
                    }
                }
                while (animations_per_control != animations->second.end());
            }
        }
        while (++animations != _animations.end());
    }
}

}; // namespace Animation

}; // namespace Gwen
