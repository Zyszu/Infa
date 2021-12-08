
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
	void						OnOK();
	afx_msg						DECLARE_MESSAGE_MAP()
public:
	bool						isFileNotSaved;
	CString						currFile;
	CEdit						m_notepad;
public:
	afx_msg bool				unsavedFileWarnign();
	afx_msg void				justReadFile(CFileDialog& fFile);
	afx_msg void				justSaveFile(CFileDialog& fFile, CString path = (CString)"");
	afx_msg void				OnBnClickedReadFile();
	afx_msg void				OnBnClickedSaveFile();
	CStatic m_path;
};
