
// MathGraphsDlg.h : header file
//

#pragma once


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
	afx_msg void OnClickedDraw();
	CEdit m_function_parameter_a;
	CEdit m_function_parameter_b;
	CEdit m_function_parameter_c;
};
