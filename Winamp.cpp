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
//  Winamp.cpp
//
//

#include "NSF.h"

CNSF		nsf;

void	in_Config(HWND hwndParent)									{ nsf.Config(hwndParent); }
void	in_About(HWND hwndParent)									{ nsf.About(hwndParent); }
void	in_Init()													{ nsf.Init(); }
void	in_Quit()													{ nsf.Quit(); }
void	in_GetFileInfo(char *file, char *title, int *length_in_ms)	{ nsf.GetFileInfo(file,title,length_in_ms); }
int		in_InfoBox(char *file, HWND hwndParent)						{ return nsf.InfoBox(file,hwndParent); }
int		in_IsOurFile(char *fn)										{ return nsf.IsOurFile(fn); }
int		in_Play(char *fn)											{ return nsf.Play(fn); }
void	in_Pause()													{ nsf.Pause(1); }
void	in_UnPause()												{ nsf.Pause(0); }
int		in_IsPaused()												{ return nsf.IsPaused(); }
void	in_Stop()													{ nsf.Stop(); }
int		in_GetLength()												{ return nsf.GetLength(); }
int		in_GetOutputTime()											{ return nsf.GetOutputTime(); }
void	in_SetOutputTime(int time_in_ms)							{ nsf.SetOutputTime(time_in_ms); }
void	in_SetVolume(int volume)									{ nsf.SetVolume(volume); }
void	in_SetPan(int pan)											{ nsf.SetPan(pan); }


LRESULT CALLBACK Winamp_WndProc(HWND wnd,UINT msg,WPARAM w,LPARAM l)
{
	if(nsf.bClingToWinamp)
	{
		if(msg == WM_COMMAND)
		{
			if(w == 40044)		//prev button
			{
				if(nsf.PrevTrack()) return 0;
			}
			if(w == 40048)		//next button
			{
				if(nsf.NextTrack()) return 0;
			}
			if(w == 40045)		//play button
			{
				nsf.SetTrack(nsf.nCurrentTrack);
				return 0;
			}
		}
		if(msg == WM_KEYDOWN)
		{
			switch(w) {
			case 'z': case 'Z': case VK_NUMPAD4:
				if(nsf.PrevTrack()) return 0;
				break;
			case 'b': case 'B': case VK_NUMPAD6:
				if(nsf.NextTrack()) return 0;
				break;
			case 'x': case 'X': case VK_NUMPAD5:
				nsf.SetTrack(nsf.nCurrentTrack);
				return 0;
			}
		}
	}

	if(wnd == nsf.wndWinampPL)	return CallWindowProc((WNDPROC)nsf.pTrueWinampPLWndProc,wnd,msg,w,l);
	if(wnd == nsf.wndWinampEQ)	return CallWindowProc((WNDPROC)nsf.pTrueWinampEQWndProc,wnd,msg,w,l);

	if(msg == WM_CLOSE)		//I shouldn't have to do this... but Winamp crashes otherwise
	{	
		SendMessage(wnd, WM_COMMAND, 40047, 0);	//tell it to stop the NSF (un-subclass the window)
		PostMessage(wnd, WM_COMMAND, 40001, 0);	//then POST (not send) another close message.  The next one should go to Winamp's true WndProc
		return 0;
	}

	return CallWindowProc((WNDPROC)nsf.pTrueWinampWndProc,wnd,msg,w,l);
}


In_Module	InMod = {
	IN_VER,
	"NotSo Fatso - NSF/NSFe Player - v0.851",
	NULL,
	NULL,
	"nsf\0NSF Files (*.nsf)\0nsfe\0NSF Extended files (*.nsfe)\0\0",
	// that 'NSFE' messes up Winamp and makes it show every file in the file selection dialog  >=(.  I think it's a Winamp problem

	// this correction is sort of a hack to keep nsfe shown, but to avoid the sideeffect
	//"ns*\0NES Sound Format (*.nsf)\0\0",  //<-- apparently this fucks up too.. .dammit..
	1,
	1,

	in_Config,
	in_About,
	in_Init,
	in_Quit,
	in_GetFileInfo,
	in_InfoBox,
	in_IsOurFile,
	in_Play,
	in_Pause,
	in_UnPause,
	in_IsPaused,
	in_Stop,
	in_GetLength,
	in_GetOutputTime,
	in_SetOutputTime,
	in_SetVolume,
	in_SetPan,

	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};

In_Module*	winampGetInModule2(void)	{
	return &InMod;
}