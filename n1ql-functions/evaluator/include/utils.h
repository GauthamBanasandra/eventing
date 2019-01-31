//
// Created by Gautham Banasandra on 2019-01-31.
//

#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <v8.h>

#define TO(maybe, local)                                                       \
  (To((maybe), (local), __FILE__, __FUNCTION__, __LINE__))
#define TO_LOCAL(maybe, local)                                                 \
  (ToLocal((maybe), (local), __FILE__, __FUNCTION__, __LINE__))

template <typename T>
bool To(const v8::Maybe<T> &from, T *to, const char *file = "",
        const char *caller = "", int line = -1) {
  if (from.To(to)) {
    return true;
  }

  std::cout << "file : " << file << " line : " << line << " caller : " << caller
            << " : Returning empty value";
  return false;
}

template <typename T>
bool ToLocal(const v8::MaybeLocal<T> &from, v8::Local<T> *to,
             const char *file = "", const char *caller = "", int line = -1) {
  if (from.ToLocal(to)) {
    return true;
  }

  std::cout << "file : " << file << " line : " << line << " caller : " << caller
            << " : Returning empty value" << std::endl;
  return false;
}

#endif // UTILS_H
