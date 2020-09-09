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
//  TagInfoDlg.cpp
//
//

#include "NSF.h"
#include <CommDlg.h>

void CTagInfoDlg::OnInitDialog()
{
	CDDialog::OnInitDialog();

	m_Title.AttachToControl(hWnd,IDC_TITLE);
	m_Artist.AttachToControl(hWnd,IDC_ARTIST);
	m_Copyright.AttachToControl(hWnd,IDC_COPYRIGHT);
	m_Ripper.AttachToControl(hWnd,IDC_RIPPER);

	LoadValues();
}

void CTagInfoDlg::LoadValues()
{
	m_Ripper.EnableWindow(pFile->bIsExtended != 0);

	if(pFile->szGameTitle)	m_Title.SetWindowText(pFile->szGameTitle);
	else					m_Title.SetWindowText("");
	
	if(pFile->szArtist)		m_Artist.SetWindowText(pFile->szArtist);
	else					m_Artist.SetWindowText("");
	
	if(pFile->szCopyright)	m_Copyright.SetWindowText(pFile->szCopyright);
	else					m_Copyright.SetWindowText("");
	
	if(pFile->szRipper)		m_Ripper.SetWindowText(pFile->szRipper);
	else					m_Ripper.SetWindowText("");
}

void CTagInfoDlg::StoreValues()
{
	CDString str;

	str = m_Title.GetWindowText();
	if(!pFile->bIsExtended) str = str.Left(31);
	if(pFile->szGameTitle) delete[] pFile->szGameTitle;
	pFile->szGameTitle = new char[str.GetLength() + 1];
	strcpy(pFile->szGameTitle,(LPCSTR)str);
	
	str = m_Artist.GetWindowText();
	if(!pFile->bIsExtended) str = str.Left(31);
	if(pFile->szArtist) delete[] pFile->szArtist;
	pFile->szArtist = new char[str.GetLength() + 1];
	strcpy(pFile->szArtist,(LPCSTR)str);
	
	str = m_Copyright.GetWindowText();
	if(!pFile->bIsExtended) str = str.Left(31);
	if(pFile->szCopyright) delete[] pFile->szCopyright;
	pFile->szCopyright = new char[str.GetLength() + 1];
	strcpy(pFile->szCopyright,(LPCSTR)str);
	
	if(pFile->bIsExtended)
	{
		str = m_Ripper.GetWindowText();
		if(!pFile->bIsExtended) str = str.Left(31);
		if(pFile->szRipper) delete[] pFile->szRipper;
		pFile->szRipper = new char[str.GetLength() + 1];
		strcpy(pFile->szRipper,(LPCSTR)str);
	}
}