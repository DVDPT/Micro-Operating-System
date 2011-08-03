#pragma once

#include "SystemTypes.h"
class Assert
{
public:

	static void NotEquals(void * expected, void * value);

	static void Equals(void * expected, void* value);

	static void True(bool expr);
};
