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
//  DFC.h
//
//		Contains classes for common windows features
//
//

#include <CommCtrl.h>
#include "DFC_String.h"
#include "DFC_Array.h"

//////////////////////////////////////////////////////////////////////////
//
//  CDWnd
//
//		for windows!
//

class CDWnd;
typedef void(CDWnd::*MessageMapCallback)();

#define AFX_MAPMESSAGE(CtrlID,MsgID,Func) MapMessage(CtrlID,MsgID,(MessageMapCallback)Func)
#define AFX_MAPNOTIFY(CtrlID,MsgID,Func) MapNotify(CtrlID,MsgID,(MessageMapCallback)Func)

class CDWnd
{
public:
	CDWnd();
	~CDWnd();

	virtual void				SetWindowText(CDString text) { ::SetWindowText(hWnd,text); }
	virtual CDString			GetWindowText();

	virtual HWND				GetHandle() { return hWnd; }
	virtual HWND				GetParentHandle() { return hParentWnd; }

	virtual void				GetWindowRect(RECT* rc) { ::GetWindowRect(hWnd,rc); }
	virtual void				MoveWindow(RECT* rc,bool redraw = 1);

	virtual void				EnableWindow(int enable) { ::EnableWindow(hWnd,enable); }
	virtual void				ShowWindow(int show) { ::ShowWindow(hWnd,show); }

	virtual void				ScreenToClient(RECT* rc);

protected:
	static INT_PTR CALLBACK		GenericWindowProc(HWND wnd,UINT msg,WPARAM wParam,LPARAM lParam);
	virtual int					WndProc(UINT msg,WPARAM wParam,LPARAM lParam) { return (int)DefWindowProc(hWnd,msg,wParam,lParam); };


protected:
	// Message mapping
	class DDlgMsgItem
	{
	public:
		DDlgMsgItem()		{ next = NULL; }

		DWORD				dwCtrlID;
		DWORD				dwMsgID;
		MessageMapCallback	pProc;
		DDlgMsgItem*		next;
	};

	DDlgMsgItem*			m_MessageMap;
	DDlgMsgItem*			m_NotifyMap;

	void					MapMessage(UINT uControl,UINT uMsg,MessageMapCallback pProc)
	{
		DDlgMsgItem*		pItem = new DDlgMsgItem();
		pItem->dwCtrlID =	uControl;
		pItem->dwMsgID =	uMsg;
		pItem->pProc =		pProc;
		pItem->next =		m_MessageMap;

		m_MessageMap =		pItem;
	}

	void					MapNotify(UINT uControl,UINT uMsg,MessageMapCallback pProc)
	{
		DDlgMsgItem*		pItem = new DDlgMsgItem();
		pItem->dwCtrlID =	uControl;
		pItem->dwMsgID =	uMsg;
		pItem->pProc =		pProc;
		pItem->next =		m_NotifyMap;

		m_NotifyMap =		pItem;
	}

protected:
	HINSTANCE				hInstance;
	HWND					hWnd;
	HWND					hParentWnd;
};


//////////////////////////////////////////////////////////////////////////
//
//  CDDialogControl
//
//		Dialog controls
//

class CDDialogControl : public CDWnd
{
public:
	CDDialogControl();
	~CDDialogControl();

	//////////////////////////////////////////////////////////////////////////
	// Creation
	virtual void		AttachToControl(HWND hParent,UINT id);

protected:
	UINT			nID;
};


//////////////////////////////////////////////////////////////////////////
//
//  CDStatic
//
//	  for static controls on dialogs
//

class CDStatic : public CDDialogControl
{
public:
	CDStatic() : CDDialogControl()		{ }
	~CDStatic()							{CDDialogControl::~CDDialogControl(); }
};

//////////////////////////////////////////////////////////////////////////
//
//  CDEdit
//
//	  for edit boxes (maybe there'll be more later?)
//

class CDEdit : public CDDialogControl
{
public:
	CDEdit() : CDDialogControl()		{ }
	~CDEdit()							{CDDialogControl::~CDDialogControl(); }
};

//////////////////////////////////////////////////////////////////////////
//
//  CDButton
//
//	  for buttons
//

class CDButton : public CDDialogControl
{
public:
	CDButton() : CDDialogControl()		{ }
	~CDButton()							{CDDialogControl::~CDDialogControl(); }

	//////////////////////////////////////////////////////////////////////////
	//interactive functions
	void			SetCheck(int set)	{::CheckDlgButton(hParentWnd,nID,set);}
	int				GetCheck()			{return ::IsDlgButtonChecked(hParentWnd,nID);}
};

//////////////////////////////////////////////////////////////////////////
//
//  CDListBox

class CDListBox : public CDDialogControl
{
public:
	CDListBox() : CDDialogControl()			{ }
	~CDListBox()							{CDDialogControl::~CDDialogControl(); }

	//////////////////////////////////////////////////////////////////////////
	//interactive functions
	int				GetCurSel()								{return (int)SendMessage(hWnd,LB_GETCURSEL,0,0);}
	void			SetCurSel(int sel)						{SendMessage(hWnd,LB_SETCURSEL,sel,0);}
	int				GetSel(int index)						{return (int)SendMessage(hWnd,LB_GETSEL,index,0);}
	void			SetSel(int index,int state)				{SendMessage(hWnd,LB_SETSEL,state,index);}
	int				GetCount()								{return (int)SendMessage(hWnd,LB_GETCOUNT,0,0);}

	//adding/removing strings
	void			ResetContent()							{SendMessage(hWnd,LB_RESETCONTENT,0,0);}
	void			DeleteString(int index)					{SendMessage(hWnd,LB_DELETESTRING,index,0);}
	int				AddString(LPCSTR str)					{return (int)SendMessage(hWnd,LB_ADDSTRING,0,(LPARAM)str);}
	int				InsertString(int index,LPCSTR str)		{return (int)SendMessage(hWnd,LB_INSERTSTRING,index,(LPARAM)str);}

	//text retrieval
	CDString		GetText(int index);
};

//////////////////////////////////////////////////////////////////////////
//
//  CDComboBox

class CDComboBox : public CDDialogControl
{
public:
	CDComboBox() : CDDialogControl()		{ }
	~CDComboBox()							{ CDDialogControl::~CDDialogControl(); }

	//////////////////////////////////////////////////////////////////////////
	//interactive functions
	int				GetCurSel()								{return (int)SendMessage(hWnd,CB_GETCURSEL,0,0);}
	void			SetCurSel(int sel)						{SendMessage(hWnd,CB_SETCURSEL,sel,0);}
	int				GetCount()								{return (int)SendMessage(hWnd,CB_GETCOUNT,0,0);}

	//adding/removing strings
	void			ResetContent()							{SendMessage(hWnd,CB_RESETCONTENT,0,0);}
	void			DeleteString(int index)					{SendMessage(hWnd,CB_DELETESTRING,index,0);}
	int				AddString(LPCSTR str)					{return (int)SendMessage(hWnd,CB_ADDSTRING,0,(LPARAM)str);}
	int				InsertString(int index,LPCSTR str)		{return (int)SendMessage(hWnd,CB_INSERTSTRING,index,(LPARAM)str);}
};

//////////////////////////////////////////////////////////////////////////
//
//  CDSlider

class CDSlider : public CDDialogControl
{
public:
	CDSlider() : CDDialogControl()		{ }
	~CDSlider()							{CDDialogControl::~CDDialogControl();}

	void			SetRange(int Min,int Max,bool redraw = 1)	{SendMessage(hWnd,TBM_SETRANGE,redraw,MAKELONG(Min,Max));}
	void			SetPos(int pos,bool redraw = 1)				{SendMessage(hWnd,TBM_SETPOS,redraw,pos);}
	int				GetPos()									{return (int)SendMessage(hWnd,TBM_GETPOS,0,0);}
};

//////////////////////////////////////////////////////////////////////////
//
//  CDTab

class CDTab : public CDDialogControl
{
public:
	CDTab() : CDDialogControl()			{ }
	~CDTab()							{CDDialogControl::~CDDialogControl(); }

	//////////////////////////////////////////////////////////////////////////
	//interactive functions
	int				GetCurSel()							{return (int)SendMessage(hWnd,TCM_GETCURSEL,0,0); }
	void			SetCurSel(int sel)					{SendMessage(hWnd,TCM_SETCURSEL,sel,0); }
	int				GetCount();

	//adding/removing items
	void			DeleteAllItems()					{SendMessage(hWnd,TCM_DELETEALLITEMS,0,0);}
	void			DeleteItem(int index)				{SendMessage(hWnd,TCM_DELETEITEM,index,0);}
	int				InsertItem(int index,LPCSTR str);
};

//////////////////////////////////////////////////////////////////////////
//
//  CDDialog
//
//    for Modal/Modeless dialogs
//

class CDDialog : public CDWnd
{
public:
	//construction / destruction
	CDDialog();
	~CDDialog();


	//creation / initialization
	int							DoModal(HINSTANCE instance,HWND parentwnd,UINT dlgtemplate);
	HWND						DoModeless(HINSTANCE instance,HWND parentwnd,UINT dlgtemplate);

	virtual void				OnOK();
	virtual	void				OnCancel();
	virtual void				OnInitDialog() { }
	virtual void				Destroy();

protected:
	// window proc
	virtual int					WndProc(UINT msg,WPARAM wParam,LPARAM lParam);


protected:
	// data members
	BYTE			bIsModal;
};