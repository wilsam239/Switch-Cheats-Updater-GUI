#include <MainApplication.hpp>

extern MainApplication::Ref global_app;

void MainApplication::OnLoad()
{
    // Create the layout (calling the smart constructor above)
    this->downloadCheats = DownloadCheatsLayout::New();
    this->downloadCheats->SetOnInput(std::bind(&MainApplication::customInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    this->viewInstalledTitles = ViewInstalledTitlesLayout::New();
    this->viewInstalledTitles->SetOnInput(std::bind(&MainApplication::testInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    this->mainMenu = MainMenuLayout::New();
    this->mainMenu->SetOnInput(std::bind(&MainApplication::mainMenuInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    // Load the layout. In applications layouts are loaded, not added into a container (you don't select an added layout, just load it from this function)
    // Simply explained: loading layout = the application will render that layout in the very next frame
    this->LoadLayout(this->mainMenu);
}

ViewInstalledTitlesLayout::Ref &MainApplication::getViewInstalledTitlesLayout() {
    return this->viewInstalledTitles;
}

DownloadCheatsLayout::Ref &MainApplication::getDownloadCheatsLayout() {
    return this->downloadCheats;
}

MainMenuLayout::Ref &MainApplication::getMainMenuLayout() {
    return this->mainMenu;
}

void MainApplication::ReturnToMainMenu() {
    this->LoadLayout(this->mainMenu);
}

void MainApplication::OnInput(u64 down, u64 up, u64 held)
{
    if(down & KEY_PLUS) this->CloseWithFadeOut();
}

void MainApplication::customInput(u64 down, u64 up, u64 held) {
    if(down & KEY_B) {
        this->ReturnToMainMenu();
    }    

    if(down & KEY_PLUS) this->CloseWithFadeOut();
}

void MainApplication::testInput(u64 down, u64 up, u64 held) {

    if(down & KEY_B) {
        this->ReturnToMainMenu();
    }

    if(down & KEY_PLUS) this->CloseWithFadeOut();
}

void MainApplication::mainMenuInput(u64 down, u64 up, u64 held) {

    if(down & KEY_B) {
        this->ReturnToMainMenu();
    }

    if(down & KEY_PLUS) this->CloseWithFadeOut();
}