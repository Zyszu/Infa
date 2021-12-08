
// NotepadDlg.h : header file
//

#pragma once


// CNotepadDlg dialog
class CNotepadDlg : public CDialogEx
{
// Construction
public:
	CNotepadDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NOTEPAD_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON						m_hIcon;
	virtual BOOL				OnInitDialog();
	afx_msg void				OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void				OnPaint();
	afx_msg HCURSOR				OnQueryDragIcon();
								DECLARE_MESSAGE_MAP()
public:
	bool						isFileNotSaved;
public:
	afx_msg bool				unsavedFileWarnign();
	afx_msg void				readFile(const CString& path);
	afx_msg void				saveFile(const CString& path);
	afx_msg void				OnBnClickedReadFile();
	CEdit m_notepad;
};
