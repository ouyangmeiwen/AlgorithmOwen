#include "pch.h"
#include "Tag.h"
#include <cstring> // For strncpy_s
#include <vector>
#include <unordered_map>
#include <string>
#include <numeric>

class Tag {
public:
    Tag(int antenna, const char* epc, double rssi) : antenna(antenna), rssi(rssi) {
        strncpy_s(this->epc, epc, sizeof(this->epc) - 1);
        this->epc[sizeof(this->epc) - 1] = '\0'; // Ensure null termination
    }

    int GetAnt() const { return antenna; }
    const char* GetEpc() const { return epc; }
    double GetRssi() const { return rssi; }

private:
    int antenna;
    char epc[100];
    double rssi;
};

extern "C" {

    MYLIBRARY_API Tag* CreateTag(int antenna, const char* epc, double rssi) {
        return new Tag(antenna, epc, rssi);
    }

    MYLIBRARY_API int GetTagAnt(Tag* Tag) {
        return Tag ? Tag->GetAnt() : -1;
    }

    MYLIBRARY_API const char* GetTagEpc(Tag* Tag) {
        return Tag ? Tag->GetEpc() : "";
    }

    MYLIBRARY_API double GetTagRssi(Tag* Tag) {
        return Tag ? Tag->GetRssi() : -1.0f;
    }

    MYLIBRARY_API void DestroyTag(Tag* Tag) {
        delete Tag;
    }

    MYLIBRARY_API std::vector<Tag*>* CreateTags() {
        return new std::vector<Tag*>();
    }

    MYLIBRARY_API void AddTag(std::vector<Tag*>* collection, Tag* Tag) {
        if (collection && Tag) {
            collection->push_back(Tag);
        }
    }

    MYLIBRARY_API Tag* GetTag(std::vector<Tag*>* collection, int index) {
        if (collection && index >= 0 && index < collection->size()) {
            return (*collection)[index];
        }
        return nullptr;
    }

    MYLIBRARY_API int GetTagsSize(std::vector<Tag*>* collection) {
        return collection ? static_cast<int>(collection->size()) : 0;
    }

    MYLIBRARY_API void DestroyTags(std::vector<Tag*>* collection) {
        if (collection) {
            for (Tag* Tag : *collection) {
                delete Tag;
            }
            delete collection;
        }
    }
    MYLIBRARY_API std::vector<Tag*>* AnalyzeTags(std::vector<Tag*>* collection)
    {
        if (collection) {
            auto* newtags = new  std::vector<Tag*>();
            std::unordered_map<std::string, std::vector<Tag*>> map_epc_tags;//标签按照EPC分组
            for (const auto& tag : *collection) {
                map_epc_tags[tag->GetEpc()].push_back(tag);
            }
            for (const auto& epc_kv : map_epc_tags) {
                auto epc = epc_kv.first;                                    //单个epc
                auto tags_epc = epc_kv.second;                              //单个EPC标签集合
                std::unordered_map<int, std::vector<Tag*>> map_ant_tags;    //单个EPC按照天线分组
                for (const auto& epc_tag : tags_epc) {
                    map_ant_tags[epc_tag->GetAnt()].push_back(epc_tag);
                }
                int ant_r = 1;
                double rssi_r = -std::numeric_limits<double>::infinity();
                for (const auto& ant_kv : map_ant_tags) {
                    auto ant = ant_kv.first;                                //单个天线
                    auto tags_ant = ant_kv.second;                          //单个天线的集合
                    //得到rssi 总和
                    double totalRssi = std::accumulate(tags_ant.begin(), tags_ant.end(), 0.0,
                        [](double sum, const Tag* tag) {
                            return sum + tag->GetRssi();
                        });
                    double avRssi = (totalRssi / tags_ant.size());
                    if (avRssi > rssi_r) {
                        ant_r = ant;
                        rssi_r = avRssi;
                    }
                }
                Tag* tag_r = new Tag(ant_r, epc.c_str(), rssi_r);
                newtags->push_back(tag_r);
            }
            return newtags;
        }
        return nullptr;
    }
}
