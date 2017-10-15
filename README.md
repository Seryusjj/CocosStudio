# CocosStudio
CocosStuidio is build on Cocos2D-x framework and integrated within wxWidgets, this is planned to be a game editor for the Cocos2d-x framework.

The philosophy of this editor is to generate the code of the configured scene, this code is going to be compatible with the structure that the cocos2d-x console generate when you create a new project. The code generation is going to be compatible with any of the supported languages by the framework (java script, lua and c++) so depending on your needs you can choose one or the other.

This editor also pretend to integrate assimp to import 3d models into Cocos. Any help is welcome
The project is set up using Cmake and is currently working on Windows and Ubuntu 16.04
The ui is edited with  [wxFormBuilder](https://github.com/wxFormBuilder/wxFormBuilder).

## Building
For Windows development you need visual studio 2015 due to the cocos2d-x gen-libs requirements
Here are the instructions to build the project on windows:
- git clone --recursive https://github.com/Seryusjj/CocosStudio
- Set up cocos2d-x (if you are looking into this project may be you already know how to, if not take a look at [Cocos2d-x](https://github.com/cocos2d/cocos2d-x))
- Once you set up the Cocos console which means that you installed Python 2.7 on your system, you can call the setupWin32.bat script that is going to compile cocos2d-x for us calling the gen-libs command of the Cocos console
- Then you have to compile wxWidgets. Open the solution at external/wxWidgets/build/msw/wx_vc14.sl and on visual studio go to build -> batch build and build everthing.

In the future I will automate this process but since this is done just once I do not write any script for it. The process is going to take some time so grab a cup of coffee or something at this point.

After all the dependencies are compiled you can call Cmake and build the editor.
Just create a build directory and call cmake .. from it. This is going to generate your visual studio solution and you are ready to go.