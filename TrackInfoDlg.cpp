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
//  TrackInfoDlg.cpp
//


#include "NSF.h"

CTrackInfoDlg::CTrackInfoDlg() : CDDialog()
{
}

CTrackInfoDlg::~CTrackInfoDlg()
{
}

void CTrackInfoDlg::OnInitDialog()
{
	CDDialog::OnInitDialog();

	m_tracklist.AttachToControl(hWnd,IDC_TRACKLIST);
	m_haslabels.AttachToControl(hWnd,IDC_HASLABELS);
	m_haslength.AttachToControl(hWnd,IDC_HASLENGTH);
	m_hasfade.AttachToControl(hWnd,IDC_HASFADE);
	m_label.AttachToControl(hWnd,IDC_LABEL);
	m_length.AttachToControl(hWnd,IDC_LENGTH);
	m_fade.AttachToControl(hWnd,IDC_FADE);
	m_getlength.AttachToControl(hWnd,IDC_GETLENGTH);
	m_getfade.AttachToControl(hWnd,IDC_GETFADE);


	m_haslabels.SetCheck(pFile->szTrackLabels != NULL);
	m_label.EnableWindow(pFile->szTrackLabels != NULL);

	m_haslength.SetCheck(pFile->pTrackTime != NULL);
	m_length.EnableWindow(pFile->pTrackTime != NULL);
	m_getlength.EnableWindow(pFile->pTrackTime != NULL);

	m_hasfade.SetCheck(pFile->pTrackFade != NULL);
	m_fade.EnableWindow(pFile->pTrackFade != NULL);
	m_getfade.EnableWindow(pFile->pTrackFade != NULL);

	int i;

	if(bShadow)
	{
		m_tracklist.InsertString(0,pNSF->GetTrackLabel(pFile,nShadowTrack,0));
		m_tracklist.EnableWindow(0);
		LoadValues();
	}
	else
	{
		for(i = 0; i < pFile->nTrackCount; i++)
			m_tracklist.InsertString(i,pNSF->GetTrackLabel(pFile,i,0));
		m_tracklist.EnableWindow(1);
		sel = -1;
		m_tracklist.SetCurSel(0);
		OnSelchangeList();
	}


	AFX_MAPMESSAGE(IDC_TRACKLIST,LBN_SELCHANGE,&CTrackInfoDlg::OnSelchangeList);
	AFX_MAPMESSAGE(IDC_TRACKLIST,LBN_DBLCLK, &CTrackInfoDlg::OnDblClickList);
	AFX_MAPMESSAGE(IDC_HASLABELS,BN_CLICKED,&CTrackInfoDlg::OnHasLabels);
	AFX_MAPMESSAGE(IDC_HASLENGTH,BN_CLICKED,&CTrackInfoDlg::OnHasLength);
	AFX_MAPMESSAGE(IDC_HASFADE,BN_CLICKED, &CTrackInfoDlg::OnHasFade);
	AFX_MAPMESSAGE(IDC_GETLENGTH,BN_CLICKED, &CTrackInfoDlg::OnGetLength);
	AFX_MAPMESSAGE(IDC_GETFADE,BN_CLICKED, &CTrackInfoDlg::OnGetFade);
}

void CTrackInfoDlg::OnDblClickList()
{
	int i = m_tracklist.GetCurSel();
	if(i < 0)
		return;

	if(bShadow)
		i = nShadowTrack;

	if(pNSF->szLoadedPath == szPath)
		pNSF->SetTrack((BYTE)i);
}

void CTrackInfoDlg::OnSelchangeList()
{
	if(bShadow)
		return;

	if(sel != -1)
		StoreValues();
	sel = m_tracklist.GetCurSel();
	if(sel != -1)
		LoadValues();
}

void CTrackInfoDlg::LoadValues()
{
	if(bShadow)
		sel = nShadowTrack;

	CDString str;

	if(pFile->szTrackLabels)
		m_label.SetWindowText(pFile->szTrackLabels[sel]);
	if(pFile->pTrackTime)
	{
		if(pFile->pTrackTime[sel] >= 0)
		{
			str.Format("%u:%02u.%03u",pFile->pTrackTime[sel] / 60000,(pFile->pTrackTime[sel] / 1000) % 60,pFile->pTrackTime[sel] % 1000);
			m_length.SetWindowText(str);
		}
		else
			m_length.SetWindowText("");
	}
	if(pFile->pTrackFade)
	{
		if(pFile->pTrackFade[sel] >= 0)
		{
			str.Format("%u:%02u.%03u",pFile->pTrackFade[sel] / 60000,(pFile->pTrackFade[sel] / 1000) % 60,pFile->pTrackFade[sel] % 1000);
			m_fade.SetWindowText(str);
		}
		else
			m_fade.SetWindowText("");
	}
}

void CTrackInfoDlg::StoreValues()
{
	if(bShadow)
		sel = nShadowTrack;

	CDString str;
	UINT mn,sc,ms;
	if(pFile->szTrackLabels)
	{
		str = m_label.GetWindowText();
		if(lstrlen(pFile->szTrackLabels[sel]) < str.GetLength())
		{
			delete[] pFile->szTrackLabels[sel];
			pFile->szTrackLabels[sel] = new char[str.GetLength() + 1];
		}
		lstrcpy(pFile->szTrackLabels[sel],str);

		if(bShadow)
		{
			m_tracklist.ResetContent();
			m_tracklist.InsertString(0,pNSF->GetTrackLabel(pFile,nShadowTrack,0));
		}
		else
		{
			int temp = m_tracklist.GetCurSel();
			m_tracklist.DeleteString(sel);
			m_tracklist.InsertString(sel,pNSF->GetTrackLabel(pFile,sel,0));
			m_tracklist.SetCurSel(temp);
		}
	}

	if(pFile->pTrackTime)
	{
		str = m_length.GetWindowText();
		if(str == "")
			pFile->pTrackTime[sel] = -1;
		else
		{
			mn = sc = ms = 0;
			sscanf(str,"%u:%u.%u",&mn,&sc,&ms);
			pFile->pTrackTime[sel] = (int)((mn * 60000) + (sc * 1000) + ms);
		}
	}
	if(pFile->pTrackFade)
	{
		str = m_fade.GetWindowText();
		if(str == "")
			pFile->pTrackFade[sel] = -1;
		else
		{
			mn = sc = ms = 0;
			sscanf(str,"%u:%u.%u",&mn,&sc,&ms);
			pFile->pTrackFade[sel] = (int)((mn * 60000) + (sc * 1000) + ms);
		}
	}
}


void CTrackInfoDlg::OnHasLabels()
{
	int i;
	if(!m_haslabels.GetCheck())
	{
		if(MessageBox(hWnd,"This will permanently erase label information.\nAre you sure?","NotSo Fatso",MB_YESNOCANCEL) != IDYES)
		{
			m_haslabels.SetCheck(1);
			return;
		}
		for(i = 0; i < pFile->nTrackCount; i++)
			delete[] pFile->szTrackLabels[i];
		delete[] pFile->szTrackLabels;
		pFile->szTrackLabels = NULL;
		m_label.EnableWindow(0);
	}
	else
	{
		pFile->szTrackLabels = new char*[pFile->nTrackCount];
		for(i = 0; i < pFile->nTrackCount; i++)
		{
			pFile->szTrackLabels[i] = new char[2];
			pFile->szTrackLabels[i][0] = 0;
		}
		m_label.EnableWindow(1);
	}
	m_label.SetWindowText("");

	m_tracklist.ResetContent();
	if(bShadow)
		m_tracklist.InsertString(0,pNSF->GetTrackLabel(pFile,nShadowTrack,0));
	else
	{
		for(i = 0; i < pFile->nTrackCount; i++)
			m_tracklist.InsertString(i,pNSF->GetTrackLabel(pFile,i,0));
		m_tracklist.SetCurSel(sel);
	}
}

void CTrackInfoDlg::OnHasLength()
{
	int i;
	if(!m_haslength.GetCheck())
	{
		if(MessageBox(hWnd,"This will permanently erase track time information.\nAre you sure?","NotSo Fatso",MB_YESNOCANCEL) != IDYES)
		{
			m_haslength.SetCheck(1);
			return;
		}
		delete[] pFile->pTrackTime;
		pFile->pTrackTime = NULL;
		m_length.EnableWindow(0);
		m_getlength.EnableWindow(0);
	}
	else
	{
		pFile->pTrackTime = new int[pFile->nTrackCount];
		for(i = 0; i < pFile->nTrackCount; i++)
			pFile->pTrackTime[i] = -1;
		m_length.EnableWindow(1);
		m_getlength.EnableWindow(1);
	}
	m_length.SetWindowText("");
}

void CTrackInfoDlg::OnHasFade()
{
	int i;
	if(!m_hasfade.GetCheck())
	{
		if(MessageBox(hWnd,"This will permanently erase track fade information.\nAre you sure?","NotSo Fatso",MB_YESNOCANCEL) != IDYES)
		{
			m_hasfade.SetCheck(1);
			return;
		}
		delete[] pFile->pTrackFade;
		pFile->pTrackFade = NULL;
		m_fade.EnableWindow(0);
		m_getfade.EnableWindow(0);
	}
	else
	{
		pFile->pTrackFade = new int[pFile->nTrackCount];
		for(i = 0; i < pFile->nTrackCount; i++)
			pFile->pTrackFade[i] = -1;
		m_fade.EnableWindow(1);
		m_getfade.EnableWindow(1);
	}
	m_fade.SetWindowText("");
}

void CTrackInfoDlg::OnGetLength()
{
	if(!pNSF->bIsThreadOpen)	return;
	if(!pFile->pTrackTime)		return;

	int tim = pNSF->GetOutputTime();

	if(bShadow)
		pFile->pTrackTime[nShadowTrack] = tim;
	else
		pFile->pTrackTime[sel] = tim;

	CDString str;
	str.Format("%u:%02u.%03u",(tim / 60000), (tim / 1000) % 60, tim  % 1000);
	m_length.SetWindowText(str);
}

void CTrackInfoDlg::OnGetFade()
{
	if(!pNSF->bIsThreadOpen)	return;
	if(!pFile->pTrackFade)		return;

	int tim, fad;
	CDString str;

	if(pFile->pTrackTime)
	{
		UINT mn,sc,ms;
		mn = sc = ms = 0;
		str = m_length.GetWindowText();
		if(str == "")
			tim = (int)pNSF->nDefaultSongLength;
		else
		{
			sscanf(str,"%u:%u.%u",&mn,&sc,&ms);
			tim = (int)( (mn * 60000) + (sc * 1000) + ms );
		}
	}
	else
		tim = (int)pNSF->nDefaultSongLength;

	fad = pNSF->GetOutputTime();
	fad -= tim;
	if(fad < 0) fad = 0;


	if(bShadow)
		pFile->pTrackFade[nShadowTrack] = fad;
	else
		pFile->pTrackFade[sel] = fad;

	str.Format("%u:%02u.%03u",(fad / 60000), (fad / 1000) % 60, fad  % 1000);
	m_fade.SetWindowText(str);
}