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
//  ConfigDlg.h
//
//

class CConfigDlg : public CDDialog
{
public:
			CConfigDlg() : CDDialog() { }
	int		WndProc(UINT msg,WPARAM wParam,LPARAM lParam);
	void	OnCancel() { }
	void	OnOK()	{ }
	void	OnInitDialog();

	CDComboBox		m_SampleRate;
	CDButton		m_Stereo;
	CDSlider		m_MasterVol;
	CDStatic		m_VolumeDisplay;
	CDButton		m_DefaultSpeed;
	CDSlider		m_SpeedThrottle;
	CDStatic		m_SpeedDisplay;
	CDEdit			m_DefaultLength;
	CDEdit			m_DefaultFade;
	CDButton		m_PreferPAL;

	CDSlider		m_HighPassBar;
	CDEdit			m_HighPass;
	CDButton		m_HighPassOn;
	CDSlider		m_LowPassBar;
	CDEdit			m_LowPass;
	CDButton		m_LowPassOn;
	CDSlider		m_PrePassBar;
	CDEdit			m_PrePass;
	CDButton		m_PrePassOn;

	void	SetOptions(int samplerate,int chans,float mastervol,BYTE usedefspeed,
		float speed,UINT DefLen,UINT DefFade,NSF_ADVANCEDOPTIONS* opt);

	void	GetPlayMode(int* samplerate,int* chans);
	void	GetDefaultTimes(UINT& song,UINT& fade);

	void	OnChangeDefaultSpeed();
	void	OnChangeFilter();
	void	OnChangeMisc();

	CNSF*			pNSF;
};

class CConfigDlg2 : public CDDialog
{
public:
	void	OnCancel() { }
	void	OnOK()	{ }
	void	OnInitDialog();

	void	SetOptions(BYTE openmulti,BYTE opensingle,BYTE openshadow,CDString& FormatMulti,
		CDString& FormatSingle,CDString& FormatShadow,BYTE useplaylist,BYTE loopforever,BYTE subclass,BYTE alwaysontop,
		BYTE usemini,BYTE minialwaysontop);

	void	GetFormatStrings(CDString& Multi,CDString& Single,CDString& Shadow);

	void	OnChangeAutoOpen();
	void	OnChangeLoop();
	void	OnChangePlaylist();
	void	OnChangeSubclass();
	void	OnChangeAlwaysOnTop();
	void	OnChangeUseMini();
	void	OnChangeMiniAlwaysOnTop();

	CDButton		m_Open_Multi;
	CDButton		m_Open_Single;
	CDButton		m_Open_Shadow;
	CDEdit			m_Format_Multi;
	CDEdit			m_Format_Single;
	CDEdit			m_Format_Shadow;
	CDButton		m_DisablePlaylist;
	CDButton		m_LoopForever;
	CDButton		m_SubclassWinamp;
	CDButton		m_AlwaysOnTop;
	CDButton		m_UseMini;
	CDButton		m_MiniAlwaysOnTop;

	CNSF*			pNSF;
};

class CConfigDlg3 : public CDDialog
{
public:
	void	OnCancel() { }
	void	OnOK()	{ }
	void	OnInitDialog();

	void	SetOptions(NSF_ADVANCEDOPTIONS* opt,BYTE ignoreversion);

	void	OnChangeMisc();
	void	OnChangeIgnoreVersion();

	CDButton		m_Ignore4011;
	CDButton		m_IgnoreBRK;
	CDButton		m_IgnoreIllegal;
	CDButton		m_NoWait;
	CDButton		m_CleanAXY;
	CDButton		m_ResetDuty;
	
	CDButton		m_DMCPopReducer;
	CDComboBox		m_Force4017;
	CDButton		m_N106PopReducer;
	CDButton		m_FDSPopReducer;
	CDButton		m_SilenceTrack;
	CDEdit			m_SilenceTrackMS;
	CDButton		m_NoSilenceIfLen;
	CDButton		m_InvertCutoff;
	CDEdit			m_InvertCutoffHz;

	CDButton		m_IgnoreVersion;

	CNSF*			pNSF;
};