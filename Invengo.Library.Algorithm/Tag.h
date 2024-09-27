#pragma once

#ifdef MYLIBRARY_EXPORTS
#define MYLIBRARY_API __declspec(dllexport)
#else
#define MYLIBRARY_API __declspec(dllexport)
#endif

#include <vector>

extern "C" {

    typedef struct Tag Tag;

    MYLIBRARY_API Tag* CreateTag(int antenna, const char* epc, double rssi, int readcount, const wchar_t* name);
    MYLIBRARY_API int GetTagAnt(Tag* Tag);
    MYLIBRARY_API const char* GetTagEpc(Tag* Tag);
    MYLIBRARY_API double GetTagRssi(Tag* Tag);
    MYLIBRARY_API int GetTagReadCount(Tag* Tag);
    MYLIBRARY_API const wchar_t* GetTagName(Tag* Tag);
    MYLIBRARY_API void DestroyTag(Tag* Tag);

    MYLIBRARY_API std::vector<Tag*>* CreateTags();
    MYLIBRARY_API void AddTag(std::vector<Tag*>* collection, Tag* Tag);
    MYLIBRARY_API Tag* GetTag(std::vector<Tag*>* collection, int index);
    MYLIBRARY_API int GetTagsSize(std::vector<Tag*>* collection);
    MYLIBRARY_API void DestroyTags(std::vector<Tag*>* collection);
    MYLIBRARY_API std::vector<Tag*>* AnalyzeTags(std::vector<Tag*>* collection,double min,double max);

}
