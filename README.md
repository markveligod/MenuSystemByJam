# :taurus: Menu System By Jam (Documentation)

## :wastebasket: How to use this nonsense ?  
1. git clone `https://github.com/markveligod/MenuSystemByJam.git`
2. Put it in the `Plugins` folder with the project (Example: `YourNameProject/Plugins/MenuSystemByJam`)
3. ReBuild your project and Run UE Editor
4. Open the browser plugin  
![](https://cdn.discordapp.com/attachments/836541085248520233/967407719193649222/unknown.png)
5. Enable the plugin  
![](https://cdn.discordapp.com/attachments/836541085248520233/967408294920605787/unknown.png)
6. Done!

## How to see the plugin in content browser?  
To see the plugin in the content browser, you need to go to `View Options` and Enable `Show plugin content`. Done!  
![](https://cdn.discordapp.com/attachments/836541085248520233/967408720168501248/unknown.png)

## How to make this shit work?  
1. Go to ProjectSettings->Maps&Modes->GameInstanceClass expose `BP_JamMSGameInstance`.
![](https://cdn.discordapp.com/attachments/836541085248520233/967410219598635028/unknown.png)  
2. Create two map: Menu and Game. Put BP_JamMSGameMode on the map Menu in World Settings. On the map Game your GameMode.
![](https://cdn.discordapp.com/attachments/836541085248520233/967411717896278056/unknown.png)
3. Change name map on YOUR MAP in BP_JamMSGameInstance.  
![](https://cdn.discordapp.com/attachments/836541085248520233/967412018715979786/unknown.png)  
4. Done!

## Debug feature
I have written simple functions for rendering any debug information on the screen. To do this, you need to inherit from the DebugHUD class and override Draw function in a AHUD class.  
Example:  
```
void AGameHUD::DrawHUD()
{
    Super::DrawHUD();

    if (this->GameMode && EnableDebugHUD)
    {
        AddText(TEXT("Test function AddText"), FText::FromString("This AddText"));
        AddFloat(TEXT("Test function AddFloat"), 1.488f);
        AddInt(TEXT("Test function AddInt"), 228);
        AddBool(TEXT("Test function AddBool"), false);
        AddBool(TEXT("Test function AddBool"), true);
    }
}
```  
Result:  
![](https://cdn.discordapp.com/attachments/836541085248520233/967741234934341732/unknown.png)  

## 📫 Other
:bangbang: Attention: If you can improve my trash code then make a pull request.  
:bangbang: Attention: If you still have questions, write to the section Issues.

**:copyright:Authors:**  
  
*[Mark Veligod](https://github.com/markveligod)*  
