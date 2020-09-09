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
//  ChannelsDlg.cpp
//
//

#include "NSF.h"

void CChannelsDlg::OnInitDialog()
{
	CDDialog::OnInitDialog();

	//get vars for all the controls
	m_mix[0].AttachToControl(hWnd,IDC_MIX_1);
	m_mix[1].AttachToControl(hWnd,IDC_MIX_2);
	m_mix[2].AttachToControl(hWnd,IDC_MIX_3);
	m_mix[3].AttachToControl(hWnd,IDC_MIX_4);
	m_mix[4].AttachToControl(hWnd,IDC_MIX_5);
	m_mix[5].AttachToControl(hWnd,IDC_MIX_6);
	m_inv[0].AttachToControl(hWnd,IDC_INV_1);
	m_inv[1].AttachToControl(hWnd,IDC_INV_2);
	m_inv[2].AttachToControl(hWnd,IDC_INV_3);
	m_inv[3].AttachToControl(hWnd,IDC_INV_4);
	m_inv[4].AttachToControl(hWnd,IDC_INV_5);
	m_inv[5].AttachToControl(hWnd,IDC_INV_6);
	m_vol[0].AttachToControl(hWnd,IDC_VOL_1);
	m_vol[1].AttachToControl(hWnd,IDC_VOL_2);
	m_vol[2].AttachToControl(hWnd,IDC_VOL_3);
	m_vol[3].AttachToControl(hWnd,IDC_VOL_4);
	m_vol[4].AttachToControl(hWnd,IDC_VOL_5);
	m_vol[5].AttachToControl(hWnd,IDC_VOL_6);
	m_pan[0].AttachToControl(hWnd,IDC_PAN_1);
	m_pan[1].AttachToControl(hWnd,IDC_PAN_2);
	m_pan[2].AttachToControl(hWnd,IDC_PAN_3);
	m_pan[3].AttachToControl(hWnd,IDC_PAN_4);
	m_pan[4].AttachToControl(hWnd,IDC_PAN_5);
	m_pan[5].AttachToControl(hWnd,IDC_PAN_6);
	m_volbox[0].AttachToControl(hWnd,IDC_VOLBOX_1);
	m_volbox[1].AttachToControl(hWnd,IDC_VOLBOX_2);
	m_volbox[2].AttachToControl(hWnd,IDC_VOLBOX_3);
	m_volbox[3].AttachToControl(hWnd,IDC_VOLBOX_4);
	m_volbox[4].AttachToControl(hWnd,IDC_VOLBOX_5);
	m_volbox[5].AttachToControl(hWnd,IDC_VOLBOX_6);
	m_panbox[0].AttachToControl(hWnd,IDC_PANBOX_1);
	m_panbox[1].AttachToControl(hWnd,IDC_PANBOX_2);
	m_panbox[2].AttachToControl(hWnd,IDC_PANBOX_3);
	m_panbox[3].AttachToControl(hWnd,IDC_PANBOX_4);
	m_panbox[4].AttachToControl(hWnd,IDC_PANBOX_5);
	m_panbox[5].AttachToControl(hWnd,IDC_PANBOX_6);

	//map messages to the desired subroutines
	AFX_MAPMESSAGE(IDC_MIX_1,BN_CLICKED,&CChannelsDlg::OnChangeMix);
	AFX_MAPMESSAGE(IDC_MIX_2,BN_CLICKED,&CChannelsDlg::OnChangeMix);
	AFX_MAPMESSAGE(IDC_MIX_3,BN_CLICKED,&CChannelsDlg::OnChangeMix);
	AFX_MAPMESSAGE(IDC_MIX_4,BN_CLICKED,&CChannelsDlg::OnChangeMix);
	AFX_MAPMESSAGE(IDC_MIX_5,BN_CLICKED,&CChannelsDlg::OnChangeMix);
	AFX_MAPMESSAGE(IDC_MIX_6,BN_CLICKED,&CChannelsDlg::OnChangeMix);
	AFX_MAPMESSAGE(IDC_VOLBOX_1,EN_UPDATE,&CChannelsDlg::OnChangeVol_1);
	AFX_MAPMESSAGE(IDC_VOLBOX_2,EN_UPDATE,&CChannelsDlg::OnChangeVol_2);
	AFX_MAPMESSAGE(IDC_VOLBOX_3,EN_UPDATE,&CChannelsDlg::OnChangeVol_3);
	AFX_MAPMESSAGE(IDC_VOLBOX_4,EN_UPDATE,&CChannelsDlg::OnChangeVol_4);
	AFX_MAPMESSAGE(IDC_VOLBOX_5,EN_UPDATE,&CChannelsDlg::OnChangeVol_5);
	AFX_MAPMESSAGE(IDC_VOLBOX_6,EN_UPDATE,&CChannelsDlg::OnChangeVol_6);
	AFX_MAPMESSAGE(IDC_PANBOX_1,EN_UPDATE,&CChannelsDlg::OnChangePan_1);
	AFX_MAPMESSAGE(IDC_PANBOX_2,EN_UPDATE,&CChannelsDlg::OnChangePan_2);
	AFX_MAPMESSAGE(IDC_PANBOX_3,EN_UPDATE,&CChannelsDlg::OnChangePan_3);
	AFX_MAPMESSAGE(IDC_PANBOX_4,EN_UPDATE,&CChannelsDlg::OnChangePan_4);
	AFX_MAPMESSAGE(IDC_PANBOX_5,EN_UPDATE,&CChannelsDlg::OnChangePan_5);
	AFX_MAPMESSAGE(IDC_PANBOX_6,EN_UPDATE,&CChannelsDlg::OnChangePan_6);
	AFX_MAPMESSAGE(IDC_INV_1,BN_CLICKED,&CChannelsDlg::OnChangeInv_1);
	AFX_MAPMESSAGE(IDC_INV_2,BN_CLICKED,&CChannelsDlg::OnChangeInv_2);
	AFX_MAPMESSAGE(IDC_INV_3,BN_CLICKED,&CChannelsDlg::OnChangeInv_3);
	AFX_MAPMESSAGE(IDC_INV_4,BN_CLICKED,&CChannelsDlg::OnChangeInv_4);
	AFX_MAPMESSAGE(IDC_INV_5,BN_CLICKED,&CChannelsDlg::OnChangeInv_5);
	AFX_MAPMESSAGE(IDC_INV_6,BN_CLICKED,&CChannelsDlg::OnChangeInv_6);

	//set the ranges for the scrollbars
	for(int i = 0; i < 6; i++)
	{
		m_vol[i].SetRange(0,255);
		m_pan[i].SetRange(-127,127);
	}
}

void CChannelsDlg::SetOptions(BYTE chan,BYTE mix,int vol,int pan,int inv)
{
	if(chan == 28)	chan = 5;
	CDString str;

	m_mix[chan].SetCheck(mix != 0);
	m_inv[chan].SetCheck(inv == 1);

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

void CChannelsDlg::GetOptions(BYTE chan,int& mix,int& vol,int& pan,int& inv)
{
	if(chan == 28)	chan = 5;

	mix = m_mix[chan].GetCheck();
	inv = m_inv[chan].GetCheck();
	vol = m_vol[chan].GetPos();
	pan = m_pan[chan].GetPos();
}

void CChannelsDlg::OnChangeMix()
{
	for(int i = 0; i < 5; i++)
		pNSF->nsfCore.SetChannelOptions(i,m_mix[i].GetCheck(),-1,1000,-1);
	pNSF->nsfCore.SetChannelOptions(28,m_mix[5].GetCheck(),-1,1000,-1);
}

void CChannelsDlg::OnChangeInv(BYTE chan)
{
	int temp = chan;
	if(chan == 5)	temp = 28;
	pNSF->nsfCore.SetChannelOptions(temp,-1,-1,1000,m_inv[chan].GetCheck());
}

void CChannelsDlg::OnChangeVol_1() { OnChangeVol(0); }
void CChannelsDlg::OnChangeVol_2() { OnChangeVol(1); }
void CChannelsDlg::OnChangeVol_3() { OnChangeVol(2); }
void CChannelsDlg::OnChangeVol_4() { OnChangeVol(3); }
void CChannelsDlg::OnChangeVol_5() { OnChangeVol(4); }
void CChannelsDlg::OnChangeVol_6() { OnChangeVol(5); }

void CChannelsDlg::OnChangePan_1() { OnChangePan(0); }
void CChannelsDlg::OnChangePan_2() { OnChangePan(1); }
void CChannelsDlg::OnChangePan_3() { OnChangePan(2); }
void CChannelsDlg::OnChangePan_4() { OnChangePan(3); }
void CChannelsDlg::OnChangePan_5() { OnChangePan(4); }
void CChannelsDlg::OnChangePan_6() { OnChangePan(5); }

void CChannelsDlg::OnChangeInv_1() { OnChangeInv(0); }
void CChannelsDlg::OnChangeInv_2() { OnChangeInv(1); }
void CChannelsDlg::OnChangeInv_3() { OnChangeInv(2); }
void CChannelsDlg::OnChangeInv_4() { OnChangeInv(3); }
void CChannelsDlg::OnChangeInv_5() { OnChangeInv(4); }
void CChannelsDlg::OnChangeInv_6() { OnChangeInv(5); }

void CChannelsDlg::OnChangePan(BYTE chan)
{
	int temp = ((chan == 5) ? 28 : chan);
	int pan;
	sscanf(m_panbox[chan].GetWindowText(),"%d",&pan);
	if(pan < -127) pan = -127;
	if(pan > 127) pan = 127;
	pNSF->nsfCore.SetChannelOptions(temp,-1,-1,pan,-1);
	m_pan[chan].SetPos(pan);
}

void CChannelsDlg::OnChangeVol(BYTE chan)
{
	int temp = ((chan == 5) ? 28 : chan);
	int vol;
	sscanf(m_volbox[chan].GetWindowText(),"%d",&vol);
	if(vol < 0) vol = 0;
	if(vol > 255) vol = 255;
	pNSF->nsfCore.SetChannelOptions(temp,-1,vol,1000,-1);
	m_vol[chan].SetPos(vol);
}

int CChannelsDlg::WndProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	if(msg == WM_HSCROLL)
	{
		register int i = 0;
		register int j;
		CDString str;
		for(; i < 6; i++)
		{
			if( ((HWND)lParam) == m_vol[i].GetHandle() )
			{
				j = m_vol[i].GetPos();
				str.Format("%d",j);
				m_volbox[i].SetWindowText(str);
				pNSF->nsfCore.SetChannelOptions( ((i == 5) ? 28 : i),-1,j,1000,-1);
				break;
			}
			if( ((HWND)lParam) == m_pan[i].GetHandle() )
			{
				j = m_pan[i].GetPos();
				str.Format("%d",j);
				m_panbox[i].SetWindowText(str);
				pNSF->nsfCore.SetChannelOptions( ((i == 5) ? 28 : i),-1,-1,j,-1);
				break;
			}
		}
	}
	return CDDialog::WndProc(msg,wParam,lParam);
}