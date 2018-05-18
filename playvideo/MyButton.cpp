#include "stdafx.h"
#include "MyButton.h"


CMyButton::CMyButton()
{
	m_DownColor = m_UpColor = RGB(0, 0, 0);
}


CMyButton::~CMyButton()
{
}
BOOL CMyButton::Attach(const UINT nID, CWnd* pParent)
{
	//GetDlgItem(nID)->ModifyStyle(0,BS_OWNERDRAW,0);
	if (!SubclassDlgItem(nID, pParent))
		return FALSE;
	return TRUE;
}
void CMyButton::SetDownColor(COLORREF color)
{
	m_DownColor = color;
}
void CMyButton::SetUpColor(COLORREF color)
{
	m_UpColor = color;
}

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your code to draw the specified item
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);//�õ����Ƶ��豸����CDC
	VERIFY(lpDrawItemStruct->CtlType == ODT_BUTTON);

	// �õ�Button������,����Ĳ�����:1,�ȵõ�����Դ��༭�İ�ť������,
	//Ȼ�󽫴��������»��Ƶ���ť��,
	//ͬʱ�������ֵı���ɫ��Ϊ͸��,����,��ť�Ͻ�����ʾ����
	const int bufSize = 512;
	TCHAR buffer[bufSize];
	GetWindowText(buffer, bufSize);
	int size = strlen(buffer);   //�õ�����
	DrawText(lpDrawItemStruct->hDC, buffer, size, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_TABSTOP);   //��������
	SetBkMode(lpDrawItemStruct->hDC, TRANSPARENT);   //͸��

	if (lpDrawItemStruct->itemState &ODS_SELECTED)  //�����°�ťʱ�Ĵ���
	{//
	 //�ػ���������
		CBrush brush(m_DownColor);
		dc.FillRect(&(lpDrawItemStruct->rcItem), &brush);//
														 //��Ϊ����������ػ�,��������ҲҪ�ػ�
		DrawText(lpDrawItemStruct->hDC, buffer, size, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_TABSTOP);
		SetBkMode(lpDrawItemStruct->hDC, TRANSPARENT);
	}
	else                       //����ť���������ߵ���ʱ
	{
		CBrush brush(m_UpColor);
		dc.FillRect(&(lpDrawItemStruct->rcItem), &brush);//
														 //ͬ��,�����ػ�����
		DrawText(lpDrawItemStruct->hDC, buffer, size, &lpDrawItemStruct->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_TABSTOP);
		SetBkMode(lpDrawItemStruct->hDC, TRANSPARENT);
	}
	if ((lpDrawItemStruct->itemState &ODS_SELECTED) && (lpDrawItemStruct->itemAction &(ODA_SELECT | ODA_DRAWENTIRE)))
	{   //ѡ���˱��ؼ�,�����߿�
		COLORREF fc = RGB(255 - GetRValue(m_UpColor), 255 - GetGValue(m_UpColor), 255 - GetBValue(m_UpColor));//
		CBrush brush(fc);//
		dc.FrameRect(&(lpDrawItemStruct->rcItem), &brush);//
	}
	if (!(lpDrawItemStruct->itemState & ODS_SELECTED) && (lpDrawItemStruct->itemAction & ODA_SELECT))
	{
		//���Ƶ�ѡ��״̬����,ȥ���߿�
		CBrush brush(m_UpColor);
		dc.FrameRect(&lpDrawItemStruct->rcItem, &brush);//
	}
	dc.Detach();//
}