﻿Summary:
* BIT_SAVER
* Version - 1.0.0
* Team - KIN GAME
* Developers & authors 
   *  Jaewoo Choi, Sunwoo Lee, Hyun Kang, Hyosang Jung


* Website / GitHub repo URL https://github.com/Rudy-Castan-DigiPen-Teaching/game-project-kingame
   * May have 404 warnings because it is a private repository.


* Small description of the game
   * Our game is a rhythm game. There are interesting effects on the game. Players should press the key with the music’s rhythm.
* License
   * Digipen has all rights for this project license.


________________

Before Starting:
* Software/hardware requirements basic computer setting.
   * Visual Studio 2019
      * How To Download: https://www.youtube.com/watch?v=IsAoIqnNia4
        


* Links and short installation instructions for necessary programs/IDE’s/libraries
   * OpenGL - https://www.opengl.org/
      * Already included in the project(Unnecessary to download)
   * FMOD - https://www.fmod.com/
      * Already included in the project(Unnecessary to download)
   * FreeType - https://freetype.org/
      * Already included in the project(Unnecessary to download)
   * Libraries not listed here are also already included in the project.
                

________________

Installation Instructions:
* How to open the source code from the IDE (Which file, etc)
   * Open BIT_SAVER.sln 
* How to set environment variables (if necessary)
   * Unnecessary( All done )
* How to set the correct compiler version (if necessary)
   * Visual studio Version 16.11.5 recommended.
* Any additional information or changes
   * None


________________

Run/Build Code:
* What to run/build properties are needed
   * It needs to include directories, post-build event properties.
      * All are already included in vcxproj


* Any errors/warnings that the user should expect
   * There are sometimes unexpected errors with FMOD. 
      * If it happens, the user should rebuild the solution and run it
   * Some recommendation warnings for using enum rather than enum class.
   * GLModel member variables uninitialized warning.


* What button or command line arguments needed to compile
   * After opening BIT_SAVER.sln in visual studio, press ctrl+F5 to run the game.

________________

Play:
* Any expected windows/visuals/audio
   * One window starting with a Digipen splash screen.
   * After our game logo splash screen, Mainmenu with play instructions popup.
      * Press P to start stage.
        
* Instructions of how to navigate any menus (Buttons, menus, etc)
   * keyboard (F / up) : move the main character to the Top.
   * keyboard (J / down) : move the main character to the bottom.
   * keyboard (ESC) : pause button.
      * Keyboard up, down to switch options
      * Volume up, down with keyboard left, right
      * Keyboard enter on restart will restart current stage
      * Keyboard enter on quit will go back to Main Menu
      * Pressing pause button once more will resume current stage


* Gameplay instructions (How to play the game)
   * The player has a life bar on top of the character, and every time the node is missed, life decreases.
   * If it’s life bar disappears(life == 0), the game is over.
   * In one stage, we have two different scenes.


   * General scene
      * The player just taps (F / Up), (F / Down) to match the rhythm.


   * Boss scene
      * When the small character on top of the screen goes to the red area, the Boss scene starts. 
      * The music tempo and note speed gets faster.
      * A Fever gauge pops up on the bottom of the screen.
      * It increases every time the player attacks the node.
      * When the gauge is full, the hit score increases.        
      * If the player retains the combo, the fever gauge fills up faster.
        
* Expected final goal/result/boss
   * The playtime will be roughly 3 and a half minutes.
   * If the small character runs although the end(The song is finished), the stage is cleared and the results, descriptions to go to MainMenu pops up.


________________

FAQ/Common Mistakes:
* Common installation mistakes that people might make
   * Just unzip it. Open BIT_SAVER.sln. Press Ctrl + F5
* Any common errors or crashes that may occur
   * In the solution directory, there should be lib files.
* Gameplay errors
   * The particles that needed to be disappeared popped up randomly.

________________

Feedback:
* Contact information for help or feedback
   * Contact our team producer Sunwoo Lee
      * Discord - sunwoo.lee(이선우)#6066
      * Kakaotalk ID- happy9078
      * Email - sunwoo9078@gmail.com

* Optional Questions
   * Was the playtest fun? (0(worst)~10(best))
   * The reason for the rating?
   * Did you feel the rhythm? (0(worst)~10(best))
   * What did you feel most distracting while playtest?
   * What would you do to improve this game? Ideas or Feedbacks.
