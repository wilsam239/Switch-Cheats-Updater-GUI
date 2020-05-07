
#pragma once

// Include Plutonium's main header
#include <pu/Plutonium>
#include <ui/ViewInstalledTitlesLayout.hpp>
#include <ui/DownloadCheatsLayout.hpp>
#include <ui/MainMenuLayout.hpp>
#include <titles/titles.hpp>
#include <sstream>

#define focus      pu::ui::Color::FromHex("#6E6E72")
#define foreground pu::ui::Color::FromHex("#45454A")
#define background pu::ui::Color::FromHex("#303036")
#define dialog     pu::ui::Color::FromHex("#3F3F3F")
#define whiteText  pu::ui::Color::FromHex("#FFFFFF")
#define blueText   pu::ui::Color::FromHex("#38B38C")

// Define your application (can't instantiate base class, so need to make a derived one)
class MainApplication : public pu::ui::Application
{
    public:
        using Application::Application;
        PU_SMART_CTOR(MainApplication)

        // We need to define this, and use it to initialize everything
        void OnLoad() override;
        ViewInstalledTitlesLayout::Ref &getViewInstalledTitlesLayout();
        DownloadCheatsLayout::Ref &getDownloadCheatsLayout();
        MainMenuLayout::Ref &getMainMenuLayout();

        void ReturnToMainMenu();

        void OnInput(u64 down, u64 up, u64 held);
        void customInput(u64 down, u64 up, u64 held);
        void testInput(u64 down, u64 up, u64 held);
        void mainMenuInput(u64 down, u64 up, u64 held);

        void debugDialog(std::string err);
        void debugDialog(std::stringstream& err);

    private:
        /*pu::ui::elm::TextBlock::Ref timeText;
        pu::ui::elm::TextBlock::Ref batteryText;
        pu::ui::elm::Image::Ref batteryImage;
        pu::ui::elm::Image::Ref batteryChargeImage;*/
        pu::ui::elm::Image::Ref menuBanner;

        // Layout instance
        DownloadCheatsLayout::Ref downloadCheats;
        ViewInstalledTitlesLayout::Ref viewInstalledTitles;
        MainMenuLayout::Ref mainMenu;
};