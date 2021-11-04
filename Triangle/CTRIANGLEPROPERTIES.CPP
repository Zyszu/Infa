#include "pch.h"
#include "CTriangleProperties.h"


void CTriangleProperties::OnCustomdrawTrianglePropertiesPrecisionSlider(NMHDR* pNMHDR, LRESULT* pResult) { LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR); *pResult = 0; updateData(_previousTriangleInfo); }
