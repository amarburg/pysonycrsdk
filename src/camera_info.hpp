#pragma once

#include "CameraRemote_SDK.h"
#include "ICrCameraObjectInfo.h"

namespace sonycrsdk {

class CrCameraObjectInfo {
    public:
     explicit CrCameraObjectInfo(const SCRSDK::ICrCameraObjectInfo* info)
         : model_name(info->GetModel()) {}

     std::string model_name;
};

}