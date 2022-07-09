# **3D Ideal Gas Simulation**
Based on a previous project with simulating ideal gas, this project will take a step further into the third dimension. </br>

Additonal features like speed up/slow down simulation, JSON for simulation snapshot & settings, Maxwell–Boltzmann distribution on histogram, and a more dynamic control to the gas container shape and size, will be the included goals of this project.

In the case of this project being finished before the proposed timeline, the **stretch goals** for this project will include, but not limited to:
- Adjustable perspective to the 3D container when dragging the cursor.
- Allowing users to create custom particles (mass, velocity, etc.) and where to begin their trajectory in the container.
- Creating a grid plane to anchor the container's "bottom" side to a visualized 2D plane.
- For now, the container will be limited to prism-shape, but other unique shapes like sphere, egg, diamond, etc. can be explored as unique container option.


## Windows Setup
    Cinder on window requires Visual Studio 2015 to be properply built.
    Follow these steps to install VS 2015 before building Cinder:
1. If a Visual Studio Build Tools is present on your machine and its version is later than 2015, uninstall it by navigating to Control Panel > Programs > Programs and Features > Uninstall a Program, and then uninstall Visual Studio Build Tools.
2. Install "Visual Studio Community 2015 with Update 3" via this [link](https://my.visualstudio.com/Downloads?q=visualstudio2015&wt.mc_id=o~msft~vscom~older-downloads)
3. Run the installer and *custom install* with "Common Tools for Visual C++ 2015" selected. Don't launch VS after installation.
4. Make default toolchain on your IDE to **only** Visual Studio.
5. Build Cinder.
6. Once Cinder is successfully built, create a folder called "my-projects" and clone this repo into said folder.

