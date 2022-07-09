# **3D Ideal Gas Simulation**
Based on a previous project with simulating ideal gas, this project will take a step further into the third dimension. </br>

![gas_demo](https://user-images.githubusercontent.com/70242197/178085932-b859dfb8-5af8-4266-91d9-b05c6aa313ae.gif)

Featuring a 3D environment with adjustable container, variable particle options and speed histograms to simulate the ideal gas law and observe the Maxwell–Boltzmann distribution on the histogram.


## Windows Setup
Cinder on window requires Visual Studio 2015 to be properply built.
Follow these steps to install VS 2015 before building Cinder:
1. If a Visual Studio Build Tools is present on your machine and its version is later than 2015, uninstall it by navigating to Control Panel > Programs > Programs and Features > Uninstall a Program, and then uninstall Visual Studio Build Tools.
2. Install "Visual Studio Community 2015 with Update 3" via this [link](https://my.visualstudio.com/Downloads?q=visualstudio2015&wt.mc_id=o~msft~vscom~older-downloads)
3. Run the installer and *custom install* with "Common Tools for Visual C++ 2015" selected. Don't launch VS after installation.
4. Make default toolchain on your IDE to **only** Visual Studio.
5. Build Cinder.
6. Once Cinder is successfully built, create a folder called "my-projects" and clone this repo into said folder.

## Begin
After you built Cinder and cloned the repo, build the project with the CMake file. Then run the executable and play around in the environment!

