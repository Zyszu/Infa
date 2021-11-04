// CTrianglePropertiesDlg.cpp : implementation file
//

#include "pch.h"
#include "Triangle.h"
#include "CTriangleProperties.h"
#include "afxdialogex.h"


// CTriangleProperties dialog

IMPLEMENT_DYNAMIC(CTriangleProperties, CDialogEx)

CTriangleProperties::CTriangleProperties(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TRIANGLE_PROPERTIES, pParent)
{

}

CTriangleProperties::~CTriangleProperties()
{
}

void CTriangleProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTriangleProperties, CDialogEx)
END_MESSAGE_MAP()


// CTriangleProperties message handlers
