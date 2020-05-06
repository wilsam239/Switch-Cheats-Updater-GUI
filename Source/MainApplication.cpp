#include <MainApplication.hpp>

extern MainApplication::Ref global_app;

void MainApplication::OnLoad()
{
    // Create the layout (calling the smart constructor above)
    this->layout = CustomLayout::New();
    this->layout->SetOnInput(std::bind(&MainApplication::customInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    this->testLayout = TestLayout::New();
    this->testLayout->SetOnInput(std::bind(&MainApplication::testInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    this->mainMenuLayout = MainMenuLayout::New();
    this->mainMenuLayout->SetOnInput(std::bind(&MainApplication::mainMenuInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

    // Load the layout. In applications layouts are loaded, not added into a container (you don't select an added layout, just load it from this function)
    // Simply explained: loading layout = the application will render that layout in the very next frame
    this->LoadLayout(this->mainMenuLayout);
}

TestLayout::Ref &MainApplication::getTestLayout() {
    return this->testLayout;
}

CustomLayout::Ref &MainApplication::getCustomLayout() {
    return this->layout;
}

MainMenuLayout::Ref &MainApplication::getMainMenuLayout() {
    return this->mainMenuLayout;
}

void MainApplication::ReturnToMainMenu() {
    this->LoadLayout(this->mainMenuLayout);
}

void MainApplication::OnInput(u64 down, u64 up, u64 held)
{
    if(down & KEY_PLUS) this->CloseWithFadeOut();
}

void MainApplication::customInput(u64 down, u64 up, u64 held) {
    if(down & KEY_X) // If X is pressed, start with our dialog questions!
    {
        int opt = this->CreateShowDialog("Question", "Do you like apples?", { "Yes!", "No...", "Cancel" }, true); // (using latest option as cancel option)
        if((opt == -1) || (opt == -2)) // -1 and -2 are similar, but if the user cancels manually -1 is set, other types or cancel should be -2.
        {
            this->CreateShowDialog("Cancel", "Last question was canceled.", { "Ok" }, true); // If we will ignore the option, it doesn't matter if this is true or false
        }
        else
        {
            switch(opt)
            {
                case 0: // "Yes" was selected
                    this->CreateShowDialog("Answer", "Really? I like apples too!", { "Ok" }, true); // Same here ^
                    break;
                case 1: // "No" was selected
                    this->CreateShowDialog("Answer", "Oh, bad news then...", { "OK" }, true); // And here ^
                    break;
            }
        }
    } else if(down & KEY_B) {
        this->ReturnToMainMenu();
    }
}

void MainApplication::testInput(u64 down, u64 up, u64 held) {

    if(down & KEY_B) {
        this->ReturnToMainMenu();
    }
}

void MainApplication::mainMenuInput(u64 down, u64 up, u64 held) {

    if(down & KEY_B) {
        this->ReturnToMainMenu();
    }
}