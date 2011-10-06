#include "Assert.h"

///
///	Debug functions and macros
///
#ifdef __DEBUG__
#define DebugExec(func) func
#define DebugField(fieldType,fieldName) fieldType fieldName
#define DebugAssertTrue(expr) Assert::True(expr);
#define DebugAssertFalse(expr) Assert::False(expr);
#define DebugAssertNotNull(value) Assert::True(value != NULL);
#define DebugAssertNotEquals(value1,value2) Assert::NotEquals((void*)value1,(void*)value2);
#define DebugMethod(retType,name,code) retType name() {code}
#define DebugAssertEquals(expected,value) Assert::Equals(expected,value)
#define DebugAssertEqualsP(type,expected,value) Assert::Equals<type*>(expected,value)
#define DebugAssertNotEqualsP(type,expected,value) Assert::NotEquals<type*>(expected,value)
#define DebugAssertFail() Assert::Fail();
#else
#define DebugExec(func)
#define DebugField(fieldType,fieldName)
#define DebugAssertTrue(expr)
#define DebugAssertFalse(expr)
#define DebugAssertNotNull(value)
#define DebugAssertNotEquals(value1,value2)
#define DebugMethod(retType,name,code)
#define DebugAssertEquals(expected,value)
#define DebugAssertEqualsP(type,expected,value)
#define DebugAssertNotEqualsP(type,expected,value)
#define DebugAssertFail()
#endif
