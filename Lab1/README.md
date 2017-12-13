## Table of Contents

- [Zedboard Overview](#zedboard-overview)
- [Lab 1.1 Platform Setup and Development Environment](#lab-11-platform-setup-and-development-environment)
- [Lab 1.2.1 Bare-metal Design](#lab-121-bare-metal-design)
- [Lab 1.2.2 Hello World Program on Basic Petalinux](#lab-122-hello-world-program-on-basic-petalinux)

## Zedboard Overview

**Zynq-7000 All Programmable SoC**
- PS: Processing system
    – Dual ARM Cortex-A9 processor based
- PL: Programmable logic
    – Artix™ FPGA

<img src="https://i.imgur.com/MMwniby.png" width="510">

**Hardware Overview**

<img src="https://i.imgur.com/kIv3ixf.jpg" width="450"> <img src="https://i.imgur.com/IKfUuPW.png" width="430">



## Lab 1.1 Platform Setup and Development Environment

**Suggested Environment**

- OS: Ubuntu 14.04 64-bit

- Vivado Design Suite: 2013.4

- Petalinux Tools: 2013.10

**Vivado Design Suite**
- Vivado Design Suite Install
    - Download 2013.4 version
    - `$ tar xvf Xilinx_Vivado_SDK_2013.4_1210_1.tar`
    - `$ sudo mkdir /opt/Xilinx`
    - `$ cd Xilinx_Vivado_SDK_2013.4_1210_1`
    - `$ sudo ./xsetup`
        
        Install Completed

        <img src="https://i.imgur.com/UDUqpXL.png" width="325">
        
    - `$ vim ~/.bashrc`
        - Add `source /opt/Xilinx/Vivado/2013.4/settings64.sh` (64bit Ubuntu)
    - Acquire License
- Vivado Design Suite – Start Vivado and SDK
    - `$ vivado &`
      
      <img src="https://i.imgur.com/e9xqiki.png" width="400">
    - `$ xsdk &`
    
**PetaLinux Tools**
    
- Install PetaLinux Tools
    - Download PetaLinux Tools, 2013.10 version
    - `$ sudo mkdir -p /opt/PetaLinux`
    -  Install Required Package
    
       <img src="https://i.imgur.com/c4GIvuY.png" width="395">

    - `$ sudo ./petalinuxv2013.10-finalinstaller.run /opt/PetaLinux`
        
        Install Completed
      
        <img src="https://i.imgur.com/2gyz811.png" width="605">

    - `$ vim ~/.bashrc`
        - Add `source /opt/PetaLinux/petalinuxv2013.10-final/settings.sh`
- PetaLinux Tools – Create Project
      
  `$ petalinux-create -t project --name software`
      
  <img src="https://i.imgur.com/OHFkxj8.png" width="605">

## Lab 1.2.1 Bare-metal Design

**Assignment**
1. Design hardware for lighting on the LEDs with switching on the corresponding switches on Xilinx FPGA
2. Show the button status from UART

<img src="https://i.imgur.com/mfpKuvv.png" width="345"> <img src="https://i.imgur.com/AlUPcqf.jpg" width="535">

---

**[Create Vivado Project](https://www.xilinx.com/support/documentation/sw_manuals/xilinx13_2/PlanAhead_Tutorial_RTL_Design_IP.pdf)**
- `$ vivado &` 
- Click **Create New Project** and click **Next**
- Name the project **lab1.2.1** (project1) and click **Next**
- Select **RTL Project** (Register Transfer Level) and click **Next**
- Under the **Specify** area select **Boards**
- Select **Zynq** from the **Library** drop-down list
- Select **Zedboard Zynq Evaluation and Development Kit** and click **Next**
  
  <img src="https://i.imgur.com/F9hHd03.png" width="500">
- Click **Finish**

**Create Block Design**
- Click **Create Block Design**
- Enter **Design name**, such as **design_1**, and click **OK**

**Create Processing System**
- Click **Add IP**

  <img src="https://i.imgur.com/O8AyFtP.png" width="300">
- Search **zynq** and double click **ZYNQ7 Processing System**
- Click **Run Block Automation** and select **/processing_system7_0** and Click **OK**

**Configure Processing System**
- Double click the **ZYNQ7 Processing System** block
- (Optional) Deselect all the I/O peripherals except **UART 1**
- Check and Select **M_AXI_GP0 interface** under **PS-PL Configuration** → **GP Master AXI**
- Check and Select **FCLK_RESET0_N** under **General** → **Enable Clock Resets**
- Check and Select **FCLK_CLK0** under **Clock Configuration** → **PL Fabric Clocks**

**Create GPIOs for Switch, Button and LED**

Take Switch as example,
- Click **Add IP**
- Search **axi** and double click **AXI GPIO** block to select it, and in the properties tab, change the name to **sw_8bit**
- Double click on the **AXI GPIO** block
- Click on **Generate Board Based IO Constraints**, and under **Board Interface**, for **GPIO**, click on **Custom** to view the dropdown menu options, and select **SWs_8Bits**
- Click **OK**
- Click **Run Connection Automation** and select **/SWs_8Bits/GPIO** and Click **OK**

**Configure AXI Interface**
- Double click the **AXI Interconnect** block
- Select **3** as the number of **master interfaces**
- Click **OK**
- Connect **AXI Interconnect** with **Proc Sys Reset** and **ZYNQ7 Processing System**

**Connect GPIOs to External Pins**
- Right click the **GPIO** port of the corresponding GPIO instance and select **Make External**
- Select the **GPIO** port and change the name to the corresponding GPIO in the **External Interfaces Properties Name** field

<img src="https://i.imgur.com/lDFEcWA.png" width="585">

**Validate Design**
- Select **File** → **Save Block Design**
- Select **Tools** → **Validate Design**

**Generate Bitstream**
- Create HDL Wrapper
- Run Synthesis
- Generate Bitstream

**Export to Xilinx SDK**
- Click **File** → **Export** → **Export Hardware for SDK**
- Check the **Launch SDK** and **Include bitstream** box and click **OK**

  Launch SDK

  <img src="https://i.imgur.com/vz7RG7D.png" width="470">

**Program FPGA**
- Install JTAG driver http://svenand.blogdrive.com/archive/172.html#.Whguw1WWYdW
- Make sure that the jumper settings are set to JTAG Mode

  <img src="https://i.imgur.com/PzGI2k0.png" width="175">
- Zedboard connected

  <img src="https://i.imgur.com/PraNpKT.png" width="400">
- Power on
- Select **Xilinx Tools** → **Program FPGA**

  Program done
  
  <img src="https://i.imgur.com/cuDyNCw.png" width="280">

**Write a Bare-metal Application**
- In SDK, select **File** → **New** → **Application Project**
- Name the project **Lab_1.2.1** and, select **Create New** in the **Board Support Package** section and type the name **standalone_bsp** and click **Next**
- Select **Empty Application** and click **Finish**
- Create a new C program at **Lab_1.2.1** in the project view
- Finish the program 
  *(Please look at lab1.2.1.c on github)*
- Right click on project **Lab_1.2.1** and select **Run As** → **Launch on Hardware (GDB)** 

  <img src="https://i.imgur.com/2SP4x8M.png" width="150">
**Observe UART Output**
- Start the **GtkTerm** (or **Putty**) at host
- Select **/dev/ttyACM0** at **Port** and **115200** at **Baud Rate** 

## Lab 1.2.2 Hello World Program on Basic Petalinux

**Assignment**
- Build and change the default host name of petalinux to you student ID
- Show Hello message under OS
- Minimize the file size of BOOT.BIN

**Design Flow**

<img src="https://i.imgur.com/UbjE4K3.png">

---

**Hardware Design**

- In Vivado, create a new design named **lab1.2.2** (project_2) with only **ZYNQ7 Processing System** block
  
  <img src="https://i.imgur.com/0zXfR5B.png" width="400">
- **Generate Bitstream**
- **Export to Xilinx SDK**

**Add PetaLinux SDK Repository**
- In SDK, select **Xilinx Tools** → **Repositories**
- Select **Repositories** then click **New**
- Browse and Select **~/opt/petalinuxv2013.3.10-final/components/** then click **OK**
  
  <img src="https://i.imgur.com/HKx0k9D.png" width="550">

**Create PetaLinux BSP (Board Support Package)**  
- Select **File** → **New** → **Board Support Package**
- Select **hw_platform_0** at **Hardware Platform** field and **petalinux** at **Board Support Package OS** field, and then click **Finish**
- Select **petalinux** in the **Board Support Package Settings** window and check the following options
  - **stdin**: **ps7_uart_1**
  - **stdout**: **ps7_uart_1**
  - **main_memory**: **ps7_ddr_0**
  - **flash_memory**: **ps7_qspi_0**
  - **sdio**: **ps7_sd_0**
  - **ethernet**: **ps7_ethernet_0**
  
    &nbsp;<img src="https://i.imgur.com/aqAzQ21.png" width="545">
  
**Create First Stage Boot Loader (FSBL)**
- Select **File** → **New** → **Application Project**
- Enter **zynq_fsbl** as the **Project name**
- Set the follow options:
  - **Hardware Platform**: **hw_platform_0**
  - **Target Software OS Platform**: **standalone**
  - **Board Support Package**: **Create New**: **zynq_fsbl_bsp**
  
    <img src="https://i.imgur.com/Cmn6SLA.png" width="400">
- Click **Next**
- Select **zynq FSBL** in the **Available Templates** box
- Click **Finish**

**Create and Configure Petalinux Project**
- Start a **Terminal** at host
- `$ cd lab1.2.2`
- `$ petalinux-create -t project --name software`
- `$ cd ~/lab1.2.2/lab1.2.2.sdk/SDK/SDK_Export/petalinux_bsp_0`
- `$ petalinux-config --get-hw-description -p ~/lab1.2.2/software/`

  <img src="https://i.imgur.com/qtgPiGO.png" width="540">
- `$ cd ~/lab1.2.2/software/`
- `$ petalinux-config`
  - Select **Host name** and change to your ID number
  
    <img src="https://i.imgur.com/2w1k17C.png" width="470">
  - Select **System boot device** and change to **SD card**
  - Select **OK** then select **Exit** and select **Yes**
- `$ petalinux-build`

  <img src="https://i.imgur.com/gaUCwVO.png" width="540">
- Uboot would be generated at **~/lab1.2.2/software/images/linux**

**Create Boot Image**
- In SDK, right click the **zynq_fsbl** project and select **Create Boot Image**
- Click **Add** then click **Browse** and select **~/lab1.2.2/software/images/linux/u-boot.elf**
- Check the order of files at **Boot image partition** field
   1. fsbl
   2. bitstream
   3. u-boot

   &nbsp;<img src="https://i.imgur.com/NgCEzrV.png" height="250">
- Click **Create Image**
- mv **~/lab1.2.2/lab1.2.2.sdk/SDK/SDK_Export/zynq_fsbl/bootimage/output.bin ~/lab1.2.2/lab1.2.2.sdk/SDK/SDK_Export/zynq_fsbl/bootimage/BOOT.BIN**
- Copy **~/lab1.2.2/lab1.2.2.sdk/SDK/SDK_Export/zynq_fsbl/bootimage/BOOT.BIN** and **~/lab1.2.2/software/images/linux/image.ub** to **SD card**

**Boot the OS on Zedboard**
- Set the jumper to SD card mode and plug in SD card

   <img src="https://i.imgur.com/EfxMT6U.png" width="175">
- Power on
- Start the **GtkTerm** at host
- `Zedboard$ run sdboot`
- The user name and password are both **root** for petalinux
 
   <img src="https://i.imgur.com/Tsniw1c.png" width="550">

**Cross-compile a Hello World Program**

- At host

  ```
  Host$ vim lab_1.2.2.c
  Host$ arm-xilinx-linux-gnueabi-gcc lab_1.2.2.c -o lab_1.2.2
  ```

**(Option 1) Execute the Hello World Program via SD Card**
- At host
    - Copy **lab_1.2.2** to **SD card**
- At Zedboard

    ```
    Zedboard$ mount /dev/mmcblk0p1 /mnt
    Zedboard$ cd /mnt/
    Zedboard$ ./lab_1.2.2
    ```
    <img src="https://i.imgur.com/5gxtbHr.png" width="625">
**(Option 2) Execute the Hello World Program via TFTP**
- TFTP Server Install and Setup
http://askubuntu.com/questions/201505/how-do-i-install-and-run-a-tftp-server
- Use LAN cable to connect host and target
- Board reset
- At host
   ```
   Host$ cp lab_1.2.2 /tftpboot
   ```
- Host IP config
  
   ```
   Host$ sudo ifconfig eth0 192.168.0.1
   ```

- Zedboard IP config

    ``` 
    Zedboard$ ifconfig eth0 192.168.0.10
    Zedboard$ tftp –g 192.168.0.1 –r lab_1.2.2
    Zedboard$ chmod 755 lab_1.2.2
    Zedboard$ ./lab_1.2.2
    ```

  
