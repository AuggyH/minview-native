#include "indexer.h"
#include <filesystem>

namespace mv {
namespace fs = std::filesystem;

int ImageIndex::scan(const std::wstring& directory, bool recursive) {
    m_files.clear();
    m_root_dir = directory;

    try {
        if (recursive) {
            for (auto& entry : fs::recursive_directory_iterator(directory)) {
                if (!entry.is_regular_file()) continue;
                auto ext = entry.path().extension().wstring();
                // Lowercase
                for (auto& c : ext) c = towlower(c);

                if (ext == L".png" || ext == L".jpg" || ext == L".jpeg" ||
                    ext == L".bmp" || ext == L".gif" || ext == L".webp" ||
                    ext == L".tiff" || ext == L".tif") {
                    ImageEntry ie;
                    ie.path  = entry.path().wstring();
                    ie.name  = entry.path().filename().wstring();
                    ie.size  = entry.file_size();
                    ie.mtime = entry.last_write_time().time_since_epoch().count();
                    m_files.push_back(std::move(ie));
                }
            }
        } else {
            for (auto& entry : fs::directory_iterator(directory)) {
                if (!entry.is_regular_file()) continue;
                auto ext = entry.path().extension().wstring();
                for (auto& c : ext) c = towlower(c);
                if (ext == L".png" || ext == L".jpg" || ext == L".jpeg" ||
                    ext == L".bmp" || ext == L".gif" || ext == L".webp" ||
                    ext == L".tiff" || ext == L".tif") {
                    ImageEntry ie;
                    ie.path  = entry.path().wstring();
                    ie.name  = entry.path().filename().wstring();
                    ie.size  = entry.file_size();
                    ie.mtime = entry.last_write_time().time_since_epoch().count();
                    m_files.push_back(std::move(ie));
                }
            }
        }
    } catch (...) {
        return -1;
    }

    return static_cast<int>(m_files.size());
}

} // namespace mv
