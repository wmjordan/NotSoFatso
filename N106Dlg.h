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
//  N106Dlg.h
//


class CN106Dlg : public CDDialog
{
public:
				CN106Dlg() : CDDialog() { }
	void		OnOK() { }
	void		OnCancel() { }
	void		OnInitDialog();

	void		SetOptions(BYTE chan,BYTE mix,int vol,int pan,int inv);
	void		GetOptions(BYTE chan,int& mix,int& vol,int& pan,int& inv);


	CDButton	m_mix[8];
	CDButton	m_inv[8];
	CDSlider	m_vol[8];
	CDSlider	m_pan[8];
	CDEdit		m_volbox[8];
	CDEdit		m_panbox[8];

	CNSF*		pNSF;

	void		OnChangeMix();
	void		OnChangeVol_1();
	void		OnChangeVol_2();
	void		OnChangeVol_3();
	void		OnChangeVol_4();
	void		OnChangeVol_5();
	void		OnChangeVol_6();
	void		OnChangeVol_7();
	void		OnChangeVol_8();
	void		OnChangePan_1();
	void		OnChangePan_2();
	void		OnChangePan_3();
	void		OnChangePan_4();
	void		OnChangePan_5();
	void		OnChangePan_6();
	void		OnChangePan_7();
	void		OnChangePan_8();
	void		OnChangeInv_1();
	void		OnChangeInv_2();
	void		OnChangeInv_3();
	void		OnChangeInv_4();
	void		OnChangeInv_5();
	void		OnChangeInv_6();
	void		OnChangeInv_7();
	void		OnChangeInv_8();
	void		OnChangeVol(BYTE chan);
	void		OnChangePan(BYTE chan);
	void		OnChangeInv(BYTE chan);
	int			WndProc(UINT msg,WPARAM wParam,LPARAM lParam);
};