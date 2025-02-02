// Copyright 2020-2023 Bloomberg Finance L.P.
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef INCLUDED_NTCA_ENCRYPTIONSECRET
#define INCLUDED_NTCA_ENCRYPTIONSECRET

#include <bsls_ident.h>
BSLS_IDENT("$Id: $")

#include <ntccfg_platform.h>
#include <ntcscm_version.h>
#include <ntsa_error.h>
#include <bslh_hash.h>
#include <bsl_functional.h>
#include <bsl_iosfwd.h>
#include <bsl_memory.h>
#include <bsl_string.h>
#include <bsl_vector.h>

namespace BloombergLP {
namespace ntca {

/// Describe a secret used in symmetric encryption.
///
/// @par Attributes
/// This class is composed of the following attributes.
///
/// @li @b data:
/// The bytes defining the secret.
///
/// @par Thread Safety
/// This class is not thread safe.
///
/// @ingroup module_ntci_encryption
class EncryptionSecret
{
    bsl::vector<bsl::uint8_t> d_data;

  public:
    /// Create a new encryption secret having the default value. Optionally
    /// specify a 'basicAllocator' used to supply memory. If 'basicAllocator'
    /// is 0, the currently installed default allocator is used.
    explicit EncryptionSecret(bslma::Allocator* basicAllocator = 0);

    /// Create a new resource secret having the same value as the specified
    /// 'original' object. Optionally specify a 'basicAllocator' used to supply
    /// memory. If 'basicAllocator' is 0, the currently installed default
    /// allocator is used.
    EncryptionSecret(const EncryptionSecret& original,
                     bslma::Allocator*       basicAllocator = 0);

    /// Destroy this object.
    ~EncryptionSecret();

    /// Assign the value of the specified 'other' object to this object.
    /// Return a reference to this modifiable object.
    EncryptionSecret& operator=(const EncryptionSecret& other);

    /// Reset the value of this object to its value upon default
    /// construction.
    void reset();

    /// Append the specified 'value'.
    void append(bsl::int8_t value);

    /// Append the specified 'value'.
    void append(bsl::uint8_t value);

    /// Append the specified 'data' having the specified 'size'.
    void append(const void* data, bsl::size_t size);

    /// Copy the secret to the specified 'destination' having the specified
    /// 'capacity'. Return the number of bytes copied. Note that the secret
    /// will be truncated if 'capacity' is less than the size of the secret.
    bsl::size_t copy(void* destination, bsl::size_t capacity) const;

    /// Return the data.
    const void* data() const;

    /// Return the number of bytes in the secret.
    bsl::size_t size() const;

    /// Return true if there are not bytes defined in the secret, otherwise
    /// return false.
    bool empty() const;

    /// Return true if this object has the same value as the specified
    /// 'other' object, otherwise return false.
    bool equals(const EncryptionSecret& other) const;

    /// Return true if the value of this object is less than the value of
    /// the specified 'other' object, otherwise return false.
    bool less(const EncryptionSecret& other) const;

    /// Format this object to the specified output 'stream' at the
    /// optionally specified indentation 'level' and return a reference to
    /// the modifiable 'stream'.  If 'level' is specified, optionally
    /// specify 'spacesPerLevel', the number of spaces per indentation level
    /// for this and all of its nested objects.  Each line is indented by
    /// the absolute value of 'level * spacesPerLevel'.  If 'level' is
    /// negative, suppress indentation of the first line.  If
    /// 'spacesPerLevel' is negative, suppress line breaks and format the
    /// entire output on one line.  If 'stream' is initially invalid, this
    /// operation has no effect.  Note that a trailing newline is provided
    /// in multiline mode only.
    bsl::ostream& print(bsl::ostream& stream,
                        int           level          = 0,
                        int           spacesPerLevel = 4) const;

    /// This type accepts an allocator argument to its constructors and may
    /// dynamically allocate memory during its operation.
    NTSCFG_TYPE_TRAIT_ALLOCATOR_AWARE(EncryptionSecret);
};

/// Define a type alias for a function invoked to load into the specified
/// 'result' a secret.
typedef bsl::function<ntsa::Error(ntca::EncryptionSecret* result)>
    EncryptionSecretCallback;

/// Format the specified 'object' to the specified output 'stream' and
/// return a reference to the modifiable 'stream'.
///
/// @related ntca::EncryptionSecret
bsl::ostream& operator<<(bsl::ostream& stream, const EncryptionSecret& object);

/// Return 'true' if the specified 'lhs' and 'rhs' attribute objects have
/// the same value, and 'false' otherwise.  Two attribute objects have the
/// same value if each respective attribute has the same value.
///
/// @related ntca::EncryptionSecret
bool operator==(const EncryptionSecret& lhs, const EncryptionSecret& rhs);

/// Return 'true' if the specified 'lhs' and 'rhs' attribute objects do not
/// have the same value, and 'false' otherwise.  Two attribute objects do
/// not have the same value if one or more respective attributes differ in
/// values.
///
/// @related ntca::EncryptionSecret
bool operator!=(const EncryptionSecret& lhs, const EncryptionSecret& rhs);

/// Return true if the value of the specified 'lhs' is less than the value
/// of the specified 'rhs', otherwise return false.
///
/// @related ntca::EncryptionSecret
bool operator<(const EncryptionSecret& lhs, const EncryptionSecret& rhs);

/// Contribute the values of the salient attributes of the specified 'value'
/// to the specified hash 'algorithm'.
///
/// @related ntca::EncryptionSecret
template <typename HASH_ALGORITHM>
void hashAppend(HASH_ALGORITHM& algorithm, const EncryptionSecret& value);

template <typename HASH_ALGORITHM>
void hashAppend(HASH_ALGORITHM& algorithm, const EncryptionSecret& value)
{
    algorithm(value.data(), value.size());
}

}  // close package namespace
}  // close enterprise namespace
#endif
