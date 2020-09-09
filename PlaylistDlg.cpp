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
//  PlaylistDlg.cpp
//

#include "NSF.h"

void CPlaylistDlg::OnInitDialog()
{
	CDDialog::OnInitDialog();

	m_tracklist.AttachToControl(hWnd,IDC_TRACKLIST);
	m_playlist.AttachToControl(hWnd,IDC_PLAYLIST);

//	AFX_MAPMESSAGE(IDC_PLAYLIST,LBN_DBLCLK,OnRemove);
//	AFX_MAPMESSAGE(IDC_TRACKLIST,LBN_DBLCLK,OnAdd);
	AFX_MAPMESSAGE(IDC_ADD,BN_CLICKED, &CPlaylistDlg::OnAdd);
	AFX_MAPMESSAGE(IDC_REMOVE,BN_CLICKED, &CPlaylistDlg::OnRemove);
	AFX_MAPMESSAGE(IDC_REMOVEALL,BN_CLICKED, &CPlaylistDlg::OnRemoveAll);
	AFX_MAPMESSAGE(IDC_ADDALL,BN_CLICKED, &CPlaylistDlg::OnAddAll);
	AFX_MAPMESSAGE(IDC_MOVEUP,BN_CLICKED, &CPlaylistDlg::OnUp);
	AFX_MAPMESSAGE(IDC_MOVEDOWN,BN_CLICKED, &CPlaylistDlg::OnDown);

	nPlaylist.RemoveAll();
	for(int i = 0; i < pFile->nPlaylistSize; i++)
		nPlaylist.Add(pFile->pPlaylist[i]);
}

void CPlaylistDlg::RefreshList()
{
	m_tracklist.ResetContent();
	m_playlist.ResetContent();

	int i;
	for(i = 0; i < pFile->nTrackCount; i++)
		m_tracklist.InsertString(i,pNSF->GetTrackLabel(pFile,i,0));

	for(i = 0; i < pFile->nPlaylistSize; i++)
		m_playlist.InsertString(i,pNSF->GetTrackLabel(pFile,pFile->pPlaylist[i],0));
}

void CPlaylistDlg::StoreValues()
{
	int count = nPlaylist.GetCount();
	if(count)
	{
		if(count > pFile->nPlaylistSize)
		{
			if(pFile->pPlaylist)
				delete[] pFile->pPlaylist;
			pFile->pPlaylist = new BYTE[count];
		}
		pFile->nPlaylistSize = count;
		memcpy(pFile->pPlaylist,nPlaylist.GetData(),count);
	}
	else
	{
		if(pFile->pPlaylist)
			delete[] pFile->pPlaylist;
		pFile->pPlaylist = NULL;
		pFile->nPlaylistSize = 0;
	}
}

void CPlaylistDlg::OnAdd()
{
	int i;
	int count = m_tracklist.GetCount();
	for(i = 0; i < count; i++)
	{
		if(m_tracklist.GetSel(i) <= 0) continue;

		m_playlist.InsertString(nPlaylist.GetCount(),pNSF->GetTrackLabel(pFile,i,0));
		nPlaylist.Add(i);
	}
}

void CPlaylistDlg::OnRemove()
{
	int i = m_playlist.GetCount() - 1;
	for(; i >= 0; i--)
	{
		if(m_playlist.GetSel(i) <= 0) continue;
		nPlaylist.RemoveAt(i);
		m_playlist.DeleteString(i);
	}
}

void CPlaylistDlg::OnAddAll()
{
	for(int i = 0; i < pFile->nTrackCount; i++)
	{
		m_playlist.InsertString(nPlaylist.GetCount(),pNSF->GetTrackLabel(pFile,i,0));
		nPlaylist.Add(i);
	}
}

void CPlaylistDlg::OnRemoveAll()
{
	nPlaylist.RemoveAll();
	m_playlist.ResetContent();
}

void CPlaylistDlg::OnUp()
{
	int count = m_playlist.GetCount();
	int i;
	BYTE temp;
	for(i = 1; i < count; i++)
	{
		if(m_playlist.GetSel(i) <= 0) continue;
		if(m_playlist.GetSel(i - 1) > 0) continue;

		temp = nPlaylist[i];
		nPlaylist[i] = nPlaylist[i - 1];
		nPlaylist[i - 1] = temp;

		m_playlist.DeleteString(i);
		m_playlist.InsertString(i - 1,pNSF->GetTrackLabel(pFile,temp,0));
		m_playlist.SetSel(i - 1,1);
	}
}

void CPlaylistDlg::OnDown()
{
	BYTE temp;
	int i;
	for(i = m_playlist.GetCount() - 2; i >= 0; i--)
	{
		if(m_playlist.GetSel(i) <= 0) continue;
		if(m_playlist.GetSel(i + 1) > 0) continue;
		
		temp = nPlaylist[i];
		nPlaylist[i] = nPlaylist[i + 1];
		nPlaylist[i + 1] = temp;

		m_playlist.DeleteString(i);
		m_playlist.InsertString(i + 1,pNSF->GetTrackLabel(pFile,temp,0));
		m_playlist.SetSel(i + 1,1);
	}
}