#include <ui/DownloadCheatsLayout.hpp>
#include <ui/MainApplication.hpp>


#define RELEASE_URL "https://github.com/HamletDuFromage/switch-cheats-db/releases/tag/v1.0"
#define ARCHIVE_URL "https://github.com/HamletDuFromage/switch-cheats-db/releases/download/v1.0/"

extern MainApplication::Ref global_app;

DownloadCheatsLayout::DownloadCheatsLayout() : Layout::Layout() {

    this->downloadText = pu::ui::elm::TextBlock::New(300, 300, "Downloding: ");
    this->downloadProgress = pu::ui::elm::ProgressBar::New(300, 350, (GetWidth()/4)*3, 50, 100);

    this->Add(this->downloadText);
    this->Add(this->downloadProgress);
    
}

/**
 * versionUpToDate()
 * Returns an int indicating:
 *      - 0: Version is not up to date
 *      - 1: Version is up to date
 *      - 2: An error occurred.
**/
int DownloadCheatsLayout::versionUpToDate() {
    std::string latestVersion = fetchVersion(RELEASE_URL, "1100-1110");
    std::string currentVersion = readVersion(VERSION_FILE);

    if(latestVersion == "-1") {
        global_app->debugDialog("An Error occurred during version fetch.");
        return 2;
    } else if(latestVersion == currentVersion) {
        return 1;
    } else {
        return 0;
    }

}

bool DownloadCheatsLayout::isServiceRunning(const char *serviceName) {
  Handle handle;
  SmServiceName service_name = smEncodeName(serviceName);
  bool running = R_FAILED(smRegisterService(&handle, service_name, false, 1));

  svcCloseHandle(handle);

  if (!running)
    smUnregisterService(service_name);

  return running;
}

void DownloadCheatsLayout::downloadFileCall() {
    bool sxos = !(isServiceRunning("dmnt:cht") && !(isServiceRunning("tx") && !isServiceRunning("rnx")));
    std::string filename;
    if(sxos){
        filename = "titles.zip";
        std::filesystem::create_directory("/sxos");
        std::filesystem::create_directory("/sxos/titles");
    }
    else{
        filename = "contents.zip";
        std::filesystem::create_directory("/atmosphere");
        std::filesystem::create_directory("/atmosphere/contents");
    }
    std::string url = std::string(ARCHIVE_URL) + filename;
    if(downloadFile(url.c_str(), filename.c_str(), OFF)) {
        global_app->debugDialog("Download was successful");
    } else {
        global_app->debugDialog("Download was unsuccessful");
    }
}

void DownloadCheatsLayout::updateProgress(std::string progress, double amount) {
    this->downloadText->SetText(progress);
    this->downloadProgress->SetProgress(amount);
}