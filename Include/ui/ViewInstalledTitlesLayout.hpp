#pragma once

#include <titles/titles.hpp>
#include <pu/Plutonium>

class ViewInstalledTitlesLayout : public pu::ui::Layout {
    public:
        ViewInstalledTitlesLayout();
        PU_SMART_CTOR(ViewInstalledTitlesLayout);
        void populateMenu();
        void setInstalledTitles();
        void clearTitles();
        void titleMenuItem_Click();
        size_t getTitlesCount();
        
    private:
        pu::ui::elm::Menu::Ref titlesMenu;
        std::vector<Title> titles;
        pu::ui::extras::Toast::Ref toast;
};