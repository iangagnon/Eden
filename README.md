# Eden
The Eden is a device, originally conceived of at the University of New Hampshire by Ian Gagnon, Annette Conticchio, Devin Kehler, Michael Gingrich, and Brian Parker that is intended to be used to measure the amount of water that flows from a water source in developing countries.

This project is no longer being actively pursued by any of its original founders and it is their hope that other groups will find their work to be useful and to further develop the Eden system into something that is usefull for themselves. Some info has been lost between the time when we actually did this (August of 2015) and now, but it is our hope people who find this useful can rebuild missing items and increase the devices capabilities.

#Hardware needed:
- 1 [Arduino Mega](https://store-usa.arduino.cc/collections/products-atheart/products/arduino-mega-2560-rev3)
- 1 [Arduino GSM Shield](https://www.amazon.com/gp/product/B00UM1QGZK/ref=oh_aui_detailpage_o00_s00?ie=UTF8&psc=1)
- 1 [GSM Enabled Sim Card](http://www.onesimcard.com/machine-to-machine-communications-sim/)
- 1 [Arduino Case](https://www.sparkfun.com/products/10088)
- 1 [USB Battery](https://www.amazon.com/gp/product/B00MLVPOWK/ref=oh_aui_detailpage_o01_s00?ie=UTF8&psc=1)
- 1 [Flow Meter](https://www.amazon.com/gp/product/B00PZMBMDW/ref=oh_aui_detailpage_o02_s00?ie=UTF8&psc=1)
- [#22 Guage Solid Wire](https://www.amazon.com/gp/product/B008L3UXO6/ref=oh_aui_detailpage_o09_s01?ie=UTF8&psc=1)

#Setup
1. Download the latest version of Arduino software from [here](https://www.arduino.cc/en/Main/Software) to your computer
2. Connect the Arduino GSM Shield to the Arduino Mega. Note, you will have to bend pin 2 on the GSM shield to the side and short out pin 2 to pin 10 on the GSM Shield as well. Instructions for this are shown [here](https://www.arduino.cc/en/Guide/GSMShieldLeonardoMega)
3. Insert your GSM Enabled Sim Card into the GSM Shield.
4. Connect your flow meter. To do this connect the black wire of the flow meter to a ground on the Arduino Mega

  * Yellow wire to pin #2 on the Arduino Mega  
  * Black wire to a ground pin  
  * Red wire to a 5V pin  
  
   ![alt text](https://github.com/iangagnon/Eden/blob/master/photos/ArduinoPinOut.PNG)  

5. Connect your Arduino Mega to your computer using the USB cable provided with the Mega. Using the Arduino software open the EdenGSM.ino code and upload it to the Arduino Mega.
