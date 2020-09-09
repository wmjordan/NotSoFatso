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
//  TrackInfoDlg.h
//
//

class CTrackInfoDlg : public CDDialog
{
public:
				CTrackInfoDlg();
				~CTrackInfoDlg();
	void		OnOK() { }
	void		OnCancel() { }
	void		OnInitDialog();

	void		StoreValues();
	void		LoadValues();

	void		OnSelchangeList();
	void		OnDblClickList();

	void		OnHasLabels();
	void		OnHasLength();
	void		OnHasFade();

	void		OnGetLength();
	void		OnGetFade();

	CNSF*			pNSF;
	CNSFFile*		pFile;
	char*			szPath;

	BYTE			bShadow;
	BYTE			nShadowTrack;

	int				sel;

	CDListBox		m_tracklist;
	CDButton		m_haslabels;
	CDButton		m_haslength;
	CDButton		m_hasfade;
	CDEdit			m_label;
	CDEdit			m_length;
	CDEdit			m_fade;
	CDButton		m_getlength;
	CDButton		m_getfade;
};