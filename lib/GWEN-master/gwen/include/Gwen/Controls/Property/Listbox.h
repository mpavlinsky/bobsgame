#pragma once
#ifndef GWEN_CONTROLS_PROPERTY_LISTBOX_H
#define GWEN_CONTROLS_PROPERTY_LISTBOX_H

#include "Gwen/Controls/Property/BaseProperty.h"
#include "Gwen/Controls/ListBox.h"

namespace Gwen
{
	namespace Controls
	{
		namespace Property
		{
			class GWEN_EXPORT Listbox : public Property::Base
			{
			public:

				GWEN_CONTROL_INLINE(Listbox, Property::Base)
				{
					m_ListBox = new Gwen::Controls::ListBox(this);
					m_ListBox->SetShouldDrawBackground(false);
					//m_ListBox->onCheckChanged.Add(this, &BaseClass::OnPropertyValueChanged);
					m_ListBox->SetTabable(true);
					m_ListBox->SetKeyboardInputEnabled(true);
					m_ListBox->SetPos(2, 1);
					SetHeight(20);
					//SetAlignment(Pos::Left | Pos::CenterV);
					SetPadding(Padding(4, 2, 4, 2));
				}

				virtual TextObject GetPropertyValue()
				{
					return m_ListBox->GetSelectedRowName();// IsChecked() ? L"1" : L"0";
				}

				virtual void SetPropertyValue(const TextObject & v, bool bFireChangeEvents)
				{
//					if (v == L"1" || v == L"true" || v == L"TRUE" || v == L"yes" || v == L"YES")
//					{
//						return m_ListBox->SetChecked(true);
//					}
//
//					return m_ListBox->SetChecked(false);
				}

				virtual bool IsEditing()
				{
					return false;// m_ListBox->HasFocus();
				}

				virtual bool IsHovered()
				{
					return BaseClass::IsHovered() || m_ListBox->IsHovered();
				}


				virtual bool OnMouseWheeled(int iDelta)
				{
					return GetParent()->OnMouseWheeled(iDelta);
				}

				Gwen::Controls::ListBox* m_ListBox;
			};
		}
	}
}
#endif
