#pragma once

#include "IOutputStream.h"


class BufferedStream : public IOutputStream
{

	void WriteShort(U16 data) = 0;
	void WriteInt(U32 data) = 0;
	void WriteString(const U8* str) = 0;


};
