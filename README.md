# Emotiv_Insight

This repository will be continuously upadated as of April 4 2020

 =============================  [ INTRODUCTION ]  =============================

The intent of this project was the premise of my Master's thesis, which was to use the Emotiv Insight, a commerically available EEG headset to control an open sourced, electrical wheelchair with PLA-based 3d printed components that could be either retrofitted, or modified to fit any commonly available push wheelchair for those who don't have the financial resources and/or the physical capabilities to control an electric wheelchair.

My intial intentions were to use both the Emotiv Insight and an Arduino microcontroller to control four directional LEDs successfully, then I would step it up and control an Arduino-based RC rover and finally the proposed open-sourced wheelchair. The first step taken was to gain access to the streaming EEG data under the assumption that all five EEG signals were to fall within a certain range when the user thought/concentrated on thinking up, down, left, or right.

However, gaining access to the streaming EEG data would require a montly subscription to Emotiv which cost around $100 as of the fall semester of 2018 when I first started this project. Since then Emotiv had implimented a multi-tier pricing, regardless of the pricing, I wanted to avoid paying any sort of montly fee. Fortunately enough, I somehow stumbled upon the "Emotiv SDK - Community Edition" which provided numerous coding examples that mimicked various functions found in other programs provided by Emotiv. I'm not entirely too sure how long the repository I found the community SDK will stay active, but for now it can be found here --> 
https://github.com/pandark/emotiv-community-sdk

IT'S IMPORTANT TO TAKE NOTE THAT THIS ENTIRE PROJECT WAS DONE IN C++ WITH WINDOWS 10. 

After gaining access to the streaming EEG data, the next step was to figure out how to send the streaming EEG data to the Arduino microcontroller. The Universal Asynchronous Receiver/Transmitter (UART) communication protocol that's built into the Arduino microcontroller can only send data generated from the Arduino back to the Arduino IDE to allow the user to monitor the incoming data in real time, however sending generated data from the computer to the Arduino was not possible using the UART on the Arduino. To resolve this issue various functions from the Win32 API were implimented. In depth documentation of the Win32 API and the various functions and their purpose can be found here --> https://www.xanthium.in/Serial-Port-Programming-using-Win32-API

 =============================  [ FILE MANAGEMENT ]  =============================

Since all of the example programs were written using Visual Studio and I wasn't sure what I was getting myself into, I opted to do the same and I downloaded the 'Community' edition here --> https://visualstudio.microsoft.com/downloads/

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

A skeleton code that reference to the Emotiv header files used in this project can be found at the following link and will be used to ensure the header files were linked correctly :https://github.com/Digital1O1/Open-sourced-EEG-Electric-Wheelchair/tree/master/Emotiv_Bare_Bones

Go to where you unzipped the Emotiv Community SDK, open it, then find/open the SDK-Master folder --> Then open/find the include folder where all the header files are stored. Click on the address bar of the folder and copy the contents. The address to the include folder will act as the 'path' that Visual Studio will to link/find the Emotiv header files that are needed for this project.

![image](https://user-images.githubusercontent.com/39348633/83313907-c39e5780-a1dd-11ea-9f05-3a1e9eb46623.png)

To include the Emotiv header files go back to Visual Studio and click on Project --> 'Project_name Option' which is the last item listed.

Once the property page(s) window pops up click on --> C/C++ --> General --> 'Additional Include Directories' 

Copy and paste the 'path' where the Emotiv header files are located and press apply. 

[ Step 4 ] : Including the DLL files in the correct location(s)

On Windows, if you were to 'build' the program right now by pressing ctrl+shift+b, or for the lack of better terms, the 'top' of Visual 

to press ctlr+shift+b, or go to build --> build solution you'll get the following error(s)

![Unresolved_External_Symbol](https://user-images.githubusercontent.com/39348633/83343576-f1f56300-a2c1-11ea-8376-78aafde583c6.JPG)

The LNK2019 is a link error that is thrown for reasons that are currently beyond my reach, but to resolve the issue go to the project drop down menu --> 'Whatever you named your project' project properties --> linker -- Input.

![Unresolved_External_Symbol](https://user-images.githubusercontent.com/39348633/83343865-aba20300-a2c5-11ea-9c88-073dc49e29eb.JPG)

Click on the 'Additional dependencies' option and the drop down menu --> edit. A window will pop up with three sub-sections. In the first just type/add the edk and glut32 library files as shown in the screen shot.

![Unresolved_External_Symbol](https://user-images.githubusercontent.com/39348633/83343982-db053f80-a2c6-11ea-9357-307665ef9725.JPG)

Once agian, I'm not entirely too sure what happens when these files are linked, but I do know for a fact that the Emotiv_Bare_bones example will build and compile successfully though! 
