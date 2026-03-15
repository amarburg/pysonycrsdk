#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>

#include <string>

#include "CameraRemote_SDK.h"
#include "camera_info.hpp"
#include "sdk_singleton.hpp"

namespace nb = nanobind;
using namespace nb::literals;

using namespace sonycrsdk;

NB_MODULE(sonycrsdk_ext, m) {
  m.doc() = "nanobind extension for accessing Sony Camera Remote SDK";

  m.def("Enumerate", &Enumerate);

  nb::class_<CrEnumCameraObjectInfo>(m, "CameraInfoList")
      .def("size", &CrEnumCameraObjectInfo::size)
      .def("at", &CrEnumCameraObjectInfo::at);

  nb::class_<CrCameraObjectInfo>(m, "CameraInfo")
      .def("model_name", &CrCameraObjectInfo::modelName);

  nb::class_<Camera>(m, "Camera");
}
