#pragma once

#include <string>

#include "CameraRemote_SDK.h"
#include "ICrCameraObjectInfo.h"
#include "camera.hpp"
#include "sdk_singleton.hpp"

namespace sonycrsdk {

class CrCameraObjectInfo {
 public:
  explicit CrCameraObjectInfo(const SCRSDK::ICrCameraObjectInfo* info)
      : info_(info) {}

  bool valid() const { return info_ != nullptr; }

  std::string modelName() const { return info_->GetModel(); }

  const SCRSDK::ICrCameraObjectInfo* info_;

  void connect(void);
};

// This wrapper only manages the lifecycle of SCRSDK::ICrEnumCameraObjectInfo
//
// Apparently there can only be one copy within the SDK, if you enumerate()
// a second time, the first one is lost in space.
class CrEnumCameraObjectInfo {
 public:
  explicit CrEnumCameraObjectInfo(SCRSDK::ICrEnumCameraObjectInfo* ilist)
      : ilist_(ilist) {}

  ~CrEnumCameraObjectInfo() {
    if (ilist_) ilist_->Release();
  }

  bool valid() const { return ilist_ != nullptr; }

  uint32_t size(void) const {
    if (!valid()) return 0;

    return ilist_->GetCount();
  }

  CrCameraObjectInfo at(uint32_t idx) const {
    if (idx >= size() || !valid()) return CrCameraObjectInfo(nullptr);

    return CrCameraObjectInfo(ilist_->GetCameraObjectInfo(idx));
  }

  SCRSDK::ICrEnumCameraObjectInfo* ilist_;
};

extern CrEnumCameraObjectInfo Enumerate();

}  // namespace sonycrsdk
