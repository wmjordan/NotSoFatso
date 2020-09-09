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
//  FileInfoDlg.cpp
//
//


#include "NSF.h"

CFileInfoDlg::CFileInfoDlg() : CDDialog()
{
}

void CFileInfoDlg::Run(CNSF* nsf,CNSFFile* file,char* filepath,BYTE shadow,BYTE shadowtrack, HWND parent)
{
	pNSF = nsf;
	pFile = file;
	szPath = filepath;
	bShadow = shadow;


	m_general.pFile = file;
	m_general.szPath = filepath;
	m_general.pNSF = nsf;
	m_general.bShadow = shadow;
	m_general.nShadowTrack = shadowtrack;

	m_tag.pFile = file;

	m_track.pFile = file;
	m_track.pNSF = nsf;
	m_track.bShadow = shadow;
	m_track.nShadowTrack = shadowtrack;

	m_playlist.pFile = file;
	m_playlist.pNSF = nsf;


	DoModal(nsf->inMod->hDllInstance,parent,IDD_FILEINFO);
}

void CFileInfoDlg::OnInitDialog()
{
	CDDialog::OnInitDialog();

	m_tab.AttachToControl(hWnd,IDC_TAB);
	m_clientrect.AttachToControl(hWnd,IDC_CLIENTRECT);

	RECT rc;
	m_clientrect.GetWindowRect(&rc);
	ScreenToClient(&rc);


	m_general.DoModeless(pNSF->inMod->hDllInstance,hWnd,IDD_GENERALFILEINFO);
	m_general.MoveWindow(&rc);

	m_track.DoModeless(pNSF->inMod->hDllInstance,hWnd,IDD_TRACKINFO);
	m_track.MoveWindow(&rc);
	m_track.szPath = szPath;

	m_playlist.DoModeless(pNSF->inMod->hDllInstance,hWnd,IDD_PLAYLISTINFO);
	m_playlist.MoveWindow(&rc);
	
	m_tag.DoModeless(pNSF->inMod->hDllInstance,hWnd,IDD_TAGINFO);
	m_tag.MoveWindow(&rc);


	AFX_MAPNOTIFY(IDC_TAB,TCN_SELCHANGE, &CFileInfoDlg::OnTab);
	AFX_MAPMESSAGE(IDC_SAVE,BN_CLICKED, &CFileInfoDlg::OnSave);
	AFX_MAPMESSAGE(IDC_SAVECLOSE,BN_CLICKED, &CFileInfoDlg::OnSaveClose);

	m_tab.InsertItem(0,"File Info");
	m_tab.InsertItem(1,"Tag Info");
	if(pFile->bIsExtended)
	{
		m_tab.InsertItem(2,"Track Info");
		if(!bShadow)
			m_tab.InsertItem(3,"Playlist Info");
	}
	m_tab.SetCurSel(0);
	OnTab();
}

void CFileInfoDlg::OnTab()
{
	int sel = m_tab.GetCurSel();

	if(!bShadow)
	{
		if(sel == 3)	m_playlist.RefreshList();
		else			m_playlist.StoreValues();
	}

	m_general.ShowWindow(sel == 0);
	m_tag.ShowWindow(sel == 1);
	m_track.ShowWindow(sel == 2);
	m_playlist.ShowWindow(sel == 3);
}

void CFileInfoDlg::OnSave()
{
	Save();
	m_general.Refresh();
}

void CFileInfoDlg::OnSaveClose()
{
	if(Save())
		CDDialog::OnOK();
	else
		m_general.Refresh();
}

BYTE CFileInfoDlg::Save()
{
	m_tag.StoreValues();
	if(pFile->bIsExtended)
	{
		if(!bShadow)
			m_playlist.StoreValues();
		m_track.StoreValues();
	}
	return !pFile->SaveFile(szPath);
}