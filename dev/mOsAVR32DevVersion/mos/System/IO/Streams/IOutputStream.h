#pragma once

#include "SystemTypes.h"


class IOutputStream
{
public:
	virtual void Write(U8 data) = 0;
	virtual void Write(U16 data) = 0;
	virtual void Write(U32 data) = 0;


	virtual void Write(const char* str) = 0;

	template <class T>
	void Write(T* buf,U32 size)
	{
		for(int i = 0; i < size; ++i,buf++)
		{
			Write(*buf);
		}

	}
	virtual void Write(S8 data) = 0;
	virtual void Write(S16 data) = 0;
	virtual void Write(S32 data) = 0;

};
