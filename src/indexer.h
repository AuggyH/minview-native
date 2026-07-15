#pragma once
#include <string>
#include <vector>

namespace mv {

struct ImageEntry {
    std::wstring path;
    std::wstring name;
    uint64_t     size = 0;
    uint64_t     mtime = 0;
};

class ImageIndex {
public:
    int scan(const std::wstring& directory, bool recursive = true);
    size_t size() const { return m_files.size(); }

private:
    std::vector<ImageEntry> m_files;
    std::wstring m_root_dir;
};

} // namespace mv
