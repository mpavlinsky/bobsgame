#pragma once
#ifndef GWEN_CONTROLS_HORIZONTALSPLITTER_H
#define GWEN_CONTROLS_HORIZONTALSPLITTER_H

#include "Gwen/Gwen.h"
#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/SplitterBar.h"

namespace Gwen
{
	namespace Controls
	{
		class GWEN_EXPORT HorizontalSplitter : public Controls::Base
		{
		public:

			GWEN_CONTROL(HorizontalSplitter, Controls::Base);

			void Layout(Skin::Base* skin);


			virtual float CalculateValueHorizontal();

			virtual void UpdateHSplitter();


			virtual void OnHorizontalMoved(Controls::Base* control);


			virtual void SetPanel(int i, Controls::Base* pPanel);
			virtual Controls::Base* GetPanel(int i);

			virtual bool IsZoomed() { return m_iZoomedSection != -1; }
			virtual void Zoom(int section);
			virtual void UnZoom();
			virtual void ZoomChanged();
			virtual void CenterPanels() { m_fHVal = 0.5f;  Invalidate(); }

			virtual void SetSplitterSize(int size) { m_fBarSize = size; }
			virtual void SetSplitterWidth(int w) { m_fHVal = (float)w/Width(); }
			virtual SplitterBar* GetSplitter() { return m_HSplitter; }

		private:


			SplitterBar* m_HSplitter;


			Controls::Base* m_Sections[2];

			float	m_fHVal;

			int		m_fBarSize;

			char		m_iZoomedSection;

			Gwen::Event::Caller	onZoomed;
			Gwen::Event::Caller	onUnZoomed;
			Gwen::Event::Caller	onZoomChange;
		};
	}
}
#endif
