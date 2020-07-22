# LaunchBox
LaunchBox is free game launcher, you can use this program, publish many games in one place, write your own presentation game pages or use website for this purpose (LaunchBox will load website as webBrowser). Main problems are solved such as version checking and updating, installing/uninstalling, this program is also self updating, when i will make new release LaunchBox will notice that and self update. LaunchBox is written in qt-qml/c++. Currenty system works only on windows i will port it on Linux asap

System is complicated i tried to desctibe it in next chapters but as always practise presentation is best so here is youtube link with full explanation/tutorial 101, how to use this system to deploy game.

--------ytlink---------
## Downloads
* Patcher
https://1drv.ms/u/s!An4cPK_Qf39gjxPbbCV4BSI43EUf?e=OyGhiQ
# Overview
System contains two main programs: Patcher and LaunchBox. Patcher is developer tool for generating game patches. (zip packets, json files). LaunchBox is client program, that allows to install your game, update, uninstall, autoupdate wchen newer verion is available. Witch patcher you can split your game files into several packets (zip files). I suggest you to separate library/game engine files, assets, executable files. When newer version is available LaunchBox dowloads packets which contains modified/new files and unpack them to game directory. LauchBox also can delete files that are not neede any more. You dont need any server to comute delta between current client game version and actual, everything is computed on client side in LaunchBox. You only need some space on the internet where you can store game files, it can be ftp or http server, there are many free options. But links to fils must be valid all the time, you cannot change links to files. Update System uses json files which stores information about your game, some of them are generated by Patcher but rest of them needs to be written manually.
# How does it work
![system](ScreenShots/Whole_system.png) 
## Patcher
Open new project -> chose game directory, project directory, project name, gameName. On the right side you can create new packets, change their names etc. On the left side you can see actual state of game directory. Now just open packet and drag folders/files from left window to packet window. When u are done press generate to create files. When u need to create patch just insted of creating new project open existing one {name}.json file. Patcher is in early development (i focused on developing LaunchBox) so if something goes wrong exit and start over i will fix bugs asap. When Game directory changes just mofify path in Project file. I suggest you to make copies of generated files, dont lose them aspecially project file.
### Patcher
![system](ScreenShots/Patcher.png)


Patcher generates 4 components:
1. fileList.json - json file that contains all information about current game directory: files, sizes, hashes, directories etc. After generation manually add urls to your packets http or ftp link (redirections are accepted)
```javascript
{
"AppName": "LaunchBox",
    "Files": {
        "bin": {
            "Id": "0",
            "Sha": "",
            "Size": "0"
        },
        "bin/LaunchBox.exe": {
            "Id": "0",
            "Sha": "35fc22fb9ffed5519493a154807eb9f2e8952be1108ea1870bb7723efe223604",
            "Size": "6836736"
        },
        .
        .
        .
    },
    "Packets": {
      "0": {
        "Name": "packet1.zip",
        "Size": "81398406",
        "Url": "paste here link to this package"
      }
    },
    "Ver": "1.0"
}
```
2. {projName}.json - Porject file contains information about last patch directory status it is almost copy of fileList.json with several additional informations. When you want to create next patch, open this file in Patcher, comparation between current state of game directory and information in this file are used to calculate wchich files was changed/deleted or added.
```javascript
{
 "AppComponents": {
        "packet1.zip": {
            "Files": {
                "bin": {
                    "LaunchBox.exe": {
                        "Sha": "35fc22fb9ffed5519493a154807eb9f2e8952be1108ea1870bb7723efe223604",
                        "Size": "6836736"
                    },
                    .
                    .
                    .
            "Size": "---",
            "Url": "---"
        },
        .
        .
        .
    },
    "AppDir": "C:/Users/Sylwester/Desktop/LaunchBox/DesktopAplication/out/install/x64-Release/LaunchBox",
    "AppName": "LaunchBox",
    "ProjectDir": "C:/Users/Sylwester/Desktop/LaunchBoxProject",
    "ProjectName": "LaunchBox",
    "Ver": "1.0"
}
```
3. game packets - zip files with compressed files from your game directory.
4. patch files - json files with information about delta between current and last state (last patch) of game directory. It contains three main infrmation which files was changed, added and deleted.
```javascript
{
    "AddedFiles": [
        "Nowy folder/Nowy folder",
        "Nowy folder",
        "Nowy folder/asdasd.txt"
    ],
    "AppName": "Sylio",
    "ChangedFiles": [
    ],
    "RemovedFiles": [
    ],
    "Ver": "1.2"
}
```

System  uses also two files that muse be edited manually
* AppInfo.json - Contains main information about game such as current version, link to fileList, and patch files. Update current version of game and add link to new patch file in Versioning section
```javascript
{
  "AppName": "Sylio",
  "Ver": "1.2",
  "FileList": "FileList link",
  "Versioning": {
    "1.2": "link to first patch file",
    "1.1": "link to second patch file",
    "1.0": "link to third patch file"
  }
}
```
* Games.json - Information about your games published in LaunchBox, it contains url to Appinfo, and presentation informations (what to show in game page) i will describe it in next chapter
```javascript
{
  "Sylio": {
    "Id": "1",
    "Ver": "1.0",
    "GameExecPath": "",
    "PresentationUrl": "presentation url",
    "PresentationQml": "",
    "PresentationPackUrl": "",
    "PresentationVer": "1.0",
    "AppInfoUrl": "appinfo url"
  },
  "Rest": {
    "Id": "2",
    "Ver": "1.0",
    "GameExecPath": "",
    "PresentationUrl": "",
    "PresentationQml": "ExampleOne.qml",
    "PresentationPackUrl": "presentation pack url",
    "PresentationVer": "2.0",
    "AppInfoUrl": "appinfo url"
  },
  "Rest2": {
    "Id": "3",
    "Ver": "1.0",
    "GameExecPath": "./Release/Sylio.exe",
    "PresentationUrl": "",
    "PresentationQml": "ExampleOne.qml",
    "PresentationPackUrl": "presentation pack url",
    "PresentationVer": "1.0",
    "AppInfoUrl": "appinfo url"
  }
}
```


Now upload files on the internet, remember to have always valid links

## LaunchBox
Becouse LaunchBox is self updating it contains 3 programs:
* Updater - program thah updates LaunchBox and Game pages if needed
* LaunchBox - main program
* Launcher small program (on Windows is written in C#) that first runs Updater and after its exection LauchBox
### Updater
![system](ScreenShots/Updater.png)
### LaunchBox
![system](ScreenShots/LaunchBox.png)
### Updating Details
User clicks on Launcher -> Updater is executed. First it loads data from files stored in Config folder:
1. LaunchBoxInfo.json - basic information about LaunchBox, your job is to change GamesInfoRepository (Games.json). Leave AppInfoUrl unchanged becouse this link allows to update LaunchBox (link to my repository with newest version of LaunchBox).
```javascript
{
  "Ver": "1.0",
  "AppInfoUrl": "https://onedrive.live.com/download?cid=607F7FD0AF3C1C7E&resid=607F7FD0AF3C1C7E%211883&authkey=AGqaPM6gtR-4R0Y",
  "GamesInfoRepository": "your link to Games.json",
  "DownloadSpeed": "0"
}
```
2. Games.json - Information about your games published in LaunchBox
```javascript
{
  "Sylio": {
    "Id": "1",
    "Ver": "1.0",
    "GameExecPath": "",
    "PresentationUrl": "presentation url",
    "PresentationQml": "",
    "PresentationPackUrl": "",
    "PresentationVer": "1.0",
    "AppInfoUrl": "appinfo url"
  },
  "Rest": {
    "Id": "2",
    "Ver": "1.0",
    "GameExecPath": "",
    "PresentationUrl": "",
    "PresentationQml": "ExampleOne.qml",
    "PresentationPackUrl": "presentation pack url",
    "PresentationVer": "2.0",
    "AppInfoUrl": "appinfo url"
  },
  "Rest2": {
    "Id": "3",
    "Ver": "1.0",
    "GameExecPath": "./Release/Sylio.exe",
    "PresentationUrl": "",
    "PresentationQml": "ExampleOne.qml",
    "PresentationPackUrl": "presentation pack url",
    "PresentationVer": "1.0",
    "AppInfoUrl": "appinfo url"
  }
}
```
These files must be edited by you when u make LaunchBox instalator. Writing Rules:
* LaunchBoxInfo.json - update link to Games.json in GamesInfoRepository slot
* Games.json - it has to be point that this file differs from stored on the internet, its local file stored in Config folder, when Updater launches it downloads Games.json and compares intormation with these stored in this file. Each game is stored in json objects eg: "Sylio", "Rest and "Rest2" by game title. In objects each game has Id it has to be unique number bigger than 0. LaunchBox must have minimum one game in this file. update also AppInfoUrl to each game stored on the internet.

Now updater downloads Appinfo.json, and Games.json, Updater parses Appinfo and if its needed updates LaunchBox, after that Updater parses Games.json, to check if never games are added to LaunchBox, and updates game pages. Here i need to clarify how u can present your game in launchBox, you have two options first is just to paste valid url in PresentationUrl slot (if u have game website), LaunchBox will just load that link as webBrowser and shows on game page, second options is to write your own qml page (qml is verry simple) if its too hard u can use my example (exampleOne.qml) in LaunchBox/Gui folder. I suggest you to use second option becoude webGameEngine works verry slow, and it will be propably hard to fit my design pattern with website. if you use second option u need to specify presentationPackUrl, it is valid link to zip file that should contain files with main qml file. Also u need to specify PresentationQMl as main qml that will be dynamicly loaded by LaunchBox. when u will need to change this presentation page just increment PresentationVer in Games.json file stored on the internet. When while updating versions differ Updater downloads this zip packet and unpack it for LaunchBox. 

When LaunchBox is up to date and game pages are updated, Launcher executes LaunchBox, user can intstall or update game (when installing LaunchBox just downloads all packets without parsing patch files). When Update process starts, LaunchBox downloads AppInfo.json by url specified in Games.json, it parses AppInfo to get version if it differs from actual than update process relly starts, fileList.json is beeing downloaded next, with patch files (links are specified in AppInfo.json). Now Aplication parses information to get which packets must be downloaded to udate game. Next these packets are downloaded and unpacked to game directory, removed files (specified in patch files) are removed from game directory, and update is done. LaunchBox also can pause update process and abort, uninstallation is supported. 

# Frameworks/Libaries/Tools
* [Qt](https://www.qt.io/) Gui framework
* [Curl](https://curl.haxx.se/libcurl/c/libcurl.html) Library used to download files
* [LibArchieve](https://www.libarchive.org/) Library used to zip/unzip packets
* [LibZip](https://libzip.org/) Library used to zip/unzip packets
* [Conan](https://conan.io/) C++ library repository
* [Cmake](https://cmake.org/) C++ build tool
* [VisualStudio](https://visualstudio.microsoft.com/pl/free-developer-offers/) IDE

# License

Distributed under the MIT License. See `LICENSE` for more information.


# Author

Sylwester Dawida </br>
Poland, AGH </br>
2020
