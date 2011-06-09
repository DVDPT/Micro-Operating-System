#pragma once

#include "SystemTypes.h"
class Assert
{
public:

	static Void NotEquals(void * expected, void * value);

	static Void Equals(void * expected, void* value);
};
