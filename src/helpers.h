#ifndef __HELPERS_H__
#define __HELPERS_H__

#include <v8.h>
#include <node.h>

using namespace node;
using namespace v8;

Handle<Object> WrapPointer(void *pointer);
void* UnwrapPointer(Handle<Object> object);

#endif // __HELPERS_H__