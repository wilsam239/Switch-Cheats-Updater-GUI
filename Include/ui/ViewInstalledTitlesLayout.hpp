#include <pu/Plutonium>
#include <titles/titles.hpp>



class ViewInstalledTitlesLayout : public pu::ui::Layout {
    public:
        ViewInstalledTitlesLayout();
        PU_SMART_CTOR(ViewInstalledTitlesLayout);
        void populateMenu();
        void getInstalledTitlesNs();
        std::string formatApplicationId(u64 ApplicationId);
        size_t getTitlesCount();
        
    private:
        pu::ui::elm::Menu::Ref titlesMenu;
        std::vector<Title> titles;
        pu::ui::extras::Toast::Ref toast;
};