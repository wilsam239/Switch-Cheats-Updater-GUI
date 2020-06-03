#pragma once

#include <download.hpp>
#include <pu/Plutonium>

#define RELEASE_URL "https://github.com/HamletDuFromage/switch-cheats-db/releases/tag/v1.0"
#define ARCHIVE_URL "https://github.com/HamletDuFromage/switch-cheats-db/releases/download/v1.0/"
#define VERSION_FILE "version.dat"

// Define your main layout as a class inheriting from pu::Layout
class DownloadCheatsLayout : public pu::ui::Layout {
    public:

        DownloadCheatsLayout();

        // Have ::Ref alias and ::New() static constructor
        PU_SMART_CTOR(DownloadCheatsLayout);

        int versionUpToDate();
        bool isServiceRunning(const char *serviceName);
        void downloadFileCall();
        void updateProgress(std::string progress, double amount);
    private:

        // An easy way to keep objects is to have them as private members
        // Using ::Ref (of a Plutonium built-in object or any class having PU_SMART_CTOR) is an alias to a shared_ptr of the instance.
        pu::ui::elm::TextBlock::Ref downloadText;
        pu::ui::elm::ProgressBar::Ref downloadProgress;
};