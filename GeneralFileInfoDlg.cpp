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
//  GeneralFileInfoDlg.cpp
//
//

#include "NSF.h"
#include <CommDlg.h>

void CGeneralFileInfoDlg::OnInitDialog()
{
	CDDialog::OnInitDialog();

	m_PathName.AttachToControl(hWnd,IDC_FILENAME);
	m_Shadow.AttachToControl(hWnd,IDC_SHADOWTEXT);
	m_Info.AttachToControl(hWnd,IDC_FILEINFO);
	m_Convert.AttachToControl(hWnd,IDC_CONVERT);

	m_PathName.SetWindowText(szPath);
	if(bShadow)
		m_Shadow.SetWindowText("This is a shadow of " + pNSF->GetTrackLabel(pFile,nShadowTrack,1));
	
	m_Convert.SetWindowText("Convert to NSF" + (CDString)(pFile->bIsExtended ? "" : "E"));
	Refresh();

	AFX_MAPMESSAGE(IDC_CONVERT,BN_CLICKED, &CGeneralFileInfoDlg::OnConvert);
	AFX_MAPMESSAGE(IDC_WINAMPSHADOW,BN_CLICKED,&CGeneralFileInfoDlg::OnShadowWinamp);
	AFX_MAPMESSAGE(IDC_FILESHADOW,BN_CLICKED,&CGeneralFileInfoDlg::OnShadowFile);
}

void CGeneralFileInfoDlg::Refresh()
{
	CDString trk;
	trk.Format("%d",pFile->nTrackCount);

	CDString info;
	info = pNSF->GetGameTitle(pFile,1) + "\n" +
		pNSF->GetArtist(pFile,1) + "\n" +
		pNSF->GetCopyright(pFile,1) + "\n" +
		pNSF->GetRipper(pFile,1) + "\n" +
		trk + "\n" +
		pNSF->GetExpansionString(pFile) + "\n" + 
		pNSF->GetNTSCPALString(pFile) + "\n\n" +
		(CDString)(pFile->bIsExtended ? "Yes" : "No") + "\n" +
		(CDString)(pFile->szTrackLabels ? "Yes" : "No") + "\n" +
		(CDString)(pFile->pTrackTime ? "Yes" : "No") + "\n" +
		(CDString)(pFile->pTrackFade ? "Yes" : "No") + "\n" +
		(CDString)(pFile->pPlaylist ? "Yes" : "No");
	m_Info.SetWindowText(info);
}

void CGeneralFileInfoDlg::OnConvert()
{
	bool temp = pFile->bIsExtended;

	OPENFILENAME ofn;
	ZeroMemory(&ofn,sizeof(OPENFILENAME));

	char filename[MAX_PATH + 1];
	lstrcpy(filename,szPath);
	for(int i = lstrlen(filename); i >= 0; i--)
	{
		if(filename[i] == '.')
		{
			filename[i] = 0;
			break;
		}
		if(filename[i] == '\\')
			break;
	}

	lstrcat(filename,temp ? ".nsf" : ".nsfe");

	ofn.lStructSize =			sizeof(OPENFILENAME);
	ofn.hwndOwner =				hWnd;
	ofn.lpstrFilter =			"NSF Files (*.nsf;*nsfe)\0*.nsf;*.nsfe\0All Files\0*\0\0";
	ofn.nFilterIndex =			1;
	ofn.lpstrFile =				filename;
	ofn.nMaxFile =				MAX_PATH;
	ofn.Flags =					OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.nFileOffset =			0xFFFF;
	ofn.nFileExtension =		0xFFFF;
	for(int i = lstrlen(filename) - 1; i >= 0; i--)
	{
		if((filename[i] == '.') && (ofn.nFileExtension == 0xFFFF))
		{
			if(i == (lstrlen(filename) - 1))	ofn.nFileExtension = 0;
			else								ofn.nFileExtension = i + 1;
		}
		if(filename[i] == '\\')
		{
			ofn.nFileOffset = i + 1;
			break;
		}
	}
	if(ofn.nFileExtension == 0xFFFF)		ofn.nFileExtension = 0;
	if(ofn.nFileOffset == 0xFFFF)			ofn.nFileOffset = 0;

	if(!GetSaveFileName(&ofn))
		return;

	//make sure the extension is proper
	if(!ofn.nFileExtension)	lstrcat(filename,temp ? "nsf" : "nsfe");
	else					lstrcpy(&filename[ofn.nFileExtension],temp ? "nsf" : "nsfe");

	//convert the file
	pFile->bIsExtended = !temp;
	if(pFile->SaveFile(filename))
		MessageBox(hWnd,"Error:\nUnable to save file.","NotSo Fatso",MB_OK);
	pFile->bIsExtended = temp;
}

void CGeneralFileInfoDlg::OnShadowWinamp()
{
	char					filename[MAX_PATH + 20];
	COPYDATASTRUCT			cs;
	cs.dwData =				100;
	cs.lpData =				filename;
	int i;
	if(pNSF->bUsePlaylists && pFile->pPlaylist)
	{
		for(i = 0; i < pFile->nPlaylistSize; i++)
		{
			sprintf(filename,"nsf://%d:%s",pFile->pPlaylist[i],szPath);
			cs.cbData = lstrlen(filename) + 1;
			SendMessage(pNSF->inMod->hMainWindow,WM_COPYDATA,0,(LPARAM)&cs);
		}
	}
	else
	{
		for(i = 0; i < pFile->nTrackCount; i++)
		{
			sprintf(filename,"nsf://%d:%s",i,szPath);
			cs.cbData = lstrlen(filename) + 1;
			SendMessage(pNSF->inMod->hMainWindow,WM_COPYDATA,0,(LPARAM)&cs);
		}
	}
}

void CGeneralFileInfoDlg::OnShadowFile()
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn,sizeof(OPENFILENAME));

	char filename[MAX_PATH + 20];
	lstrcpy(filename,szPath);
	for(int i = lstrlen(filename); i >= 0; i--)
	{
		if(filename[i] == '.')
		{
			filename[i] = 0;
			break;
		}
		if(filename[i] == '\\')
			break;
	}

	lstrcat(filename,".m3u");

	ofn.lStructSize =			sizeof(OPENFILENAME);
	ofn.hwndOwner =				hWnd;
	ofn.lpstrFilter =			"Winamp Playlists (*.m3u)\0*.m3u\0All Files\0*\0\0";
	ofn.nFilterIndex =			1;
	ofn.lpstrFile =				filename;
	ofn.nMaxFile =				MAX_PATH;
	ofn.Flags =					OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	ofn.nFileOffset =			0xFFFF;
	ofn.nFileExtension =		0xFFFF;
	for(int i = lstrlen(filename) - 1; i >= 0; i--)
	{
		if((filename[i] == '.') && (ofn.nFileExtension == 0xFFFF))
		{
			if(i == (lstrlen(filename) - 1))	ofn.nFileExtension = 0;
			else								ofn.nFileExtension = i + 1;
		}
		if(filename[i] == '\\')
		{
			ofn.nFileOffset = i + 1;
			break;
		}
	}
	if(ofn.nFileExtension == 0xFFFF)		ofn.nFileExtension = 0;
	if(ofn.nFileOffset == 0xFFFF)			ofn.nFileOffset = 0;

	if(!GetSaveFileName(&ofn))
		return;

	//make sure the extension is proper
	if(!ofn.nFileExtension)	lstrcat(filename,"m3u");
	else					lstrcpy(&filename[ofn.nFileExtension],"m3u");

	//save the file
	FILE* file = fopen(filename,"wb");
	if(!file)
	{
		MessageBox(hWnd,"Error:\nUnable to save file.","NotSo Fatso",MB_OK);
		return;
	}
	fwrite("#EXTM3U\r\n",1,9,file);

	if(pNSF->bUsePlaylists && pFile->pPlaylist)
	{
		for(int i = 0; i < pFile->nPlaylistSize; i++)
		{
			sprintf(filename,"nsf://%d:%s\r\n",pFile->pPlaylist[i],szPath);
			fwrite(filename,1,lstrlen(filename),file);
		}
	}
	else
	{
		for(int i = 0; i < pFile->nTrackCount; i++)
		{
			sprintf(filename,"nsf://%d:%s\r\n",i,szPath);
			fwrite(filename,1,lstrlen(filename),file);
		}
	}
	fclose(file);
}