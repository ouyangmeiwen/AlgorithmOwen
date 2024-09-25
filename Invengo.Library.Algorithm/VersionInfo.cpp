// Version.cpp
#include "pch.h"
#include "VersionInfo.h"
#include <windows.h>

// 定义版本信息字符串
extern "C" {
    __declspec(dllexport) const char* GetFileVersion() { return FILE_VERSION; }
    __declspec(dllexport) const char* GetProductVersion() { return PRODUCT_VERSION; }
    __declspec(dllexport) const char* GetCompanyName() { return COMPANY_NAME; }
    __declspec(dllexport) const char* GetFileDescription() { return FILE_DESCRIPTION; }
    __declspec(dllexport) const char* GetInternalName() { return INTERNAL_NAME; }
    __declspec(dllexport) const char* GetLegalCopyright() { return LEGAL_COPYRIGHT; }
    __declspec(dllexport) const char* GetOriginalFilename() { return ORIGINAL_FILENAME; }
    __declspec(dllexport) const char* GetProductName() { return PRODUCT_NAME; }
    __declspec(dllexport) const char* GetComments() { return COMMENTS; }
    __declspec(dllexport) const char* GetBuildDate() { return BUILD_DATE; }
    __declspec(dllexport) const char* GetBuildTime() { return BUILD_TIME; }
}
