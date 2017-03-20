#FPDev
Sandbox for Unreal Engine 4.

See the Wiki for more information!



##Simple Setup

###1. Create an Unreal Engine 4 Project:

![create fpdev](https://cloud.githubusercontent.com/assets/1817852/22621947/1ee4f084-eaf5-11e6-9afe-c56f19a4bed4.png)

1. Select from C++ project templates "First Person"
2. Create the template in a Folder separate from Git project location.
3. Name the project "FPDev", otherwise C++ files with not compile.

###2. Clone the project from this site:

![clone using desktop](https://cloud.githubusercontent.com/assets/1817852/22621948/2b5b6d52-eaf5-11e6-9262-0761dbbdccd0.png)

Verify the location where Git Desktop has cloned the project. You will need this folder for the next step.

###3. Copy the files:
  
  Copy and paste files
  From: "Your Git Projects"/FPDev/Source/FPDev/ 
  To: "Your Unreal Projects"/FPDev/Source/FPDev/

  a. Copy all of them.
  
  b. Overwrite in destination if needed. 

###4. Rebuild Solution:

![rebuild](https://cloud.githubusercontent.com/assets/1817852/22622065/2c54e650-eaf7-11e6-93a7-fb7c7f7d12c4.png)

1. With Visual Studio Open, Close the UE4 Editor. (File->Open Visual Studio before closing UE4)
2. In Visual Studio select Build->Rebuild Solution.  (this may take some time, have a snack or chill)
3.  When it finishes you can re-open EU4 and in the C++ folder in content browser you should see all the classes added from Git project.




##Simple Update:

![sync](https://cloud.githubusercontent.com/assets/1817852/22622009/125f5498-eaf6-11e6-8f93-b8f5561ccbeb.png)

1.  Press "Sync" in Github Desktop then repeat step 3 and 4 in setup.

  - If all else fails delete Unreal Project directory and repeat simple Setup 1, 3, and 4. (skip 2 you got the git right?) 


