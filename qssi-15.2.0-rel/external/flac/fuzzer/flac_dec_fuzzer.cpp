/******************************************************************************
 *
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *****************************************************************************
 * Originally developed and contributed by Ittiam Systems Pvt. Ltd, Bangalore
 */

#include <fuzzer/FuzzedDataProvider.h>
#include <stdlib.h>
#include <utils/String8.h>
#include "FLAC/stream_decoder.h"

constexpr FLAC__MetadataType kMetadataTypes[8] = {
  FLAC__METADATA_TYPE_PICTURE,
  FLAC__METADATA_TYPE_STREAMINFO,
  FLAC__METADATA_TYPE_PADDING,
  FLAC__METADATA_TYPE_APPLICATION,
  FLAC__METADATA_TYPE_SEEKTABLE,
  FLAC__METADATA_TYPE_VORBIS_COMMENT,
  FLAC__METADATA_TYPE_CUESHEET,
  FLAC__METADATA_TYPE_UNDEFINED,
};

const char *kMetadataIDs[3] = {
  "aiff",
  "riff",
  "w64",
};

// First four bytes are always "fLaC" in ASCII format.
#define FIRST_ENCODED_BYTE_OFFSET 4

class Codec {
 public:
  Codec(const uint8_t* data, size_t size) : mFdp(data, size) {
    mBuffer = data;
    mBufferLen = size;
  };
  ~Codec() { deInitDecoder(); }
  bool initDecoder();
  void decodeFrames();
  void deInitDecoder();

 private:
  FLAC__StreamDecoder *mDecoder = nullptr;
  const uint8_t *mBuffer = nullptr;
  size_t mBufferLen = 0;
  size_t mBufferPos = 0;
  FLAC__StreamDecoderReadStatus readCallback(FLAC__byte buffer[], size_t *bytes);
  FLAC__StreamDecoderWriteStatus writeCallback(const FLAC__Frame *frame,
                                               const FLAC__int32 *const buffer[]);
  void errorCallback(FLAC__StreamDecoderErrorStatus status);
  void metadataCallback(const FLAC__StreamMetadata *metadata);
  FuzzedDataProvider mFdp;
};

bool Codec::initDecoder() {
  mDecoder = FLAC__stream_decoder_new();
  if (!mDecoder) {
    return false;
  }
  FLAC__stream_decoder_set_metadata_ignore_all(mDecoder);
  FLAC__stream_decoder_set_md5_checking(mDecoder, true);
  // read_callback, write_callback, error_callback and metadata_callback cannot be nullptrs

  static auto read_callback = [](const FLAC__StreamDecoder *, FLAC__byte buffer[], size_t *bytes,
                                 void *client_data) -> FLAC__StreamDecoderReadStatus {
    Codec *client = reinterpret_cast<Codec *>(client_data);
    return client->readCallback(buffer, bytes);
  };
  static auto write_callback = [](const FLAC__StreamDecoder *, const FLAC__Frame *frame,
                                  const FLAC__int32 *const buffer[],
                                  void *client_data) -> FLAC__StreamDecoderWriteStatus {
    Codec *client = reinterpret_cast<Codec *>(client_data);
    return client->writeCallback(frame, buffer);
  };
  static auto error_callback = [](const FLAC__StreamDecoder *,
                                  FLAC__StreamDecoderErrorStatus status, void *client_data) {
    Codec *client = reinterpret_cast<Codec *>(client_data);
    client->errorCallback(status);
  };

  if (mFdp.ConsumeBool()) {
    FLAC__stream_decoder_set_metadata_ignore(mDecoder, mFdp.PickValueInArray(kMetadataTypes));
  }
  if (mFdp.ConsumeBool()) {
    FLAC__stream_decoder_skip_single_frame(mDecoder);
  }

  if (mFdp.ConsumeBool()) {
    FLAC__MetadataType metadataType = mFdp.PickValueInArray(kMetadataTypes);
    FLAC__stream_decoder_set_metadata_respond(mDecoder, metadataType);
  }
  else {
    FLAC__byte* metadataIgnoreID = (FLAC__byte*)mFdp.PickValueInArray(kMetadataIDs);
    FLAC__byte* metadataRespondID = (FLAC__byte*)mFdp.PickValueInArray(kMetadataIDs);
    FLAC__stream_decoder_set_metadata_ignore_application(mDecoder, metadataIgnoreID);
    FLAC__stream_decoder_set_metadata_respond_application(mDecoder, metadataRespondID);
  }

  static auto metadata_callback = [](const FLAC__StreamDecoder *,
                                     const FLAC__StreamMetadata *metadata, void *client_data) {
    Codec *client = reinterpret_cast<Codec *>(client_data);
    client->metadataCallback(metadata);
  };
  void *client_data = reinterpret_cast<void *>(this);
  FLAC__StreamDecoderInitStatus initStatus = FLAC__stream_decoder_init_stream(
      mDecoder, read_callback, nullptr, nullptr, nullptr, nullptr, write_callback,
      metadata_callback, error_callback, client_data);
  if (initStatus != FLAC__STREAM_DECODER_INIT_STATUS_OK) {
    return false;
  }
  if (mFdp.ConsumeBool()) {
    FLAC__stream_decoder_set_metadata_respond_all(mDecoder);
  }
  if (mFdp.ConsumeBool()) {
    FLAC__stream_decoder_seek_absolute(mDecoder, (FLAC__uint64)mFdp.ConsumeIntegral<uint64_t>());
  }
  return true;
}

FLAC__StreamDecoderReadStatus Codec::readCallback(FLAC__byte buffer[], size_t *bytes) {
  if (!mBuffer || mBufferLen == 0) {
    *bytes = 0;
    return FLAC__STREAM_DECODER_READ_STATUS_ABORT;
  }
  size_t bytesRequested = *bytes;
  if (bytesRequested > mBufferLen - mBufferPos) {
    bytesRequested = mBufferLen - mBufferPos;
  }
  memcpy(buffer, mBuffer + mBufferPos, bytesRequested);
  mBufferPos += bytesRequested;
  *bytes = bytesRequested;
  return (bytesRequested == 0 ? FLAC__STREAM_DECODER_READ_STATUS_END_OF_STREAM
                              : FLAC__STREAM_DECODER_READ_STATUS_CONTINUE);
}

FLAC__StreamDecoderWriteStatus Codec::writeCallback(const FLAC__Frame *frame,
                                                    const FLAC__int32 *const buffer[]) {
  (void)frame;
  (void)buffer;
  return FLAC__STREAM_DECODER_WRITE_STATUS_CONTINUE;
}

void Codec::errorCallback(FLAC__StreamDecoderErrorStatus status) {
  (void)status;
  return;
}

void Codec::metadataCallback(const FLAC__StreamMetadata *metadata) {
  (void)metadata;
  return;
}

void Codec::decodeFrames() {
  if (mFdp.ConsumeBool()) {
    if (!FLAC__stream_decoder_process_until_end_of_metadata(mDecoder)) {
      return;
    }
    while(mBufferPos <= mBufferLen) {
      FLAC__stream_decoder_process_single(mDecoder);
      if (FLAC__STREAM_DECODER_END_OF_STREAM == FLAC__stream_decoder_get_state(mDecoder)) {
        return;
      }
    }
  } else {
    FLAC__stream_decoder_process_until_end_of_stream(mDecoder);
  }
  FLAC__stream_decoder_finish(mDecoder);
}

void Codec::deInitDecoder() {
  if (mDecoder != nullptr) {
    FLAC__stream_decoder_delete(mDecoder);
  }
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size == 0) {
    return 0;
  }
  auto codec = std::make_unique<Codec>(data, size);
  if (codec->initDecoder()) {
    codec->decodeFrames();
  }
  return 0;
}
