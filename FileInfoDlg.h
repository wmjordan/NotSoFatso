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
//  FileInfoDlg.h


class CFileInfoDlg : public CDDialog
{
public:
			CFileInfoDlg();
			~CFileInfoDlg() { }
	void	OnOK() { }
	void	OnInitDialog();

	void	Run(CNSF* nsf,CNSFFile* file,char* filepath,BYTE shadow,BYTE shadowtrack, HWND parent);

	void	OnTab();

	BYTE	Save();
	void	OnSave();
	void	OnSaveClose();

	CNSF*					pNSF;
	CNSFFile*				pFile;
	BYTE					bShadow;

	char*					szPath;

	CGeneralFileInfoDlg		m_general;
	CTagInfoDlg				m_tag;
	CTrackInfoDlg			m_track;
	CPlaylistDlg			m_playlist;

	CDTab					m_tab;
	CDStatic				m_clientrect;
};