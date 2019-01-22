// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: evaluator.proto

#ifndef PROTOBUF_INCLUDED_evaluator_2eproto
#define PROTOBUF_INCLUDED_evaluator_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_evaluator_2eproto 

namespace protobuf_evaluator_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[4];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_evaluator_2eproto
namespace nftp {
class Config;
class ConfigDefaultTypeInternal;
extern ConfigDefaultTypeInternal _Config_default_instance_;
class Info;
class InfoDefaultTypeInternal;
extern InfoDefaultTypeInternal _Info_default_instance_;
class Port;
class PortDefaultTypeInternal;
extern PortDefaultTypeInternal _Port_default_instance_;
class Void;
class VoidDefaultTypeInternal;
extern VoidDefaultTypeInternal _Void_default_instance_;
}  // namespace nftp
namespace google {
namespace protobuf {
template<> ::nftp::Config* Arena::CreateMaybeMessage<::nftp::Config>(Arena*);
template<> ::nftp::Info* Arena::CreateMaybeMessage<::nftp::Info>(Arena*);
template<> ::nftp::Port* Arena::CreateMaybeMessage<::nftp::Port>(Arena*);
template<> ::nftp::Void* Arena::CreateMaybeMessage<::nftp::Void>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace nftp {

// ===================================================================

class Config : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:nftp.Config) */ {
 public:
  Config();
  virtual ~Config();

  Config(const Config& from);

  inline Config& operator=(const Config& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Config(Config&& from) noexcept
    : Config() {
    *this = ::std::move(from);
  }

  inline Config& operator=(Config&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Config& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Config* internal_default_instance() {
    return reinterpret_cast<const Config*>(
               &_Config_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(Config* other);
  friend void swap(Config& a, Config& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Config* New() const final {
    return CreateMaybeMessage<Config>(NULL);
  }

  Config* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Config>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Config& from);
  void MergeFrom(const Config& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Config* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string NsServerUrl = 3;
  void clear_nsserverurl();
  static const int kNsServerUrlFieldNumber = 3;
  const ::std::string& nsserverurl() const;
  void set_nsserverurl(const ::std::string& value);
  #if LANG_CXX11
  void set_nsserverurl(::std::string&& value);
  #endif
  void set_nsserverurl(const char* value);
  void set_nsserverurl(const char* value, size_t size);
  ::std::string* mutable_nsserverurl();
  ::std::string* release_nsserverurl();
  void set_allocated_nsserverurl(::std::string* nsserverurl);

  // uint32 WorkersPerNode = 1;
  void clear_workerspernode();
  static const int kWorkersPerNodeFieldNumber = 1;
  ::google::protobuf::uint32 workerspernode() const;
  void set_workerspernode(::google::protobuf::uint32 value);

  // uint32 ThreadsPerWorker = 2;
  void clear_threadsperworker();
  static const int kThreadsPerWorkerFieldNumber = 2;
  ::google::protobuf::uint32 threadsperworker() const;
  void set_threadsperworker(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:nftp.Config)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr nsserverurl_;
  ::google::protobuf::uint32 workerspernode_;
  ::google::protobuf::uint32 threadsperworker_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_evaluator_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Info : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:nftp.Info) */ {
 public:
  Info();
  virtual ~Info();

  Info(const Info& from);

  inline Info& operator=(const Info& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Info(Info&& from) noexcept
    : Info() {
    *this = ::std::move(from);
  }

  inline Info& operator=(Info&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Info& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Info* internal_default_instance() {
    return reinterpret_cast<const Info*>(
               &_Info_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(Info* other);
  friend void swap(Info& a, Info& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Info* New() const final {
    return CreateMaybeMessage<Info>(NULL);
  }

  Info* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Info>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Info& from);
  void MergeFrom(const Info& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Info* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string Message = 2;
  void clear_message();
  static const int kMessageFieldNumber = 2;
  const ::std::string& message() const;
  void set_message(const ::std::string& value);
  #if LANG_CXX11
  void set_message(::std::string&& value);
  #endif
  void set_message(const char* value);
  void set_message(const char* value, size_t size);
  ::std::string* mutable_message();
  ::std::string* release_message();
  void set_allocated_message(::std::string* message);

  // bool IsFatal = 1;
  void clear_isfatal();
  static const int kIsFatalFieldNumber = 1;
  bool isfatal() const;
  void set_isfatal(bool value);

  // @@protoc_insertion_point(class_scope:nftp.Info)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr message_;
  bool isfatal_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_evaluator_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Void : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:nftp.Void) */ {
 public:
  Void();
  virtual ~Void();

  Void(const Void& from);

  inline Void& operator=(const Void& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Void(Void&& from) noexcept
    : Void() {
    *this = ::std::move(from);
  }

  inline Void& operator=(Void&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Void& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Void* internal_default_instance() {
    return reinterpret_cast<const Void*>(
               &_Void_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  void Swap(Void* other);
  friend void swap(Void& a, Void& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Void* New() const final {
    return CreateMaybeMessage<Void>(NULL);
  }

  Void* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Void>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Void& from);
  void MergeFrom(const Void& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Void* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // @@protoc_insertion_point(class_scope:nftp.Void)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_evaluator_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class Port : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:nftp.Port) */ {
 public:
  Port();
  virtual ~Port();

  Port(const Port& from);

  inline Port& operator=(const Port& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  Port(Port&& from) noexcept
    : Port() {
    *this = ::std::move(from);
  }

  inline Port& operator=(Port&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const Port& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Port* internal_default_instance() {
    return reinterpret_cast<const Port*>(
               &_Port_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  void Swap(Port* other);
  friend void swap(Port& a, Port& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline Port* New() const final {
    return CreateMaybeMessage<Port>(NULL);
  }

  Port* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<Port>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const Port& from);
  void MergeFrom(const Port& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Port* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string EvaluatorId = 1;
  void clear_evaluatorid();
  static const int kEvaluatorIdFieldNumber = 1;
  const ::std::string& evaluatorid() const;
  void set_evaluatorid(const ::std::string& value);
  #if LANG_CXX11
  void set_evaluatorid(::std::string&& value);
  #endif
  void set_evaluatorid(const char* value);
  void set_evaluatorid(const char* value, size_t size);
  ::std::string* mutable_evaluatorid();
  ::std::string* release_evaluatorid();
  void set_allocated_evaluatorid(::std::string* evaluatorid);

  // uint32 Port = 2;
  void clear_port();
  static const int kPortFieldNumber = 2;
  ::google::protobuf::uint32 port() const;
  void set_port(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:nftp.Port)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr evaluatorid_;
  ::google::protobuf::uint32 port_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_evaluator_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Config

// uint32 WorkersPerNode = 1;
inline void Config::clear_workerspernode() {
  workerspernode_ = 0u;
}
inline ::google::protobuf::uint32 Config::workerspernode() const {
  // @@protoc_insertion_point(field_get:nftp.Config.WorkersPerNode)
  return workerspernode_;
}
inline void Config::set_workerspernode(::google::protobuf::uint32 value) {
  
  workerspernode_ = value;
  // @@protoc_insertion_point(field_set:nftp.Config.WorkersPerNode)
}

// uint32 ThreadsPerWorker = 2;
inline void Config::clear_threadsperworker() {
  threadsperworker_ = 0u;
}
inline ::google::protobuf::uint32 Config::threadsperworker() const {
  // @@protoc_insertion_point(field_get:nftp.Config.ThreadsPerWorker)
  return threadsperworker_;
}
inline void Config::set_threadsperworker(::google::protobuf::uint32 value) {
  
  threadsperworker_ = value;
  // @@protoc_insertion_point(field_set:nftp.Config.ThreadsPerWorker)
}

// string NsServerUrl = 3;
inline void Config::clear_nsserverurl() {
  nsserverurl_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Config::nsserverurl() const {
  // @@protoc_insertion_point(field_get:nftp.Config.NsServerUrl)
  return nsserverurl_.GetNoArena();
}
inline void Config::set_nsserverurl(const ::std::string& value) {
  
  nsserverurl_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:nftp.Config.NsServerUrl)
}
#if LANG_CXX11
inline void Config::set_nsserverurl(::std::string&& value) {
  
  nsserverurl_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:nftp.Config.NsServerUrl)
}
#endif
inline void Config::set_nsserverurl(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  nsserverurl_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:nftp.Config.NsServerUrl)
}
inline void Config::set_nsserverurl(const char* value, size_t size) {
  
  nsserverurl_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:nftp.Config.NsServerUrl)
}
inline ::std::string* Config::mutable_nsserverurl() {
  
  // @@protoc_insertion_point(field_mutable:nftp.Config.NsServerUrl)
  return nsserverurl_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Config::release_nsserverurl() {
  // @@protoc_insertion_point(field_release:nftp.Config.NsServerUrl)
  
  return nsserverurl_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Config::set_allocated_nsserverurl(::std::string* nsserverurl) {
  if (nsserverurl != NULL) {
    
  } else {
    
  }
  nsserverurl_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), nsserverurl);
  // @@protoc_insertion_point(field_set_allocated:nftp.Config.NsServerUrl)
}

// -------------------------------------------------------------------

// Info

// bool IsFatal = 1;
inline void Info::clear_isfatal() {
  isfatal_ = false;
}
inline bool Info::isfatal() const {
  // @@protoc_insertion_point(field_get:nftp.Info.IsFatal)
  return isfatal_;
}
inline void Info::set_isfatal(bool value) {
  
  isfatal_ = value;
  // @@protoc_insertion_point(field_set:nftp.Info.IsFatal)
}

// string Message = 2;
inline void Info::clear_message() {
  message_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Info::message() const {
  // @@protoc_insertion_point(field_get:nftp.Info.Message)
  return message_.GetNoArena();
}
inline void Info::set_message(const ::std::string& value) {
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:nftp.Info.Message)
}
#if LANG_CXX11
inline void Info::set_message(::std::string&& value) {
  
  message_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:nftp.Info.Message)
}
#endif
inline void Info::set_message(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:nftp.Info.Message)
}
inline void Info::set_message(const char* value, size_t size) {
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:nftp.Info.Message)
}
inline ::std::string* Info::mutable_message() {
  
  // @@protoc_insertion_point(field_mutable:nftp.Info.Message)
  return message_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Info::release_message() {
  // @@protoc_insertion_point(field_release:nftp.Info.Message)
  
  return message_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Info::set_allocated_message(::std::string* message) {
  if (message != NULL) {
    
  } else {
    
  }
  message_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), message);
  // @@protoc_insertion_point(field_set_allocated:nftp.Info.Message)
}

// -------------------------------------------------------------------

// Void

// -------------------------------------------------------------------

// Port

// string EvaluatorId = 1;
inline void Port::clear_evaluatorid() {
  evaluatorid_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& Port::evaluatorid() const {
  // @@protoc_insertion_point(field_get:nftp.Port.EvaluatorId)
  return evaluatorid_.GetNoArena();
}
inline void Port::set_evaluatorid(const ::std::string& value) {
  
  evaluatorid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:nftp.Port.EvaluatorId)
}
#if LANG_CXX11
inline void Port::set_evaluatorid(::std::string&& value) {
  
  evaluatorid_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:nftp.Port.EvaluatorId)
}
#endif
inline void Port::set_evaluatorid(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  evaluatorid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:nftp.Port.EvaluatorId)
}
inline void Port::set_evaluatorid(const char* value, size_t size) {
  
  evaluatorid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:nftp.Port.EvaluatorId)
}
inline ::std::string* Port::mutable_evaluatorid() {
  
  // @@protoc_insertion_point(field_mutable:nftp.Port.EvaluatorId)
  return evaluatorid_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Port::release_evaluatorid() {
  // @@protoc_insertion_point(field_release:nftp.Port.EvaluatorId)
  
  return evaluatorid_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Port::set_allocated_evaluatorid(::std::string* evaluatorid) {
  if (evaluatorid != NULL) {
    
  } else {
    
  }
  evaluatorid_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), evaluatorid);
  // @@protoc_insertion_point(field_set_allocated:nftp.Port.EvaluatorId)
}

// uint32 Port = 2;
inline void Port::clear_port() {
  port_ = 0u;
}
inline ::google::protobuf::uint32 Port::port() const {
  // @@protoc_insertion_point(field_get:nftp.Port.Port)
  return port_;
}
inline void Port::set_port(::google::protobuf::uint32 value) {
  
  port_ = value;
  // @@protoc_insertion_point(field_set:nftp.Port.Port)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace nftp

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_evaluator_2eproto
