#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/stl/vector.h>

#include <string>

#include "CameraRemote_SDK.h"

#include "sdk_singleton.hpp"
#include "camera_info.hpp"

namespace nb = nanobind;
using namespace nb::literals;

using namespace sonycrsdk;

class Camera {
  public:
   static CrEnumCameraObjectInfo Enumerate() {
     SDKSingleton::get_instance();

     SCRSDK::ICrEnumCameraObjectInfo* enumCameraObjectInfo = nullptr;
     auto err =
         SCRSDK::EnumCameraObjects(&enumCameraObjectInfo, 3 /*timeInSec*/);

if(err)
  return CrEnumCameraObjectInfo(nullptr);

return CrEnumCameraObjectInfo(enumCameraObjectInfo);

     // if (err || !enumCameraObjectInfo) return
     // std::vector<CrCameraObjectInfo>();

     // auto count = enumCameraObjectInfo->GetCount();
     // std::vector<CrCameraObjectInfo> camInfo;
     // for (uint32_t i = 0; i < count; ++i) {
     //   camInfo.emplace_back(enumCameraObjectInfo->GetCameraObjectInfo(i));
     // }

     // if(enumCameraObjectInfo) enumCameraObjectInfo->Release();
     // return camInfo;
   }
};

NB_MODULE(sonycrsdk_ext, m) {
  m.doc() = "nanobind extension for accessing Sony Camera Remote SDK";

  nb::class_<CrEnumCameraObjectInfo>(m, "CameraInfoList");

  nb::class_<CrCameraObjectInfo>(m, "CameraInfo")
      .def_ro("model_name", &CrCameraObjectInfo::model_name);

  nb::class_<Camera>(m, "Camera")
      .def_static("Enumerate", &Camera::Enumerate);
}