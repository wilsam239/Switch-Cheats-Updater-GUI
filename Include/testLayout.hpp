#include <pu/Plutonium>

class TestLayout : public pu::ui::Layout {
    public:
        TestLayout();
        PU_SMART_CTOR(TestLayout);
    private:
        pu::ui::elm::TextBlock::Ref helloText;
};