// CTrianglePropertiesDlg.cpp : implementation file
//

#include "pch.h"
#include "Triangle.h"
#include "CTriangleProperties.h"
#include "afxdialogex.h"


// CTriangleProperties dialog

IMPLEMENT_DYNAMIC(CTriangleProperties, CDialogEx)

CTriangleProperties::CTriangleProperties(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TRIANGLE_PROPERTIES, pParent)
{

}

CTriangleProperties::~CTriangleProperties()
{
}

void CTriangleProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TRIANGLE_PROPERTIES_CIRCUT, m_TRIANGLE_PROPERTIES_CIRCUT);
	DDX_Control(pDX, IDC_TRIANGLE_PROPERTIES_FIELD, m_TRIANGLE_PROPERTIES_FIELD);
	DDX_Control(pDX, IDC_TRIANGLE_PROPERTIES_PRECISION, m_IDC_TRIANGLE_PROPERTIES_PRECISION);
	DDX_Control(pDX, IDC_TRIANGLE_PROPERTIES_PRECISION_SLIDER, m_IDC_TRIANGLE_PROPERTIES_PRECISION_SLIDER);
}


BEGIN_MESSAGE_MAP(CTriangleProperties, CDialogEx)
//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_TRIANGLE_PROPERTIES_PRECISION_SLIDER, &CTriangleProperties::OnNMCustomdrawTrianglePropertiesPrecisionSlider)
ON_NOTIFY(NM_CUSTOMDRAW, IDC_TRIANGLE_PROPERTIES_PRECISION_SLIDER, &CTriangleProperties::OnCustomdrawTrianglePropertiesPrecisionSlider)
END_MESSAGE_MAP()


// CTriangleProperties message handlers

void CTriangleProperties::updateData(TriangleInfo info) {
	CString _FIELD, _CIRCUT;
	CString _PRECISION; _PRECISION.Format(_T("%i"), m_IDC_TRIANGLE_PROPERTIES_PRECISION_SLIDER.GetPos());
	_previousTriangleInfo = info;

	if (!info.isItTriangle) {
		_FIELD.Format(_T("-"));
		_CIRCUT.Format(_T("-"));
	}
	else {
		_FIELD.Format(_T("%." + _PRECISION + "f"), info.field);
		_CIRCUT.Format(_T("%." + _PRECISION + "f"), info.circuit);
	}

	m_TRIANGLE_PROPERTIES_FIELD.SetWindowTextW(_FIELD);
	m_TRIANGLE_PROPERTIES_CIRCUT.SetWindowTextW(_CIRCUT);
	m_IDC_TRIANGLE_PROPERTIES_PRECISION.SetWindowTextW(_PRECISION);
}