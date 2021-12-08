
// MFCApplication1Dlg.h : header file
//

#pragma once
#include "afxwin.h"


// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialogEx
{
// Construction
public:
									CMFCApplication1Dlg(CWnd* pParent = NULL);	// standard constructor
									~CMFCApplication1Dlg();

public:
	static CDC*						dc;
	static CPen						clock_face_pen;
	static CPen						clock_hand_pen;

// Dialog Data
	enum							{ IDD = IDD_MFCAPPLICATION1_DIALOG };

	protected:
	virtual void					DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON							m_hIcon;
	virtual BOOL					OnInitDialog();
	afx_msg void					OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void					OnPaint();
	afx_msg HCURSOR					OnQueryDragIcon();
									DECLARE_MESSAGE_MAP()
public:
	static int						clock_speed;
	static CEdit					m_speed_control;
	static bool						doTickTick;
	static bool						killClock;
	CWinThread*						clock;

	afx_msg void					changeClockSpeed(int new_speed);
	afx_msg static UINT				initClock(LPVOID  pvParam);

public:
	afx_msg void					OnEnChangeSpeedControl();
	afx_msg void					OnBnClickedButton1();
};
