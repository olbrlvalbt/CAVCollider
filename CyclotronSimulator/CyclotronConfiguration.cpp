#include "CyclotronConfiguration.h"

CyclotronConfiguration::CyclotronConfiguration() {
	ringWidth = 2;
	ringRadius = 500;
	refreshRate = 50;
	ringOffset = 1;

	enableRule110T3Filter = true;
	
	deadCellPenColor = wxPen(wxColour(220, 170, 15), ringWidth);
	deadCellPenColor.SetCap(wxCAP_BUTT);
	aliveCellPenColor = wxPen(wxColour(115, 35, 15), ringWidth);
	aliveCellPenColor.SetCap(wxCAP_BUTT);
	filterExteriorPenColor = wxPen(wxColour(15, 15, 95), ringWidth);
	filterExteriorPenColor.SetCap(wxCAP_BUTT);
	filterInteriorPenColor = wxPen(wxColour(45, 45, 120), ringWidth);
	filterInteriorPenColor.SetCap(wxCAP_BUTT);
}

CyclotronConfiguration::CyclotronConfiguration(int _ringWidth, int _ringRadius, int _refreshRate, int _ringOffset, bool _enableFilter,
											   wxColour _deadCellColor, wxColour _aliveCellColor,
											   wxColour _filterExteriorColor, wxColour _filterInteriorColor) {
	ringWidth = _ringWidth;
	ringRadius = _ringRadius;
	refreshRate = _refreshRate;
	ringOffset = _ringOffset;

	enableRule110T3Filter = _enableFilter;
	
	deadCellPenColor = wxPen(_deadCellColor, ringWidth);
	deadCellPenColor.SetCap(wxCAP_BUTT);
	aliveCellPenColor = wxPen(_aliveCellColor, ringWidth);
	aliveCellPenColor.SetCap(wxCAP_BUTT);
	filterExteriorPenColor = wxPen(_filterExteriorColor, ringWidth);
	filterExteriorPenColor.SetCap(wxCAP_BUTT);
	filterInteriorPenColor = wxPen(_filterInteriorColor, ringWidth);
	filterInteriorPenColor.SetCap(wxCAP_BUTT);
}
