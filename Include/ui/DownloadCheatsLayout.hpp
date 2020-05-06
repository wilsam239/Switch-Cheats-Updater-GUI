#include <pu/Plutonium>

// Define your main layout as a class inheriting from pu::Layout
class DownloadCheatsLayout : public pu::ui::Layout {
    public:

        DownloadCheatsLayout();

        // Have ::Ref alias and ::New() static constructor
        PU_SMART_CTOR(DownloadCheatsLayout)

    private:

        // An easy way to keep objects is to have them as private members
        // Using ::Ref (of a Plutonium built-in object or any class having PU_SMART_CTOR) is an alias to a shared_ptr of the instance.
        pu::ui::elm::TextBlock::Ref helloText;
};