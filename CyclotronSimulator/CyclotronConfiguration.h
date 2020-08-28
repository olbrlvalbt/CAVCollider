#pragma once

#include <wx/wx.h>

class CyclotronConfiguration {
public:
	int ringWidth;
	int ringRadius;
	int refreshRate;
	int ringOffset;
	wxPen deadCellPenColor;
	wxPen aliveCellPenColor;
	wxPen filterExteriorPenColor;
	wxPen filterInteriorPenColor;
	bool enableRule110T3Filter;
	

	CyclotronConfiguration();

	CyclotronConfiguration(int _ringWidth, int _ringRadius, int _refreshRate, int _ringOffset, bool enableFilter,
						   wxColour _deadCellColor, wxColour _aliveCellColor,
						   wxColour _filterExteriorColor = wxNullColour, wxColour filterInteriorColor = wxNullColour);
};

