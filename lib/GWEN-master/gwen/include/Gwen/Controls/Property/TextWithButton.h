/*
GWEN
Copyright (c) 2010 Facepunch Studios
See license in Gwen.h
*/

#pragma once
#ifndef GWEN_CONTROLS_PROPERTY_TEXTWITHBUTTON_H
#define GWEN_CONTROLS_PROPERTY_TEXTWITHBUTTON_H

#include "Gwen/Controls/Property/BaseProperty.h"
#include "Gwen/Controls/TextBox.h"

namespace Gwen
{
	namespace Controls
	{
		namespace Property
		{
			class GWEN_EXPORT TextWithButton : public Property::Base
			{
			public:

				GWEN_CONTROL_INLINE(TextWithButton, Property::Base)
				{
					//std::cout << pName << std::endl;
					m_Button = new Button(this,pName);
					m_Button->SetText(pName);
					m_Button->Dock(Pos::Left);
					m_Button->SetWidth((int)pName.length() * 8);//GetSkin()->GetRender()->MeasureText(GetFont(), pName) + 8);

					m_TextBox = new TextBox(this);
					m_TextBox->Dock(Pos::Left);
					m_TextBox->SetShouldDrawBackground(false);
					//m_TextBox->onTextChanged.Add(this, &BaseClass::OnPropertyValueChanged);
					m_TextBox->SetEditable(false);

				}

				virtual TextObject GetPropertyValue()
				{
					return m_TextBox->GetText();
				}

				virtual void SetPropertyValue(const TextObject & v, bool bFireChangeEvents)
				{
					m_TextBox->SetText(v, bFireChangeEvents);
				}

				virtual bool IsEditing()
				{
					return m_TextBox->HasFocus();
				}

				virtual bool IsHovered()
				{
					return BaseClass::IsHovered() || m_TextBox->IsHovered();
				}


				virtual bool OnMouseWheeled(int iDelta)
				{
					//std::cout << "text" << std::endl;
					return GetParent()->OnMouseWheeled(iDelta);
				}

				Button* GetButton()
				{
					return m_Button;
				}

				TextBox* m_TextBox;
				Button* m_Button;
				
			};
		}
	}
}
#endif
