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
//  MiniPlayControlDlg.cpp
//

#include "NSF.h"

CMiniPlayControlDlg::CMiniPlayControlDlg() : CDDialog()
{
	pNSF = NULL;
	pFile = NULL;
	bShadow = 0;
}

void CMiniPlayControlDlg::OnInitDialog()
{
	CDDialog::OnInitDialog();

	HICON hIcon = (HICON)LoadImage(pNSF->inMod->hDllInstance,MAKEINTRESOURCE(IDI_WBWINAMP),IMAGE_ICON,
									GetSystemMetrics(SM_CXSMICON),GetSystemMetrics(SM_CYSMICON),0);

	SendMessage(hWnd,WM_SETICON,ICON_SMALL,(LPARAM)hIcon);

	m_Slider.AttachToControl(hWnd,IDC_PLAYSLIDER);
	m_TrackLabel.AttachToControl(hWnd,IDC_TRACKLABEL);

	AFX_MAPMESSAGE(IDC_PLAY,BN_CLICKED,&CMiniPlayControlDlg::OnPlay);
	AFX_MAPMESSAGE(IDC_NEXT,BN_CLICKED,&CMiniPlayControlDlg::OnNext);
	AFX_MAPMESSAGE(IDC_PREV,BN_CLICKED,&CMiniPlayControlDlg::OnPrev);
	AFX_MAPMESSAGE(IDC_CONFIG,BN_CLICKED,&CMiniPlayControlDlg::OnConfig);
}

void CMiniPlayControlDlg::PutWindow(int x, int y)
{
	RECT rc;
	GetWindowRect(&rc);

	rc.right = (rc.right - rc.left) + x;
	rc.bottom = (rc.bottom - rc.top) + y;
	rc.left = x;
	rc.top = y;

	MoveWindow(&rc,1);
}

int	CMiniPlayControlDlg::WndProc(UINT msg,WPARAM wParam,LPARAM lParam)
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
	if(msg == WM_HSCROLL)
		UpdateTrack(0);
	return CDDialog::WndProc(msg,wParam,lParam);
}

void CMiniPlayControlDlg::OnNext()
{
	if(!pFile)	return;
	pNSF->NextTrack();
}

void CMiniPlayControlDlg::OnPrev()
{
	if(!pFile)	return;
	pNSF->PrevTrack();
}

void CMiniPlayControlDlg::OnConfig()
{
	pNSF->mControlDlg.OpenAsConfig();
}

void CMiniPlayControlDlg::OnPlay()
{
	if(!pFile)	return;

	BYTE reset = 0;
	int sel = m_Slider.GetPos();

	if(bShadow)		reset = 1;
	if(sel < 0)		reset = 1;
	if(pNSF->bUsePlaylists && pFile->pPlaylist)
	{
		if(pFile->nPlaylistSize <= sel)
			reset = 1;
	}
	else if(pFile->nTrackCount <= sel)
		reset = 1;

	if(reset)
		pNSF->SetTrack(pNSF->nCurrentTrack);
	else
	{
		if(pNSF->bUsePlaylists && pFile->pPlaylist)
		{
			pNSF->nPlaylistIndex = sel;
			pNSF->SetTrack(pFile->pPlaylist[sel]);
		}
		else
			pNSF->SetTrack(sel);
	}
}

void CMiniPlayControlDlg::LoadValues()
{
	if(!pFile)
	{
		m_Slider.ShowWindow(0);
		m_TrackLabel.SetWindowText("");
		return;
	}

	UpdateSlider();
}

void CMiniPlayControlDlg::UpdateSlider()
{
	if(!pFile)
	{
		m_Slider.ShowWindow(0);
		m_TrackLabel.SetWindowText("");
		return;
	}

	CDString main;

	if(bShadow)
	{
		m_Slider.ShowWindow(0);
		main = pNSF->GetTrackLabel(pFile,pNSF->nCurrentTrack,1);
	}
	else
	{
		if(pNSF->bUsePlaylists && pFile->pPlaylist)
		{
			m_Slider.ShowWindow(pFile->nPlaylistSize > 1);
			m_Slider.SetRange(0,pFile->nPlaylistSize - 1);
			m_Slider.SetPos(pNSF->nPlaylistIndex,1);
			main = pNSF->GetTrackLabel(pFile,pFile->pPlaylist[pNSF->nPlaylistIndex],1);
		}
		else
		{
			m_Slider.ShowWindow(pFile->nTrackCount > 1);
			m_Slider.SetRange(0,pFile->nTrackCount - 1);
			m_Slider.SetPos(pNSF->nCurrentTrack,1);
			main = pNSF->GetTrackLabel(pFile,pNSF->nCurrentTrack,1);
		}
	}

	m_TrackLabel.SetWindowText(main);
}

void CMiniPlayControlDlg::UpdateTrack(BYTE resetsel)
{
	CDString selected;

	if(!pFile)
	{
		m_TrackLabel.SetWindowText("");
		return;
	}

	if(resetsel)
	{
		if(pNSF->bUsePlaylists && pFile->pPlaylist)
			m_Slider.SetPos(pNSF->nPlaylistIndex);
		else
			m_Slider.SetPos(pNSF->nCurrentTrack);
	}

	if(bShadow)
		selected = pNSF->GetTrackLabel(pFile,pNSF->nCurrentTrack,1);
	else
	{
		int sel = m_Slider.GetPos();
		if(pNSF->bUsePlaylists && pFile->pPlaylist)
			selected = pNSF->GetTrackLabel(pFile,pFile->pPlaylist[sel],1);
		else
			selected = pNSF->GetTrackLabel(pFile,sel,1);
	}
	m_TrackLabel.SetWindowText(selected);
}