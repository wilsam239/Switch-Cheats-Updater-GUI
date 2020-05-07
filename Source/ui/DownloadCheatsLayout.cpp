#include <ui/DownloadCheatsLayout.hpp>
#include <ui/MainApplication.hpp>

extern MainApplication::Ref global_app;

DownloadCheatsLayout::DownloadCheatsLayout() : Layout::Layout()
{
    // Create the TextBlock instance with the text we want
    this->helloText = pu::ui::elm::TextBlock::New(300, 300, "This is where the download would occur.");
    
    // Add the instance to the layout. IMPORTANT! this MUST be done for them to be used, having them as members is not enough (just a simple way to keep them)
    this->Add(this->helloText);

    
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

