#include <titles/titles.hpp>
#include <ui/MainApplication.hpp>

extern MainApplication::Ref global_app;

/**
 * writeTitlesToFile
 * Writes the input vector to the updated.dat file in config
 * Stores the id and name of each title seprated by a comma
**/
void writeTitlesToFile(std::vector<Title> titles) {
    std::ofstream updatedTitlesFile;
    updatedTitlesFile.open(UPDATED_TITLES_PATH, std::ofstream::out | std::ofstream::trunc);
    if(updatedTitlesFile.is_open()) {
        for(int t = 0; t < (int)titles.size(); t++) {
            updatedTitlesFile << titles.at(t).id << "," << titles.at(t).name << std::endl;
        }
        updatedTitlesFile.close();
    }
}

/**
 * readTitlesFromFile
 * Reads titles from the updated.dat file in config
 * Stores them as a new titles vector, and returns this to the function calling.
**/
std::vector<Title> readTitlesFromFile() {
    std::ifstream updatedTitlesFile;
    updatedTitlesFile.open(UPDATED_TITLES_PATH);

    std::string name;
    std::string id;
    std::string line;

    std::vector<Title> titles;

    if(updatedTitlesFile.is_open()) {
        while(getline(updatedTitlesFile, line)) {
            id = line.substr(0, 16);
            name = line.substr(17, line.size());
            titles.push_back({id, name});
        }
        updatedTitlesFile.close();
    }
    return titles;
}

/**
 * outputUpdatedTitles
 * Displays the contents of the updated.dat file in /config/
**/
void outputUpdatedTitles() {
    std::vector<Title> titles = readTitlesFromFile();
    std::cout << "Updated Titles:" << std::endl << std::endl;
    printTitles(titles);

    std::cout << "\033[7;37m"<< "\nPress [-] to return to main menu" << "\033[0m" <<std::endl;
    std::cout << "\033[7;37m"<< "\nPress [+] to quit" << "\033[0m" <<std::endl;
}

/**
 * printTitles
 * Display the titles vector parsed in
 * Truncates the name of the titles when necessary
 */ 
void printTitles(std::vector<Title> titles) {
    for(int i = 0; i < (int)titles.size(); i++) {
        if(titles.at(i).name.size() > 35) {
            titles.at(i).name = titles.at(i).name.substr(0, 35);
            titles.at(i).name.append("...");
        }
        std::cout << "\033[1;37m" << "Title ID: " << "\033[0m" << titles.at(i).id << "\033[1;37m" << " Title Name: " << "\033[0m" << titles.at(i).name << std::endl;
    }
}

std::vector<Title> getInstalledTitlesNs() {
    // This function has been cobbled together from the "app_controldata" example in devkitpro.

    // Set the rc variable to begin with
    Result rc = 0;
    std::stringstream err;
    // Initialise a vector of tuples, storing the title ID and the title name.
    std::vector<Title> titles;

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
    err << "Total records: " << total;
    global_app->debugDialog(err);
    err.str(std::string());
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
                titles.push_back({formatApplicationId(recs[i].application_id), name});
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

    return titles;
}

std::string formatApplicationId(u64 ApplicationId){
    std::stringstream strm;
    strm << std::uppercase << std::hex << ApplicationId;
    return strm.str();
}