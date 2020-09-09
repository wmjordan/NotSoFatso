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
//  ConfigDlg.cpp
//

#include "NSF.h"

void CConfigDlg::OnInitDialog()
{
	CDDialog::OnInitDialog();

	m_SampleRate.AttachToControl(hWnd,IDC_SAMPLERATE);
	m_Stereo.AttachToControl(hWnd,IDC_STEREO);
	m_MasterVol.AttachToControl(hWnd,IDC_MASTERVOL);
	m_VolumeDisplay.AttachToControl(hWnd,IDC_VOLUMEDISPLAY);
	m_DefaultSpeed.AttachToControl(hWnd,IDC_DEFAULTSPEED);
	m_SpeedThrottle.AttachToControl(hWnd,IDC_SPEEDTHROTTLE);
	m_SpeedDisplay.AttachToControl(hWnd,IDC_SPEEDDISPLAY);
	m_DefaultLength.AttachToControl(hWnd,IDC_DEFAULTLENGTH);
	m_DefaultFade.AttachToControl(hWnd,IDC_DEFAULTFADE);
	m_PreferPAL.AttachToControl(hWnd,IDC_PREFERPAL);

	m_HighPass.AttachToControl(hWnd,IDC_HIGHPASS);
	m_HighPassBar.AttachToControl(hWnd,IDC_HIGHPASSBAR);
	m_HighPassOn.AttachToControl(hWnd,IDC_HIGHPASSON);
	m_LowPass.AttachToControl(hWnd,IDC_LOWPASS);
	m_LowPassBar.AttachToControl(hWnd,IDC_LOWPASSBAR);
	m_LowPassOn.AttachToControl(hWnd,IDC_LOWPASSON);
	m_PrePass.AttachToControl(hWnd,IDC_PREPASS);
	m_PrePassBar.AttachToControl(hWnd,IDC_PREPASSBAR);
	m_PrePassOn.AttachToControl(hWnd,IDC_PREPASSON);

	m_SampleRate.InsertString(0,"11025");
	m_SampleRate.InsertString(1,"22050");
	m_SampleRate.InsertString(2,"32000");
	m_SampleRate.InsertString(3,"44100");
	m_SampleRate.InsertString(4,"48000");
	m_SampleRate.InsertString(5,"64000");
	m_SampleRate.InsertString(6,"72000");
	m_SampleRate.InsertString(7,"88200");
	m_SampleRate.InsertString(8,"96000");

	m_MasterVol.SetRange(0,2000);

	m_SpeedThrottle.SetRange(100,1200);

	m_HighPassBar.SetRange(5,500);
	m_LowPassBar.SetRange(0,520);  //80 - 600
	m_PrePassBar.SetRange(0,100);

	AFX_MAPMESSAGE(IDC_DEFAULTSPEED,BN_CLICKED, &CConfigDlg::OnChangeDefaultSpeed);
	AFX_MAPMESSAGE(IDC_PREFERPAL,BN_CLICKED, &CConfigDlg::OnChangeMisc);
	AFX_MAPMESSAGE(IDC_HIGHPASS,EN_UPDATE, &CConfigDlg::OnChangeFilter);
	AFX_MAPMESSAGE(IDC_LOWPASS,EN_UPDATE,&CConfigDlg::OnChangeFilter);
	AFX_MAPMESSAGE(IDC_PREPASS,EN_UPDATE,&CConfigDlg::OnChangeFilter);
	AFX_MAPMESSAGE(IDC_HIGHPASSON,BN_CLICKED, &CConfigDlg::OnChangeMisc);
	AFX_MAPMESSAGE(IDC_LOWPASSON,BN_CLICKED,&CConfigDlg::OnChangeMisc);
	AFX_MAPMESSAGE(IDC_PREPASSON,BN_CLICKED,&CConfigDlg::OnChangeMisc);
}

int eastereggfoobar = 1;

void CConfigDlg::OnChangeFilter()
{
	int hi = 0, lo = 0, pre = 0;

	sscanf((LPCSTR)m_HighPass.GetWindowText(),"%u",&hi);
	sscanf( (LPCSTR)m_LowPass.GetWindowText(),"%u",&lo);
	sscanf( (LPCSTR)m_PrePass.GetWindowText(),"%u",&pre);

	if(hi < 50)			hi = 50;
	if(hi > 5000)		hi = 5000;
	if(lo < 8000)		lo = 8000;
	if(lo > 60000)		lo = 60000;
	if(pre < 0)			pre = 0;
	if(pre > 100)		pre = 100;

	if((lo == 12345) && eastereggfoobar)
	{
		MessageBox(NULL,"Are Belong to Us!","All Your Base",MB_OK);	//Little Easter Egg.
		//AYB fo-evah!
		// NEVER TELL A SOUL!!!!!
	}

	m_HighPassBar.SetPos(hi / 10);
	m_LowPassBar.SetPos(600 - (lo / 100));
	m_PrePassBar.SetPos(pre);

	NSF_ADVANCEDOPTIONS opt;
	pNSF->nsfCore.GetAdvancedOptions(&opt);

	opt.nHighPassBase = hi;
	opt.nLowPassBase = lo;
	opt.nPrePassBase = pre;

	pNSF->nsfCore.SetAdvancedOptions(&opt);
}

int CConfigDlg::WndProc(UINT msg,WPARAM wParam,LPARAM lParam)
{
	int temp;
	if(msg == WM_HSCROLL)
	{
		CDString str;
		if(((HWND)lParam) == m_MasterVol.GetHandle())
		{
			temp = m_MasterVol.GetPos();
			pNSF->fMasterVolume = temp / 1000.0f;
			str.Format("%d.%03d",temp / 1000,temp % 1000);
			m_VolumeDisplay.SetWindowText(str);

			pNSF->nsfCore.SetMasterVolume(pNSF->fMasterVolume);
		}
		else if(((HWND)lParam) == m_SpeedThrottle.GetHandle())
		{
			temp = m_SpeedThrottle.GetPos();
			pNSF->fSpeedThrottle = temp / 10.0f;
			str.Format("%d.%d",temp / 10,temp % 10);
			m_SpeedDisplay.SetWindowText(str);

			if(!m_DefaultSpeed.GetCheck())
				pNSF->nsfCore.SetPlaybackSpeed(pNSF->fSpeedThrottle);
		}
		else if(((HWND)lParam) == m_HighPassBar.GetHandle())
		{
			temp = m_HighPassBar.GetPos() * 10;
			str.Format("%d",temp);
			m_HighPass.SetWindowText(str);
			NSF_ADVANCEDOPTIONS opt;
			pNSF->nsfCore.GetAdvancedOptions(&opt);
			opt.nHighPassBase = temp;
			pNSF->nsfCore.SetAdvancedOptions(&opt);
		}
		else if(((HWND)lParam) == m_LowPassBar.GetHandle())
		{
			temp = (600 - m_LowPassBar.GetPos()) * 100;
			str.Format("%d",temp);
			m_LowPass.SetWindowText(str);
			NSF_ADVANCEDOPTIONS opt;
			pNSF->nsfCore.GetAdvancedOptions(&opt);
			opt.nLowPassBase = temp;
			pNSF->nsfCore.SetAdvancedOptions(&opt);
		}
		else if(((HWND)lParam) == m_PrePassBar.GetHandle())
		{
			temp = m_PrePassBar.GetPos();
			str.Format("%d",temp);
			m_PrePass.SetWindowText(str);
			NSF_ADVANCEDOPTIONS opt;
			pNSF->nsfCore.GetAdvancedOptions(&opt);
			opt.nPrePassBase = temp;
			pNSF->nsfCore.SetAdvancedOptions(&opt);
		}
	}

	return 0;
}

void CConfigDlg::OnChangeDefaultSpeed()
{
	pNSF->bUseDefaultSpeed = m_DefaultSpeed.GetCheck();
	if(pNSF->bUseDefaultSpeed)
		pNSF->nsfCore.SetPlaybackSpeed(0);
	else
		pNSF->nsfCore.SetPlaybackSpeed(pNSF->fSpeedThrottle);
}

void CConfigDlg::SetOptions(int samplerate,int chans,
					float mastervol,BYTE usedefspeed,float speed,UINT DefLen,UINT DefFade,
					NSF_ADVANCEDOPTIONS* opt)
{
	CDString str;
	int temp;

	str.Format("%d",samplerate);
	m_SampleRate.SetWindowText(str);

	m_Stereo.SetCheck(chans == 2);

	temp = (int)(mastervol * 1000);
	m_MasterVol.SetPos(temp);
	str.Format("%d.%03d",temp / 1000,temp % 1000);
	m_VolumeDisplay.SetWindowText(str);

	m_DefaultSpeed.SetCheck(usedefspeed != 0);
	m_SpeedThrottle.SetPos((int)(speed * 10));

	temp = (int)(speed * 10);
	str.Format("%d.%d",temp / 10,temp % 10);
	m_SpeedDisplay.SetWindowText(str);


	str.Format("%d:%02d.%03d",(DefLen / 60000),(DefLen / 1000) % 60,(DefLen % 1000));
	m_DefaultLength.SetWindowText(str);

	str.Format("%d.%03d",(DefFade / 1000),(DefFade % 1000));
	m_DefaultFade.SetWindowText(str);
	
	m_PreferPAL.SetCheck(opt->bPALPreference != 0);

	eastereggfoobar = 0;
	str.Format("%d",opt->nHighPassBase);
	m_HighPass.SetWindowText(str);
	m_HighPassBar.SetPos(opt->nHighPassBase / 10);
	m_HighPassOn.SetCheck(opt->bHighPassEnabled != 0);

	str.Format("%d",opt->nLowPassBase);
	m_LowPass.SetWindowText(str);
	m_LowPassBar.SetPos(600 - (opt->nLowPassBase / 100));
	m_LowPassOn.SetCheck(opt->bLowPassEnabled != 0);

	str.Format("%d",opt->nPrePassBase);
	m_PrePass.SetWindowText(str);
	m_PrePassBar.SetPos(opt->nPrePassBase);
	m_PrePassOn.SetCheck(opt->bPrePassEnabled != 0);
	eastereggfoobar = 1;
}

void CConfigDlg::GetDefaultTimes(UINT& song,UINT& fade)
{
	UINT mn, sec, ms;

	mn = sec = ms = 0;
	sscanf(m_DefaultLength.GetWindowText(),"%u:%u.%u",&mn,&sec,&ms);
	song = ms + (sec * 1000) + (mn * 60000);

	mn = sec = ms = 0;
	sscanf(m_DefaultFade.GetWindowText(),"%u.%u",&sec,&ms);
	fade = ms + (sec * 1000);
}

void CConfigDlg::GetPlayMode(int* samplerate,int* chans)
{
	sscanf(m_SampleRate.GetWindowText(),"%d",samplerate);
	if(*samplerate < 8000)	*samplerate = 8000;
	if(*samplerate > 96000) *samplerate = 96000;

	*chans = (m_Stereo.GetCheck() ? 2 : 1);
}

void CConfigDlg::OnChangeMisc()
{
	NSF_ADVANCEDOPTIONS opt;
	pNSF->nsfCore.GetAdvancedOptions(&opt);

	opt.bPALPreference = (BYTE)m_PreferPAL.GetCheck();
	opt.bPrePassEnabled = (BYTE)m_PrePassOn.GetCheck();
	opt.bLowPassEnabled = (BYTE)m_LowPassOn.GetCheck();
	opt.bHighPassEnabled = (BYTE)m_HighPassOn.GetCheck();

	pNSF->nsfCore.SetAdvancedOptions(&opt);
}

//////////////////////////////////////////////////////////////////////////
// Second dialog

void CConfigDlg2::OnInitDialog()
{
	CDDialog::OnInitDialog();

	m_Open_Multi.AttachToControl(hWnd,IDC_OPEN_MULTI);
	m_Open_Single.AttachToControl(hWnd,IDC_OPEN_SINGLE);
	m_Open_Shadow.AttachToControl(hWnd,IDC_OPEN_SHADOW);
	m_Format_Multi.AttachToControl(hWnd,IDC_FORMAT_MULTI);
	m_Format_Single.AttachToControl(hWnd,IDC_FORMAT_SINGLE);
	m_Format_Shadow.AttachToControl(hWnd,IDC_FORMAT_SHADOW);
	m_DisablePlaylist.AttachToControl(hWnd,IDC_DISABLEPLAYLIST);
	m_LoopForever.AttachToControl(hWnd,IDC_LOOPFOREVER);
	m_SubclassWinamp.AttachToControl(hWnd,IDC_SUBCLASSWINAMP);
	m_AlwaysOnTop.AttachToControl(hWnd,IDC_ALWAYSONTOP);
	m_UseMini.AttachToControl(hWnd,IDC_USEMINI);
	m_MiniAlwaysOnTop.AttachToControl(hWnd,IDC_MINIALWAYSONTOP);

	AFX_MAPMESSAGE(IDC_OPEN_MULTI,BN_CLICKED, &CConfigDlg2::OnChangeAutoOpen);
	AFX_MAPMESSAGE(IDC_OPEN_SINGLE,BN_CLICKED,&CConfigDlg2::OnChangeAutoOpen);
	AFX_MAPMESSAGE(IDC_OPEN_SHADOW,BN_CLICKED,&CConfigDlg2::OnChangeAutoOpen);
	AFX_MAPMESSAGE(IDC_LOOPFOREVER,BN_CLICKED,&CConfigDlg2::OnChangeLoop);
	AFX_MAPMESSAGE(IDC_DISABLEPLAYLIST,BN_CLICKED, &CConfigDlg2::OnChangePlaylist);
	AFX_MAPMESSAGE(IDC_SUBCLASSWINAMP,BN_CLICKED, &CConfigDlg2::OnChangeSubclass);
	AFX_MAPMESSAGE(IDC_ALWAYSONTOP,BN_CLICKED, &CConfigDlg2::OnChangeAlwaysOnTop);
	AFX_MAPMESSAGE(IDC_USEMINI,BN_CLICKED, &CConfigDlg2::OnChangeUseMini);
	AFX_MAPMESSAGE(IDC_MINIALWAYSONTOP,BN_CLICKED, &CConfigDlg2::OnChangeMiniAlwaysOnTop);
}

void CConfigDlg2::OnChangePlaylist()
{
	pNSF->bUsePlaylists = !m_DisablePlaylist.GetCheck();
	pNSF->mControlDlg.m_playcontrol_slide.UpdateSlider();
}

void CConfigDlg2::OnChangeAutoOpen()
{
	pNSF->bOpenPlay_Normal = m_Open_Multi.GetCheck();
	pNSF->bOpenPlay_Single = m_Open_Single.GetCheck();
	pNSF->bOpenPlay_Shadow = m_Open_Shadow.GetCheck();
}

void CConfigDlg2::OnChangeSubclass()
{
	pNSF->bClingToWinamp = m_SubclassWinamp.GetCheck();
}

void CConfigDlg2::OnChangeLoop()
{
	pNSF->ResetFade(m_LoopForever.GetCheck());
}

void CConfigDlg2::OnChangeAlwaysOnTop()
{
	pNSF->SetAlwaysOnTop(m_AlwaysOnTop.GetCheck());
}

void CConfigDlg2::OnChangeMiniAlwaysOnTop()
{
	pNSF->SetMiniAlwaysOnTop(m_MiniAlwaysOnTop.GetCheck());
}

void CConfigDlg2::OnChangeUseMini()
{
	pNSF->bUseMiniPlayControl = m_UseMini.GetCheck();
	if(pNSF->bIsThreadOpen)
	{
		if(pNSF->bUseMiniPlayControl)	pNSF->mMiniPlayDlg.Open();
		else							pNSF->mMiniPlayDlg.Close();
	}
}

void CConfigDlg2::SetOptions(BYTE openmulti,BYTE opensingle,BYTE openshadow,CDString& FormatMulti,
				   CDString& FormatSingle,CDString& FormatShadow,BYTE useplaylist,BYTE loopforever,BYTE subclass,
				   BYTE alwaysontop,BYTE usemini,BYTE minialwaysontop)
{
	m_Open_Multi.SetCheck(openmulti);
	m_Open_Single.SetCheck(opensingle);
	m_Open_Shadow.SetCheck(openshadow);
	m_Format_Multi.SetWindowText(FormatMulti);
	m_Format_Single.SetWindowText(FormatSingle);
	m_Format_Shadow.SetWindowText(FormatShadow);
	m_DisablePlaylist.SetCheck(!useplaylist);
	m_LoopForever.SetCheck(loopforever);
	m_SubclassWinamp.SetCheck(subclass);
	m_AlwaysOnTop.SetCheck(alwaysontop);
	m_UseMini.SetCheck(usemini);
	m_MiniAlwaysOnTop.SetCheck(minialwaysontop);
}

void CConfigDlg2::GetFormatStrings(CDString& Multi,CDString& Single,CDString& Shadow)
{
	Multi = m_Format_Multi.GetWindowText();
	Single = m_Format_Single.GetWindowText();
	Shadow = m_Format_Shadow.GetWindowText();
}


//////////////////////////////////////////////////////////////////////////
// Third dialog

void CConfigDlg3::OnInitDialog()
{
	CDDialog::OnInitDialog();

	m_Ignore4011.AttachToControl(hWnd,IDC_IGNORE4011);
	m_IgnoreBRK.AttachToControl(hWnd,IDC_IGNOREBRK);
	m_IgnoreIllegal.AttachToControl(hWnd,IDC_IGNOREILLEGAL);
	m_NoWait.AttachToControl(hWnd,IDC_NOWAIT);
	m_CleanAXY.AttachToControl(hWnd,IDC_CLEANAXY);
	m_ResetDuty.AttachToControl(hWnd,IDC_RESETDUTY);

	m_DMCPopReducer.AttachToControl(hWnd,IDC_DMCPOPREDUCER);
	m_Force4017.AttachToControl(hWnd,IDC_FORCE4017);
	m_N106PopReducer.AttachToControl(hWnd,IDC_N106POPREDUCER);
	m_SilenceTrack.AttachToControl(hWnd,IDC_SILENCETRACK);
	m_SilenceTrackMS.AttachToControl(hWnd,IDC_SILENCETRACKMS);
	m_NoSilenceIfLen.AttachToControl(hWnd,IDC_NOSILENCEIFLEN);
	m_InvertCutoff.AttachToControl(hWnd,IDC_INVERTCUTOFF);
	m_InvertCutoffHz.AttachToControl(hWnd,IDC_INVERTCUTOFFHZ);
	m_FDSPopReducer.AttachToControl(hWnd,IDC_FDSPOPREDUCER);

	m_IgnoreVersion.AttachToControl(hWnd,IDC_IGNOREVERSION);
	
	m_Force4017.InsertString(0,"None");
	m_Force4017.InsertString(1,"Force $00");
	m_Force4017.InsertString(2,"Force $80");

	AFX_MAPMESSAGE(IDC_IGNORE4011,BN_CLICKED, &CConfigDlg3::OnChangeMisc);
	AFX_MAPMESSAGE(IDC_IGNOREBRK,BN_CLICKED, &CConfigDlg3::OnChangeMisc);
	AFX_MAPMESSAGE(IDC_IGNOREILLEGAL,BN_CLICKED, &CConfigDlg3::OnChangeMisc);
	AFX_MAPMESSAGE(IDC_NOWAIT,BN_CLICKED, &CConfigDlg3::OnChangeMisc);
	AFX_MAPMESSAGE(IDC_CLEANAXY,BN_CLICKED, &CConfigDlg3::OnChangeMisc);
	AFX_MAPMESSAGE(IDC_RESETDUTY,BN_CLICKED, &CConfigDlg3::OnChangeMisc);
	
	AFX_MAPMESSAGE(IDC_FDSPOPREDUCER,BN_CLICKED,&CConfigDlg3::OnChangeMisc);
	AFX_MAPMESSAGE(IDC_DMCPOPREDUCER,BN_CLICKED,&CConfigDlg3::OnChangeMisc);
	AFX_MAPMESSAGE(IDC_FORCE4017,CBN_SELCHANGE, &CConfigDlg3::OnChangeMisc);
	AFX_MAPMESSAGE(IDC_N106POPREDUCER,BN_CLICKED, &CConfigDlg3::OnChangeMisc);
	AFX_MAPMESSAGE(IDC_SILENCETRACK,BN_CLICKED, &CConfigDlg3::OnChangeMisc);
	AFX_MAPMESSAGE(IDC_SILENCETRACKMS,EN_UPDATE, &CConfigDlg3::OnChangeMisc);
	AFX_MAPMESSAGE(IDC_NOSILENCEIFLEN,BN_CLICKED, &CConfigDlg3::OnChangeMisc);
	AFX_MAPMESSAGE(IDC_INVERTCUTOFF,BN_CLICKED, &CConfigDlg3::OnChangeMisc);
	AFX_MAPMESSAGE(IDC_INVERTCUTOFFHZ,EN_UPDATE, &CConfigDlg3::OnChangeMisc);

	AFX_MAPMESSAGE(IDC_IGNOREVERSION,BN_CLICKED, &CConfigDlg3::OnChangeIgnoreVersion);
}

void CConfigDlg3::SetOptions(NSF_ADVANCEDOPTIONS* opt,BYTE ignoreversion)
{
	m_Ignore4011.SetCheck(opt->bIgnore4011Writes != 0);
	m_IgnoreBRK.SetCheck(opt->bIgnoreBRK != 0);
	m_IgnoreIllegal.SetCheck(opt->bIgnoreIllegalOps != 0);
	m_NoWait.SetCheck(opt->bNoWaitForReturn != 0);
	m_CleanAXY.SetCheck(opt->bCleanAXY != 0);
	m_ResetDuty.SetCheck(opt->bResetDuty != 0);

	m_IgnoreVersion.SetCheck(ignoreversion != 0);

	CDString str;
	
	m_NoSilenceIfLen.SetCheck(opt->bNoSilenceIfTime != 0);
	m_SilenceTrack.SetCheck(opt->nSilenceTrackMS > 0);
	str.Format("%d", ((opt->nSilenceTrackMS >= 0) ? opt->nSilenceTrackMS : -opt->nSilenceTrackMS));
	m_SilenceTrackMS.SetWindowText(str);
	
	m_InvertCutoff.SetCheck(opt->nInvertCutoffHz > 0);
	str.Format("%d", ((opt->nInvertCutoffHz >= 0) ? opt->nInvertCutoffHz : -opt->nInvertCutoffHz));
	m_InvertCutoffHz.SetWindowText(str);

	m_DMCPopReducer.SetCheck(opt->bDMCPopReducer != 0);
	m_Force4017.SetCurSel(opt->nForce4017Write);
	m_N106PopReducer.SetCheck(opt->bN106PopReducer != 0);
	m_FDSPopReducer.SetCheck(opt->bFDSPopReducer != 0);
}

void CConfigDlg3::OnChangeMisc()
{
	NSF_ADVANCEDOPTIONS opt;

	pNSF->nsfCore.GetAdvancedOptions(&opt);

	opt.bIgnore4011Writes = (BYTE)m_Ignore4011.GetCheck();
	opt.bIgnoreBRK = (BYTE)m_IgnoreBRK.GetCheck();
	opt.bIgnoreIllegalOps = (BYTE)m_IgnoreIllegal.GetCheck();
	opt.bNoWaitForReturn = (BYTE)m_NoWait.GetCheck();
	opt.bCleanAXY = (BYTE)m_CleanAXY.GetCheck();
	opt.bResetDuty = (BYTE)m_ResetDuty.GetCheck();

	opt.bDMCPopReducer = (BYTE)m_DMCPopReducer.GetCheck();
	opt.nForce4017Write = (BYTE)m_Force4017.GetCurSel();
	opt.bN106PopReducer = (BYTE)m_N106PopReducer.GetCheck();
	opt.bFDSPopReducer = (BYTE)m_FDSPopReducer.GetCheck();

	opt.nSilenceTrackMS = 0;
	opt.bNoSilenceIfTime = (BYTE)m_NoSilenceIfLen.GetCheck();
	sscanf(m_SilenceTrackMS.GetWindowText(),"%u",&opt.nSilenceTrackMS);
	if(!m_SilenceTrack.GetCheck())
		opt.nSilenceTrackMS = -opt.nSilenceTrackMS;
	
	opt.nInvertCutoffHz = 0;
	sscanf(m_InvertCutoffHz.GetWindowText(),"%u",&opt.nInvertCutoffHz);
	if(!m_InvertCutoff.GetCheck())
		opt.nInvertCutoffHz = -opt.nInvertCutoffHz;

	pNSF->nsfCore.SetAdvancedOptions(&opt);
}

void CConfigDlg3::OnChangeIgnoreVersion()
{
	pNSF->bIgnoreNSFVersion = (m_IgnoreVersion.GetCheck() != 0);
}