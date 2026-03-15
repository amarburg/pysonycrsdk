

#include "camera_info.hpp"

namespace sonycrsdk {

CrEnumCameraObjectInfo Enumerate() {
  SDKSingleton::get_instance();

  SCRSDK::ICrEnumCameraObjectInfo* enumCameraObjectInfo = nullptr;
  auto err = SCRSDK::EnumCameraObjects(&enumCameraObjectInfo, 3 /*timeInSec*/);

  if (err) return CrEnumCameraObjectInfo(nullptr);

  return CrEnumCameraObjectInfo(enumCameraObjectInfo);
}

void CrCameraObjectInfo::connect() { ; }
}  // namespace sonycrsdk
