// CSECTION_ADVANCED.cpp : implementation file
//

#include "pch.h"
#include "BendingMoments.h"
#include "afxdialogex.h"
#include "CSECTION_ADVANCED.h"


// CSECTION_ADVANCED dialog

IMPLEMENT_DYNAMIC(CSECTION_ADVANCED, CDialogEx)

CSECTION_ADVANCED::CSECTION_ADVANCED(CWnd* pParent)
	: CDialogEx(IDD_CSECTION_ADVANCED, pParent)
{
	this->pPatent = pParent;
}

CSECTION_ADVANCED::~CSECTION_ADVANCED() {}

void CSECTION_ADVANCED::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMG_SECTIONS, m_img_sections);
	DDX_Control(pDX, IDC_VALUE_LENGTH_A, m_value_length_a);
	DDX_Control(pDX, IDC_VALUE_LENGTH_B, m_value_length_b);
	DDX_Control(pDX, IDC_VALUE_LENGTH_T1, m_value_length_t1);
	DDX_Control(pDX, IDC_VALUE_LENGTH_T2, m_value_length_t2);
}


BEGIN_MESSAGE_MAP(CSECTION_ADVANCED, CDialogEx)
	ON_EN_CHANGE(IDC_VALUE_LENGTH_A, &CSECTION_ADVANCED::OnChangeValueLengthA)
	ON_EN_CHANGE(IDC_VALUE_LENGTH_B, &CSECTION_ADVANCED::OnChangeValueLengthB)
	ON_EN_CHANGE(IDC_VALUE_LENGTH_T1, &CSECTION_ADVANCED::OnChangeValueLengthT1)
	ON_EN_CHANGE(IDC_VALUE_LENGTH_T2, &CSECTION_ADVANCED::OnChangeValueLengthT2)
END_MESSAGE_MAP()


CString CSECTION_ADVANCED::getImgName(const SectionType s_type) {
	switch (s_type)
	{
		case SectionType::S_CIRCLE:		return _T("Circle.png");
		case SectionType::S_RECTANGLE:	return _T("Rectangle.png");
		case SectionType::S_TEE:		return _T("Tee.png");
		default:						return _T("Undefined.png");
	}
}

void CSECTION_ADVANCED::pickImg(const SectionType s_type) {

	CString path = _T("./res/Sections/") + getImgName(s_type);

	CImage awesomeImg; CBitmap btmp;
	awesomeImg.Load(path);
	btmp.Attach(awesomeImg.Detach());
	m_img_sections.SetBitmap((HBITMAP)btmp);
}

long double* CSECTION_ADVANCED::getValues() {
	long double arr[4];
	CString data;

	m_value_length_a.GetWindowTextW(data);
	arr[0] = data.GetLength() == 0 ? 0.0L : _tcstold(data, NULL);

	m_value_length_b.GetWindowTextW(data);
	arr[1] = data.GetLength() == 0 ? 0.0L : _tcstold(data, NULL);

	m_value_length_t1.GetWindowTextW(data);
	arr[2] = data.GetLength() == 0 ? 0.0L : _tcstold(data, NULL);

	m_value_length_t2.GetWindowTextW(data);
	arr[3] = data.GetLength() == 0 ? 0.0L : _tcstold(data, NULL);

	return arr;
}

void CSECTION_ADVANCED::OnAnyChange() {
	
}

void CSECTION_ADVANCED::OnChangeValueLengthA()			{ OnAnyChange(); }
void CSECTION_ADVANCED::OnChangeValueLengthB()			{ OnAnyChange(); }
void CSECTION_ADVANCED::OnChangeValueLengthT1()			{ OnAnyChange(); }
void CSECTION_ADVANCED::OnChangeValueLengthT2()			{ OnAnyChange(); }