<h1>ChamelionInfoStealer</h1>
<p align="center">
    <img src="https://i.pinimg.com/originals/e3/30/b6/e330b6c78137fd53a959ea52459bd79d.gif">
</p>
<br>
<b>PROJECT IS NOT READY YET PLEASE BE PATIENT...</b><br>
Chamelion Infostealer is a Info Stealer that is able to steal most of the passwords and informations stored on a system and browser (credit cards too), hardware informations, BIOS informations, it check for a lot of stuff.<br>

<h2>What is Chamelion ?</h2>
Chamelion is a simple Windows Infostealer that you can use to expose information about someone.<br><br>
Chamelion is able to retrieve :<br>
     - <b>Passwords on a system.</b><br>
     - <b>Credentials stored on browsers (Might need to be cracked).</b><br>
     - <b>Network Passwords.</b><br>
     - <b>Credit Cards.</b><br>
     - <b>Network connected clients at the time of infection.</b><br>
     - <b>Name of all computers on the network with their IP Address and ports they run.</b><br>
     - <b>IP Address.</b><br>
     - <b>Browser Location.</b><br>
     - <b>Server DNS.</b><br>
     - <b>All files smaller than 700MB in Images folder.</b><br>
     - <b>Hardware Informations (Motherboard, BIOS, BIOS Version, USB Devices...).</b><br>
     - <b>Printer Enumeration</b><br><br>

<h2>How it works ?</h2>
After his recon on the victim computer Chamelion send a couple of request to our websevrer. (you're going to need to set this up files will eventually be in WEB directory), you can search your targets by going to the most recent infections or by their IP Address/Computer Name.

<h2>Here's a (really really really simplified) graph (There is actually more happening)</h2>
Note that the project will become bigger everyday.

![Image](https://i.imgur.com/tffP503.png)


Also even though not available yet, i am not responsible of any misuses made by user of this program, it is a learning experience and everyone can contribute.

<h2>How to compile and use ?</h2>
You're gonna need to follow these steps to compile the project :<br>
     - <b>git clone https://github.com/k0rup71n/ChamelionInfoStealer</b><br>
     - <b>cd ChamelionInfoStealer/Releases or ChamelionInfoStealer/Debug</b><br>
     - <b>cmake ../CMake</b><br><br>
     - (<b>RELEASE</b>) : <b>cmake --build . --config Release</b><br>
     or<br>
     - (<b>DEBUG</b>) : <b>cmake --build . --config Debug</b><br><br>
     - Compiled file will be located in ChamelionInfoStealer/Release or ChamelionInfoStealer\Debug (Depending on how you compiled the file)<br>


<h2>Things to come for Chamelion</h2>
     - <b>Black Fax Attack</b><br>
     - <b>Net Users Enumeration</b><br>
     - <b>Discord Cache Stealing</b><br>
     - <b>Discord Token and cache stored data</b><br>
     - <b>Listing of all available BSSID around the computer (Useful with WIGLE)</b><br>
     - <b>Listing of every computer with their MAC Address</b><br>
     - <b>Extraction of data from more browsers</b><br>
     - <b>Persistence on the computer</b><br>
     - <b>Take screenshots and send them every hour to the webserver. (Will come after Persistence)</b><br>
