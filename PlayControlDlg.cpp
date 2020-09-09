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
//  PlayControlDlg.cpp
//
//


#include "NSF.h"

CPlayControlDlg_Slide::CPlayControlDlg_Slide() : CDDialog()
{
	pNSF = NULL;
	pFile = NULL;
}

int CPlayControlDlg_Slide::WndProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg == WM_HSCROLL)
		UpdateTrack(0);

	return CDDialog::WndProc(msg,wParam,lParam);
}


void CPlayControlDlg_Slide::OnInitDialog()
{
	CDDialog::OnInitDialog();

	m_fileinfo.AttachToControl(hWnd,IDC_FILEINFO);
	m_slider.AttachToControl(hWnd,IDC_PLAYSLIDER);
	m_tracktext.AttachToControl(hWnd,IDC_TRACKTEXT);

	AFX_MAPMESSAGE(IDC_NEXT,BN_CLICKED, &CPlayControlDlg_Slide::OnNext);
	AFX_MAPMESSAGE(IDC_PREV,BN_CLICKED,&CPlayControlDlg_Slide::OnPrev);
	AFX_MAPMESSAGE(IDC_PLAY,BN_CLICKED,&CPlayControlDlg_Slide::OnPlay);

	LoadValues();
}

void CPlayControlDlg_Slide::LoadValues()
{
	if(!pFile)
	{
		m_fileinfo.SetWindowText("");
		m_slider.ShowWindow(0);
		m_tracktext.SetWindowText("");
		return;
	}

	m_fileinfo.SetWindowText((pNSF->GetGameTitle(pFile,1) + "\n" + pNSF->GetArtist(pFile,1) + "\n" +
		pNSF->GetCopyright(pFile,1) + "\n" + pNSF->GetRipper(pFile,1) + "\n" +
		pNSF->GetExpansionString(pFile) + "\n" + pNSF->GetNTSCPALString(pFile)));

	UpdateSlider();
}

void CPlayControlDlg_Slide::UpdateSlider()
{
	if(!pFile)
	{
		m_slider.ShowWindow(0);
		m_tracktext.SetWindowText("");
		return;
	}

	CDString main;

	if(bShadow)
	{
		m_slider.ShowWindow(0);
		main = pNSF->GetTrackLabel(pFile,pNSF->nCurrentTrack,1);
	}
	else
	{
		if(pNSF->bUsePlaylists && pFile->pPlaylist)
		{
			m_slider.ShowWindow(pFile->nPlaylistSize > 1);
			m_slider.SetRange(0,pFile->nPlaylistSize - 1);
			m_slider.SetPos(pNSF->nPlaylistIndex,1);
			main = pNSF->GetTrackLabel(pFile,pFile->pPlaylist[pNSF->nPlaylistIndex],1);
		}
		else
		{
			m_slider.ShowWindow(pFile->nTrackCount > 1);
			m_slider.SetRange(0,pFile->nTrackCount - 1);
			m_slider.SetPos(pNSF->nCurrentTrack,1);
			main = pNSF->GetTrackLabel(pFile,pNSF->nCurrentTrack,1);
		}
	}

	main += "\n" + main;
	m_tracktext.SetWindowText(main);
}

void CPlayControlDlg_Slide::UpdateTrack(BYTE resetsel)
{
	CDString playing;
	CDString selected;

	if(!pFile)
	{
		m_tracktext.SetWindowText("");
		return;
	}

	if(resetsel)
	{
		if(pNSF->bUsePlaylists && pFile->pPlaylist)
			m_slider.SetPos(pNSF->nPlaylistIndex);
		else
			m_slider.SetPos(pNSF->nCurrentTrack);
	}

	playing = pNSF->GetTrackLabel(pFile,pNSF->nCurrentTrack,1);

	if(bShadow)
		selected = playing;
	else
	{
		int sel = m_slider.GetPos();
		if(pNSF->bUsePlaylists && pFile->pPlaylist)
			selected = pNSF->GetTrackLabel(pFile,pFile->pPlaylist[sel],1);
		else
			selected = pNSF->GetTrackLabel(pFile,sel,1);
	}
	selected += "\n" + playing;
	m_tracktext.SetWindowText(selected);
}

void CPlayControlDlg_Slide::OnNext()
{
	if(!pFile)	return;
	pNSF->NextTrack();
}

void CPlayControlDlg_Slide::OnPrev()
{
	if(!pFile)	return;
	pNSF->PrevTrack();
}

void CPlayControlDlg_Slide::OnPlay()
{
	if(!pFile)	return;

	BYTE reset = 0;
	int sel = m_slider.GetPos();

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