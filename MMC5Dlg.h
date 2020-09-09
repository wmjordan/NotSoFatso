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
//  MMC5Dlg.h
//

class CMMC5Dlg : public CDDialog
{
public:
				CMMC5Dlg() : CDDialog() { }
	void		OnOK() { }
	void		OnCancel() { }
	void		OnInitDialog();

	void		SetOptions(BYTE chan,BYTE mix,int vol,int pan,int inv);
	void		GetOptions(BYTE chan,int& mix,int& vol,int& pan,int& inv);


	CDButton	m_mix[3];
	CDButton	m_inv[3];
	CDSlider	m_vol[3];
	CDSlider	m_pan[3];
	CDEdit		m_volbox[3];
	CDEdit		m_panbox[3];

	CNSF*		pNSF;

	void		OnChangeMix();
	void		OnChangeVol_1();
	void		OnChangeVol_2();
	void		OnChangeVol_3();
	void		OnChangePan_1();
	void		OnChangePan_2();
	void		OnChangePan_3();
	void		OnChangeInv_1();
	void		OnChangeInv_2();
	void		OnChangeInv_3();
	void		OnChangeInv(BYTE chan);
	void		OnChangeVol(BYTE chan);
	void		OnChangePan(BYTE chan);
	int			WndProc(UINT msg,WPARAM wParam,LPARAM lParam);
};