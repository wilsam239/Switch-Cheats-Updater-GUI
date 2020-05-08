#include <ui/ViewInstalledTitlesLayout.hpp>
#include <ui/MainApplication.hpp>

extern MainApplication::Ref global_app;

ViewInstalledTitlesLayout::ViewInstalledTitlesLayout() : Layout::Layout() {

    this->titlesMenu = pu::ui::elm::Menu::New(0, 100, 1280, foreground, 80, 560);
    this->titlesMenu->SetOnFocusColor(focus);
    //getInstalledTitlesNs();
    //populateMenu();
    this->Add(titlesMenu);
}

void ViewInstalledTitlesLayout::titleMenuItem_Click() {
    Title sel = this->titles[this->titlesMenu->GetSelectedIndex()];
    global_app->CreateShowDialog(sel.name, formatApplicationId(sel.id), {"Close"}, false);
}

void ViewInstalledTitlesLayout::populateMenu() {
    for(int i = 0; i < this->titles.size(); i++) {
        //global_app->CreateShowDialog(this->titles.at(i).name, formatApplicationId(this->titles.at(i).id), {"Ok"}, false);
        auto titleMenuItem = pu::ui::elm::MenuItem::New(this->titles.at(i).name);
        titleMenuItem->SetColor(whiteText);
        titleMenuItem->AddOnClick(std::bind(&ViewInstalledTitlesLayout::titleMenuItem_Click, this));
        this->titlesMenu->AddItem(titleMenuItem);
    }
    this->titlesMenu->SetSelectedIndex(0);
}
void ViewInstalledTitlesLayout::setInstalledTitles() {
    //std::vector<Title> test = getInstalledTitlesNs();
    this->titles = getInstalledTitles();
}

void ViewInstalledTitlesLayout::clearTitles() {
    this->titles.clear();
    this->titlesMenu->ClearItems();
}
/*void ViewInstalledTitlesLayout::getInstalledTitlesNs() {
    // This function has been cobbled together from the "app_controldata" example in devkitpro.

    // Set the rc variable to begin with
    Result rc = 0;
    std::stringstream err;
    // Initialise a vector of tuples, storing the title ID and the title name.
    //std::vector<Title> titles;

    // Initialise an application record array, where the size is MaxTitleCount
    NsApplicationRecord *recs = new NsApplicationRecord[MaxTitleCount]();

    // Set the buffer to NULL
    NsApplicationControlData *buf=NULL;
    // Set outsize to 0
    u64 outsize=0;
    // Set the language entry to NULL
    NacpLanguageEntry *langentry = NULL;

    // Create a char array to store the name of the title
    char name[0x201];

    // Set the total records to 0
    s32 total = 0;
    // Set a failed counter to 0
    int totalFailed = 0;
    // Fill the recs array with application records
    rc = nsListApplicationRecord(recs, MaxTitleCount, 0, &total);

    // If filling the recs array was successful
    if (R_SUCCEEDED(rc)){
        // Loop through records
        for (s32 i = 0; i < total; i++){

            // Reset varaibles for accessing memory
            outsize=0;
            buf = (NsApplicationControlData*)malloc(sizeof(NsApplicationControlData));
            if (buf==NULL) {
                rc = MAKERESULT(Module_Libnx, LibnxError_OutOfMemory);
                err << "Failed to alloc mem.";
                global_app->debugDialog(err);
                err.str(std::string());
            } else {
                memset(buf, 0, sizeof(NsApplicationControlData));
            }

            if (R_SUCCEEDED(rc)) {
                rc = nsInitialize();
                if (R_FAILED(rc)) {
                    err << "nsInitialize() failed: 0x" << std::hex << rc;
                    global_app->debugDialog(err);
                    err.str(std::string());
                }
            }
            
            // Get the application control data for the current record
            rc = nsGetApplicationControlData(NsApplicationControlSource_Storage, recs[i].application_id, buf, sizeof(NsApplicationControlData), &outsize);

            if (R_FAILED(rc)) {
                totalFailed++;
                err << "nsGetApplicationControlData() failed: 0x" << std::hex << rc << " for Title ID: " << formatApplicationId(recs[i].application_id);
                global_app->debugDialog(err);
                err.str(std::string());
            }

            if (outsize < sizeof(buf->nacp)) {
                rc = -1;
                err << "Outsize is too small: 0x" << std::hex << outsize;
                global_app->debugDialog(err);
                err.str(std::string());
            }

            // If application control data was retrieved successfully
            if (R_SUCCEEDED(rc)) {
                rc = nacpGetLanguageEntry(&buf->nacp, &langentry);

                if (R_FAILED(rc) || langentry==NULL) {
                    err << "Failed to load LanguageEntry";
                    global_app->debugDialog(err);
                    err.str(std::string());
                }
            }

            // If nacp language entry was retrieved successfully
            if (R_SUCCEEDED(rc)) {
                memset(name, 0, sizeof(name));
                strncpy(name, langentry->name, sizeof(name)-1); //Don't assume the nacp string is NUL-terminated for safety.
                this->titles.push_back({formatApplicationId(recs[i].application_id), name});
            }

            nsExit();
        }
    } else {
        err << "Initial nsListApp failed";
        global_app->debugDialog(err);
        err.str(std::string());
    }

    free(buf);
    delete[] recs;
    std::sort(titles.begin(), titles.end());
    if(totalFailed > 0)  {
        err << "Failed " << totalFailed << " titles";
        global_app->debugDialog(err);
        err.str(std::string());
    }
}

std::string ViewInstalledTitlesLayout::formatApplicationId(u64 ApplicationId){
    std::stringstream strm;
    strm << std::uppercase << std::hex << ApplicationId;
    return strm.str();
}
*/
size_t ViewInstalledTitlesLayout::getTitlesCount() {
    return this->titles.size();
}