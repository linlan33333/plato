// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: cmdcontext.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_cmdcontext_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_cmdcontext_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3011000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3011000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_cmdcontext_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_cmdcontext_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_cmdcontext_2eproto;
namespace gateway {
class CmdContext;
class CmdContextDefaultTypeInternal;
extern CmdContextDefaultTypeInternal _CmdContext_default_instance_;
}  // namespace gateway
PROTOBUF_NAMESPACE_OPEN
template<> ::gateway::CmdContext* Arena::CreateMaybeMessage<::gateway::CmdContext>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace gateway {

enum CmdContext_CMD : int {
  CmdContext_CMD_DelConnCmd = 0,
  CmdContext_CMD_PushCmd = 1,
  CmdContext_CMD_CmdContext_CMD_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  CmdContext_CMD_CmdContext_CMD_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool CmdContext_CMD_IsValid(int value);
constexpr CmdContext_CMD CmdContext_CMD_CMD_MIN = CmdContext_CMD_DelConnCmd;
constexpr CmdContext_CMD CmdContext_CMD_CMD_MAX = CmdContext_CMD_PushCmd;
constexpr int CmdContext_CMD_CMD_ARRAYSIZE = CmdContext_CMD_CMD_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* CmdContext_CMD_descriptor();
template<typename T>
inline const std::string& CmdContext_CMD_Name(T enum_t_value) {
  static_assert(::std::is_same<T, CmdContext_CMD>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function CmdContext_CMD_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    CmdContext_CMD_descriptor(), enum_t_value);
}
inline bool CmdContext_CMD_Parse(
    const std::string& name, CmdContext_CMD* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<CmdContext_CMD>(
    CmdContext_CMD_descriptor(), name, value);
}
// ===================================================================

class CmdContext :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:gateway.CmdContext) */ {
 public:
  CmdContext();
  virtual ~CmdContext();

  CmdContext(const CmdContext& from);
  CmdContext(CmdContext&& from) noexcept
    : CmdContext() {
    *this = ::std::move(from);
  }

  inline CmdContext& operator=(const CmdContext& from) {
    CopyFrom(from);
    return *this;
  }
  inline CmdContext& operator=(CmdContext&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const CmdContext& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const CmdContext* internal_default_instance() {
    return reinterpret_cast<const CmdContext*>(
               &_CmdContext_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(CmdContext& a, CmdContext& b) {
    a.Swap(&b);
  }
  inline void Swap(CmdContext* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline CmdContext* New() const final {
    return CreateMaybeMessage<CmdContext>(nullptr);
  }

  CmdContext* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<CmdContext>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const CmdContext& from);
  void MergeFrom(const CmdContext& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(CmdContext* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "gateway.CmdContext";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_cmdcontext_2eproto);
    return ::descriptor_table_cmdcontext_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  typedef CmdContext_CMD CMD;
  static constexpr CMD DelConnCmd =
    CmdContext_CMD_DelConnCmd;
  static constexpr CMD PushCmd =
    CmdContext_CMD_PushCmd;
  static inline bool CMD_IsValid(int value) {
    return CmdContext_CMD_IsValid(value);
  }
  static constexpr CMD CMD_MIN =
    CmdContext_CMD_CMD_MIN;
  static constexpr CMD CMD_MAX =
    CmdContext_CMD_CMD_MAX;
  static constexpr int CMD_ARRAYSIZE =
    CmdContext_CMD_CMD_ARRAYSIZE;
  static inline const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor*
  CMD_descriptor() {
    return CmdContext_CMD_descriptor();
  }
  template<typename T>
  static inline const std::string& CMD_Name(T enum_t_value) {
    static_assert(::std::is_same<T, CMD>::value ||
      ::std::is_integral<T>::value,
      "Incorrect type passed to function CMD_Name.");
    return CmdContext_CMD_Name(enum_t_value);
  }
  static inline bool CMD_Parse(const std::string& name,
      CMD* value) {
    return CmdContext_CMD_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  enum : int {
    kPayloadFieldNumber = 3,
    kConnIDFieldNumber = 2,
    kCmdFieldNumber = 1,
  };
  // bytes Payload = 3;
  void clear_payload();
  const std::string& payload() const;
  void set_payload(const std::string& value);
  void set_payload(std::string&& value);
  void set_payload(const char* value);
  void set_payload(const void* value, size_t size);
  std::string* mutable_payload();
  std::string* release_payload();
  void set_allocated_payload(std::string* payload);
  private:
  const std::string& _internal_payload() const;
  void _internal_set_payload(const std::string& value);
  std::string* _internal_mutable_payload();
  public:

  // uint64 ConnID = 2;
  void clear_connid();
  ::PROTOBUF_NAMESPACE_ID::uint64 connid() const;
  void set_connid(::PROTOBUF_NAMESPACE_ID::uint64 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint64 _internal_connid() const;
  void _internal_set_connid(::PROTOBUF_NAMESPACE_ID::uint64 value);
  public:

  // .gateway.CmdContext.CMD Cmd = 1;
  void clear_cmd();
  ::gateway::CmdContext_CMD cmd() const;
  void set_cmd(::gateway::CmdContext_CMD value);
  private:
  ::gateway::CmdContext_CMD _internal_cmd() const;
  void _internal_set_cmd(::gateway::CmdContext_CMD value);
  public:

  // @@protoc_insertion_point(class_scope:gateway.CmdContext)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr payload_;
  ::PROTOBUF_NAMESPACE_ID::uint64 connid_;
  int cmd_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_cmdcontext_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// CmdContext

// .gateway.CmdContext.CMD Cmd = 1;
inline void CmdContext::clear_cmd() {
  cmd_ = 0;
}
inline ::gateway::CmdContext_CMD CmdContext::_internal_cmd() const {
  return static_cast< ::gateway::CmdContext_CMD >(cmd_);
}
inline ::gateway::CmdContext_CMD CmdContext::cmd() const {
  // @@protoc_insertion_point(field_get:gateway.CmdContext.Cmd)
  return _internal_cmd();
}
inline void CmdContext::_internal_set_cmd(::gateway::CmdContext_CMD value) {
  
  cmd_ = value;
}
inline void CmdContext::set_cmd(::gateway::CmdContext_CMD value) {
  _internal_set_cmd(value);
  // @@protoc_insertion_point(field_set:gateway.CmdContext.Cmd)
}

// uint64 ConnID = 2;
inline void CmdContext::clear_connid() {
  connid_ = PROTOBUF_ULONGLONG(0);
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 CmdContext::_internal_connid() const {
  return connid_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint64 CmdContext::connid() const {
  // @@protoc_insertion_point(field_get:gateway.CmdContext.ConnID)
  return _internal_connid();
}
inline void CmdContext::_internal_set_connid(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  
  connid_ = value;
}
inline void CmdContext::set_connid(::PROTOBUF_NAMESPACE_ID::uint64 value) {
  _internal_set_connid(value);
  // @@protoc_insertion_point(field_set:gateway.CmdContext.ConnID)
}

// bytes Payload = 3;
inline void CmdContext::clear_payload() {
  payload_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& CmdContext::payload() const {
  // @@protoc_insertion_point(field_get:gateway.CmdContext.Payload)
  return _internal_payload();
}
inline void CmdContext::set_payload(const std::string& value) {
  _internal_set_payload(value);
  // @@protoc_insertion_point(field_set:gateway.CmdContext.Payload)
}
inline std::string* CmdContext::mutable_payload() {
  // @@protoc_insertion_point(field_mutable:gateway.CmdContext.Payload)
  return _internal_mutable_payload();
}
inline const std::string& CmdContext::_internal_payload() const {
  return payload_.GetNoArena();
}
inline void CmdContext::_internal_set_payload(const std::string& value) {
  
  payload_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
}
inline void CmdContext::set_payload(std::string&& value) {
  
  payload_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:gateway.CmdContext.Payload)
}
inline void CmdContext::set_payload(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  payload_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:gateway.CmdContext.Payload)
}
inline void CmdContext::set_payload(const void* value, size_t size) {
  
  payload_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:gateway.CmdContext.Payload)
}
inline std::string* CmdContext::_internal_mutable_payload() {
  
  return payload_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* CmdContext::release_payload() {
  // @@protoc_insertion_point(field_release:gateway.CmdContext.Payload)
  
  return payload_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void CmdContext::set_allocated_payload(std::string* payload) {
  if (payload != nullptr) {
    
  } else {
    
  }
  payload_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), payload);
  // @@protoc_insertion_point(field_set_allocated:gateway.CmdContext.Payload)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace gateway

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::gateway::CmdContext_CMD> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::gateway::CmdContext_CMD>() {
  return ::gateway::CmdContext_CMD_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_cmdcontext_2eproto
