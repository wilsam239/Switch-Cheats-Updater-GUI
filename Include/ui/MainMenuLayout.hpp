#pragma once

#include <pu/Plutonium>

class MainMenuLayout : public pu::ui::Layout {
    public:
        MainMenuLayout();
        PU_SMART_CTOR(MainMenuLayout);

        void downloadMenuItem_Click();
        void viewInstalledMenuItem_Click();
        void deleteMenuItem_Click();

    private:
        pu::ui::elm::Menu::Ref optionMenu;
        pu::ui::elm::MenuItem::Ref downloadMenuItem;
        pu::ui::elm::MenuItem::Ref viewInstalledMenuItem;
        pu::ui::elm::MenuItem::Ref deleteMenuItem;
};