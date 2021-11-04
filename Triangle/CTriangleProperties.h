#pragma once
#include "TriangleInfo.h"

// CTriangleProperties dialog

class CTriangleProperties : public CDialogEx
{
	DECLARE_DYNAMIC(CTriangleProperties)

public:
	CTriangleProperties(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTriangleProperties();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRIANGLE_PROPERTIES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	TriangleInfo _previousTriangleInfo;
	CStatic m_TRIANGLE_PROPERTIES_CIRCUT;
	CStatic m_TRIANGLE_PROPERTIES_FIELD;
	afx_msg void updateData(TriangleInfo);
	CStatic m_IDC_TRIANGLE_PROPERTIES_PRECISION;
	CSliderCtrl m_IDC_TRIANGLE_PROPERTIES_PRECISION_SLIDER;
//	afx_msg void OnNMCustomdrawTrianglePropertiesPrecisionSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCustomdrawTrianglePropertiesPrecisionSlider(NMHDR* pNMHDR, LRESULT* pResult);
};
