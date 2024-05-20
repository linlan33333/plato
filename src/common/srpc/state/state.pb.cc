// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: state.proto

#include "state.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
class StateRequestDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<StateRequest> _instance;
} _StateRequest_default_instance_;
class StateResponseDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<StateResponse> _instance;
} _StateResponse_default_instance_;
static void InitDefaultsscc_info_StateRequest_state_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_StateRequest_default_instance_;
    new (ptr) ::StateRequest();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::StateRequest::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_StateRequest_state_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_StateRequest_state_2eproto}, {}};

static void InitDefaultsscc_info_StateResponse_state_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_StateResponse_default_instance_;
    new (ptr) ::StateResponse();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::StateResponse::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_StateResponse_state_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_StateResponse_state_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_state_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_state_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_state_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_state_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::StateRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::StateRequest, endpoint_),
  PROTOBUF_FIELD_OFFSET(::StateRequest, connid_),
  PROTOBUF_FIELD_OFFSET(::StateRequest, data_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::StateResponse, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::StateResponse, code_),
  PROTOBUF_FIELD_OFFSET(::StateResponse, msg_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::StateRequest)},
  { 8, -1, sizeof(::StateResponse)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_StateRequest_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_StateResponse_default_instance_),
};

const char descriptor_table_protodef_state_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\013state.proto\">\n\014StateRequest\022\020\n\010endpoin"
  "t\030\001 \001(\t\022\016\n\006connID\030\002 \001(\004\022\014\n\004data\030\003 \001(\014\"*\n"
  "\rStateResponse\022\014\n\004code\030\001 \001(\005\022\013\n\003msg\030\002 \001("
  "\t2^\n\005State\022+\n\nCancelConn\022\r.StateRequest\032"
  "\016.StateResponse\022(\n\007SendMsg\022\r.StateReques"
  "t\032\016.StateResponseb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_state_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_state_2eproto_sccs[2] = {
  &scc_info_StateRequest_state_2eproto.base,
  &scc_info_StateResponse_state_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_state_2eproto_once;
static bool descriptor_table_state_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_state_2eproto = {
  &descriptor_table_state_2eproto_initialized, descriptor_table_protodef_state_2eproto, "state.proto", 225,
  &descriptor_table_state_2eproto_once, descriptor_table_state_2eproto_sccs, descriptor_table_state_2eproto_deps, 2, 0,
  schemas, file_default_instances, TableStruct_state_2eproto::offsets,
  file_level_metadata_state_2eproto, 2, file_level_enum_descriptors_state_2eproto, file_level_service_descriptors_state_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_state_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_state_2eproto), true);

// ===================================================================

void StateRequest::InitAsDefaultInstance() {
}
class StateRequest::_Internal {
 public:
};

StateRequest::StateRequest()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:StateRequest)
}
StateRequest::StateRequest(const StateRequest& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  endpoint_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_endpoint().empty()) {
    endpoint_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.endpoint_);
  }
  data_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_data().empty()) {
    data_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.data_);
  }
  connid_ = from.connid_;
  // @@protoc_insertion_point(copy_constructor:StateRequest)
}

void StateRequest::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_StateRequest_state_2eproto.base);
  endpoint_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  data_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  connid_ = PROTOBUF_ULONGLONG(0);
}

StateRequest::~StateRequest() {
  // @@protoc_insertion_point(destructor:StateRequest)
  SharedDtor();
}

void StateRequest::SharedDtor() {
  endpoint_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  data_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void StateRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const StateRequest& StateRequest::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_StateRequest_state_2eproto.base);
  return *internal_default_instance();
}


void StateRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:StateRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  endpoint_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  data_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  connid_ = PROTOBUF_ULONGLONG(0);
  _internal_metadata_.Clear();
}

const char* StateRequest::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // string endpoint = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_endpoint();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "StateRequest.endpoint"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // uint64 connID = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          connid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // bytes data = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
          auto str = _internal_mutable_data();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* StateRequest::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:StateRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string endpoint = 1;
  if (this->endpoint().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_endpoint().data(), static_cast<int>(this->_internal_endpoint().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "StateRequest.endpoint");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_endpoint(), target);
  }

  // uint64 connID = 2;
  if (this->connid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteUInt64ToArray(2, this->_internal_connid(), target);
  }

  // bytes data = 3;
  if (this->data().size() > 0) {
    target = stream->WriteBytesMaybeAliased(
        3, this->_internal_data(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:StateRequest)
  return target;
}

size_t StateRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:StateRequest)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string endpoint = 1;
  if (this->endpoint().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_endpoint());
  }

  // bytes data = 3;
  if (this->data().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_data());
  }

  // uint64 connID = 2;
  if (this->connid() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::UInt64Size(
        this->_internal_connid());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void StateRequest::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:StateRequest)
  GOOGLE_DCHECK_NE(&from, this);
  const StateRequest* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<StateRequest>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:StateRequest)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:StateRequest)
    MergeFrom(*source);
  }
}

void StateRequest::MergeFrom(const StateRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:StateRequest)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.endpoint().size() > 0) {

    endpoint_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.endpoint_);
  }
  if (from.data().size() > 0) {

    data_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.data_);
  }
  if (from.connid() != 0) {
    _internal_set_connid(from._internal_connid());
  }
}

void StateRequest::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:StateRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void StateRequest::CopyFrom(const StateRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:StateRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool StateRequest::IsInitialized() const {
  return true;
}

void StateRequest::InternalSwap(StateRequest* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  endpoint_.Swap(&other->endpoint_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  data_.Swap(&other->data_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  swap(connid_, other->connid_);
}

::PROTOBUF_NAMESPACE_ID::Metadata StateRequest::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void StateResponse::InitAsDefaultInstance() {
}
class StateResponse::_Internal {
 public:
};

StateResponse::StateResponse()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:StateResponse)
}
StateResponse::StateResponse(const StateResponse& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  msg_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_msg().empty()) {
    msg_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.msg_);
  }
  code_ = from.code_;
  // @@protoc_insertion_point(copy_constructor:StateResponse)
}

void StateResponse::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_StateResponse_state_2eproto.base);
  msg_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  code_ = 0;
}

StateResponse::~StateResponse() {
  // @@protoc_insertion_point(destructor:StateResponse)
  SharedDtor();
}

void StateResponse::SharedDtor() {
  msg_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void StateResponse::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const StateResponse& StateResponse::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_StateResponse_state_2eproto.base);
  return *internal_default_instance();
}


void StateResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:StateResponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  msg_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  code_ = 0;
  _internal_metadata_.Clear();
}

const char* StateResponse::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // int32 code = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          code_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string msg = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_msg();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "StateResponse.msg"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* StateResponse::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:StateResponse)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 code = 1;
  if (this->code() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_code(), target);
  }

  // string msg = 2;
  if (this->msg().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_msg().data(), static_cast<int>(this->_internal_msg().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "StateResponse.msg");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_msg(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:StateResponse)
  return target;
}

size_t StateResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:StateResponse)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string msg = 2;
  if (this->msg().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_msg());
  }

  // int32 code = 1;
  if (this->code() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_code());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void StateResponse::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:StateResponse)
  GOOGLE_DCHECK_NE(&from, this);
  const StateResponse* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<StateResponse>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:StateResponse)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:StateResponse)
    MergeFrom(*source);
  }
}

void StateResponse::MergeFrom(const StateResponse& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:StateResponse)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.msg().size() > 0) {

    msg_.AssignWithDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from.msg_);
  }
  if (from.code() != 0) {
    _internal_set_code(from._internal_code());
  }
}

void StateResponse::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:StateResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void StateResponse::CopyFrom(const StateResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:StateResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool StateResponse::IsInitialized() const {
  return true;
}

void StateResponse::InternalSwap(StateResponse* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  msg_.Swap(&other->msg_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  swap(code_, other->code_);
}

::PROTOBUF_NAMESPACE_ID::Metadata StateResponse::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::StateRequest* Arena::CreateMaybeMessage< ::StateRequest >(Arena* arena) {
  return Arena::CreateInternal< ::StateRequest >(arena);
}
template<> PROTOBUF_NOINLINE ::StateResponse* Arena::CreateMaybeMessage< ::StateResponse >(Arena* arena) {
  return Arena::CreateInternal< ::StateResponse >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
