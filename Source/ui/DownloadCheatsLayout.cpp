#include "MainApplication.hpp"

DownloadCheatsLayout::DownloadCheatsLayout() : Layout::Layout()
{
    // Create the TextBlock instance with the text we want
    this->helloText = pu::ui::elm::TextBlock::New(300, 300, "Press X to answer my question");
    
    // Add the instance to the layout. IMPORTANT! this MUST be done for them to be used, having them as members is not enough (just a simple way to keep them)
    this->Add(this->helloText);

    
}