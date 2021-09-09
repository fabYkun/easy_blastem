# EasyBlastem
EasyBlastem is a fork of [BlastEm](https://www.retrodev.com/blastem) and [Steamshim](https://github.com/icculus/steamshim). It was developed to let Windows and macOS users enjoy megadrive games on Steam without worrying about emulator shenanigans. It is used for the Steam version of Demons of Asteborg and serves as a base for the Switch port. After building you are left with a steam launcher and a moded emulator executable that launches your rom automatically. 

## Features
- Everything [BlastEm](https://www.retrodev.com/blastem) and [Steamshim](https://github.com/icculus/steamshim) (reliable megadrive emulator, steam API access)
- Access to settings menu, save, unlock achievements and send stats to Steam directly from the game
- Aspect ratio options (4:3, 16:9), windowed and fullscreen modes, overlay image and shaders
- Friendlier settings menu featuring a new A-B-C type controller configuration, still fully customizable for power users in file default.cfg
- Localized settings menu (french, german, english, brazilian portuguese, spanish and italian)

# Emulation
## Setup
1. On Windows, install [MSYS2](https://www.msys2.org/) and open a *MSYS2 MINGW 64-bit* terminal, on macOS the default terminal will do. 

2. Check if you have make, gcc and gdb installed. Install them otherwise.

```
    make --version
    g++ --version
    gdb --version
```
3. Fetch [glew](http://glew.sourceforge.net/index.html) and [sdl2](https://www.libsdl.org/download-2.0.php) and put their lastest binaries and headers in their corresponding folders at the root of the project.  

_On Windows you can download their lastest versions but alternatively, or if you are on macOS, you can build the sources yourself using the make command._

4. Make the project !
Navigate to the root and input one of the following command depending on if you're using Windows or macOS:
```
    make OS=Windows CPU=x86_64
```
```
    make OS=Darwin PORTABLE=1
```
Now if this does not work chances are that one or more path defined in the makefile, either for dependencies (SDL2, Glew) or GCC, are misleading. Check if the values for GLEW_PREFIX, SDL2_PREFIX and CC are correctly defined in the Makefile. 

5. Launch the project !

Now just make sure to have the SDL2 dynamic library and your rom.bin in /output and you're up for the next part. 

### Build and debug setup on Visual Studio Code
On Windows, Visual Studio Code needs to be launched from  a *[MSYS2](https://www.msys2.org/) MINGW 64-bit* terminal. 

Download the extension "Makefile Tools" and change cwd and binaryPath in settings.json so that it links the correct files. 
Now you can build the project from Visual Studio Code and use break points to debug it. 

## Configuration
- The name of the program file is set in the Makefile via the NAME variable. 
You'll want to change EasyBlastem.rc to reflect that change as well and review its content. 
- The program loads and launches ROM_PATH right away by default. 
- Savefiles are stored in SAVE_DIR. The program saves on exit and/or if triggered by a save log. 
- APP_NAME defines the name of the window and the directory containing configuration files whose, once modified by the user, are stored in %localappdata%/APP_NAME (Windows) or $HOME/.config/ (UNIX). 
APP_NAME (EasyBlastem), ROM_PATH (rom.bin), SAVE_DIR (SavesDir) are defined in blastem.h

# Steam Integration
## Setup
1. Create a Visual Studio/Xcode project (having a platform-specific editor such as those will be easier for production-ready builds) containing steamshim_parent.cpp, edit it to have its GAME_LAUNCH_NAME set to NAME (see configuration above). 
2. Fetch steam's [SDK](https://partner.steamgames.com/) and put its content in its corresponding folders at the root of the project.
3. Find steam's header directory (sdk/public/steam/) and static .lib library (sdk/redistributable_bin) and link them in your project. 
4. Find steam's dynamic library (sdk/redistributable_bin) and put it in your output directory
5. Have steam runing on a developer account, create a steam_appid.txt in your output directory containing your appid number. If you have your running EasyBlastem executable, your launcher, dynamic library, correct appid and steam runing on a developer account then it should all work ! If not you can refer to [Steamshim's readme](https://github.com/icculus/steamshim) and error logs. 
6. Get your silly megadrive game having its best life in the wildlands of steam !

### Quicknote on having it work on macOS
Your game might run on macOS but to put it on steam you'll have to get it notarized. Both EasyBlastem and SteamLauncher will need to pass this process. Having one or both executable build process on Xcode might help but you can manage it, good luck you can start with the official [documentation](https://developer.apple.com/documentation/security/notarizing_macos_software_before_distribution). 

## Usage
The game should communicate with the emulator using logs. If you are using [SGDK](https://github.com/Stephane-D/SGDK) use its function KLog(). EasyBlastem will try to parse logs this way:


```[EzB]:MENU``` > To open the settings menu

```[EzB]:SAVE``` > To trigger a save

```[EzB]:LANGUAGE:NUMBER``` > To change EasyBlastem language (*where NUMBER is a valid Language_Id defined in steam_cmd.h*)

```[EzB]:SUCCESS:STRING``` > To unlock a steam success (*where STRING is the api string defined on the steam website and steam_cmd.c*)

```[EzB]:STAT:STRING``` > To increase a stat by 1 (*where STRING is the api string defined on the steam website and steam_cmd.c and steam_cmd.h*)