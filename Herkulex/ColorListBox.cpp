// ColorListBox.cpp : implementation file

#include "stdafx.h"
#include "ColorListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CColorListBox::CColorListBox()
{
}

CColorListBox::~CColorListBox()
{
}

BEGIN_MESSAGE_MAP(CColorListBox, CListBox)
	//{{AFX_MSG_MAP(CColorListBox)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////
void CColorListBox::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	if ((int)lpDIS->itemID < 0)
		return; 

	CDC* pDC = CDC::FromHandle(lpDIS->hDC);

	COLORREF crText;
	CString sText;
	COLORREF crNorm = (COLORREF)lpDIS->itemData;		// Color information is in item data.
	COLORREF crHilite = RGB(255-GetRValue(crNorm), 255-GetGValue(crNorm), 255-GetBValue(crNorm));

	// If item has been selected, draw the highlight rectangle using the item's color.
	if ((lpDIS->itemState & ODS_SELECTED) &&
		 (lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
		CBrush brush(crNorm);
		pDC->FillRect(&lpDIS->rcItem, &brush);
	}

	// If item has been deselected, draw the rectangle using the window color.
	if (!(lpDIS->itemState & ODS_SELECTED) &&	(lpDIS->itemAction & ODA_SELECT))
	{
		CBrush brush(::GetSysColor(COLOR_WINDOW));
		pDC->FillRect(&lpDIS->rcItem, &brush);
	}	 	

	// If item has focus, draw the focus rect.
	if ((lpDIS->itemAction & ODA_FOCUS) && (lpDIS->itemState & ODS_FOCUS))
		pDC->DrawFocusRect(&lpDIS->rcItem); 

	// If item does not have focus, redraw (erase) the focus rect.
	if ((lpDIS->itemAction & ODA_FOCUS) &&	!(lpDIS->itemState & ODS_FOCUS))
		pDC->DrawFocusRect(&lpDIS->rcItem); 


	// Set the background mode to TRANSPARENT to draw the text.
	int nBkMode = pDC->SetBkMode(TRANSPARENT);

	// If the item's color information is set, use the highlight color
	// gray text color, or normal color for the text.
	if (lpDIS->itemData)		
	{
		if (lpDIS->itemState & ODS_SELECTED)
			crText = pDC->SetTextColor(crHilite);
		else if (lpDIS->itemState & ODS_DISABLED)
			crText = pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
		else
			crText = pDC->SetTextColor(crNorm);
	}
	// Else the item's color information is not set, so use the
	// system colors for the text.
	else
	{
		if (lpDIS->itemState & ODS_SELECTED)
			crText = pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		else if (lpDIS->itemState & ODS_DISABLED)
			crText = pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
		else
			crText = pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
	}


	// Get and display item text.
	GetText(lpDIS->itemID, sText);
	CRect rect = lpDIS->rcItem;

	// Setup the text format.
	UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER;
	if (GetStyle() & LBS_USETABSTOPS)
		nFormat |= DT_EXPANDTABS;
	
	// Calculate the rectangle size before drawing the text.
	pDC->DrawText(sText, -1, &rect, nFormat | DT_CALCRECT);
	pDC->DrawText(sText, -1, &rect, nFormat);

	pDC->SetTextColor(crText); 
	pDC->SetBkMode(nBkMode);
}	// DrawItem


void CColorListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
	// ### Is the default list box item height the same as
	// the menu check height???
	lpMIS->itemHeight = ::GetSystemMetrics(SM_CYMENUCHECK);
}	// MeasureItem

int CColorListBox::AddString(LPCTSTR lpszItem)
{
	return ((CListBox*)this)->AddString(lpszItem);
}	// AddString

int CColorListBox::AddString(LPCTSTR lpszItem, COLORREF rgb)
{
	int nItem = AddString(lpszItem);
	if (nItem >= 0)
		SetItemData(nItem, rgb);
	return nItem;
}	// AddString


int CColorListBox::InsertString(int nIndex, LPCTSTR lpszItem)
{
	return ((CListBox*)this)->InsertString(nIndex, lpszItem);
}	// InsertString

int CColorListBox::InsertString(int nIndex, LPCTSTR lpszItem, COLORREF rgb)
{
	int nItem = ((CListBox*)this)->InsertString(nIndex,lpszItem);
	if (nItem >= 0)
		SetItemData(nItem, rgb);
	return nItem;
}	// InsertString

void CColorListBox::SetItemColor(int nIndex, COLORREF rgb)
{
	SetItemData(nIndex, rgb);	
	RedrawWindow();
}	// SetItemColor
