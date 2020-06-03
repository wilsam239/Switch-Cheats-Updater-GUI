#include <ui/MainMenuLayout.hpp>
#include <ui/MainApplication.hpp>

extern MainApplication::Ref global_app;

MainMenuLayout::MainMenuLayout() : Layout::Layout() {
    this->optionMenu = pu::ui::elm::Menu::New(0, 100, 1280, foreground, 80, 240);
    this->optionMenu->SetOnFocusColor(focus);

    this->downloadMenuItem = pu::ui::elm::MenuItem::New("Download Cheats");
    this->downloadMenuItem->SetColor(whiteText);
    this->downloadMenuItem->AddOnClick(std::bind(&MainMenuLayout::downloadMenuItem_Click, this));
    this->downloadMenuItem->SetIcon("/config/icons/Download.png");

    this->viewInstalledMenuItem = pu::ui::elm::MenuItem::New("View Installed Titles");
    this->viewInstalledMenuItem->SetColor(whiteText);
    this->viewInstalledMenuItem->AddOnClick(std::bind(&MainMenuLayout::viewInstalledMenuItem_Click, this));
    this->viewInstalledMenuItem->SetIcon("/config/icons/Installed.png");

    this->deleteMenuItem = pu::ui::elm::MenuItem::New("Delete All Cheats");
    this->deleteMenuItem->SetColor(whiteText);
    this->deleteMenuItem->AddOnClick(std::bind(&MainMenuLayout::deleteMenuItem_Click, this));
    this->deleteMenuItem->SetIcon("/config/icons/Delete.png");

    this->optionMenu->AddItem(this->downloadMenuItem);
    this->optionMenu->AddItem(this->viewInstalledMenuItem);
    this->optionMenu->AddItem(this->deleteMenuItem);

    this->Add(this->optionMenu);
}

void MainMenuLayout::downloadMenuItem_Click() {
    int upToDate = global_app->getDownloadCheatsLayout()->versionUpToDate();
    if(upToDate == 1) {
        global_app->CreateShowDialog("Already up to date!", "The current cheats revision is up to date, there is nothing to be done.", {"Ok"}, false);
    } else if(upToDate == 0){
        global_app->LoadLayout(global_app->getDownloadCheatsLayout());
        global_app->getDownloadCheatsLayout()->downloadFileCall();
    }
}

void MainMenuLayout::deleteMenuItem_Click() {
    int opt = global_app->CreateShowDialog("Are you sure?", "All cheat files found in the titles folder will be deleted.", { "Yes", "No"}, true); // (using latest option as cancel option)
    if((opt == -1) || (opt == -2)) // -1 and -2 are similar, but if the user cancels manually -1 is set, other types or cancel should be -2.
    {
        global_app->CreateShowDialog("Cancelled","No cheat files were deleted.", { "Ok" }, true); // If we will ignore the option, it doesn't matter if this is true or false
    }
    else
    {
        switch(opt)
        {
            case 0: // "Yes" was selected
                global_app->CreateShowDialog("Deleted", "N titles had their cheats deleted.", { "Ok" }, true); // Same here ^
                break;
            /*case 1: // "No" was selected
                global_app->CreateShowDialog("Cancelled", "No cheat files were deleted.", { "OK" }, true); // And here ^
                break;*/
        }
    }
}

void MainMenuLayout::viewInstalledMenuItem_Click() {
    global_app->getViewInstalledTitlesLayout()->setInstalledTitles();
    
    if(global_app->getViewInstalledTitlesLayout()->getTitlesCount() == 0) {
        global_app->CreateShowDialog("No titles found.", "", {"Ok"}, false);
    } else {
        global_app->getViewInstalledTitlesLayout()->populateMenu();
        global_app->LoadLayout(global_app->getViewInstalledTitlesLayout());
    }
}