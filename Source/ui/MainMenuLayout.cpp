#include "MainApplication.hpp"

extern MainApplication::Ref global_app;

#define yellow pu::ui::Color::FromHex("F6D632")
#define grey pu::ui::Color::FromHex("414548")
#define white pu::ui::Color::FromHex("FFFFFF")

MainMenuLayout::MainMenuLayout() : Layout::Layout() {
    this->SetBackgroundColor(white);
    this->optionMenu = pu::ui::elm::Menu::New(0, 0, 960, white, 80, 240);
    //this->optionMenu->SetOnFocusColor(white);

    this->downloadMenuItem = pu::ui::elm::MenuItem::New("Download Cheats");
    this->downloadMenuItem->SetColor(grey);
    this->downloadMenuItem->AddOnClick(std::bind(&MainMenuLayout::downloadMenuItem_Click, this));
    this->downloadMenuItem->SetIcon("/config/gui-icons/download-from-cloud.png");
    this->downloadMenuItem->SetName("Download Cheats");

    this->viewInstalledMenuItem = pu::ui::elm::MenuItem::New("View Installed Titles");
    this->viewInstalledMenuItem->SetColor(grey);
    this->viewInstalledMenuItem->AddOnClick(std::bind(&MainMenuLayout::viewInstalledMenuItem_Click, this));
    this->viewInstalledMenuItem->SetIcon("/config/gui-icons/search.png");

    this->deleteMenuItem = pu::ui::elm::MenuItem::New("Delete All Cheats");
    this->deleteMenuItem->SetColor(grey);
    this->deleteMenuItem->AddOnClick(std::bind(&MainMenuLayout::deleteMenuItem_Click, this));
    this->deleteMenuItem->SetIcon("/config/gui-icons/eliminar.png");

    this->optionMenu->AddItem(this->downloadMenuItem);
    this->optionMenu->AddItem(this->viewInstalledMenuItem);
    this->optionMenu->AddItem(this->deleteMenuItem);

    this->Add(this->optionMenu);
}

void MainMenuLayout::downloadMenuItem_Click() {
    global_app->LoadLayout(global_app->getViewInstalledTitlesLayout());
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
    global_app->LoadLayout(global_app->getMainMenuLayout());
}