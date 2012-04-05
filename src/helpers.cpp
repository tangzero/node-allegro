#include "helpers.h" 

static Persistent<ObjectTemplate> pointer_template;

Handle<Object> WrapPointer(void *pointer) {
  HandleScope scope;

  if (pointer_template.IsEmpty()) {
    Handle<ObjectTemplate> raw_template = ObjectTemplate::New();
    raw_template->SetInternalFieldCount(1);
    pointer_template = Persistent<ObjectTemplate>::New(raw_template);
  }
  
  Handle<Object> result = pointer_template->NewInstance();
  result->SetInternalField(0, External::New(pointer));

  return scope.Close(result);
}

void* UnwrapPointer(Handle<Object> object) {
  return Handle<External>::Cast(object->GetInternalField(0))->Value();
}