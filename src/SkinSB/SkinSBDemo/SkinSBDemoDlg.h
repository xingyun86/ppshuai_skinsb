// SkinSBDemoDlg.h : header file
//

#pragma once
#include "afxcmn.h"


// CSkinSBDemoDlg dialog
class CSkinSBDemoDlg : public CDialog
{
// Construction
public:
	CSkinSBDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SKINSBDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CBitmap m_bmScroll;
	CListCtrl m_ListCtrl;
	CRichEditCtrl m_RichEditCtrl;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
	
};
