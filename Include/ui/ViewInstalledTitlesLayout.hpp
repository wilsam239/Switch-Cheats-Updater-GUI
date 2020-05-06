#include <pu/Plutonium>

class ViewInstalledTitlesLayout : public pu::ui::Layout {
    public:
        ViewInstalledTitlesLayout();
        PU_SMART_CTOR(ViewInstalledTitlesLayout);
    private:
        pu::ui::elm::TextBlock::Ref helloText;
};