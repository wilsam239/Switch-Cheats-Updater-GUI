
#pragma once

// Include Plutonium's main header
#include <pu/Plutonium>
#include <testLayout.hpp>
#include <CustomLayout.hpp>
#include <MainMenuLayout.hpp>

// Define your application (can't instantiate base class, so need to make a derived one)
class MainApplication : public pu::ui::Application
{
    public:
        using Application::Application;
        PU_SMART_CTOR(MainApplication)

        // We need to define this, and use it to initialize everything
        void OnLoad() override;
        TestLayout::Ref &getTestLayout();
        CustomLayout::Ref &getCustomLayout();
        MainMenuLayout::Ref &getMainMenuLayout();

        void ReturnToMainMenu();

        void OnInput(u64 down, u64 up, u64 held);
        void customInput(u64 down, u64 up, u64 held);
        void testInput(u64 down, u64 up, u64 held);
        void mainMenuInput(u64 down, u64 up, u64 held);

    private:

        // Layout instance
        CustomLayout::Ref layout;
        TestLayout::Ref testLayout;
        MainMenuLayout::Ref mainMenuLayout;
};