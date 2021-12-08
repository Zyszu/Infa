
// KolosDlg.h : header file
//

#pragma once


// CKolosDlg dialog
class CKolosDlg : public CDialogEx
{
// Construction
public:
	CKolosDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KOLOS_DIALOG };
#endif

	CDC* dc;
	CPen _pen;

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
	CEdit m_input1;
	CEdit m_input2;
	CEdit m_input3;
	CEdit m_input4;
	CEdit m_input5;
	CEdit m_input6;
	CEdit m_input7;
	CEdit m_input8;
	CEdit m_input9;
	CEdit m_input10;

	CEdit* input[10];

	COLORREF magicColors[10];

	afx_msg void randomizeInput();
	afx_msg void updateOutput();
	afx_msg void updateGraph();
	afx_msg void onParametersChange();

	afx_msg void OnChangeInput1();
	afx_msg void OnChangeInput2();
	afx_msg void OnChangeInput3();
	afx_msg void OnChangeInput4();
	afx_msg void OnChangeInput5();
	afx_msg void OnChangeInput6();
	afx_msg void OnChangeInput7();
	afx_msg void OnChangeInput8();
	afx_msg void OnChangeInput9();
	afx_msg void OnChangeInput10();
	afx_msg void OnBnClickedButton1();
	CEdit m_output_average;
	CEdit m_output_standard_deviation;
};
