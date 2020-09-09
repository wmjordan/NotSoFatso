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
//  DFC_String.h
//



class CDString
{
protected:
	char*			szData;		//must be very first element, so that it can be fed into Format()

public:
	//construction
	CDString() { Construct(""); }
	CDString(LPCSTR str) { Construct(str); }
	CDString(const CDString& str);

	~CDString();

	//typecasting
	operator LPCSTR() const { return szData; }

	//assignment
	void Append(char ch);
	void Append(LPCSTR str);

	void Set(LPCSTR str);

	//section
	CDString		Mid(int section);
	CDString		Left(int count);

	//finding
	int				ReverseFind(char ch);
	void			Replace(LPCSTR find,LPCSTR replace);


	void operator += (char ch) { Append(ch); }
	void operator += (LPCSTR str) { Append(str); }
	void operator = (CDString& str);
	void operator = (LPCSTR str) {
		Set(str);
	}

	friend CDString operator + (const CDString& str1,LPCSTR str2);

	//comparison
	bool operator == (LPCSTR str) const { return !lstrcmp(szData,str); }

	//info
	int GetLength() const { return nDataLength; }

	//buffer retrieving
	LPSTR			GetBuffer(int musthavesize);
	void			ReleaseBuffer();

	//formatting
	void Format(const char* pszFormat, ...);
	void FormatV(const char* pszFormat, va_list list);
	void AppendFormat(const char* pszFormat, ...);
	void AppendFormatV(const char* pszFormat, va_list list);


protected:
	void			Construct(LPCSTR);
	void			IncreaseBufferSize(int size);
	void			SeperateFromRef();

	//data members
	int*			pRefCount;
	int				nDataBufferSize;
	int				nDataLength;
	int				nGrowBy;
};