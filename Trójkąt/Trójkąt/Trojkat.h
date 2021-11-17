
// TrojkatDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CTrojkatDlg dialog
class CTrojkatDlg : public CDialogEx
{
	// Construction
public:
	CTrojkatDlg(CWnd* pParent = NULL);	// standard constructor

	// Dialog Data
	enum { IDD = IDD_TRJKT_DIALOG };

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
	afx_msg void OnNMCustomdrawNodeBSliderY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedNodeAActive();
	afx_msg void OnBnClickedNodeBActive();
	afx_msg void OnBnClickedNodeCActive();
	CButton m_NODE_A_ACTIVE;
	CButton m_NODE_B_ACTIVE;
	CButton m_NODE_C_ACTIVE;
	CSliderCtrl m_NODE_A_SLIDER_X;
	CSliderCtrl m_NODE_A_SLIDER_Y;
	CSliderCtrl m_NODE_B_SLIDER_X;
	CSliderCtrl m_NODE_B_SLIDER_Y;
	CSliderCtrl m_NODE_C_SLIDER_X;
	CSliderCtrl m_NODE_C_SLIDER_Y;
	afx_msg void OnCustomdrawNodeASliderX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawNodeASliderY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawNodeBSliderX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawNodeBSliderY(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawNodeCSliderX(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawNodeCSliderY(NMHDR *pNMHDR, LRESULT *pResult);
};
