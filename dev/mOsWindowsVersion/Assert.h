#pragma once

#include "SystemTypes.h"
#include <stdio.h>
class Assert
{
public:

	static Void NotEquals(void * expected, void * value)
	{
		printf("NOT EQUALS %s", expected == value ? "FALSE": "TRUE");
	}

	static Void Equals(void * expected, void* value)
	{
		printf("EQUALS %s", expected != value ? "FALSE": "TRUE");
	}
};