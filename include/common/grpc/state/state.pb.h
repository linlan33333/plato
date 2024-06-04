// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: state.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_state_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_state_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3019000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3019004 < PROTOBUF_MIN_PROTOC_VERSION
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
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_state_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_state_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_state_2eproto;
class StateRequest;
struct StateRequestDefaultTypeInternal;
extern StateRequestDefaultTypeInternal _StateRequest_default_instance_;
class StateResponse;
struct StateResponseDefaultTypeInternal;
extern StateResponseDefaultTypeInternal _StateResponse_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::StateRequest* Arena::CreateMaybeMessage<::StateRequest>(Arena*);
template<> ::StateResponse* Arena::CreateMaybeMessage<::StateResponse>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class StateRequest final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:StateRequest) */ {
 public:
  inline StateRequest() : StateRequest(nullptr) {}
  ~StateRequest() override;
  explicit constexpr StateRequest(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  StateRequest(const StateRequest& from);
  StateRequest(StateRequest&& from) noexcept
    : StateRequest() {
    *this = ::std::move(from);
  }

  inline StateRequest& operator=(const StateRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline StateRequest& operator=(StateRequest&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const StateRequest& default_instance() {
    return *internal_default_instance();
  }
  static inline const StateRequest* internal_default_instance() {
    return reinterpret_cast<const StateRequest*>(
               &_StateRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(StateRequest& a, StateRequest& b) {
    a.Swap(&b);
  }
  inline void Swap(StateRequest* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(StateRequest* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  StateRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<StateRequest>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const StateRequest& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const StateRequest& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(StateRequest* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "StateRequest";
  }
  protected:
  explicit StateRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kEndpointFieldNumber = 1,
    kDataFieldNumber = 3,
    kConnIDFieldNumber = 2,
  };
  // string endpoint = 1;
  void clear_endpoint();
  const std::string& endpoint() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_endpoint(ArgT0&& arg0, ArgT... args);
  std::string* mutable_endpoint();
  PROTOBUF_NODISCARD std::string* release_endpoint();
  void set_allocated_endpoint(std::string* endpoint);
  private:
  const std::string& _internal_endpoint() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_endpoint(const std::string& value);
  std::string* _internal_mutable_endpoint();
  public:

  // bytes data = 3;
  void clear_data();
  const std::string& data() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_data(ArgT0&& arg0, ArgT... args);
  std::string* mutable_data();
  PROTOBUF_NODISCARD std::string* release_data();
  void set_allocated_data(std::string* data);
  private:
  const std::string& _internal_data() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_data(const std::string& value);
  std::string* _internal_mutable_data();
  public:

  // uint64 connID = 2;
  void clear_connid();
  uint64_t connid() const;
  void set_connid(uint64_t value);
  private:
  uint64_t _internal_connid() const;
  void _internal_set_connid(uint64_t value);
  public:

  // @@protoc_insertion_point(class_scope:StateRequest)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr endpoint_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr data_;
  uint64_t connid_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_state_2eproto;
};
// -------------------------------------------------------------------

class StateResponse final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:StateResponse) */ {
 public:
  inline StateResponse() : StateResponse(nullptr) {}
  ~StateResponse() override;
  explicit constexpr StateResponse(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  StateResponse(const StateResponse& from);
  StateResponse(StateResponse&& from) noexcept
    : StateResponse() {
    *this = ::std::move(from);
  }

  inline StateResponse& operator=(const StateResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline StateResponse& operator=(StateResponse&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const StateResponse& default_instance() {
    return *internal_default_instance();
  }
  static inline const StateResponse* internal_default_instance() {
    return reinterpret_cast<const StateResponse*>(
               &_StateResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(StateResponse& a, StateResponse& b) {
    a.Swap(&b);
  }
  inline void Swap(StateResponse* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(StateResponse* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  StateResponse* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<StateResponse>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const StateResponse& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const StateResponse& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(StateResponse* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "StateResponse";
  }
  protected:
  explicit StateResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kMsgFieldNumber = 2,
    kCodeFieldNumber = 1,
  };
  // string msg = 2;
  void clear_msg();
  const std::string& msg() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_msg(ArgT0&& arg0, ArgT... args);
  std::string* mutable_msg();
  PROTOBUF_NODISCARD std::string* release_msg();
  void set_allocated_msg(std::string* msg);
  private:
  const std::string& _internal_msg() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_msg(const std::string& value);
  std::string* _internal_mutable_msg();
  public:

  // int32 code = 1;
  void clear_code();
  int32_t code() const;
  void set_code(int32_t value);
  private:
  int32_t _internal_code() const;
  void _internal_set_code(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:StateResponse)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr msg_;
  int32_t code_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_state_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// StateRequest

// string endpoint = 1;
inline void StateRequest::clear_endpoint() {
  endpoint_.ClearToEmpty();
}
inline const std::string& StateRequest::endpoint() const {
  // @@protoc_insertion_point(field_get:StateRequest.endpoint)
  return _internal_endpoint();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void StateRequest::set_endpoint(ArgT0&& arg0, ArgT... args) {
 
 endpoint_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:StateRequest.endpoint)
}
inline std::string* StateRequest::mutable_endpoint() {
  std::string* _s = _internal_mutable_endpoint();
  // @@protoc_insertion_point(field_mutable:StateRequest.endpoint)
  return _s;
}
inline const std::string& StateRequest::_internal_endpoint() const {
  return endpoint_.Get();
}
inline void StateRequest::_internal_set_endpoint(const std::string& value) {
  
  endpoint_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* StateRequest::_internal_mutable_endpoint() {
  
  return endpoint_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* StateRequest::release_endpoint() {
  // @@protoc_insertion_point(field_release:StateRequest.endpoint)
  return endpoint_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void StateRequest::set_allocated_endpoint(std::string* endpoint) {
  if (endpoint != nullptr) {
    
  } else {
    
  }
  endpoint_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), endpoint,
      GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (endpoint_.IsDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited())) {
    endpoint_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:StateRequest.endpoint)
}

// uint64 connID = 2;
inline void StateRequest::clear_connid() {
  connid_ = uint64_t{0u};
}
inline uint64_t StateRequest::_internal_connid() const {
  return connid_;
}
inline uint64_t StateRequest::connid() const {
  // @@protoc_insertion_point(field_get:StateRequest.connID)
  return _internal_connid();
}
inline void StateRequest::_internal_set_connid(uint64_t value) {
  
  connid_ = value;
}
inline void StateRequest::set_connid(uint64_t value) {
  _internal_set_connid(value);
  // @@protoc_insertion_point(field_set:StateRequest.connID)
}

// bytes data = 3;
inline void StateRequest::clear_data() {
  data_.ClearToEmpty();
}
inline const std::string& StateRequest::data() const {
  // @@protoc_insertion_point(field_get:StateRequest.data)
  return _internal_data();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void StateRequest::set_data(ArgT0&& arg0, ArgT... args) {
 
 data_.SetBytes(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:StateRequest.data)
}
inline std::string* StateRequest::mutable_data() {
  std::string* _s = _internal_mutable_data();
  // @@protoc_insertion_point(field_mutable:StateRequest.data)
  return _s;
}
inline const std::string& StateRequest::_internal_data() const {
  return data_.Get();
}
inline void StateRequest::_internal_set_data(const std::string& value) {
  
  data_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* StateRequest::_internal_mutable_data() {
  
  return data_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* StateRequest::release_data() {
  // @@protoc_insertion_point(field_release:StateRequest.data)
  return data_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void StateRequest::set_allocated_data(std::string* data) {
  if (data != nullptr) {
    
  } else {
    
  }
  data_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), data,
      GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (data_.IsDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited())) {
    data_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:StateRequest.data)
}

// -------------------------------------------------------------------

// StateResponse

// int32 code = 1;
inline void StateResponse::clear_code() {
  code_ = 0;
}
inline int32_t StateResponse::_internal_code() const {
  return code_;
}
inline int32_t StateResponse::code() const {
  // @@protoc_insertion_point(field_get:StateResponse.code)
  return _internal_code();
}
inline void StateResponse::_internal_set_code(int32_t value) {
  
  code_ = value;
}
inline void StateResponse::set_code(int32_t value) {
  _internal_set_code(value);
  // @@protoc_insertion_point(field_set:StateResponse.code)
}

// string msg = 2;
inline void StateResponse::clear_msg() {
  msg_.ClearToEmpty();
}
inline const std::string& StateResponse::msg() const {
  // @@protoc_insertion_point(field_get:StateResponse.msg)
  return _internal_msg();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void StateResponse::set_msg(ArgT0&& arg0, ArgT... args) {
 
 msg_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:StateResponse.msg)
}
inline std::string* StateResponse::mutable_msg() {
  std::string* _s = _internal_mutable_msg();
  // @@protoc_insertion_point(field_mutable:StateResponse.msg)
  return _s;
}
inline const std::string& StateResponse::_internal_msg() const {
  return msg_.Get();
}
inline void StateResponse::_internal_set_msg(const std::string& value) {
  
  msg_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* StateResponse::_internal_mutable_msg() {
  
  return msg_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* StateResponse::release_msg() {
  // @@protoc_insertion_point(field_release:StateResponse.msg)
  return msg_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void StateResponse::set_allocated_msg(std::string* msg) {
  if (msg != nullptr) {
    
  } else {
    
  }
  msg_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), msg,
      GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (msg_.IsDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited())) {
    msg_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:StateResponse.msg)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_state_2eproto