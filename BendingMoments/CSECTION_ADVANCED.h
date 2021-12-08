#pragma once
#include "afxdialogex.h"
#include "PrayToTheLordBecauseHeGaveUsShawtiesAndCoffe.h"


// CSECTION_ADVANCED dialog

class CSECTION_ADVANCED : public CDialogEx
{
	DECLARE_DYNAMIC(CSECTION_ADVANCED)
	CWnd* pPatent;
public:
	CSECTION_ADVANCED(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSECTION_ADVANCED();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CSECTION_ADVANCED };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic						m_img_sections;
	afx_msg CString				getImgName(const SectionType s_type);
	afx_msg void				pickImg(const SectionType s_type);
	CEdit						m_value_length_a;
	CEdit						m_value_length_b;
	CEdit						m_value_length_t1;
	CEdit						m_value_length_t2;
	afx_msg long double*		getValues();
	afx_msg void				OnAnyChange();
	afx_msg void				OnChangeValueLengthA();
	afx_msg void				OnChangeValueLengthB();
	afx_msg void				OnChangeValueLengthT1();
	afx_msg void				OnChangeValueLengthT2();
};
