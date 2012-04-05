#include "helpers.h" 
#include <allegro5/allegro.h>

#include <v8.h>
#include <node.h>

using namespace node;
using namespace v8;

static Persistent<Function> main;

static Handle<Value> init(const Arguments& args) {
  HandleScope scope;
  return scope.Close(Boolean::New(al_init()));
}

static Handle<Value> create_display(const Arguments& args) {
  HandleScope scope;

  if ((args.Length() != 2) && !(args[0]->IsNumber() && !args[1]->IsNumber())) {
    return ThrowException(Exception::TypeError(
      String::New("Invalid arguments: Expected create_display(Number, Number)")));
  }

  ALLEGRO_DISPLAY *display = al_create_display(args[0]->Int32Value(), args[1]->Int32Value());
  return scope.Close(WrapPointer(display));
}

static Handle<Value> set_window_title(const Arguments& args) {
  if ((args.Length() != 2) && (!args[0]->IsObject()) && (!args[1]->IsString())) {
    return ThrowException(Exception::TypeError(
      String::New("Invalid arguments: Expected set_window_title(Object, String)")));
  }

  ALLEGRO_DISPLAY *display = (ALLEGRO_DISPLAY*) UnwrapPointer(args[0]->ToObject());
  String::Utf8Value title(args[1]);
  al_set_window_title(display, *title);
  return Undefined();
}

static Handle<Value> flip_display(const Arguments& args) {
  al_flip_display();
  return Undefined();
}

static Handle<Value> clear_to_color(const Arguments& args) {
  al_clear_to_color(al_map_rgb(args[0]->Int32Value(), args[1]->Int32Value(), args[2]->Int32Value()));
  return Undefined();
}

int user_main(int argv, char** argc) {
  main->Call(Context::GetCurrent()->Global(), 0, NULL);
  return 1;
}

static Handle<Value> run_main(const Arguments& args) {
  main = Persistent<Function>::New(Local<Function>::Cast(args[0]));
  return Boolean::New(al_run_main(0, NULL, &user_main));
}

extern "C" {
  static void init(Handle<Object> target) {
    NODE_SET_METHOD(target, "init", init);
    NODE_SET_METHOD(target, "create_display", create_display);
    NODE_SET_METHOD(target, "set_window_title", set_window_title);
    NODE_SET_METHOD(target, "flip_display", flip_display);
    NODE_SET_METHOD(target, "clear_to_color", clear_to_color);
    NODE_SET_METHOD(target, "run_main", run_main);
  }

  NODE_MODULE(allegro, init);
}