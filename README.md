# Switch Cheats Updater GUI
<p align="center">
<img src = "https://raw.githubusercontent.com/wilsam239/Switch-Cheats-Updater-GUI/master/icon.jpg"\><br>
<img src = "https://user-images.githubusercontent.com/11286118/81375217-60705680-9144-11ea-9429-8c517b998488.PNG" height="240"\>
<img src = "https://user-images.githubusercontent.com/11286118/81375240-6ebe7280-9144-11ea-8a34-11366cbd5404.PNG" height="240"\><br>
</p>
A GUI version of my fork of the Switch Cheats Updater homebrew application.

This app makes use of XorTroll's Plutonium library for developing switch homebrew GUI's.
## Required For Compilation
A number of tools are required to compile this project. They are listed below.
### DevkitPro
In order to compile the app, you will need to have installed devkitPro from [here](https://devkitpro.org/wiki/Getting_Started). Once installed, a number of libraries will need to be installed (other than the default libraries that get installed during the setup).

### Pacman Packages

Once devkitpro has been installed, a number of libraries will be required in order to run this project.

Install the following packages:
```
switch-sdl2 switch-sdl2_ttf switch-sdl2_image switch-sdl2_gfx switch-sdl2_mixer switch-mesa switch-glad switch-glm switch-libdrm_nouveau switch-libwebp switch-libpng switch-freetype switch-bzip2 switch-libjpeg-turbo switch-opusfile switch-libopus switch-curl switch-zziplib
``` 

### Plutonium
As mentioned above, [Plutonium](https://github.com/XorTroll/Plutonium) is the foundation of this project. The repo is initialised with a submodule in the `libs/Plutonium` folder, which will need to be updated accordingly.

To update a submodule repo:
1. Open a bash prompt in the directory where `Switch-Cheats-Updater-GUI` has been 
cloned
2. Run `git submodule init`
3. Run `git submodule update`

Alternatively, if you clone this repo with the `git clone --recourse-submodules` command, it will be automatically cloned for you.

***Note: After updating the Plutonium submodule, you will be required to compile it too, in order to generate the `Output` folder that is required in the `makefile`***


