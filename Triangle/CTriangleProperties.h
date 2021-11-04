#pragma once


// CTriangleProperties dialog

class CTriangleProperties : public CDialogEx
{
	DECLARE_DYNAMIC(CTriangleProperties)

public:
	CTriangleProperties(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTriangleProperties();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRIANGLE_PROPERTIES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
