#include <ui/MainApplication.hpp>



// If you would like to initialize and finalize stuff before or after Plutonium, you can use libnx's userAppInit/userAppExit

extern "C" void userAppInit()
{
    nsInitialize();
    socketInitializeDefault();
}

extern "C" void userAppExit()
{
    socketExit();
    nsExit();
}

// Main entrypoint
MainApplication::Ref global_app;

int main()
{
    // First create our renderer, where one can customize SDL or other stuff's initialization.
    auto renderer = pu::ui::render::Renderer::New(pu::ui::render::RendererInitOptions(SDL_INIT_EVERYTHING, pu::ui::render::RendererHardwareFlags).WithIMG(pu::ui::render::IMGAllFlags).WithMixer(pu::ui::render::MixerAllFlags).WithTTF());

    // Create our main application from the renderer
    global_app = MainApplication::New(renderer);

    // Prepare out application. This MUST be called or Show() will exit and nothing will be rendered.
    global_app->Prepare();

    // Show -> start rendering in an "infinite" loop
    // If wou would like to show with a "fade in" from black-screen to the UI, use instead ->ShowWithFadeIn();
    global_app->Show();

    // Exit homebrew (Plutonium will handle all disposing of UI and renderer/application, don't worry!

    return 0;
}