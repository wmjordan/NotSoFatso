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
//  N106Dlg.cpp
//

#include "NSF.h"

void CN106Dlg::OnInitDialog()
{
	CDDialog::OnInitDialog();

	m_mix[0].AttachToControl(hWnd,IDC_MIX_1);
	m_mix[1].AttachToControl(hWnd,IDC_MIX_2);
	m_mix[2].AttachToControl(hWnd,IDC_MIX_3);
	m_mix[3].AttachToControl(hWnd,IDC_MIX_4);
	m_mix[4].AttachToControl(hWnd,IDC_MIX_5);
	m_mix[5].AttachToControl(hWnd,IDC_MIX_6);
	m_mix[6].AttachToControl(hWnd,IDC_MIX_7);
	m_mix[7].AttachToControl(hWnd,IDC_MIX_8);
	m_vol[0].AttachToControl(hWnd,IDC_VOL_1);
	m_vol[1].AttachToControl(hWnd,IDC_VOL_2);
	m_vol[2].AttachToControl(hWnd,IDC_VOL_3);
	m_vol[3].AttachToControl(hWnd,IDC_VOL_4);
	m_vol[4].AttachToControl(hWnd,IDC_VOL_5);
	m_vol[5].AttachToControl(hWnd,IDC_VOL_6);
	m_vol[6].AttachToControl(hWnd,IDC_VOL_7);
	m_vol[7].AttachToControl(hWnd,IDC_VOL_8);
	m_pan[0].AttachToControl(hWnd,IDC_PAN_1);
	m_pan[1].AttachToControl(hWnd,IDC_PAN_2);
	m_pan[2].AttachToControl(hWnd,IDC_PAN_3);
	m_pan[3].AttachToControl(hWnd,IDC_PAN_4);
	m_pan[4].AttachToControl(hWnd,IDC_PAN_5);
	m_pan[5].AttachToControl(hWnd,IDC_PAN_6);
	m_pan[6].AttachToControl(hWnd,IDC_PAN_7);
	m_pan[7].AttachToControl(hWnd,IDC_PAN_8);
	m_volbox[0].AttachToControl(hWnd,IDC_VOLBOX_1);
	m_volbox[1].AttachToControl(hWnd,IDC_VOLBOX_2);
	m_volbox[2].AttachToControl(hWnd,IDC_VOLBOX_3);
	m_volbox[3].AttachToControl(hWnd,IDC_VOLBOX_4);
	m_volbox[4].AttachToControl(hWnd,IDC_VOLBOX_5);
	m_volbox[5].AttachToControl(hWnd,IDC_VOLBOX_6);
	m_volbox[6].AttachToControl(hWnd,IDC_VOLBOX_7);
	m_volbox[7].AttachToControl(hWnd,IDC_VOLBOX_8);
	m_panbox[0].AttachToControl(hWnd,IDC_PANBOX_1);
	m_panbox[1].AttachToControl(hWnd,IDC_PANBOX_2);
	m_panbox[2].AttachToControl(hWnd,IDC_PANBOX_3);
	m_panbox[3].AttachToControl(hWnd,IDC_PANBOX_4);
	m_panbox[4].AttachToControl(hWnd,IDC_PANBOX_5);
	m_panbox[5].AttachToControl(hWnd,IDC_PANBOX_6);
	m_panbox[6].AttachToControl(hWnd,IDC_PANBOX_7);
	m_panbox[7].AttachToControl(hWnd,IDC_PANBOX_8);
	m_inv[0].AttachToControl(hWnd,IDC_INV_1);
	m_inv[1].AttachToControl(hWnd,IDC_INV_2);
	m_inv[2].AttachToControl(hWnd,IDC_INV_3);
	m_inv[3].AttachToControl(hWnd,IDC_INV_4);
	m_inv[4].AttachToControl(hWnd,IDC_INV_5);
	m_inv[5].AttachToControl(hWnd,IDC_INV_6);
	m_inv[6].AttachToControl(hWnd,IDC_INV_7);
	m_inv[7].AttachToControl(hWnd,IDC_INV_8);

	AFX_MAPMESSAGE(IDC_MIX_1,BN_CLICKED,&CN106Dlg::OnChangeMix);
	AFX_MAPMESSAGE(IDC_MIX_2,BN_CLICKED,&CN106Dlg::OnChangeMix);
	AFX_MAPMESSAGE(IDC_MIX_3,BN_CLICKED,&CN106Dlg::OnChangeMix);
	AFX_MAPMESSAGE(IDC_MIX_4,BN_CLICKED,&CN106Dlg::OnChangeMix);
	AFX_MAPMESSAGE(IDC_MIX_5,BN_CLICKED,&CN106Dlg::OnChangeMix);
	AFX_MAPMESSAGE(IDC_MIX_6,BN_CLICKED,&CN106Dlg::OnChangeMix);
	AFX_MAPMESSAGE(IDC_MIX_7,BN_CLICKED,&CN106Dlg::OnChangeMix);
	AFX_MAPMESSAGE(IDC_MIX_8,BN_CLICKED,&CN106Dlg::OnChangeMix);
	AFX_MAPMESSAGE(IDC_VOLBOX_1,EN_UPDATE,&CN106Dlg::OnChangeVol_1);
	AFX_MAPMESSAGE(IDC_VOLBOX_2,EN_UPDATE,&CN106Dlg::OnChangeVol_2);
	AFX_MAPMESSAGE(IDC_VOLBOX_3,EN_UPDATE,&CN106Dlg::OnChangeVol_3);
	AFX_MAPMESSAGE(IDC_VOLBOX_4,EN_UPDATE,&CN106Dlg::OnChangeVol_4);
	AFX_MAPMESSAGE(IDC_VOLBOX_5,EN_UPDATE,&CN106Dlg::OnChangeVol_5);
	AFX_MAPMESSAGE(IDC_VOLBOX_6,EN_UPDATE,&CN106Dlg::OnChangeVol_6);
	AFX_MAPMESSAGE(IDC_VOLBOX_7,EN_UPDATE,&CN106Dlg::OnChangeVol_7);
	AFX_MAPMESSAGE(IDC_VOLBOX_8,EN_UPDATE,&CN106Dlg::OnChangeVol_8);
	AFX_MAPMESSAGE(IDC_PANBOX_1,EN_UPDATE,&CN106Dlg::OnChangePan_1);
	AFX_MAPMESSAGE(IDC_PANBOX_2,EN_UPDATE,&CN106Dlg::OnChangePan_2);
	AFX_MAPMESSAGE(IDC_PANBOX_3,EN_UPDATE,&CN106Dlg::OnChangePan_3);
	AFX_MAPMESSAGE(IDC_PANBOX_4,EN_UPDATE,&CN106Dlg::OnChangePan_4);
	AFX_MAPMESSAGE(IDC_PANBOX_5,EN_UPDATE,&CN106Dlg::OnChangePan_5);
	AFX_MAPMESSAGE(IDC_PANBOX_6,EN_UPDATE,&CN106Dlg::OnChangePan_6);
	AFX_MAPMESSAGE(IDC_PANBOX_7,EN_UPDATE,&CN106Dlg::OnChangePan_7);
	AFX_MAPMESSAGE(IDC_PANBOX_8,EN_UPDATE,&CN106Dlg::OnChangePan_8);
	AFX_MAPMESSAGE(IDC_INV_1,BN_CLICKED,&CN106Dlg::OnChangeInv_1);
	AFX_MAPMESSAGE(IDC_INV_2,BN_CLICKED,&CN106Dlg::OnChangeInv_2);
	AFX_MAPMESSAGE(IDC_INV_3,BN_CLICKED,&CN106Dlg::OnChangeInv_3);
	AFX_MAPMESSAGE(IDC_INV_4,BN_CLICKED,&CN106Dlg::OnChangeInv_4);
	AFX_MAPMESSAGE(IDC_INV_5,BN_CLICKED,&CN106Dlg::OnChangeInv_5);
	AFX_MAPMESSAGE(IDC_INV_6,BN_CLICKED,&CN106Dlg::OnChangeInv_6);
	AFX_MAPMESSAGE(IDC_INV_7,BN_CLICKED,&CN106Dlg::OnChangeInv_7);
	AFX_MAPMESSAGE(IDC_INV_8,BN_CLICKED,&CN106Dlg::OnChangeInv_8);

	for(int i = 0; i < 8; i++)
	{
		m_vol[i].SetRange(0,255);
		m_pan[i].SetRange(-127,127);
	}
}

void CN106Dlg::SetOptions(BYTE chan,BYTE mix,int vol,int pan,int inv)
{
	chan -= 11;

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

void CN106Dlg::GetOptions(BYTE chan,int& mix,int& vol,int& pan,int& inv)
{
	chan -= 11;
	mix = m_mix[chan].GetCheck();
	vol = m_vol[chan].GetPos();
	pan = m_pan[chan].GetPos();
	inv = m_inv[chan].GetCheck();
}

void CN106Dlg::OnChangeMix()
{
	for(int i = 0; i < 8; i++)
		pNSF->nsfCore.SetChannelOptions(i + 11,m_mix[i].GetCheck(),-1,1000,-1);
}

void CN106Dlg::OnChangeVol_1() { OnChangeVol(0); }
void CN106Dlg::OnChangeVol_2() { OnChangeVol(1); }
void CN106Dlg::OnChangeVol_3() { OnChangeVol(2); }
void CN106Dlg::OnChangeVol_4() { OnChangeVol(3); }
void CN106Dlg::OnChangeVol_5() { OnChangeVol(4); }
void CN106Dlg::OnChangeVol_6() { OnChangeVol(5); }
void CN106Dlg::OnChangeVol_7() { OnChangeVol(6); }
void CN106Dlg::OnChangeVol_8() { OnChangeVol(7); }

void CN106Dlg::OnChangePan_1() { OnChangePan(0); }
void CN106Dlg::OnChangePan_2() { OnChangePan(1); }
void CN106Dlg::OnChangePan_3() { OnChangePan(2); }
void CN106Dlg::OnChangePan_4() { OnChangePan(3); }
void CN106Dlg::OnChangePan_5() { OnChangePan(4); }
void CN106Dlg::OnChangePan_6() { OnChangePan(5); }
void CN106Dlg::OnChangePan_7() { OnChangePan(6); }
void CN106Dlg::OnChangePan_8() { OnChangePan(7); }

void CN106Dlg::OnChangeInv_1() { OnChangeInv(0); }
void CN106Dlg::OnChangeInv_2() { OnChangeInv(1); }
void CN106Dlg::OnChangeInv_3() { OnChangeInv(2); }
void CN106Dlg::OnChangeInv_4() { OnChangeInv(3); }
void CN106Dlg::OnChangeInv_5() { OnChangeInv(4); }
void CN106Dlg::OnChangeInv_6() { OnChangeInv(5); }
void CN106Dlg::OnChangeInv_7() { OnChangeInv(6); }
void CN106Dlg::OnChangeInv_8() { OnChangeInv(7); }

void CN106Dlg::OnChangeInv(BYTE chan)
{
	pNSF->nsfCore.SetChannelOptions(chan + 11,-1,-1,1000,m_inv[chan].GetCheck());
}

void CN106Dlg::OnChangePan(BYTE chan)
{
	int pan;
	sscanf(m_panbox[chan].GetWindowText(),"%d",&pan);
	if(pan < -127) pan = -127;
	if(pan > 127) pan = 127;
	pNSF->nsfCore.SetChannelOptions(chan + 11,-1,-1,pan,-1);
	m_pan[chan].SetPos(pan);
}

void CN106Dlg::OnChangeVol(BYTE chan)
{
	int vol;
	sscanf(m_volbox[chan].GetWindowText(),"%d",&vol);
	if(vol < 0) vol = 0;
	if(vol > 255) vol = 255;
	pNSF->nsfCore.SetChannelOptions(chan + 11,-1,vol,1000,-1);
	m_vol[chan].SetPos(vol);
}

int CN106Dlg::WndProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg == WM_HSCROLL)
	{
		register int i = 0;
		register int j;
		CDString str;
		for(; i < 8; i++)
		{
			if( ((HWND)lParam) == m_vol[i].GetHandle() )
			{
				j = m_vol[i].GetPos();
				str.Format("%d",j);
				m_volbox[i].SetWindowText(str);
				pNSF->nsfCore.SetChannelOptions(i + 11,-1,j,1000,-1);
				break;
			}
			if( ((HWND)lParam) == m_pan[i].GetHandle() )
			{
				j = m_pan[i].GetPos();
				str.Format("%d",j);
				m_panbox[i].SetWindowText(str);
				pNSF->nsfCore.SetChannelOptions(i + 11,-1,-1,j,-1);
				break;
			}
		}
	}
	return CDDialog::WndProc(msg,wParam,lParam);
}