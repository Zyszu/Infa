
// TriangleDlg.h : header file
//

#pragma once
#include "CTriangleProperties.h"

// CTriangleDlg dialog
class CTriangleDlg : public CDialogEx
{
// Construction
public:
	CTriangleDlg(CWnd* pParent = nullptr);	// standard constructor
	CTriangleProperties triangle_prop;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRIANGLE_DIALOG };
#endif

	CDC* dc; // CDC class pointer
	CPen _penRed;
	CPen _penGreen;
	CPen _penBlue;

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
	int df_x;
	int df_y;
	int df_width;
	int df_height;
	int df_margin;

	struct TriangleInfo {
		float circuit;
		float field;
		bool isItTriangle;
	};

	CButton m_NODE_A_ACTIVE;
	CButton m_NODE_B_ACTIVE;
	CButton m_NODE_C_ACTIVE;
	CSliderCtrl m_NODE_A_SLIDER_X;
	CSliderCtrl m_NODE_B_SLIDER_X;
	CSliderCtrl m_NODE_C_SLIDER_X;
	CSliderCtrl m_NODE_A_SLIDER_Y;
	CSliderCtrl m_NODE_B_SLIDER_Y;
	CSliderCtrl m_NODE_C_SLIDER_Y;
	afx_msg void OnBnClickedNodeAActive();
	afx_msg void OnBnClickedNodeBActive();
	afx_msg void OnBnClickedNodeCActive();
	afx_msg void OnNMCustomdrawNodeASlidebarX(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawNodeASlidebarY(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawNodeBSlidebarX(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawNodeBSlidebarY(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawNodeCSlidebarX(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMCustomdrawNodeCSlidebarY(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void drawTriangle();
	afx_msg void onAnyChange();
	afx_msg CTriangleDlg::TriangleInfo getTriangleInfo();
	CStatic m_DRAWING_FRAME;
	CButton m_TRIANGLE_PROPERTIES_ACTIVE;
	afx_msg void OnBnClickedTrianglePropertiesActive();
};
