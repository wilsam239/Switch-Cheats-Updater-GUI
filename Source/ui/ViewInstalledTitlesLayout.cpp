#include <ui/ViewInstalledTitlesLayout.hpp>
#include <ui/MainApplication.hpp>

extern MainApplication::Ref global_app;

ViewInstalledTitlesLayout::ViewInstalledTitlesLayout() : Layout::Layout() {

    this->titlesMenu = pu::ui::elm::Menu::New(0, 100, 1280, foreground, 80, 560);
    this->titlesMenu->SetOnFocusColor(focus);
    
    this->Add(titlesMenu);
}

void ViewInstalledTitlesLayout::titleMenuItem_Click() {
    Title sel = this->titles[this->titlesMenu->GetSelectedIndex()];
    global_app->CreateShowDialog(sel.name, formatApplicationId(sel.id), {"Close"}, false);
}

void ViewInstalledTitlesLayout::populateMenu() {
    for(int i = 0; i < this->titles.size(); i++) {
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

size_t ViewInstalledTitlesLayout::getTitlesCount() {
    return this->titles.size();
}