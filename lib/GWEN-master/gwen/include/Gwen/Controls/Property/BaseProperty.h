/*
	GWEN
	Copyright (c) 2010 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#ifndef GWEN_CONTROLS_PROPERTY_BASEPROPERTY_H
#define GWEN_CONTROLS_PROPERTY_BASEPROPERTY_H

#include "Gwen/Controls/Base.h"
#include "Gwen/Gwen.h"
#include "Gwen/Skin.h"
#include "Gwen/Utility.h"
#include <iostream>


namespace Gwen
{
	namespace Controls
	{
		namespace Property
		{
			class GWEN_EXPORT Base : public Gwen::Controls::Base
			{
				public:

					GWEN_CONTROL_INLINE( Base, Gwen::Controls::Base )
					{
						SetHeight( 20 );
						//SetAlignment(Pos::Left | Pos::CenterV);
						SetPadding(Padding(4, 2, 4, 2));
						//SetTextColor(Gwen::Color(0, 0, 0, 255));
					}

					virtual TextObject GetPropertyValue() = 0;

					virtual void SetPropertyValue( const TextObject & v, bool bFireChangeEvents = false ) = 0;

					virtual bool IsEditing() = 0;

					virtual void DoChanged()
					{
						Event::Information info;
						info.String = GetPropertyValue();
						onChange.Call( this, info );
					}

					void OnPropertyValueChanged( Gwen::Controls::Base* /*control*/ )
					{
						DoChanged();
					}

					virtual bool OnMouseWheeled(int iDelta)
					{
						//std::cout << "baseprop" << std::endl;
						return GetParent()->OnMouseWheeled(iDelta);
					}



					Event::Caller	onChange;
			};
		}
	}
}
#endif
