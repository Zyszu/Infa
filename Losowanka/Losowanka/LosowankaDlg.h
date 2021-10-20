
// LosowankaDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CLosowankaDlg dialog
class CLosowankaDlg : public CDialogEx
{
// Construction
public:
	CLosowankaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_LOSOWANKA_DIALOG };

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
	CEdit m_output1;
	CEdit m_output2;
	CEdit m_output3;
	CEdit m_output4;
	CEdit m_output5;
	CEdit m_rand_number1;
	CEdit m_rand_number2;
	CEdit m_rand_number3;
	CEdit m_rand_number4;
	CEdit m_rand_number5;
	afx_msg void OnClickedGenRandNum();
	afx_msg void gen_numbers();
	afx_msg void bubbleSort(bool);
	afx_msg void OnClickedSort();
	CStatic m_sort_info;
	afx_msg void OnClickedSortAsc();
	CButton m_sort_asc;
};
