#pragma once

#include "IOutputStream.h"
#include "Debug.h"
#include "Bits.h"

class TextOutputStream : public IOutputStream
{
public:
	void Write(U16 data);
	void Write(U32 data);
	void Write(const char* str);

	void Write(S8 data);
	void Write(S16 data);
	void Write(S32 data);

};
