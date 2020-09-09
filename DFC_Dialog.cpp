/* 
 * Copyright (C) 2004      Disch
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA 
 */

//////////////////////////////////////////////////////////////////////////
//
//  DFC_Dialog.cpp
//
//

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "DFC.h"



//////////////////////////////////////////////////////////////////////////
//
//  WndProc

int CDDialog::WndProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg == WM_COMMAND)
	{
		if(LOWORD(wParam) == IDOK)			OnOK();
		if(LOWORD(wParam) == IDCANCEL)		OnCancel();
	}

	return 0;
}


//////////////////////////////////////////////////////////////////////////
//
//  Construction / Destruction

CDDialog::CDDialog() : CDWnd()
{
	hWnd = NULL;
	bIsModal = 0;
}

CDDialog::~CDDialog()
{
	CDWnd::~CDWnd();
}


//////////////////////////////////////////////////////////////////////////
//
//  OnOK / OnCancel

void CDDialog::OnOK()
{
	if(bIsModal)
		EndDialog(hWnd,IDOK);
	else
		ShowWindow(0);
}

void CDDialog::OnCancel()
{
	if(bIsModal)
		EndDialog(hWnd,IDCANCEL);
	else
		ShowWindow(0);
}

void CDDialog::Destroy()
{
	if(!bIsModal)
		DestroyWindow(hWnd);
}

//////////////////////////////////////////////////////////////////////////
//
//  Creation Initialization

int		CDDialog::DoModal(HINSTANCE instance,HWND parentwnd,UINT dlgtemplate)
{
	if(hWnd != NULL)	return -1;		//dialog cannot already be in use

	bIsModal = 1;
	hInstance = instance;
	
	return (int)DialogBoxParam(instance,MAKEINTRESOURCE(dlgtemplate),parentwnd,
		GenericWindowProc,(LPARAM)this);
}

HWND	CDDialog::DoModeless(HINSTANCE instance,HWND parentwnd,UINT dlgtemplate)
{
	if(hWnd != NULL)	return NULL;

	bIsModal = 0;
	hInstance = instance;

	return CreateDialogParam(instance,MAKEINTRESOURCE(dlgtemplate),parentwnd,
		GenericWindowProc,(LPARAM)this);
}


//////////////////////////////////////////////////////////////////////////
//  DIALOG CONTROLS

CDDialogControl::CDDialogControl() : CDWnd()
{
	nID = 0;
}

CDDialogControl::~CDDialogControl()
{
	CDWnd::~CDWnd();
}

void CDDialogControl::AttachToControl(HWND hParent,UINT id)
{
	hParentWnd = hParent;
	nID = id;
	hWnd = GetDlgItem(hParent,id);
}

//////////////////////////////////////////////////////////////////////////
// Individual controls


//////////////////////////////////////////////////////////////////////////
//  CDListBox

CDString CDListBox::GetText(int index)
{
	CDString			str;
	int len = (int)SendMessage(hWnd,LB_GETTEXTLEN,index,0);
	SendMessage(hWnd,LB_GETTEXT,index,(LPARAM)str.GetBuffer(len));
	str.ReleaseBuffer();
	return str;
}

//////////////////////////////////////////////////////////////////////////
//  CDTab

int CDTab::InsertItem(int index,LPCSTR str)
{
	TCITEM item;
	ZeroMemory(&item,sizeof(TCITEM));
	item.mask = TCIF_TEXT;
	item.pszText = (LPSTR)str;
	item.iImage = -1;

	return (int)SendMessage(hWnd,TCM_INSERTITEM,index,(LPARAM)&item);
}