#GIF++ Data Reformatting Tool

####Author: Alexis Fagot
####email : alexis.fagot@ugent.be
####Tel.: +32 9 264 65 69

##Compilation

To compile the project, simply use

   make

###Usage

From scan 001002 to scan 001141, all the data (TDC + CAEN + DIP) was saved into a single ROOT file. It is needed to split these files into 3 separate files in order to use the GIF++ Offline Analysis tool:

* `Scan00XXXX_HVY_DAQ.root` : contains the TDC data from the RPCs
* `Scan00XXXX_HVY_CAEN.root` : contains the HV and LV data from the RPCs (voltages and currents)
* `Scan00XXXX_HVY_DIP.root` : contains the environmental parameters + source and beam information

To use it (even if it only is meant to be used once), call:

   ./run.sh first_Scan last_Scan

In our case, we need to use it on all Scans between scan 1002 and 1141, thus:

   ./run.sh 1002 1141
