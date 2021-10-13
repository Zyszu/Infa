
// KalkulatorDlg.h : header file
//

#pragma once


// CKalkulatorDlg dialog
class CKalkulatorDlg : public CDialogEx
{
// Construction
public:
	CKalkulatorDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KALKULATOR_DIALOG };
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

	enum MathOperations {
		ADDITION,
		SUBTRACTION,
		MULTIPLICATION,
		DIVISON,
		INPUT_ERROR
	};

	afx_msg void OnEnChangeEdit1();
	CEdit m_input1;
	CEdit m_input2;
	CEdit m_output;
	void make_operation(MathOperations);
	afx_msg void OnClickedAddition();
	afx_msg void OnClickedSubtraction();
	afx_msg void OnClickedMultiplication();
	afx_msg void OnClickedDivision();
};
