# <img src="./res/icons/icon.jpg" height="42" width="45" align="top"/>tpgz</h1>

## About

tpgz is a rom hack of the game Twilight Princess geared towards enhancing practice and testing for speedrunning.

<p align="center">
  <img src="./res/icons/giphy.gif?raw=true" />
</p>

## Features

```
Use L+R+dpadDown to open the main menu which contains the following options:

cheats menu:
- infinite air                  // Gives Link infinite air underwater
- infinite arrows               // Gives Link 99 arrows
- infinite bombs                // Gives Link 99 bombs in all bags
- infinite hearts               // Link will always have full hearts
- infinite oil                  // Gives Link infinite lantern oil
- infinite rupees               // Link will always have 1000 rupees
- infinite slingshot            // Gives Link 99 slingshot pellets
- invincible                    // Makes Link invincible (no hurtbox, but can still take fall damage and drown)
- invincible enemies*           // Makes some enemies invincible (infinite health)
- moon jump                     // Hold R+A to moon jump
- super clawshot (TBD)          // Clawshot is long and can grab most things (not implemented yet)
- super spinner (TBD)           // Spinner is very fast and can hover (not implemented yet)

flags menu:
- boss flag                     // Set the boss flag value. Press A to lock the value
- epona stolen                  // Toggle flag for Epona being stolen
- epona tamed                   // Toggle flag for Epona being tamed
- map warping                   // Toggle flag for having map warping
- midna charge                  // Toggle flag for Midna charge
- midna healthy                 // Toggle flag for Midna being healthy/sick
- midna on back                 // Toggle flag for Midna appearing on Wolf Link's back
- midna on z                    // Toggle flag for being able to use Midna
- transform/warp                // Toggle flag for transforming/warping
- wolf sense                    // Toggle flag for having wolf sense

inventory menu:
- item wheel                    // Can set the 24 item wheel slots to any item
- pause menu (TBD)              // Can modify the pause menu collection (not implemented yet)

memory menu:
- Add memory watches to the screen (not implemented yet)

practice menu:
- Load practice files* (only supports popular any% locations currently)

scene menu:
- disable bg music*             // Disables background and enemy music
- disable sfx                   // Disables sound effects (item, weather, etc.)
- freeze actors                 // Freezes actors
- freeze camera                 // Locks the camera in place
- hide actors                   // Hides actors
- hide hud                      // Hides the heads-up display
- time (hrs)                    // The current in-game hour
- time (mins)                   // The current in-game minutes

settings menu:
- log level                     // Changes log level for debugging
- drop shadows                  // Adds shadows to all font letters
- save card                     // Save settings to memory card
- load card                     // Load settings from memory card
- area reload behavior          // load area = Reload last area; load file = Reload last file

tools menu:
- area reload                   // Use L+R+Start+A to reload current area
- fast bonk recovery            // Reduces bonk animation significantly
- fast movement                 // Link's movement is much faster
- gorge checker                 // Use L+Z to warp to Kakariko Gorge
- input viewer                  // Show current inputs (buttons only for now)
- link debug info               // Show Link's position, angle, and speed
- no sinking in sand            // Link won't sink in sand
- roll checker                  // Frame counter for chaining rolls
- teleport                      // dpadUp to set, dpadDown to load
- timer                         // Frame timer: Z+A to start/stop, Z+B to reset
- link tunic color:             // Changes Link's tunic color (green, blue, red, orange, yellow, white, or cycle)

warping menu:
- warp to dungeons, towns, grottos, etc. (not implemented yet)
```

## Known Bugs

```
- invicible enemies cheat can't be turned off once turned on
- disabled bg music tool may not always disable bg music
- loading practice files can crash in certain situations
```

## Planned Features

```
- free cam
- actor spawner
- frame advance
- collision viewer
- menu font selector
- lag counter & loading counter
```

## Download / Usage

You will need the **Twilight Princess ISO** -- currently only the US version is supported.

1. Download the latest release [here](https://github.com/hallcristobal/tpgz/releases).

2. Unzip the contents into a folder and run the `romhack-patcher.exe`

3. Select the associated patch file and the Twilight Princess ISO

4. Click apply

   - You will be asked to select a save directory for the newly patched ISO. After giving the ISO a name, the patcher will freeze briefly while generating the ISO.

5. You can now load the generated ISO in Dolphin emulator or in a Wii in a homebrew loader such as [Nintendont](https://github.com/FIX94/Nintendont).

6. Use L+R+dpadDown to open the features menu in game.

## Project structure

```
tpgz
├───.github
│   └───workflows         // github action(s) used to test code compilation
├───external              // external libraries and programs consumed by tpgz
│   ├───fonts             // small rust program to generate raw bytes and c code for utilizing true-type fonts in game
│   │   ├───fonts         // ttf files
│   │   └───src           // source code for fonts
│   ├───gcn_c             // game independent gamecube apis to link to
│   │   ├───include       // header files for gcn_c
│   │   └───src           // source code for gcn_c
│   └───libtp_c           // game bindings for twilight princess
│       ├───.github
│       │   └───workflows // github action(s) used to test code compilation
│       ├───include       // header files for libtp_c
│       └───src           // source code for libtp_c
├───include               // header files for tpgz
│   └───fonts             // individual font properties such as width, height, glyphs, etc.
├───res                   // external resources to be consumed
│   └───save_files        // raw quest log bytes to be injected at compile time
└───src                   // source code for tpgz
    └───fonts             // raw bytes for fonts
```

## Building

See [BUILDING](./BUILDING.md).

## Contributing

See [CONTRIBUTING](./CONTRIBUTING.md).