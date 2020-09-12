# **THIS REPOSITORY IS A WORK IN PROGRESS AND WILL BE CONTINIOUSLY UPDATED** <h1>

# **SIGNIFICANT UPDATE AS OF [9/11/2020]** <h1>

Around the June-July timeframe I got a new laptop and had updated the Emotiv software.

Prior to the update, I was still able to get data off the headset as long as the contact quality was ~66%, which meant as long as I had "Good" contact with at least 4 of the 6 dry polymer electrodes, I was golden.

But after the update, in order to get data off the headset required a contact quality of AT LEAST 95% which was something I couldn't achieve despite troubleshooting any and every possible issue that would come to mind.

As much as I hate to admit it, I un-intentionally "bricked" the headset.

On the flip side, the Emotiv Insight was the most expensive part of the entire build.

Which reminds me that I need to upload an excel spreadsheet for the parts being used and how much everything costs.

So in the mean time, the new controlling methods that I plan on using for the wheelchair are : 

1) An analog joystick
![image](https://user-images.githubusercontent.com/39348633/92987649-2e705780-f48a-11ea-893a-061003f9f61e.png)

2) An MPU-9250 Iternal Measurement Unit which can measure gyroscopic/accelerometer/magnetometer data
![image](https://user-images.githubusercontent.com/39348633/92987692-7abb9780-f48a-11ea-9370-aeb466b43597.png)

Interfacing the joystick isn't difficult at all, is the most reliable way to control the wheelchair and will be the primary method of controlling the wheelchair

With the MPU-9250, my intention is to use Machine Learning (ML) and different gestures to control the wheelchair. 

However implimenting ML isn't going to be easy. 

To make things worse (Or at least that's how I see it) Tensorflow JUST started supporting machine learning for microcontrollers.

Why am I throwing shade at what seems like an awesome thing?

There's hardley any documentation/support for the various supported microcontrollers because all of this is so new.

So essentially, I'm almost starting back at square one considering my circumstances since the last update from 6/22 to now.

Then there's the 3d-printing aspect of the entire project that I have to worry about.

And to be honest, at this point, in addition to all the things going on in my personal life, I feel pretty shitty on how things have turned out so far.

But I know that there's a demograph of people that could benefit from this, or a handful of people that could take this project and further refine it.

There's also a person since day 1 of me stepping into the engineering world who has supported me the entire way and my life would probably be very different had we not crossed paths.

And there's no way I can let him down.

If any sigificant progress is made, I'll update this accordingly.

But in the mean time, it's all up hill from here, and it's a steep incline.

# **IMPORTANT NOTE [6/22/2020]** <h1>

I recently had to do a factory reset on my laptop and lost the majority of my files in the process.

I'm currently back tracking and piecing everything back together to the best of my ability, so please bear with me in the meantime.

 # [ INTRODUCTION ] <h1>

The intent of this project was the premise of my Master's thesis, which was geared towards integrating a commerically avilable EEG headset called the Emotiv Insight to control an open sourced, electric wheelchair that had PLA-based 3d-printed components that could be retrofitted onto a commonly available push wheelchair for those who are suffering from a physical disability and can't operate a traditional push wheelchair, or give those who don't have the fiancial resources to purchase a commerically available electric wheelchair an option.

Before any attempts were made to control the proposed wheelchair, simpiler peripherals such as a single LED were used to solidify the proof of concept that the headset could be used as a controlling factor. Over time, more complex peripherals such as four directional LEDs and an Arduino-based RC rover were also used to solidify the proof of concept before finally controlling the proposed open-sourced wheelchair. 

The first step I took was to figure out a way to gain access to the streaming EEG data since I was under the assumption that all five EEG signals were to fall within a certain range when the user concentated on a particular direction.

Gaining access to the streaming EEG data with the Emotiv headset however would require a montly subscription. When I started this project in the Fall semester of 2018, the  monthly subscription was around $100 dollars a month. Since then Emotiv had implimented a multi-tier pricing with a lower price for students, but regardless of the price, I was strongly against paying the montly subscription due to a combination of personal reasons and the intention of keeping the proposed wheelchair as affordiable as possible.

Fortunately enough, I somehow stumbled upon the "Emotiv SDK - Community Edition" which provided numerous coding examples that mimicked the funcionality of the programs provided by Emotiv. 

I'm not entirely too sure how long the repository I found the community SDK will stay active, but for now it can be found here --> 
https://github.com/pandark/emotiv-community-sdk

***IT'S IMPORTANT TO TAKE NOTE THAT THIS ENTIRE PROJECT WAS DONE IN C++ WITH WINDOWS 10.*** 

The next section will discuss the steps taken to configure various settings in Microsoft Visual Studio in order to build/compile/run a skeletonized C++ program based off the Community version of the Emotiv SDK.

# [Running the Emotiv_Bare_Bones program] <h1>
 
Since all of the example programs in the Emotiv Community SDK were written using Visual Studio and I wasn't sure what I was getting myself into, I opted to do the same.

The downloaded the 'Community' edition here --> https://visualstudio.microsoft.com/downloads/

# [ Step 1 ] : Download the Emotiv Community SDK edition <h5> 
 
Download here --> https://github.com/pandark/emotiv-community-sdk

# [ Step 2 ] : Start Visual Studio <h5>
 
Under 'Get started' on the right hand side, click on 'Create a new project'

![Capture22](https://user-images.githubusercontent.com/39348633/83283699-3ccb8980-a1a1-11ea-9e65-ffa6595e668b.JPG)

Then choose in the first drop down menu 'C++' and click on the 'Empty project'

![Visual Studio](https://user-images.githubusercontent.com/39348633/83285122-58379400-a1a3-11ea-99fb-69b7b904f075.JPG)

Once everything is loaded, you'll be presented with a blank screen and the 'Solution Explorer' all the way to your right. All the drop down menus should be expanded and you should see a folder called 'Source Files'. Right click on it and go to 'Add --> New Item'

![Capture22](https://user-images.githubusercontent.com/39348633/83313212-e0855b80-a1da-11ea-9d24-d222ec9e532e.JPG)

Another window will pop up, click/highlight the C++ file option and name the file whatever you wish. Out of habit, I''ll be calling mine main.cpp

![Capture22](https://user-images.githubusercontent.com/39348633/83313256-11659080-a1db-11ea-960f-075b093e18e9.JPG)

As of Version 16.6.2 of Visual Studio, you will have to set the 'Character Set' from Single-byte to Multi-Byte in order to open the COMM port between the C++ program and the Arduino. 

In order to do so from the top menu bar click on --> Project --> 'Project name' Properties --> Advanced --> Under advanced properties find 'Character Set' --> Click on the drop down menu --> Click on 'Use Multi-Byte Character Set'

![image](https://user-images.githubusercontent.com/39348633/86062993-7e18b880-ba2f-11ea-8035-b8357fb18061.png)

![image](https://user-images.githubusercontent.com/39348633/86062935-64777100-ba2f-11ea-98d5-2e4d9bdb75c2.png)

# [ Step 3 ] : Adding the Emotiv header files <h5>

A skeleton code approperately named Emotiv_Bare_Bones can be found in the repoistory and will be used to ensure the header files were linked correctly : https://github.com/Digital1O1/Open-sourced-EEG-Electric-Wheelchair/tree/master/Emotiv_Bare_Bones

After unzipping the Emotiv Community SDK find and open the following folders --> SDK-Master --> Include folder. Click on the address bar of the Include folder and copy the address/contents as we'll need it later to link the header files to the Emotiv_Bare_Bones program.

![image](https://user-images.githubusercontent.com/39348633/83313907-c39e5780-a1dd-11ea-9f05-3a1e9eb46623.png)

To include the Emotiv header files to the Emotiv_Bare_Bones program go back to Visual Studio and click on Project --> 'Emotiv_Bare_Bones Option' which is the last item listed.

Once the property page(s) window pops up click on --> C/C++ --> General --> 'Additional Include Directories' 

Copy and paste the 'path' where the Emotiv header files are located and press apply. 

![image](https://user-images.githubusercontent.com/39348633/85958801-e5fece80-b95d-11ea-9615-53fd6326eabb.png)

# [ Step 4 ] : Including the DLL files and PATH <h5>

On Windows, if you were to 'build' the program right now by pressing ctrl+shift+b you'll get the following error(s)

![Unresolved_External_Symbol](https://user-images.githubusercontent.com/39348633/83343576-f1f56300-a2c1-11ea-8376-78aafde583c6.JPG)

To resolve the LNK error, the PATH of the DLL files must be included in the current project.

To do so, to go 'Project' in the menu bar --> 'Whatever you named your project' project properties --> linker -- Input.

![Unresolved_External_Symbol](https://user-images.githubusercontent.com/39348633/83343865-aba20300-a2c5-11ea-9c88-073dc49e29eb.JPG)

Click on the 'Additional dependencies' option and the drop down menu --> edit. 

A window will pop up with three sub-sections. 

In the first just type/add edk.lib, press enter, then add glut32.lib as shown in the screen shot.

![Unresolved_External_Symbol](https://user-images.githubusercontent.com/39348633/83343982-db053f80-a2c6-11ea-9357-307665ef9725.JPG)

To include the path to the .lib files, look for 'VC++ Directories' --> Library Directories.

From there, just copy and paste the path where the .lib files are located as done with the header files. For clarification-sake, I used the .lib files in the Win32 folder and used that PATH, and I highly recommend y'all do the same.

![image](https://user-images.githubusercontent.com/39348633/85937895-8658e280-b8cd-11ea-8a50-f33b79a0bc2f.png)

# [ Step 6 ] : Adding the DLL files to Debug folder <h5>

If you go to the Emotiv Folder --> bin --> Win32 --> You should see two files:

*Edk.dll
*Glut32.dll

![image](https://user-images.githubusercontent.com/39348633/85967937-3d666400-b989-11ea-9157-c5eda42136ce.png)

Copy and paste both of those files

Go to where ever you have the Emotiv_Bare_Bones folder stored and find the 'Debug' folder

![image](https://user-images.githubusercontent.com/39348633/85959441-3e37cf80-b962-11ea-9c0f-5c14184a4676.png)

Then copy and paste both DLL files into the Debug folder

![image](https://user-images.githubusercontent.com/39348633/85959516-7ccd8a00-b962-11ea-9cd6-0a758345624d.png)


# [ Step 6 ] : Build/Compile the program! <h5>

The last step to do is just press ctrl + F5 to run the program and you should see the debug console pop up stating that the program successfully compiled!


![image](https://user-images.githubusercontent.com/39348633/85937924-e2236b80-b8cd-11ea-9d5b-d072a2637170.png)

