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
// DFC_String.cpp
//

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include "DFC_String.h"

//////////////////////////////////////////////////////////////////////////
// construction / destruction

void CDString::Construct(LPCSTR str)
{
	szData = NULL;
	nGrowBy = 16;

	nDataLength = strlen(str);
	nDataBufferSize = nDataLength + nGrowBy + 1;

	szData = new char[nDataBufferSize];
	
	pRefCount = new int;
	*pRefCount = 1;

	strcpy(szData,str);
}

CDString::CDString(const CDString& str)
{
	pRefCount = str.pRefCount;
	szData = str.szData;
	nDataLength = str.nDataLength;
	nDataBufferSize = str.nDataBufferSize;
	nGrowBy = 16;

	(*pRefCount)++;
}

CDString::~CDString()
{
	(*pRefCount)--;
	if(!*pRefCount)
	{
		delete[] szData;
		delete pRefCount;
	}
	szData = NULL;
	nDataLength = 0;
	nDataBufferSize = 0;
}

//////////////////////////////////////////////////////////////////////////
// assignment

void CDString::Append(LPCSTR str)
{
	SeperateFromRef();

	nDataLength += strlen(str);
	if(nDataLength >= nDataBufferSize)
		IncreaseBufferSize(nDataLength + 1);

	strcat(szData,str);
}

void CDString::Append(char ch)
{
	SeperateFromRef();

	nDataLength++;
	if(nDataLength >= nDataBufferSize)
		IncreaseBufferSize(nDataLength + 1);

	szData[nDataLength - 1] = ch;
	szData[nDataLength] = 0;
}

void CDString::Set(LPCSTR str)
{
	SeperateFromRef();

	nDataLength = lstrlen(str);
	if(nDataLength >= nDataBufferSize)
		IncreaseBufferSize(nDataLength + 1);

	strcpy(szData,str);
}

//////////////////////////////////////////////////////////////////////////
//  Increase Buffer Size
//


void CDString::IncreaseBufferSize(int size)
{
	SeperateFromRef();

	int newsize = nDataBufferSize;
	while(newsize < size)
		newsize += nGrowBy;

	char* str = new char[newsize];
	memcpy(str,szData,nDataBufferSize);

	delete[] szData;
	szData = str;
	nDataBufferSize = newsize;
}

void CDString::SeperateFromRef()
{
	if(*pRefCount <= 1) return;
	(*pRefCount)--;

	int temp = nGrowBy;
	Construct(szData);
	nGrowBy = temp;
}

//////////////////////////////////////////////////////////////////////////
//  Buffer Retrieval

LPSTR CDString::GetBuffer(int musthavesize)
{
	SeperateFromRef();

	if(musthavesize >= nDataBufferSize)
		IncreaseBufferSize(musthavesize + 1);

	return szData;
}

void CDString::ReleaseBuffer()
{
	nDataLength = strlen(szData);
}

//////////////////////////////////////////////////////////////////////////
//  Formatting
void CDString::Format(const char* pszFormat, ...) 
{ 
	va_list list; 
	va_start(list, pszFormat);
	FormatV(pszFormat, list);
	va_end(list);
}

void CDString::FormatV(const char* pszFormat, va_list list) 
{ 
	SeperateFromRef();
	nDataLength = _vscprintf(pszFormat, list); 
	if(nDataLength >= nDataBufferSize) 
		IncreaseBufferSize(nDataLength + 1); 
	vsprintf(szData, pszFormat, list); 
}

void CDString::AppendFormat(const char* pszFormat, ...)
{
	va_list list;
	va_start(list,pszFormat);
	AppendFormatV(pszFormat,list);
	va_end(list);
}

void CDString::AppendFormatV(const char* pszFormat, va_list list)
{
	SeperateFromRef();

	int len = nDataLength + _vscprintf(pszFormat, list);

	if(len >= nDataBufferSize) 
		IncreaseBufferSize(len + 1);

	vsprintf(&szData[nDataLength], pszFormat, list);
	nDataLength = len;
}

//////////////////////////////////////////////////////////////////////////
//  Clipping and searching
CDString CDString::Left(int count)
{
	CDString ret(szData);
	if(count >= nDataLength)
		return ret;

	ret.szData[count] = 0;
	ret.nDataLength = count;

	return ret;
}

CDString CDString::Mid(int section)
{
	if(section <= 0)			return szData;
	if(section >= nDataLength)	return "";

	return &(szData[section]);
}

int CDString::ReverseFind(char ch)
{
	int find;
	for(find = nDataLength - 1; find >= 0; find--)
	{
		if(szData[find] == ch)
			break;
	}
	return find;
}

void CDString::Replace(LPCSTR find,LPCSTR replace)
{
	SeperateFromRef();

	int len = strlen(find);
	if(!len)	return;

	int dif = strlen(replace) - len;
	int last = nDataLength - len;
	char temp;
	int cmp;

	CDString tempstr;

	for(int i = 0; i <= last; i++)
	{
		temp = szData[i + len];
		szData[i + len] = 0;
		cmp = strcmp(&szData[i],find);
		szData[i + len] = temp;

		if(!cmp)
		{
			tempstr = Left(i) + replace;
			if(i < last) tempstr += (&szData[i + len]);
			i += dif;
			last += dif;
			Set(tempstr);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//  Extra stuff

CDString operator + (const CDString& str1,LPCSTR str2)
{
	CDString str(str1);
	str.Append(str2);
	return str;
}

void CDString::operator = (CDString& str)
{
	if(*pRefCount <= 1)
	{
		delete pRefCount;
		delete[] szData;
	}
	else
		SeperateFromRef();

	pRefCount = str.pRefCount;
	szData = str.szData;
	nDataLength = str.nDataLength;
	nDataBufferSize = str.nDataBufferSize;
	(*pRefCount)++;
}