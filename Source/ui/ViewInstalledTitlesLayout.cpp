#include <ui/MainApplication.hpp>

ViewInstalledTitlesLayout::ViewInstalledTitlesLayout() : Layout::Layout() {

    // Create the TextBlock instance with the text we want
    this->helloText = pu::ui::elm::TextBlock::New(300, 300, "This is my custom text! Fuk u Ethan");

    this->Add(this->helloText);
}