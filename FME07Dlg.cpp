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
//  MMC5Dlg.cpp
//


#include "NSF.h"

void CFME07Dlg::OnInitDialog()
{
	CDDialog::OnInitDialog();

	m_mix[0].AttachToControl(hWnd,IDC_MIX_1);
	m_mix[1].AttachToControl(hWnd,IDC_MIX_2);
	m_mix[2].AttachToControl(hWnd,IDC_MIX_3);
	m_vol[0].AttachToControl(hWnd,IDC_VOL_1);
	m_vol[1].AttachToControl(hWnd,IDC_VOL_2);
	m_vol[2].AttachToControl(hWnd,IDC_VOL_3);
	m_pan[0].AttachToControl(hWnd,IDC_PAN_1);
	m_pan[1].AttachToControl(hWnd,IDC_PAN_2);
	m_pan[2].AttachToControl(hWnd,IDC_PAN_3);
	m_volbox[0].AttachToControl(hWnd,IDC_VOLBOX_1);
	m_volbox[1].AttachToControl(hWnd,IDC_VOLBOX_2);
	m_volbox[2].AttachToControl(hWnd,IDC_VOLBOX_3);
	m_panbox[0].AttachToControl(hWnd,IDC_PANBOX_1);
	m_panbox[1].AttachToControl(hWnd,IDC_PANBOX_2);
	m_panbox[2].AttachToControl(hWnd,IDC_PANBOX_3);
	m_inv[0].AttachToControl(hWnd,IDC_INV_1);
	m_inv[1].AttachToControl(hWnd,IDC_INV_2);
	m_inv[2].AttachToControl(hWnd,IDC_INV_3);

	AFX_MAPMESSAGE(IDC_MIX_1,BN_CLICKED, &CFME07Dlg::OnChangeMix);
	AFX_MAPMESSAGE(IDC_MIX_2,BN_CLICKED,&CFME07Dlg::OnChangeMix);
	AFX_MAPMESSAGE(IDC_MIX_3,BN_CLICKED,&CFME07Dlg::OnChangeMix);
	AFX_MAPMESSAGE(IDC_VOLBOX_1,EN_UPDATE,&CFME07Dlg::OnChangeVol_1);
	AFX_MAPMESSAGE(IDC_VOLBOX_2,EN_UPDATE,&CFME07Dlg::OnChangeVol_2);
	AFX_MAPMESSAGE(IDC_VOLBOX_3,EN_UPDATE,&CFME07Dlg::OnChangeVol_3);
	AFX_MAPMESSAGE(IDC_PANBOX_1,EN_UPDATE,&CFME07Dlg::OnChangePan_1);
	AFX_MAPMESSAGE(IDC_PANBOX_2,EN_UPDATE,&CFME07Dlg::OnChangePan_2);
	AFX_MAPMESSAGE(IDC_PANBOX_3,EN_UPDATE,&CFME07Dlg::OnChangePan_3);
	AFX_MAPMESSAGE(IDC_INV_1,BN_CLICKED,&CFME07Dlg::OnChangeInv_1);
	AFX_MAPMESSAGE(IDC_INV_2,BN_CLICKED,&CFME07Dlg::OnChangeInv_2);
	AFX_MAPMESSAGE(IDC_INV_3,BN_CLICKED,&CFME07Dlg::OnChangeInv_3);

	for(int i = 0; i < 3; i++)
	{
		m_vol[i].SetRange(0,255);
		m_pan[i].SetRange(-127,127);
	}
}

void CFME07Dlg::SetOptions(BYTE chan,BYTE mix,int vol,int pan,int inv)
{
	chan -= 25;

	CDString str;

	m_mix[chan].SetCheck(mix != 0);
	m_inv[chan].SetCheck(inv != 0);

	if(vol < 0) vol = 0;
	if(vol > 255) vol = 255;
	m_vol[chan].SetPos(vol);
	str.Format("%d",vol);
	m_volbox[chan].SetWindowText(str);

	if(pan < -127) pan = -127;
	if(pan > 127) pan = 127;
	m_pan[chan].SetPos(pan);
	str.Format("%d",pan);
	m_panbox[chan].SetWindowText(str);
}

void CFME07Dlg::GetOptions(BYTE chan,int& mix,int& vol,int& pan,int& inv)
{
	chan -= 25;
	mix = m_mix[chan].GetCheck();
	vol = m_vol[chan].GetPos();
	pan = m_pan[chan].GetPos();
	inv = m_inv[chan].GetCheck();
}

void CFME07Dlg::OnChangeMix()
{
	for(int i = 0; i < 3; i++)
		pNSF->nsfCore.SetChannelOptions(i + 25,m_mix[i].GetCheck(),-1,1000,-1);
}

void CFME07Dlg::OnChangeVol_1() { OnChangeVol(0); }
void CFME07Dlg::OnChangeVol_2() { OnChangeVol(1); }
void CFME07Dlg::OnChangeVol_3() { OnChangeVol(2); }

void CFME07Dlg::OnChangePan_1() { OnChangePan(0); }
void CFME07Dlg::OnChangePan_2() { OnChangePan(1); }
void CFME07Dlg::OnChangePan_3() { OnChangePan(2); }

void CFME07Dlg::OnChangeInv_1() { OnChangeInv(0); }
void CFME07Dlg::OnChangeInv_2() { OnChangeInv(1); }
void CFME07Dlg::OnChangeInv_3() { OnChangeInv(2); }

void CFME07Dlg::OnChangeInv(BYTE chan)
{
	pNSF->nsfCore.SetChannelOptions(chan + 25,-1,-1,1000,m_inv[chan].GetCheck());
}

void CFME07Dlg::OnChangePan(BYTE chan)
{
	int pan;
	sscanf(m_panbox[chan].GetWindowText(),"%d",&pan);
	if(pan < -127) pan = -127;
	if(pan > 127) pan = 127;
	pNSF->nsfCore.SetChannelOptions(chan + 25,-1,-1,pan,-1);
	m_pan[chan].SetPos(pan);
}

void CFME07Dlg::OnChangeVol(BYTE chan)
{
	int vol;
	sscanf(m_volbox[chan].GetWindowText(),"%d",&vol);
	if(vol < 0) vol = 0;
	if(vol > 255) vol = 255;
	pNSF->nsfCore.SetChannelOptions(chan + 25,-1,vol,1000,-1);
	m_vol[chan].SetPos(vol);
}

int CFME07Dlg::WndProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg == WM_HSCROLL)
	{
		register int i = 0;
		register int j;
		CDString str;
		for(; i < 3; i++)
		{
			if( ((HWND)lParam) == m_vol[i].GetHandle() )
			{
				j = m_vol[i].GetPos();
				str.Format("%d",j);
				m_volbox[i].SetWindowText(str);
				pNSF->nsfCore.SetChannelOptions(i + 25,-1,j,1000,-1);
				break;
			}
			if( ((HWND)lParam) == m_pan[i].GetHandle() )
			{
				j = m_pan[i].GetPos();
				str.Format("%d",j);
				m_panbox[i].SetWindowText(str);
				pNSF->nsfCore.SetChannelOptions(i + 25,-1,-1,j,-1);
				break;
			}
		}
	}
	return CDDialog::WndProc(msg,wParam,lParam);
}