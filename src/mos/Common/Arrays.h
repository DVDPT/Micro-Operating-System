#pragma once


class Arrays
{
public:
	template<typename T, int size>
	static S32 Length(T(&)[size]){return size;}
};
