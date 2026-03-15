#pragma once

#include "CameraRemote_SDK.h"
#include "ICrCameraObjectInfo.h"

namespace sonycrsdk {

class CrCameraObjectInfo {
 public:
  explicit CrCameraObjectInfo(const SCRSDK::ICrCameraObjectInfo* info)
      : model_name(info->GetModel()), info_(info) {}

bool valid() const { return info_ != nullptr; }

  std::string model_name;

  const SCRSDK::ICrCameraObjectInfo *info_;
};




// This wrapper only manages the lifecycle of SCRSDK::ICrEnumCameraObjectInfo
//
// Apparently there can only be one copy within the SDK, if you enumerate()
// a second time, the first one is lost in space.
class CrEnumCameraObjectInfo {
public:

explicit CrEnumCameraObjectInfo( SCRSDK::ICrEnumCameraObjectInfo *ilist )
: ilist_(ilist)
{}

~CrEnumCameraObjectInfo() {
    if(ilist_) ilist_->Release();
}

uint32_t size(void) const { 
    if(ilist_) return ilist_->GetCount();
}    

CrCameraObjectInfo at( uint32_t idx ) const {
if( idx >= size() || !ilist_) return CrCameraObjectInfo(nullptr);

return CrCameraObjectInfo( ilist_->GetCameraObjectInfo(idx));
}


SCRSDK::ICrEnumCameraObjectInfo* ilist_;
};

}