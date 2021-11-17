
// MathGraphsDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CMathGraphsDlg dialog
class CMathGraphsDlg : public CDialogEx
{
// Construction
public:
	CMathGraphsDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data

	CDC* dc;
	CPen pen;
	CPen graph_pen;

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MATHGRAPHS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_math_function_formula;
	afx_msg void OnStnClickedMathFunctionFormula();
	afx_msg void rootPointsUpdate();
	afx_msg void mathGraphUpdate();
	CEdit m_function_parameter_a;
	CEdit m_function_parameter_b;
	CEdit m_function_parameter_c;
	CStatic m_root_points;
	afx_msg void OnUpdateValueA();
	afx_msg void OnUpdateValueB();
	afx_msg void OnUpdateValueC();
	afx_msg void OnNMCustomdrawGraphScale(NMHDR* pNMHDR, LRESULT* pResult);
	CSliderCtrl m_graph_scale;
	CStatic m_graph_scale_info;
	afx_msg void OnBnClickedCheck1();
	CButton m_a_value_active;
	CButton m_b_value_active;
	CButton m_c_value_active;
	afx_msg void OnClickedAValueActive();
	afx_msg void OnClickedBValueActive();
	afx_msg void OnClickedCValueActive();
};
