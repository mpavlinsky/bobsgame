/*
	GWEN
	Copyright (c) 2012 Facepunch Studios
	See license in Gwen.h
*/

#pragma once
#ifndef GWEN_CONTROLS_PROPERTY_SCROLLABLECOMBOBOX_H
#define GWEN_CONTROLS_PROPERTY_SCROLLABLECOMBOBOX_H

#include "Gwen/Controls/Property/BaseProperty.h"
#include "Gwen/Controls/ComboBox.h"

namespace Gwen
{
	namespace Controls
	{
		namespace Property
		{
			class GWEN_EXPORT ScrollableComboBox : public Property::Base
			{
				public:

					GWEN_CONTROL_INLINE(ScrollableComboBox, Property::Base )
					{
						m_ScrollControl = new Gwen::Controls::ScrollControl(this);
						m_ScrollControl->Dock(Pos::Fill);
						//m_ScrollControl->SetWidth(this->Width() / 2);
						//m_ScrollControl->SetHeight(blockListsBase->Height());
						m_ScrollControl->SetAutoHideBars(false);
						m_ScrollControl->SetScroll(true, true);
						m_ScrollControl->SetHeight(200);


						m_ComboBox = new Gwen::Controls::ComboBox(m_ScrollControl);
						m_ComboBox->Dock( Pos::Fill );
						m_ComboBox->onSelection.Add( this, &BaseClass::OnPropertyValueChanged );
						m_ComboBox->SetTabable( true );
						m_ComboBox->SetKeyboardInputEnabled( true );
						m_ComboBox->SetShouldDrawBackground( false );
						SetHeight( 24 );
						//SetAlignment(Pos::Left | Pos::CenterV);
						SetPadding(Padding(4, 2, 4, 2));
					}

					virtual TextObject GetPropertyValue()
					{
						Gwen::Controls::Label* pControl = m_ComboBox->GetSelectedItem();

						if ( !pControl ) { return L""; }

						return pControl->GetName();
					}

					virtual void SetPropertyValue( const TextObject & v, bool bFireChangeEvents )
					{
						m_ComboBox->SelectItemByName( v.Get(), bFireChangeEvents );
					}

					virtual bool IsEditing()
					{
						return m_ComboBox->HasFocus();
					}

					virtual bool IsHovered()
					{
						return BaseClass::IsHovered() || m_ComboBox->IsHovered();
					}

					Gwen::Controls::ComboBox* GetComboBox()
					{
						return m_ComboBox;
					}


					virtual bool OnMouseWheeled(int iDelta)
					{
						//std::cout << "combobox" << std::endl;
						return GetParent()->OnMouseWheeled(iDelta);
					}

				protected:

					Gwen::Controls::ComboBox* m_ComboBox;
					Gwen::Controls::ScrollControl* m_ScrollControl;
			};
		}
	}
}
#endif
