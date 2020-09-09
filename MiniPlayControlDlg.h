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
//  MiniPlayControlDlg.h
//

class CMiniPlayControlDlg : public CDDialog
{
public:
				CMiniPlayControlDlg();
	void		OnOK()		{ }
	void		OnInitDialog();
	
	void		PutWindow(int x, int y);
	int			WndProc(UINT msg,WPARAM wParam,LPARAM lParam);

	void		OnPlay();
	void		OnNext();
	void		OnPrev();
	void		OnConfig();
	void		UpdateTrack(BYTE resetsel);
	void		LoadValues();
	void		UpdateSlider();

	void		Open() { ShowWindow(1); SetFocus(hWnd); }
	void		Close() { ShowWindow(0); }
	
	int			x_pos;
	int			y_pos;
	
	CNSFFile*	pFile;
	BYTE		bShadow;
	CNSF*		pNSF;

	CDSlider	m_Slider;
	CDStatic	m_TrackLabel;
};