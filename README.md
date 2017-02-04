#FPDev
First Person Shooter Development for Unreal Engine 4.




##Simple Setup

###1. Create an Unreal Engine 4 Project:

![create fpdev](https://cloud.githubusercontent.com/assets/1817852/22621947/1ee4f084-eaf5-11e6-9afe-c56f19a4bed4.png)

1. Select from C++ project templates "First Person"
2. Create the template in a Folder separate from Git project location.
3. Name the project "FPDev", otherwise C++ files with not compile.

###2. Clone the project from this site:

![clone using desktop](https://cloud.githubusercontent.com/assets/1817852/22621948/2b5b6d52-eaf5-11e6-9262-0761dbbdccd0.png)

Verify the location where Git Desktop has clone the project. You will need this folder for the next step.

###3. Copy the files:
  
  Copy and paste files
  From: "Your Git Projects"/FPDev/Source/FPDev/ 
  To: "Your Unreal Projects"/FPDev/Source/FPDev/

  a. Copy all of them.
  
  b. Overwrite in destination if needed. 

###4. Refresh Visual Studio Project:

![refresh](https://cloud.githubusercontent.com/assets/1817852/22622048/c87c8b4c-eaf6-11e6-95bc-c3086a01cc27.png)

In the UE4 Editor select File->Refresh Visual Studio Project.

###5. Close UE4 Editor and in Rebuild Solution:

![rebuild](https://cloud.githubusercontent.com/assets/1817852/22622065/2c54e650-eaf7-11e6-93a7-fb7c7f7d12c4.png)

1. With Visual Studio Open, Close the UE4 Editor. (You might need to select File->Open Visual Studio before closing UE4)
2. In Visual Studio select Build->Rebuild Solution.  (this may take some time, have a stack or chill)
3.  When it finishes ryou can reopen EU4 and in the C++ folder in content browser you should see all the classed added from Git project.   (if you still don't see them try refresh VS project, step 4, one more time)




##Simple Update:

![sync](https://cloud.githubusercontent.com/assets/1817852/22622009/125f5498-eaf6-11e6-8f93-b8f5561ccbeb.png)

1.  Press "Sync" in Github Desktop then repeat step 3 to 5 in setup.

  - If all else fails delete Unreal Project directory and repeat simple Setup 1 and 3 - 5. (skip 2 you got the git right?) 




##Usage:

1.  Do anything you want in the Unreal Project.

2.  For the time being do not save in the Git Project.

3.  Simple update only below.




##Extending C++ Classes to create a Blueprint Class:

###1. In Content Browser open the C++ Source folder:

![sourcefolder](https://cloud.githubusercontent.com/assets/1817852/22622353/38dd68a6-eafd-11e6-98d9-815d8eb77430.png)

You must click on the little folder icon to select the C++ folder.

###2. Right click on a "Base Class" to extend and select the "Create Blueprint class based on ...." option.

![extend](https://cloud.githubusercontent.com/assets/1817852/22622388/0dbbf40c-eafe-11e6-8186-ab953452aec8.png)

I'll show you an example with the MortalActor class.

###3. Give your Blueprint Class a name, and BE SURE TO Save in the Blueprints folder.

![nameblueprint](https://cloud.githubusercontent.com/assets/1817852/22622403/9e57bf50-eafe-11e6-94e8-6f8550150a63.png)

BE SURE TO SAVE IN THE BLUEPRINTS FOLDER!

###4.  Customize you class in the Blueprints Editor.

![browsetobps](https://cloud.githubusercontent.com/assets/1817852/22622422/07ba2136-eaff-11e6-84af-44906b310549.png)

If the BP editor does not open automatically navigate to your new BP class in the content browser and open the BP editor by double clicking your new BP class.

![bpexample](https://cloud.githubusercontent.com/assets/1817852/22622429/4fd582b2-eaff-11e6-8996-052d6b1e669b.png)

MortalActors just implement the health system, with no thing else added. For this Example I added a static mesh component and assigned it a 1M_Cube_Champfer static mesh from the starter content with the M_Concrete_Grime material also from stater content.

I've also Overridden the HeathDepleatedEvent (part of MortalActors health system) to spawn an exploasion Emitter effect at the cubes loaction and destroy the actor.

##C++ Objects available to extend ATM:

FPDevProjectile

WeaponComponent

MortalActor

FPDevCharacter (kinda, there is already one extension "FirstPersonCharacter" from the template, you can modify this or make a new extension, but be sure to add it to the World and remove the old one. You may have input issues when testing by doing this).


##Example:  Apply damage with FPDevProjectile HitEvent.

You will want to do this for any projectile class you create, so that they apply damage to MortalActor objects they collide with.  

As we develope the game mechanics this will evolve to incoperate different damage types.  This basic method will work for now.

###1. Add the HitEvent to EventGraph:

![add hitevent](https://cloud.githubusercontent.com/assets/1817852/22622543/88b687a4-eb02-11e6-990a-05503d27aa7a.png)

###2. Cast Other to Mortal and use ApplyPointDamage:

![hitevent damage](https://cloud.githubusercontent.com/assets/1817852/22622544/88bb1c42-eb02-11e6-8ab7-1a5cba8c2c0f.png)

