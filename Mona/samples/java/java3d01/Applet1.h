// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __Applet1__
#define __Applet1__

#pragma interface

#include <java/lang/Object.h>
#include <gcj/array.h>

extern "Java"
{
  class Applet1;
  class Vector;
}

class Applet1 : public ::java::lang::Object
{
public:
  virtual void init ();
  virtual void run ();
  virtual void stop () { }
  virtual void MainLoop ();
  static void main (JArray< ::java::lang::String *> *);
  Applet1 ();
public: // actually package-private
  static const jint SCREENW = 320L;
  static const jint SCREENH = 200L;
  static const jint FRAMERATE = 10L;
  static const jint DETAILLEVEL = 32L;
  jfloat __attribute__((aligned(__alignof__( ::java::lang::Object ))))  rx;
  jfloat ry;
  jfloat rz;
  JArray< ::Vector *> *vertices;
  jintArray pbuf;
public:

  static ::java::lang::Class class$;
};

#endif /* __Applet1__ */
