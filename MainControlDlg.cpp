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
//  MainControlDlg.cpp
//

#include "NSF.h"

CMainControlDlg::CMainControlDlg() : CDDialog()
{
	pNSF = NULL;
	hInst = NULL;
	pFile = NULL;
	bShadow = 0;
}

void CMainControlDlg::OnInitDialog()
{
	CDDialog::OnInitDialog();
	
	HICON hIcon = (HICON)LoadImage(hInst,MAKEINTRESOURCE(IDI_WBWINAMP),IMAGE_ICON,
									GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),0);

	SendMessage(hWnd,WM_SETICON,ICON_SMALL,(LPARAM)hIcon);

	m_tab.AttachToControl(hWnd,IDC_TAB);
	m_clientbox.AttachToControl(hWnd,IDC_CLIENTBOX);

	RECT rc;
	m_clientbox.GetWindowRect(&rc);
	ScreenToClient(&rc);

	m_playcontrol_slide.DoModeless(hInst,hWnd,IDD_PLAYCONTROL_SLIDE);
	m_playcontrol_slide.MoveWindow(&rc);

	m_config.DoModeless(hInst,hWnd,IDD_CONFIG);
	m_config.MoveWindow(&rc);

	m_config2.DoModeless(hInst,hWnd,IDD_CONFIG_2);
	m_config2.MoveWindow(&rc);
	
	m_config3.DoModeless(hInst,hWnd,IDD_CONFIG_3);
	m_config3.MoveWindow(&rc);

	m_channels.DoModeless(hInst,hWnd,IDD_CHANNELS);
	m_channels.MoveWindow(&rc);

	m_vrc6.DoModeless(hInst,hWnd,IDD_VRC6);
	m_vrc6.MoveWindow(&rc);

	m_mmc5.DoModeless(hInst,hWnd,IDD_MMC5);
	m_mmc5.MoveWindow(&rc);
	
	m_n106.DoModeless(hInst,hWnd,IDD_N106);
	m_n106.MoveWindow(&rc);
	
	m_vrc7.DoModeless(hInst,hWnd,IDD_VRC7);
	m_vrc7.MoveWindow(&rc);
	
	m_fme07.DoModeless(hInst,hWnd,IDD_FME07);
	m_fme07.MoveWindow(&rc);

	m_about.DoModeless(hInst,hWnd,IDD_ABOUT);
	m_about.MoveWindow(&rc);

	m_tab.InsertItem(0,"Play Control");
	m_tab.InsertItem(1,"Config");
	m_tab.InsertItem(2,"Config 2");
	m_tab.InsertItem(3,"Config 3");
	m_tab.InsertItem(4,"Channels");
	m_tab.InsertItem(5,"VRC6");
	m_tab.InsertItem(6,"MMC5");
	m_tab.InsertItem(7,"N106");
	m_tab.InsertItem(8,"VRC7");
	m_tab.InsertItem(9,"FME-07");
	m_tab.InsertItem(10,"About");

	AFX_MAPNOTIFY(IDC_TAB,TCN_SELCHANGE,&CMainControlDlg::OnSelChangeTab);
}

void CMainControlDlg::OpenAsAbout()
{
	m_tab.SetCurSel(10);
	ShowWindow(1);
	OnSelChangeTab();
	SetFocus(hWnd);
}

void CMainControlDlg::OpenAsConfig()
{
	m_tab.SetCurSel(1);
	ShowWindow(1);
	OnSelChangeTab();
	SetFocus(hWnd);
}

void CMainControlDlg::OpenAsPlay()
{
	m_tab.SetCurSel(0);
	ShowWindow(1);
	OnSelChangeTab();
	SetFocus(hWnd);
}

void CMainControlDlg::ClosePlay()
{
	if(!m_tab.GetCurSel())
		ShowWindow(0);
}

void CMainControlDlg::Build(HWND parent)
{
	if(hWnd)		return;
	
	DoModeless(hInst,parent,IDD_MAINCONTROL);
}

void CMainControlDlg::UnBuild()
{
	if(!hWnd)		return;
	m_playcontrol_slide.Destroy();
	m_config.Destroy();
	m_config2.Destroy();
	m_config3.Destroy();
	m_channels.Destroy();
	m_vrc6.Destroy();
	m_n106.Destroy();
	m_vrc7.Destroy();
	m_fme07.Destroy();
	m_about.Destroy();

	Destroy();
	hWnd = NULL;
}

void CMainControlDlg::OnSelChangeTab()
{
	int sel = m_tab.GetCurSel();

	m_playcontrol_slide.ShowWindow(sel == 0);
	m_config.ShowWindow(sel == 1);
	m_config2.ShowWindow(sel == 2);
	m_config3.ShowWindow(sel == 3);
	m_channels.ShowWindow(sel == 4);
	m_vrc6.ShowWindow(sel == 5);
	m_mmc5.ShowWindow(sel == 6);
	m_n106.ShowWindow(sel == 7);
	m_vrc7.ShowWindow(sel == 8);
	m_fme07.ShowWindow(sel == 9);
	m_about.ShowWindow(sel == 10);
}

void CMainControlDlg::PutWindow(int x, int y)
{
	RECT rc;
	GetWindowRect(&rc);

	rc.right = (rc.right - rc.left) + x;
	rc.bottom = (rc.bottom - rc.top) + y;
	rc.left = x;
	rc.top = y;

	MoveWindow(&rc,1);
}

int	CMainControlDlg::WndProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg == WM_MOVE)
	{
		if(!IsIconic(hWnd))
		{
			RECT rc;
			GetWindowRect(&rc);
			x_pos = rc.left;
			y_pos = rc.top;
		}
	}
	return CDDialog::WndProc(msg,wParam,lParam);
}