//
// Created by Gautham Banasandra on 2019-01-31.
//

#ifndef FUNCTION_H
#define FUNCTION_H

#include <string>

#include "evaluator.pb.h"

using LibraryID = std::string;

struct Library {
  Library(const nftp::Library *library)
      : id(library->id()), code(library->code()) {}

  LibraryID id;
  std::string code;
};

struct EvaluateRequest {
  EvaluateRequest(const nftp::EvaluateRequest *request)
      : library_id(request->libraryid()),
        function_name(request->functionname()), thread_id(request->threadid()) {
  }

  LibraryID library_id;
  std::string function_name;
  std::string thread_id;
};

#endif // FUNCTION_H
