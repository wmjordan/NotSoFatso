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
//  PlaylistDlg.h
//
//

class CPlaylistDlg : public CDDialog
{
public:
				CPlaylistDlg() : CDDialog() { }
				~CPlaylistDlg() { }

	void		OnOK() { }
	void		OnCancel() { }
	void		OnInitDialog();

	void		OnRemove();
	void		OnRemoveAll();
	void		OnAdd();
	void		OnAddAll();
	void		OnUp();
	void		OnDown();

	void		StoreValues();

	void		RefreshList();

	CNSF*		pNSF;
	CNSFFile*	pFile;

	CDByteArray	nPlaylist;

	CDListBox	m_tracklist;
	CDListBox	m_playlist;
};