# Emotiv_Insight

This repository will be continuously upadated as of April 4 2020

*** IMPORTANT NOTE [6/22/2020] ***

I recently had to do a factory reset on my laptop and have lost the majority of my files.

But I am in the process of working on getting everything back together, so please bear with me in the meantime.

 =============================  [ INTRODUCTION ]  =============================

The intent of this project was the premise of my Master's thesis which involved an Emotiv Insight, a commerically available EEG headset to control an open sourced, electrical wheelchair with PLA-based 3d printed components that could be either retrofitted, or modified to fit any commonly available push wheelchair for those who don't have the financial resources and/or the physical capabilities to control an electric wheelchair.

Before controlling the proposed wheelchair my intentions were focused on controlling four LEDs successfully. I would then step it up to see if I could successfully control an Arduino-based RC rover before finally controlling the proposed open-sourced wheelchair. The first step taken was to gain access to the streaming EEG data under the assumption that all five EEG signals were to fall within a certain range when the user thought/concentrated on thinking up, down, left, or right.

However after gaining access to the streaming EEG data would require a montly subscription to Emotiv which cost around $100 as of the fall semester of 2018 when I first started this project. Since then Emotiv had implimented a multi-tier pricing, but I was strongly against paying for any sort of subscription with the intentions of making the wheelchair as affordable as possible. Fortunately enough, I somehow stumbled upon the "Emotiv SDK - Community Edition" which provided numerous coding examples that mimicked the funcionality of the programs provided by Emotiv. 

I'm not entirely too sure how long the repository I found the community SDK will stay active, but for now it can be found here --> 
https://github.com/pandark/emotiv-community-sdk

IT'S IMPORTANT TO TAKE NOTE THAT THIS ENTIRE PROJECT WAS DONE IN C++ WITH WINDOWS 10. 

After gaining access to the streaming EEG data, the next step was to figure out how to send the streaming EEG data to the Arduino microcontroller. The Universal Asynchronous Receiver/Transmitter (UART) communication protocol that's built into the Arduino microcontroller can only send data generated from the Arduino back to the Arduino IDE to allow the user to monitor the incoming data in real time, however sending generated data from the computer to the Arduino was not possible using the UART on the Arduino. To resolve this issue various functions from the Win32 API were implimented. In depth documentation of the Win32 API and the various functions and their purpose can be found here --> https://www.xanthium.in/Serial-Port-Programming-using-Win32-API

 =============================  [ FILE MANAGEMENT ]  =============================

Since all of the example programs in the Emotiv Community SDK were written using Visual Studio and I wasn't sure what I was getting myself into, I opted to do the same and I downloaded the 'Community' edition here --> https://visualstudio.microsoft.com/downloads/

------ Steps taken to compile SDK program ------

[ Step 1 ] : Download the Emotiv Community SDK edition from the link in the introduction
https://github.com/pandark/emotiv-community-sdk

[ Step 2 ] : Start Visual Studio and under 'Get started' on the right hand side, click on 'Create a new project'

![Capture22](https://user-images.githubusercontent.com/39348633/83283699-3ccb8980-a1a1-11ea-9e65-ffa6595e668b.JPG)

Then choose in the first drop down menu 'C++' and click on the 'Empty project'

![Visual Studio](https://user-images.githubusercontent.com/39348633/83285122-58379400-a1a3-11ea-99fb-69b7b904f075.JPG)

Once everything is loaded, you'll be presented with a blank screen and the 'Solution Explorer' all the way to your right. All the drop down menus should be expanded and you should see a folder called 'Source Files'. Right click on it and go to 'Add --> New Item'

![Capture22](https://user-images.githubusercontent.com/39348633/83313212-e0855b80-a1da-11ea-9d24-d222ec9e532e.JPG)


Another window will pop up, click/highlight the C++ file option and name the file whatever you wish. Out of habit, I''ll be calling mine main.cpp

![Capture22](https://user-images.githubusercontent.com/39348633/83313256-11659080-a1db-11ea-960f-075b093e18e9.JPG)

[ Step 3 ] : Including the Emotiv header file into the project.

A skeleton code approperately named Emotiv_Bare_Bones can be found in the repoistory and will be used to ensure the header files were linked correctly :https://github.com/Digital1O1/Open-sourced-EEG-Electric-Wheelchair/tree/master/Emotiv_Bare_Bones

After unzipping the Emotiv Community SDK find and open the following folders --> SDK-Master --> Include folder. Click on the address bar of the Include folder and copy the address/contents as we'll need it later to link the header files to the Emotiv_Bare_Bones program.

![image](https://user-images.githubusercontent.com/39348633/83313907-c39e5780-a1dd-11ea-9f05-3a1e9eb46623.png)

To include the Emotiv header files to the Emotiv_Bare_Bones program go back to Visual Studio and click on Project --> 'Project_name Option' which is the last item listed.

Once the property page(s) window pops up click on --> C/C++ --> General --> 'Additional Include Directories' 

Copy and paste the 'path' where the Emotiv header files are located and press apply. 

[ Step 4 ] : Including the path and DLL files

On Windows, if you were to 'build' the program right now by pressing ctrl+shift+b you'll get the following error(s)

![Unresolved_External_Symbol](https://user-images.githubusercontent.com/39348633/83343576-f1f56300-a2c1-11ea-8376-78aafde583c6.JPG)

The LNK2019 is a link error that is thrown for reasons that are currently beyond my reach, but to resolve the DLL files and the path where they are located must be included in the current project.

To do so, to go 'Project' in the menu bar --> 'Whatever you named your project' project properties --> linker -- Input.

![Unresolved_External_Symbol](https://user-images.githubusercontent.com/39348633/83343865-aba20300-a2c5-11ea-9c88-073dc49e29eb.JPG)

Click on the 'Additional dependencies' option and the drop down menu --> edit. 

A window will pop up with three sub-sections. 

In the first just type/add edk.lib, press enter, then add glut32.lib as shown in the screen shot.

![Unresolved_External_Symbol](https://user-images.githubusercontent.com/39348633/83343982-db053f80-a2c6-11ea-9357-307665ef9725.JPG)

To include the path to the .lib files, look for 'VC++ Directories' --> Library Directories.

From there, just copy and paste the path where the .lib files are located as done with the header files

![image](https://user-images.githubusercontent.com/39348633/85937895-8658e280-b8cd-11ea-8a50-f33b79a0bc2f.png)

[ Step 5 ] : Build/Compile the program!

The last step to do is just press ctrl + F5 to run the program and you should see the debug console pop up stating that the program successfully compiled!


![image](https://user-images.githubusercontent.com/39348633/85937924-e2236b80-b8cd-11ea-9d5b-d072a2637170.png)

