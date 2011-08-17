#include "Assert.h"

///
///	Debug functions and macros
///
#ifdef __DEBUG__
#define DebugExec(func) func
#define DebugField(fieldType,fieldName) fieldType fieldName
#define DebugAssertTrue(expr) Assert::True(expr)
#define DebugAssertNotNull(value) Assert::True(value != NULL);
#define DebugAssertNotEquals(value1,value2) Assert::NotEquals((void*)value1,(void*)value2);
#define DebugMethod(retType,name,code) retType name() {code}
#define DebugAssertEquals(expected,value) Assert::Equals(expected,value)
#define DebugAssertEqualsP(type,expected,value) Assert::Equals<type*>(expected,value)

#else
#define DebugExec(x)
#define DebugField(fieldType,fieldName)
#define DebugAssertTrue(expr)
#define DebugMethod(retType,name,code)
#define DebugAssertNotNull(value)
#define DebugAssertNotEquals(value1,value2)
#define DebugAssertEquals(expected,value)
DebugAssertEqualsT(type,expected,value)
#endif
