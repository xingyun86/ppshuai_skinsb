// VirtualList.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualList.h"

// CVirtualList

IMPLEMENT_DYNAMIC(CVirtualList, CListCtrl)

CVirtualList::CVirtualList()
{

}

CVirtualList::~CVirtualList()
{
}

BEGIN_MESSAGE_MAP(CVirtualList, CListCtrl)
END_MESSAGE_MAP()



// CVirtualList message handlers

enum ListID
{
	L_ID=0,
	L_Offset,
	L_Address,
	L_Thread,
	L_Command,
	L_Reg
};

int CVirtualList::InsertItemDataCallBack(NMHDR* pNMHDR,std::vector<ListData*>& pVec)
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM* pItem= &(pDispInfo)->item;
	int iItemIndx= pItem->iItem;
	if (pItem->mask & LVIF_TEXT) //�ַ�����������Ч
	{
		CString szTmp;
		switch(pItem->iSubItem){
		case L_ID: //��������������
			{
				TCHAR bufId[20]={0};
				_itot(pItem->iItem+1,bufId,10);
				szTmp = bufId;
			}
			break;
		case L_Offset:
			{
				TCHAR bufId[20]={0};
				_itot(pVec[iItemIndx]->nOffset,bufId,10);
				szTmp = bufId;
			}
			break;
		case L_Address: //�������2
			szTmp = pVec[iItemIndx]->szAddress;
			break;
		case L_Thread: //�������3
			szTmp = pVec[iItemIndx]->szThread;
			break;
		case L_Command: //�������4
			szTmp = pVec[iItemIndx]->szCom;
			break;
		case L_Reg: //�������5
			szTmp = pVec[iItemIndx]->szReg;
			break;
		}
		lstrcpy(pItem->pszText,szTmp);
	}
	return 0;
}
