#LaOwlSandbox
Sandbox for Unreal Engine 4.

See the Wiki for more information!



##Simple Setup

### 1. Create an Unreal Engine 4 Project:

![create laowlsandbox](https://cloud.githubusercontent.com/assets/1817852/25784857/c98c160c-3339-11e7-92e7-3ab5cf76f366.png)

1. Select from C++ project tab "Basic Code"
2. Create the project in a Folder separate from Git project location.
3. Name the project "LaOwlSandbox", otherwise C++ files may not compile.
    * You will also need to add some input bindings and modify some of the GameMode settings. [Read more here.](https://github.com/LaOwlLol/FPDev/wiki/UE4-Project-Settings-and-details.)

### 2. Clone the project from this site:

Verify the location where Git Desktop has cloned the project. You will need this folder for the next step.

### 3. Copy the files:
  
  Copy and paste files

From: "Your Git Projects"/LaOwlSandbox/Source/LaOwlSandbox/ 

To: "Your Unreal Projects"/LaOwlSandbox/Source/LaOwlSandbox/

  a. Copy all of them.
  
  b. Overwrite in destination if needed. 

  c. Do the same for LaOwlSandbox/Content directories.  (You should already have starter content generated UE4 by including the starter content when creating the project.)

 
### 4. Rebuild Solution:

1. With Visual Studio Open, close the UE4 Editor. (File->Open Visual Studio before closing UE4)
2. In Visual Studio select Build->Rebuild Solution.  (This may take some time, have a snack or chill)
3.  When it finishes you can re-open UE4 and in the C++ folder in content browser you should see all the classes added from Git project.



##Simple Update:

![sync](https://cloud.githubusercontent.com/assets/1817852/22622009/125f5498-eaf6-11e6-8f93-b8f5561ccbeb.png)

1.  Press "Sync" in Github Desktop then repeat step 3 and 4 in setup.

  - If all else fails delete Unreal Project directory and repeat simple Setup 1, 3, and 4. (skip 2 you got the git right?) 


