//////////////////////////////////////////////
// MyCombo.cpp
//  Definitions for the CMyCombo class

#include "stdafx.h"
#include "MyCombo.h"
#include "resource.h"

CMyCombo::CMyCombo() : m_himlImages(NULL)
{
	SetImages(3, IDB_STATUS);
}

CMyCombo::~CMyCombo()
{
	ImageList_Destroy(m_himlImages);
}

void CMyCombo::PreCreate(CREATESTRUCT &cs)
{
	cs.lpszClass = WC_COMBOBOXEX;
	cs.style = WS_VISIBLE | WS_CHILD | CBS_DROPDOWN;

	// Set the hight of the combobox in order to see a dropdown list
	cs.cy = 100;
}

BOOL CMyCombo::AddItems()
{
    typedef struct
	{
        int iImage;
        int iSelectedImage;
        int iIndent;
        LPTSTR pszText;
    } ITEMINFO, *PITEMINFO;

    ITEMINFO IInf[ ] =
	{
        { 0, 0,  0, (LPTSTR)_T("Item 1")},
        { 1, 1,  0, (LPTSTR)_T("Item 2")},
        { 2, 2,  0, (LPTSTR)_T("Item 3")},
    };

    int MaxItems = 3;
	for(int i = 0; i < MaxItems; ++i)
	{
		COMBOBOXEXITEM cbei = {0};
		cbei.mask = CBEIF_TEXT | CBEIF_INDENT | CBEIF_IMAGE| CBEIF_SELECTEDIMAGE;
        cbei.iItem          = i;
        cbei.pszText        = IInf[i].pszText;
        cbei.cchTextMax     = sizeof(IInf[i].pszText);
        cbei.iImage         = IInf[i].iImage;
        cbei.iSelectedImage = IInf[i].iSelectedImage;
        cbei.iIndent        = IInf[i].iIndent;

        // Add the items to the ComboBox's dropdown list
        if(-1 == SendMessage(CBEM_INSERTITEM, 0L, (LPARAM)&cbei))
            return FALSE;
    }

	// Assign the existing image list to the ComboBoxEx control
    SendMessage(CBEM_SETIMAGELIST, 0L, (LPARAM)m_himlImages);

    return TRUE;
}

void CMyCombo::SetImages(int nImages, UINT ImageID)
{
	if (m_himlImages)
	{
		ImageList_Destroy(m_himlImages);
		m_himlImages = NULL;
	}

	HBITMAP hbm = LoadBitmap(MAKEINTRESOURCE(ImageID));
	BITMAP bm = {0};
	::GetObject(hbm, sizeof(BITMAP), &bm);
	int iImageWidth  = bm.bmWidth / nImages;
	int iImageHeight = bm.bmHeight;
	COLORREF crMask = RGB(255,0,255);
	m_himlImages = ImageList_Create(iImageWidth, iImageHeight, ILC_COLOR32 | ILC_MASK, nImages, 0);
	ImageList_AddMasked(m_himlImages, hbm, crMask);
	::DeleteObject(hbm);
}

LRESULT CMyCombo::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		{
			SendMessage(CBEM_SETIMAGELIST, 0L, 0L);
			break;
		}
	}

	return WndProcDefault(uMsg, wParam, lParam);
}

