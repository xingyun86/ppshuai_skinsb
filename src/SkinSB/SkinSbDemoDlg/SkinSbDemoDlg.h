
// SkinSbDemoDlg.h : ͷ�ļ�
//

#pragma once
#include "virtuallist.h"
#include <vector>
#include "afxwin.h"

// CSkinSbDemoDlg �Ի���
class CSkinSbDemoDlg : public CDialog
{
// ����
public:
	CSkinSbDemoDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CSkinSbDemoDlg();
// �Ի�������
	enum { IDD = IDD_SKINSBDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	std::vector<ListData*> m_listData;
// ʵ��
protected:
	HICON m_hIcon;
	CBitmap m_bmScroll;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CVirtualList m_list;
	afx_msg void OnLvnGetdispinfoList1(NMHDR *pNMHDR, LRESULT *pResult);
};
