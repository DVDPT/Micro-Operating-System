#pragma once

#include "SystemTypes.h"

class IOutputStream
{
public:
	void WriteByte(U8 data) = 0;
	void WriteShort(U16 data) = 0;
	void WriteInt(U32 data) = 0;
	void WriteString(const U8* str) = 0;

	void Write(U8* buf,U32 size)
	{
		for(int i = 0; i < size; ++i,buf++)
		{
			WriteByte(*buf);
		}
	}

};
