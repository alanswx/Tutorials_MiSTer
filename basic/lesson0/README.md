# Lesson 0: Setup

1) Install Quartus 17.0.2

Download [this](https://downloads.intel.com/akdlm/software/acdsinst/17.0std.2/602/ib_tar/Quartus-lite-17.0.2.602-windows.tar)


OLD ONE:
[old](https://cdrdv2.intel.com/v1/dl/downloadStart/674766/674776?filename=Quartus-lite-17.0.2.602-windows.tar) version.
[older](http://download.altera.com/akdlm/software/acdsinst/17.0std.2/602/ib_tar/Quartus-lite-17.0.2.602-windows.tar) version.

2) Install Github Deksop

3) Checkout [Template](https://github.com/MiSTer-devel/Template_MiSTer) Repo

4) Build Repo

5) Install RBF onto MiSTer


### Linux (Ubuntu 20.04) notes for installing and running quartus

Download 
[this](https://downloads.intel.com/akdlm/software/acdsinst/17.0std.2/602/ib_tar/Quartus-lite-17.0.2.602-linux.tar)

[old](http://download.altera.com/akdlm/software/acdsinst/17.0std.2/602/ib_tar/Quartus-lite-17.0.2.602-linux.tar) version.

Note: The installation scripts do not quite work - each component's install hangs for some reason, so if you try to install more than one at a time, the install won't complete correctly. In particular, the final step that tells the install that it's a lite install instead of standard doesn't happen, so the tool wants a license file. I followed these steps to get a working install from the command line. If you run the GUI installer, it will be similar questions - just make sure you only install one component at a time.

1. Go into the `components` directory
2. Run `./QuartusLiteSetup-17.0.0.595-linux.run`. Hold down `Enter` until you get the prompt asking to accept the license. Press `y` and then specify the install directory.
4. Answer `y` to the install of `Quartus Prime Lite Edition (Free)` and 'n' to all other components. After the install, answer `n` to those questions.
5. The installer will hang; hit `Ctrl-C` to exit.
6. Run `./QuartusLiteSetup-17.0.0.595-linux.run` again. Hold down `Enter` until you get the prompt asking to accept the license. Press `y` and then specify the same install directory as before. Answer `y` to update the installation.
7. Answer `n` to all components other than Devices and Cyclone V.
8. After the install, answer `n` to those questions. This time the installer should exit cleanly.
6. Run `./QuartusSetup-17.0.2.602-linux.run` (the patch run file). Hold down `Enter` until you get the prompt asking to accept the license. Press `y` and then specify the same install directory as before. Note that you'll have to explicitly type the path in, as it won't be prepopulated.
7. Answer `n` to 'Allow patches to be uninstalled'. The install takes 15 or so seconds to run and may look like it has hung close to 100%; however, it should report that it has finished and then hang. Hit `Ctrl-C` to exit.

All the tools should work now. E.g. if you add the `.../17.0/quartus/bin` directory to your path and go into one of the lessons directory, you should be able to build the rbf by running `quartus_sh --flow compile Lesson#` (Where '#' is the Lesson number).
 
 f you want to run the GUI, you will likely need to install some dependencies. These should be obvious by the reported missing DLLs when you try to run `quartus`. The one that is likely not available through `apt-get` is `libpng12`. I followed [these](https://www.linuxuprising.com/2018/05/fix-libpng12-0-missing-in-ubuntu-1804.html) instructions to add the 20.04 PPA and install.
