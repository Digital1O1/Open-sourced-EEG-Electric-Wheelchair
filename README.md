# Emotiv_Insight

This repository will be continuously upadated as of April 4 2020

============== [ May 26, 2020 ] ==============

[ INTRODUCTION ]

The intent of this project was the premise of my Master's thesis, which was to use the Emotiv Insight, a commerically available EEG headset to control an open sourced, electrical wheelchair with PLA-based 3d printed components that could be either retrofitted, or modified to fit any commonly available push wheelchair for those who don't have the financial resources and/or the physical capabilities to control an electric wheelchair.

My intial intentions were to use both the Emotiv Insight and an Arduino microcontroller to control four directional LEDs successfully, then I would step it up and control an Arduino-based RC rover and finally the proposed open-sourced wheelchair. The first step taken was to gain access to the streaming EEG data under the assumption that all five EEG signals were to fall within a certain range when the user thought/concentrated on thinking up, down, left, or right.

However, gaining access to the streaming EEG data would require a montly subscription to Emotiv which cost around $100 as of the fall semester of 2018 when I first started this project. Since then Emotiv had implimented a multi-tier pricing, regardless of the pricing, I wanted to avoid paying any sort of montly fee. Fortunately enough, I somehow stumbled upon the "Emotiv SDK - Community Edition" which provided numerous coding examples that mimicked various functions found in other programs provided by Emotiv. I'm not entirely too sure how long the repository I found the community SDK will stay active, but for now it can be found here --> 
https://github.com/pandark/emotiv-community-sdk

IT'S IMPORTANT TO TAKE NOTE THAT THIS ENTIRE PROJECT WAS DONE IN C++ WITH WINDOWS 10. 

After gaining access to the streaming EEG data, the next step was to figure out how to send the streaming EEG data to the Arduino microcontroller. Since the Universal Asynchronous Receiver/Transmitter (UART) communication protocol that's built into the Arduino microcontroller could only send data generated from the Arduino back to the Arduino IDE for the user to monitor the incoming data in real time rather than the other way around, various functions from the Win32 API had to be implimented in order to send the streaming EEG data to the Arduino. In depth documentation of the Win32 API and the various functions and their purpose can be found here --> https://www.xanthium.in/Serial-Port-Programming-using-Win32-API
