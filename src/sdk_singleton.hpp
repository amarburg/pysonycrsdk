#pragma once

#include "CameraRemote_SDK.h"
namespace sonycrsdk {

class SDKSingleton {
 public:
  static SDKSingleton& get_instance() {
    static SDKSingleton instance;
    return instance;
  }

 private:
  SDKSingleton() {
    bool boolRet = SCRSDK::Init();
    // if (!boolRet) GotoError("", 0);
  }
  ~SDKSingleton() { SCRSDK::Release(); }

  SDKSingleton(const SDKSingleton&) = delete;
  SDKSingleton& operator=(const SDKSingleton&) = delete;
};

}