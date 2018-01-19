# Mighty 1284P: An Arduino core for the ATmega1284P #
  

## What is it? ##

Everything you need to run [Arduino](http://arduino.cc/) on an [ATmega1284P](http://www.atmel.com/devices/ATMEGA1284P.aspx) microcontroller.

This branch has been updated to work with the 1.6.x versions of the Arduino IDE. (Some files have needed some changes from the 1.0.6 version, and the files need to be installed into a different directory structure.)

If you are installing for the older 1.0.5 or 1.0.6 versions of the IDE, use those branches to download. If you are using the newer 1.6.x versions of the IDE, use this branch to download.
 
This is a refreshed version of [maniacbug's mighty-1284p core](https://github.com/maniacbug/mighty-1284p) which was based on Arduino 1.0. With the invaluable help of many kind folks on the Arduino forum, I was able to produce this updated core. (If you're interested, and a bit masochistic, [here](http://forum.arduino.cc/index.php?topic=235521.0) is the rather lengthy discussion that took place during the process of updating the core.)

## Revision history <a name="revision history"></a>
**11Nov2015 Mark Pendrith (aka pico--)**
- updated Installation instructions below to deal with possible Library Manager conflicts

**15Jun2015 Mark Pendrith (aka pico--)**
- added support for variant "Sleeping Beauty"
- updated boards.txt.alt to include menu options for enabling/disabling JTAG, as well as A4/A5 functionality for Sleeping Beauty
- updated boards.txt.alt clock speed options to disallow bootloader options that flash LED on PB7 for boards that do not have the board LED connected to PB7
- added platform.local.txt to restore Mighty-1284p separator heading in Tools|Board list

**06May2015 Mark Pendrith (aka pico--)**
- v1.6.3 branch created for Arduino IDE 1.6.x support

**29Oct2014 Jack Christensen**
- The following changes are in a branch named v1.0.6. The v1.0.5 branch will remain the default for the time being, until the v1.0.6 branch can be tested further.
- With the release of Arduino 1.0.6, changes to the core files are no longer needed to support the ATmega1284P. Deleted the Mighty 1284P cores directory pointed all boards in the boards.txt file to the regular Arduino core.
- Added an 8MHz "Mighty Mini 1284P" board to the boards.txt file, and 8MHz bootloaders for several different baud rates.

**13May2014 Jack Christensen**
- Added a 1M baud version of Optiboot.
- Added the "Mighty Mini 1284P" board to the boards.txt file.

**05May2014 Jack Christensen**
- Updates to pins_arduino.h files for correct pin mapping.
- Renamed the core directory from "standard" to "mighty" and updated board.txt accordingly.
- Changed wiring_analog.c to support correct analog pin mapping. This single-line change is the only change needed to the Arduino 1.0.5 "cores" files. [An equivalent change](http://github.com/arduino/Arduino/pull/1368) has been made in the Arduino repository and should be included in later releases.

**03May2014 Jack Christensen**
- An attempt to bring the mighty-1284p core up to Arduino 1.0.5 level. In researching the changes I came to the conclusion that the core was originally based on Arduino 1.0 and that since then all the changes in maniacbug's core files necessary to support the ATmega1284P had been worked into subsequent Arduino releases. This may have occurred as early as Arduino 1.0.1. Nevertheless, this update is working with Arduino 1.0.5 and while it may work with earlier releases, I do not plan to test them, so there is no guarantee.
- The initial commit is therefore just a matter of removing the cores directory and updating the boards.txt file to point at the cores directory in the Arduino distribution.

**23Jun2012 maniacbug**
- Everything is here and has been initially tested.  It should work fine.  There is more detailed testing which must be completed before calling it completely 'done' though.
- The platform now includes optiboot.  This bootloader is better in every way than the previous version, so it is recommended in all cases.  The prior one is included for reference.

## Installation <a name="installation"></a>

1. Go to https://github.com/JChristensen/mighty-1284p/tree/v1.6.3, click the **Download ZIP** button and save the ZIP file to a convenient location on your computer.

2. Ensure that the Arduino IDE is **not** running.

3. Go to your Arduino **hardware** folder.

4. Unzip the downloaded file into the **hardware** folder.

5. The download from GitHub will have a dash and branch name appended, so the folder will be named, e.g. mighty-1284p-v1.6.3. Rename the folder to just **mighty-1284p**.

6. The following folders and files should now exist:

	- hardware\mighty-1284p\avr\bootloaders
	- hardware\mighty-1284p\avr\libraries
	- hardware\mighty-1284p\avr\patched-3rd-party-libs
	- hardware\mighty-1284p\avr\variants
	- hardware\mighty-1284p\avr\boards.txt
	- hardware\mighty-1284p\avr\boards.txt.alt
	- hardware\mighty-1284p\.gitignore
	- hardware\mighty-1284p\README.md

7. The mighty-1284p compatible "official" patched libs are located to be used as default when a mighty-1284p board is selected in the **Board** menu by being in **hardware\mighty-1284p\avr\libraries**. **However**, be aware that a version of any of these libraries located in **[sketchfolder]\libraries** will take precedence over the corresponding mighty-1284p patched version:

    - Ethernet  
    - Firmata  
    - GSM  
    - SD  
    - Servo

    Unfortunately, in its present design (IDE 1.6.5) **Library Manager** installs and updates libraries to **[sketchfolder]\libraries**. This obviously presents a potential problem if you are using **Library Manager**. The following is the recommended work-around:

    If there are any of the above-named libraries installed in **[sketchfolder]\libraries**, then move those libraries from **[sketchfolder]\libraries** to **[Arduino install folder]\libraries**. This will then allow the mighty-1284p patched libraries to take precedence when (but only when) a mighty-1284p board is selected.

    Finally, note this manual move of the libraries from **[sketchfolder]\libraries** to **[Arduino install folder]\libraries** will need to be repeated after any updating any of the named libraries using **Library Manager**.

    Hopefully, as the design of **Library Manager** is improved, this issue and inconvenience will disappear in future revisions of the IDE.

8. Once all the libraries are verified to be in their appropriate locations, restart the Arduino IDE.  
9. Select the desired board from the Tools > Board menu and enjoy those extra pins and all that extra memory!  

Note: There is an alternative version of the boards.txt file supplied named boards.txt.alt. It provides more combinations of boards and clock speeds than the standard boards.txt selection menu. It uses a two-step selection of board type and then clock-speed via a submenu. As this differs from the standard boards.txt format, it is provided as an option for those users with more specialized needs, while the default boards.txt retains the more familiar style of interface, to minimise any potential for confusion.

To enable the alternate version, rename boards.txt to boards.txt.org, and then rename boards.txt.alt to boards.txt. Restart IDE, and the new selection options will appear. 

## Requirements <a name="requirements"></a>

* Works with Arduino 1.6.3. and later. It may work on other versions as early as 1.5.x but these have not been tested. For earlier versions of the Arduino IDE, there is also a v1.0.6 branch, and a v1.0.5 branch for 1.0.x (possibly back to 1.0.1) support. Download and install from the appropriate branch as required for the version of IDE.
* The [USBtinyISP](http://www.adafruit.com/products/46) is advertised as not able to program chips with more than 64K of flash, however there are varying reports of success using it with the ATmega1284P. Sometimes error messages are given but the upload process seems to have worked OK. Be forewarned. YMMV.

## See also <a name="seealso"></a>

http://maniacbug.wordpress.com/2011/11/27/arduino-on-atmega1284p-4/

## Supported Boards <a name="boards"></a>

* **avr-developers.com pinouts 16MHz using Optiboot** - Some people prefer the pinouts from avr-developers.com.  The classic pinouts.
* **Bobuino** - [CrossRoads' board](http://crossroadsfencing.com/BobuinoRev17/index.html) built for maximum compatibility with Arduino Uno-class shields.
* **RFX 1284P Development/Deployment Board** (a.k.a. "Skinny Bob") from [Embedded Coolness](http://embeddedcoolness.com/shop/rfx-1284p-devdep-board-w-prototyping-area-nrf24l01-headers-kit/); also built for maximum compatibility with Arduino Uno-class shields, has prototyping area, configurable 5V/3v3 voltage selection, and nRF24L01+ support.
* **Mighty Mini 1284P** - A small breadboard-friendly version of the Mighty 1284p built with SMT components. Open-source design [available on GitHub](http://goo.gl/5fAHca).
* **"maniacbug" Mighty 1284p 16MHz using Optiboot** - This uses a straightforward pinout that is especially helpful on a breadboard-built unit.
* **"Windlogger Digital Board"** [Digital Board](https://github.com/netbomo/windlogger_digital) Just an other arduino board based on the Atmega1284p. Unfortunatly pinout are close to the bobuino but not exact.

