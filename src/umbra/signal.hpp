/*
 *  Signal.h
 *  CoreGame
 *  A lightweight signals and slots implementation using fast delegates
 *
 *  Created by Patrick Hogan on 5/18/09.
 *
 */
#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include <set>

#include "delegate.hpp"

template <class Param0 = void>
class Signal0 {
 public:
  typedef Delegate0<void> _Delegate;

 private:
  typedef std::set<_Delegate> DelegateList;
  typedef typename DelegateList::iterator DelegateIterator;
  DelegateList delegateList;

 public:
  void connect(_Delegate delegate) { delegateList.insert(delegate); }

  template <class X, class Y>
  void connect(Y* obj, void (X::*func)()) {
    delegateList.insert(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void connect(Y* obj, void (X::*func)() const) {
    delegateList.insert(MakeDelegate(obj, func));
  }

  void disconnect(_Delegate delegate) { delegateList.erase(delegate); }

  template <class X, class Y>
  void disconnect(Y* obj, void (X::*func)()) {
    delegateList.erase(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void disconnect(Y* obj, void (X::*func)() const) {
    delegateList.erase(MakeDelegate(obj, func));
  }

  void emit() const {
    for (DelegateIterator i = delegateList.begin(); i != delegateList.end(); ++i) {
      (*i)();
    }
  }

  void operator()() const { emit(); }
};

template <class Param1>
class Signal1 {
 public:
  typedef Delegate1<Param1> _Delegate;

 private:
  typedef std::set<_Delegate> DelegateList;
  typedef typename DelegateList::iterator DelegateIterator;
  DelegateList delegateList;

 public:
  void connect(_Delegate delegate) { delegateList.insert(delegate); }

  template <class X, class Y>
  void connect(Y* obj, void (X::*func)(Param1 p1)) {
    delegateList.insert(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void connect(Y* obj, void (X::*func)(Param1 p1) const) {
    delegateList.insert(MakeDelegate(obj, func));
  }

  void disconnect(_Delegate delegate) { delegateList.erase(delegate); }

  template <class X, class Y>
  void disconnect(Y* obj, void (X::*func)(Param1 p1)) {
    delegateList.erase(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void disconnect(Y* obj, void (X::*func)(Param1 p1) const) {
    delegateList.erase(MakeDelegate(obj, func));
  }

  void emit(Param1 p1) const {
    for (DelegateIterator i = delegateList.begin(); i != delegateList.end(); ++i) {
      (*i)(p1);
    }
  }

  void operator()(Param1 p1) const { emit(p1); }
};

template <class Param1, class Param2>
class Signal2 {
 public:
  typedef Delegate2<Param1, Param2> _Delegate;

 private:
  typedef std::set<_Delegate> DelegateList;
  typedef typename DelegateList::iterator DelegateIterator;
  DelegateList delegateList;

 public:
  void connect(_Delegate delegate) { delegateList.insert(delegate); }

  template <class X, class Y>
  void connect(Y* obj, void (X::*func)(Param1 p1, Param2 p2)) {
    delegateList.insert(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void connect(Y* obj, void (X::*func)(Param1 p1, Param2 p2) const) {
    delegateList.insert(MakeDelegate(obj, func));
  }

  void disconnect(_Delegate delegate) { delegateList.erase(delegate); }

  template <class X, class Y>
  void disconnect(Y* obj, void (X::*func)(Param1 p1, Param2 p2)) {
    delegateList.erase(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void disconnect(Y* obj, void (X::*func)(Param1 p1, Param2 p2) const) {
    delegateList.erase(MakeDelegate(obj, func));
  }

  void emit(Param1 p1, Param2 p2) const {
    for (DelegateIterator i = delegateList.begin(); i != delegateList.end(); ++i) {
      (*i)(p1, p2);
    }
  }

  void operator()(Param1 p1, Param2 p2) const { emit(p1, p2); }
};

template <class Param1, class Param2, class Param3>
class Signal3 {
 public:
  typedef Delegate3<Param1, Param2, Param3> _Delegate;

 private:
  typedef std::set<_Delegate> DelegateList;
  typedef typename DelegateList::iterator DelegateIterator;
  DelegateList delegateList;

 public:
  void connect(_Delegate delegate) { delegateList.insert(delegate); }

  template <class X, class Y>
  void connect(Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3)) {
    delegateList.insert(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void connect(Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3) const) {
    delegateList.insert(MakeDelegate(obj, func));
  }

  void disconnect(_Delegate delegate) { delegateList.erase(delegate); }

  template <class X, class Y>
  void disconnect(Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3)) {
    delegateList.erase(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void disconnect(Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3) const) {
    delegateList.erase(MakeDelegate(obj, func));
  }

  void emit(Param1 p1, Param2 p2, Param3 p3) const {
    for (DelegateIterator i = delegateList.begin(); i != delegateList.end(); ++i) {
      (*i)(p1, p2, p3);
    }
  }

  void operator()(Param1 p1, Param2 p2, Param3 p3) const { emit(p1, p2, p3); }
};

template <class Param1, class Param2, class Param3, class Param4>
class Signal4 {
 public:
  typedef Delegate4<Param1, Param2, Param3, Param4> _Delegate;

 private:
  typedef std::set<_Delegate> DelegateList;
  typedef typename DelegateList::iterator DelegateIterator;
  DelegateList delegateList;

 public:
  void connect(_Delegate delegate) { delegateList.insert(delegate); }

  template <class X, class Y>
  void connect(Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4)) {
    delegateList.insert(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void connect(Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4) const) {
    delegateList.insert(MakeDelegate(obj, func));
  }

  void disconnect(_Delegate delegate) { delegateList.erase(delegate); }

  template <class X, class Y>
  void disconnect(Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4)) {
    delegateList.erase(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void disconnect(Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4) const) {
    delegateList.erase(MakeDelegate(obj, func));
  }

  void emit(Param1 p1, Param2 p2, Param3 p3, Param4 p4) const {
    for (DelegateIterator i = delegateList.begin(); i != delegateList.end(); ++i) {
      (*i)(p1, p2, p3, p4);
    }
  }

  void operator()(Param1 p1, Param2 p2, Param3 p3, Param4 p4) const { emit(p1, p2, p3, p4); }
};

template <class Param1, class Param2, class Param3, class Param4, class Param5>
class Signal5 {
 public:
  typedef Delegate5<Param1, Param2, Param3, Param4, Param5> _Delegate;

 private:
  typedef std::set<_Delegate> DelegateList;
  typedef typename DelegateList::iterator DelegateIterator;
  DelegateList delegateList;

 public:
  void connect(_Delegate delegate) { delegateList.insert(delegate); }

  template <class X, class Y>
  void connect(Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)) {
    delegateList.insert(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void connect(Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const) {
    delegateList.insert(MakeDelegate(obj, func));
  }

  void disconnect(_Delegate delegate) { delegateList.erase(delegate); }

  template <class X, class Y>
  void disconnect(Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5)) {
    delegateList.erase(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void disconnect(Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const) {
    delegateList.erase(MakeDelegate(obj, func));
  }

  void emit(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const {
    for (DelegateIterator i = delegateList.begin(); i != delegateList.end(); ++i) {
      (*i)(p1, p2, p3, p4, p5);
    }
  }

  void operator()(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5) const { emit(p1, p2, p3, p4, p5); }
};

template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6>
class Signal6 {
 public:
  typedef Delegate6<Param1, Param2, Param3, Param4, Param5, Param6> _Delegate;

 private:
  typedef std::set<_Delegate> DelegateList;
  typedef typename DelegateList::iterator DelegateIterator;
  DelegateList delegateList;

 public:
  void connect(_Delegate delegate) { delegateList.insert(delegate); }

  template <class X, class Y>
  void connect(Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6)) {
    delegateList.insert(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void connect(Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const) {
    delegateList.insert(MakeDelegate(obj, func));
  }

  void disconnect(_Delegate delegate) { delegateList.erase(delegate); }

  template <class X, class Y>
  void disconnect(Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6)) {
    delegateList.erase(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void disconnect(Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const) {
    delegateList.erase(MakeDelegate(obj, func));
  }

  void emit(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const {
    for (DelegateIterator i = delegateList.begin(); i != delegateList.end(); ++i) {
      (*i)(p1, p2, p3, p4, p5, p6);
    }
  }

  void operator()(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6) const {
    emit(p1, p2, p3, p4, p5, p6);
  }
};

template <class Param1, class Param2, class Param3, class Param4, class Param5, class Param6, class Param7>
class Signal7 {
 public:
  typedef Delegate7<Param1, Param2, Param3, Param4, Param5, Param6, Param7> _Delegate;

 private:
  typedef std::set<_Delegate> DelegateList;
  typedef typename DelegateList::iterator DelegateIterator;
  DelegateList delegateList;

 public:
  void connect(_Delegate delegate) { delegateList.insert(delegate); }

  template <class X, class Y>
  void connect(Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7)) {
    delegateList.insert(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void connect(
      Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) const) {
    delegateList.insert(MakeDelegate(obj, func));
  }

  void disconnect(_Delegate delegate) { delegateList.erase(delegate); }

  template <class X, class Y>
  void disconnect(
      Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7)) {
    delegateList.erase(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void disconnect(
      Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) const) {
    delegateList.erase(MakeDelegate(obj, func));
  }

  void emit(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) const {
    for (DelegateIterator i = delegateList.begin(); i != delegateList.end(); ++i) {
      (*i)(p1, p2, p3, p4, p5, p6, p7);
    }
  }

  void operator()(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7) const {
    emit(p1, p2, p3, p4, p5, p6, p7);
  }
};

template <
    class Param1,
    class Param2,
    class Param3,
    class Param4,
    class Param5,
    class Param6,
    class Param7,
    class Param8>
class Signal8 {
 public:
  typedef Delegate8<Param1, Param2, Param3, Param4, Param5, Param6, Param7, Param8> _Delegate;

 private:
  typedef std::set<_Delegate> DelegateList;
  typedef typename DelegateList::iterator DelegateIterator;
  DelegateList delegateList;

 public:
  void connect(_Delegate delegate) { delegateList.insert(delegate); }

  template <class X, class Y>
  void connect(
      Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8)) {
    delegateList.insert(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void connect(
      Y* obj,
      void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) const) {
    delegateList.insert(MakeDelegate(obj, func));
  }

  void disconnect(_Delegate delegate) { delegateList.erase(delegate); }

  template <class X, class Y>
  void disconnect(
      Y* obj, void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8)) {
    delegateList.erase(MakeDelegate(obj, func));
  }

  template <class X, class Y>
  void disconnect(
      Y* obj,
      void (X::*func)(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) const) {
    delegateList.erase(MakeDelegate(obj, func));
  }

  void emit(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) const {
    for (DelegateIterator i = delegateList.begin(); i != delegateList.end(); ++i) {
      (*i)(p1, p2, p3, p4, p5, p6, p7, p8);
    }
  }

  void operator()(Param1 p1, Param2 p2, Param3 p3, Param4 p4, Param5 p5, Param6 p6, Param7 p7, Param8 p8) const {
    emit(p1, p2, p3, p4, p5, p6, p7, p8);
  }
};

#endif  //_SIGNAL_H_
