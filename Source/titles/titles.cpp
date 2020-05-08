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
            //titles.push_back({id, name});
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

std::vector<Title> getInstalledTitles() {
    std::stringstream err;
    std::vector<Title> titles;
    NcmContentMetaDatabase metadb;
    Result rc = ncmOpenContentMetaDatabase(&metadb, static_cast<NcmStorageId>(5));
    if(R_SUCCEEDED(rc)) {
        NcmContentMetaKey *recs = new NcmContentMetaKey[MaxTitleCount]();
        s32 wrt = 0;
        s32 total = 0;
        rc = ncmContentMetaDatabaseList(&metadb, &total, &wrt, recs, MaxTitleCount, static_cast<NcmContentMetaType>(0), 0, 0, UINT64_MAX, NcmContentInstallType_Full);
        
        err << "Total returned: " << total;
        global_app->debugDialog(err.str());
        err.str(std::string());

        err << "wrt returned: " << wrt;
        global_app->debugDialog(err.str());
        err.str(std::string());

        if((R_SUCCEEDED(rc)) && (wrt > 0)) {
            titles.reserve(wrt);
            for(s32 i = 0; i < wrt; i++) {
                Title t = {};
                t.id = recs[i].id;
                NacpStruct *nacp = TryGetNACP(t.id);
                if(nacp != NULL) {
                    t.name = GetNACPName(nacp);
                    err << "Name: " << t.name;
                    global_app->debugDialog(err.str());
                    err.str(std::string());
                    delete nacp;
                }
                //t.Type = static_cast<ncm::ContentMetaType>(recs[i].type);
                t.Version = recs[i].version;
                //t.Location = Location;
                memcpy(&t.Record, &recs[i], sizeof(NcmContentMetaKey));
                titles.push_back(t);
            }
        }
        delete[] recs;
        serviceClose(&metadb.s);
    } else {
        global_app->debugDialog("ncmOpenContentMetaDatabase failed to return success.");
        for(int i = 0; i < 5; i++) {
            Title t = {};
            t.id = i;
            t.name = "Test";
            t.Version = 1;
            titles.push_back(t);
        }
    }
    return titles;
}

std::string formatApplicationId(u64 ApplicationId) {
    std::stringstream strm;
    strm << std::uppercase << std::hex << ApplicationId;
    return strm.str();
}

NacpStruct *TryGetNACP(u64 id) {
    NacpStruct *nacp = NULL;
    NsApplicationControlData *ctdata = new NsApplicationControlData;
    size_t acsz = 0;
    Result rc = nsGetApplicationControlData(NsApplicationControlSource_Storage, id, ctdata, sizeof(NsApplicationControlData), &acsz);
    if((R_SUCCEEDED(rc)) && !(acsz < sizeof(ctdata->nacp))) {
        nacp = new NacpStruct();
        memcpy(nacp, &ctdata->nacp, sizeof(NacpStruct));
    } else {
        rc = nsGetApplicationControlData(NsApplicationControlSource_Storage, id, ctdata, sizeof(NsApplicationControlData), &acsz);
        if((R_SUCCEEDED(rc)) && !(acsz < sizeof(ctdata->nacp)))
        {
            nacp = new NacpStruct();
            memcpy(nacp, &ctdata->nacp, sizeof(NacpStruct));
        }
    }
    delete ctdata;
    return nacp;
}

std::string GetNACPName(NacpStruct *NACP) {
    NacpLanguageEntry *lent;
    nacpGetLanguageEntry(NACP, &lent);
    std::string ret;
    if(lent != NULL) ret = std::string(lent->name);
    return ret;
}