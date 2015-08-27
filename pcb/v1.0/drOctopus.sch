EESchema Schematic File Version 2
LIBS:drOctopus-rescue
LIBS:power
LIBS:niceAVR
LIBS:niceModules
LIBS:niceRLC
LIBS:niceSemiconductors
LIBS:niceSwitches
LIBS:test
LIBS:nicePinheaders
LIBS:niceMosfets
LIBS:nicePowerSupplies
LIBS:niceTerminalBlocks
LIBS:niceResonators
LIBS:niceDiodes
LIBS:niceMechanical
LIBS:drOctopus-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Wi-Fi Servo Controller"
Date "2015-08-10"
Rev "1.0"
Comp "NiceCircuits"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATmega328-AU U1
U 1 1 55C27F0F
P 4400 1900
F 0 "U1" H 4400 3060 60  0000 C CNN
F 1 "ATmega328-AU" H 4400 840 60  0000 C CNN
F 2 "QFP-32-0.8_M" H 4400 750 40  0001 C CNN
F 3 "" H 4400 1900 60  0000 C CNN
	1    4400 1900
	1    0    0    -1  
$EndComp
$Comp
L R_Network_4 RN1
U 1 1 55C27FAE
P 6600 1300
F 0 "RN1" H 6600 1380 60  0000 C CNN
F 1 "10k" H 6600 1300 40  0000 C CNN
F 2 "4x0603_N" H 6600 1240 40  0001 C CNN
F 3 "" H 6600 1300 60  0000 C CNN
	1    6600 1300
	1    0    0    1   
$EndComp
$Comp
L R_Network_4 RN1
U 2 1 55C28030
P 6600 1200
F 0 "RN1" H 6600 1280 60  0001 C CNN
F 1 "10k" H 6600 1200 40  0000 C CNN
F 2 "4x0603_N" H 6600 1140 40  0001 C CNN
F 3 "" H 6600 1200 60  0000 C CNN
	2    6600 1200
	1    0    0    1   
$EndComp
$Comp
L R_Network_4 RN1
U 3 1 55C28073
P 6600 1100
F 0 "RN1" H 6600 1180 60  0001 C CNN
F 1 "10k" H 6600 1100 40  0000 C CNN
F 2 "4x0603_N" H 6600 1040 40  0001 C CNN
F 3 "" H 6600 1100 60  0000 C CNN
	3    6600 1100
	1    0    0    1   
$EndComp
$Comp
L R_Network_4 RN1
U 4 1 55C28084
P 6600 1000
F 0 "RN1" H 6600 1080 60  0001 C CNN
F 1 "10k" H 6600 1000 40  0000 C CNN
F 2 "4x0603_N" H 6600 940 40  0001 C CNN
F 3 "" H 6600 1000 60  0000 C CNN
	4    6600 1000
	1    0    0    1   
$EndComp
Wire Wire Line
	8600 1200 8700 1200
Connection ~ 8600 1200
Wire Wire Line
	8600 1100 8700 1100
Connection ~ 8600 1100
Wire Wire Line
	9400 1200 9500 1200
Connection ~ 9400 1200
Wire Wire Line
	9400 1100 9500 1100
Connection ~ 9400 1100
$Comp
L PIN-3x4 CON1
U 1 1 55C2E73C
P 9900 1200
F 0 "CON1" H 9900 1560 60  0000 C CNN
F 1 "Servo" H 9900 940 60  0000 C CNN
F 2 "PIN-3x4_angled_N" H 9900 850 40  0001 C CNN
F 3 "" H 9900 1200 60  0000 C CNN
	1    9900 1200
	1    0    0    -1  
$EndComp
$Comp
L PIN-3x4 CON1
U 2 1 55C2E79D
P 9100 1200
F 0 "CON1" H 9100 1560 60  0000 C CNN
F 1 "Servo" H 9100 940 60  0000 C CNN
F 2 "" H 9100 850 40  0001 C CNN
F 3 "" H 9100 1200 60  0000 C CNN
	2    9100 1200
	1    0    0    -1  
$EndComp
$Comp
L PIN-3x4 CON1
U 3 1 55C2E7EC
P 8300 1200
F 0 "CON1" H 8300 1560 60  0000 C CNN
F 1 "Servo" H 8300 940 60  0000 C CNN
F 2 "" H 8300 850 40  0001 C CNN
F 3 "" H 8300 1200 60  0000 C CNN
	3    8300 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 1000 9400 1000
Wire Wire Line
	8600 1300 8700 1300
$Comp
L GND #PWR01
U 1 1 55C7932E
P 9400 1500
F 0 "#PWR01" H 9400 1250 50  0001 C CNN
F 1 "GND" H 9400 1350 50  0000 C CNN
F 2 "" H 9400 1500 60  0000 C CNN
F 3 "" H 9400 1500 60  0000 C CNN
	1    9400 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6800 1300 7900 1300
Wire Wire Line
	6800 1200 7900 1200
Wire Wire Line
	6800 1100 7900 1100
Wire Wire Line
	6800 1000 7900 1000
Wire Wire Line
	8600 700  8600 1300
Wire Wire Line
	8600 1000 8700 1000
Connection ~ 8600 1000
Wire Wire Line
	9400 1000 9400 1500
Wire Wire Line
	9500 1300 9400 1300
Connection ~ 9400 1300
Wire Wire Line
	8600 2500 8700 2500
Connection ~ 8600 2500
Wire Wire Line
	8600 2400 8700 2400
Connection ~ 8600 2400
Wire Wire Line
	9400 2500 9500 2500
Connection ~ 9400 2500
Wire Wire Line
	9400 2400 9500 2400
Connection ~ 9400 2400
$Comp
L PIN-3x4 CON2
U 1 1 55C7A25B
P 9900 2500
F 0 "CON2" H 9900 2860 60  0000 C CNN
F 1 "Servo" H 9900 2240 60  0000 C CNN
F 2 "PIN-3x4_angled_N" H 9900 2150 40  0001 C CNN
F 3 "" H 9900 2500 60  0000 C CNN
	1    9900 2500
	1    0    0    -1  
$EndComp
$Comp
L PIN-3x4 CON2
U 2 1 55C7A261
P 9100 2500
F 0 "CON2" H 9100 2860 60  0000 C CNN
F 1 "Servo" H 9100 2240 60  0000 C CNN
F 2 "" H 9100 2150 40  0001 C CNN
F 3 "" H 9100 2500 60  0000 C CNN
	2    9100 2500
	1    0    0    -1  
$EndComp
$Comp
L PIN-3x4 CON2
U 3 1 55C7A267
P 8300 2500
F 0 "CON2" H 8300 2860 60  0000 C CNN
F 1 "Servo" H 8300 2240 60  0000 C CNN
F 2 "" H 8300 2150 40  0001 C CNN
F 3 "" H 8300 2500 60  0000 C CNN
	3    8300 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9500 2300 9400 2300
Wire Wire Line
	8600 2600 8700 2600
$Comp
L GND #PWR02
U 1 1 55C7A26F
P 9400 2800
F 0 "#PWR02" H 9400 2550 50  0001 C CNN
F 1 "GND" H 9400 2650 50  0000 C CNN
F 2 "" H 9400 2800 60  0000 C CNN
F 3 "" H 9400 2800 60  0000 C CNN
	1    9400 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 2000 8600 2600
Wire Wire Line
	8600 2300 8700 2300
Connection ~ 8600 2300
Wire Wire Line
	9400 2300 9400 2800
Wire Wire Line
	9500 2600 9400 2600
Connection ~ 9400 2600
$Comp
L C C3
U 1 1 55C7A7D9
P 1800 2200
F 0 "C3" H 1820 2300 60  0000 L CNN
F 1 "100n" H 1820 2100 60  0000 L CNN
F 2 "0603_N" H 1820 2010 40  0001 C CNN
F 3 "" H 1800 2200 60  0000 C CNN
	1    1800 2200
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 55C7A882
P 1400 2200
F 0 "C2" H 1420 2300 60  0000 L CNN
F 1 "100n" H 1420 2100 60  0000 L CNN
F 2 "0603_N" H 1420 2010 40  0001 C CNN
F 3 "" H 1400 2200 60  0000 C CNN
	1    1400 2200
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 55C7A8BB
P 1000 2200
F 0 "C1" H 1020 2300 60  0000 L CNN
F 1 "100n" H 1020 2100 60  0000 L CNN
F 2 "0603_N" H 1020 2010 40  0001 C CNN
F 3 "" H 1000 2200 60  0000 C CNN
	1    1000 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 2200 2600 2200
Wire Wire Line
	2600 2200 2600 2400
Wire Wire Line
	1000 2400 2700 2400
Wire Wire Line
	2700 2300 2600 2300
Connection ~ 2600 2300
Wire Wire Line
	1000 2300 1000 2500
Connection ~ 2600 2400
Wire Wire Line
	1400 2400 1400 2300
Connection ~ 1400 2400
Wire Wire Line
	1800 2400 1800 2300
Connection ~ 1800 2400
Wire Wire Line
	1000 1900 2700 1900
Wire Wire Line
	1800 1900 1800 2100
Wire Wire Line
	2700 1700 2600 1700
Connection ~ 2600 1900
Wire Wire Line
	2700 1800 2600 1800
Connection ~ 2600 1800
Wire Wire Line
	1400 1900 1400 2100
Connection ~ 1800 1900
Wire Wire Line
	1000 1800 1000 2100
Connection ~ 1400 1900
$Comp
L GND #PWR03
U 1 1 55C7AD3A
P 1000 2500
F 0 "#PWR03" H 1000 2250 50  0001 C CNN
F 1 "GND" H 1000 2350 50  0000 C CNN
F 2 "" H 1000 2500 60  0000 C CNN
F 3 "" H 1000 2500 60  0000 C CNN
	1    1000 2500
	1    0    0    -1  
$EndComp
Connection ~ 1000 2400
$Comp
L +5V #PWR04
U 1 1 55C7AE32
P 1000 1800
F 0 "#PWR04" H 1000 1650 50  0001 C CNN
F 1 "+5V" H 1000 1940 50  0000 C CNN
F 2 "" H 1000 1800 60  0000 C CNN
F 3 "" H 1000 1800 60  0000 C CNN
	1    1000 1800
	1    0    0    -1  
$EndComp
Connection ~ 1000 1900
$Comp
L C C4
U 1 1 55C8D2C8
P 2200 2200
F 0 "C4" H 2220 2300 60  0000 L CNN
F 1 "100n" H 2220 2100 60  0000 L CNN
F 2 "0603_N" H 2220 2010 40  0001 C CNN
F 3 "" H 2200 2200 60  0000 C CNN
	1    2200 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 2300 2200 2400
Connection ~ 2200 2400
Wire Wire Line
	2700 2000 2200 2000
Wire Wire Line
	2200 2000 2200 2100
Wire Wire Line
	2600 1700 2600 1900
$Comp
L R_Network_4 RN2
U 1 1 55C8DFBC
P 6600 2600
F 0 "RN2" H 6600 2680 60  0000 C CNN
F 1 "10k" H 6600 2600 40  0000 C CNN
F 2 "4x0603_N" H 6600 2540 40  0001 C CNN
F 3 "" H 6600 2600 60  0000 C CNN
	1    6600 2600
	1    0    0    1   
$EndComp
$Comp
L R_Network_4 RN2
U 2 1 55C8DFC2
P 6600 2500
F 0 "RN2" H 6600 2580 60  0001 C CNN
F 1 "10k" H 6600 2500 40  0000 C CNN
F 2 "4x0603_N" H 6600 2440 40  0001 C CNN
F 3 "" H 6600 2500 60  0000 C CNN
	2    6600 2500
	1    0    0    1   
$EndComp
$Comp
L R_Network_4 RN2
U 3 1 55C8DFC8
P 6600 2400
F 0 "RN2" H 6600 2480 60  0001 C CNN
F 1 "10k" H 6600 2400 40  0000 C CNN
F 2 "4x0603_N" H 6600 2340 40  0001 C CNN
F 3 "" H 6600 2400 60  0000 C CNN
	3    6600 2400
	1    0    0    1   
$EndComp
$Comp
L R_Network_4 RN2
U 4 1 55C8DFCE
P 6600 2300
F 0 "RN2" H 6600 2380 60  0001 C CNN
F 1 "10k" H 6600 2300 40  0000 C CNN
F 2 "4x0603_N" H 6600 2240 40  0001 C CNN
F 3 "" H 6600 2300 60  0000 C CNN
	4    6600 2300
	1    0    0    1   
$EndComp
Wire Wire Line
	6800 2600 7900 2600
Wire Wire Line
	6800 2500 7900 2500
Wire Wire Line
	6800 2400 7900 2400
Wire Wire Line
	6800 2300 7900 2300
$Comp
L 78M05CDT U2
U 1 1 55CA4654
P 4700 4300
F 0 "U2" H 4700 4650 60  0000 C CNN
F 1 "78M05CDT" H 4700 4560 60  0000 C CNN
F 2 "D-PAK_M" H 4700 4470 40  0001 C CNN
F 3 "" H 4700 4300 60  0000 C CNN
	1    4700 4300
	1    0    0    -1  
$EndComp
$Comp
L C C5
U 1 1 55CA4C67
P 4100 4400
F 0 "C5" H 4120 4500 60  0000 L CNN
F 1 "100n" H 4120 4300 60  0000 L CNN
F 2 "0603_N" H 4120 4210 40  0001 C CNN
F 3 "" H 4100 4400 60  0000 C CNN
	1    4100 4400
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 55CA4CCC
P 5300 4400
F 0 "C6" H 5320 4500 60  0000 L CNN
F 1 "100n" H 5320 4300 60  0000 L CNN
F 2 "0603_N" H 5320 4210 40  0001 C CNN
F 3 "" H 5300 4400 60  0000 C CNN
	1    5300 4400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 55CA4F4E
P 4700 4600
F 0 "#PWR05" H 4700 4350 50  0001 C CNN
F 1 "GND" H 4700 4450 50  0000 C CNN
F 2 "" H 4700 4600 60  0000 C CNN
F 3 "" H 4700 4600 60  0000 C CNN
	1    4700 4600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 55CA4F89
P 4100 4600
F 0 "#PWR06" H 4100 4350 50  0001 C CNN
F 1 "GND" H 4100 4450 50  0000 C CNN
F 2 "" H 4100 4600 60  0000 C CNN
F 3 "" H 4100 4600 60  0000 C CNN
	1    4100 4600
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 55CA4FC4
P 5300 4600
F 0 "#PWR07" H 5300 4350 50  0001 C CNN
F 1 "GND" H 5300 4450 50  0000 C CNN
F 2 "" H 5300 4600 60  0000 C CNN
F 3 "" H 5300 4600 60  0000 C CNN
	1    5300 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 4600 5300 4500
Wire Wire Line
	4700 4600 4700 4500
Wire Wire Line
	4100 4600 4100 4500
Wire Wire Line
	4200 4200 4100 4200
Wire Wire Line
	4100 4100 4100 4300
Wire Wire Line
	5200 4200 5300 4200
Wire Wire Line
	5300 4100 5300 4300
$Comp
L +6V #PWR08
U 1 1 55CA53BC
P 8600 700
F 0 "#PWR08" H 8600 550 50  0001 C CNN
F 1 "+6V" H 8600 840 50  0000 C CNN
F 2 "" H 8600 700 60  0000 C CNN
F 3 "" H 8600 700 60  0000 C CNN
	1    8600 700 
	1    0    0    -1  
$EndComp
$Comp
L +6V #PWR09
U 1 1 55CA545A
P 8600 2000
F 0 "#PWR09" H 8600 1850 50  0001 C CNN
F 1 "+6V" H 8600 2140 50  0000 C CNN
F 2 "" H 8600 2000 60  0000 C CNN
F 3 "" H 8600 2000 60  0000 C CNN
	1    8600 2000
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR010
U 1 1 55CA5655
P 5300 4100
F 0 "#PWR010" H 5300 3950 50  0001 C CNN
F 1 "+5V" H 5300 4240 50  0000 C CNN
F 2 "" H 5300 4100 60  0000 C CNN
F 3 "" H 5300 4100 60  0000 C CNN
	1    5300 4100
	1    0    0    -1  
$EndComp
Connection ~ 5300 4200
$Comp
L IRLR2905PBF T1
U 1 1 55CA5084
P 1600 5900
F 0 "T1" H 1725 5960 60  0000 L CNN
F 1 "IRLR2905PBF" H 1725 5840 60  0000 L CNN
F 2 "D-PAK_M" H 1725 5750 40  0001 L CNN
F 3 "" H 1600 5900 60  0000 C CNN
	1    1600 5900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 55CA55E7
P 1600 6200
F 0 "#PWR011" H 1600 5950 50  0001 C CNN
F 1 "GND" H 1600 6050 50  0000 C CNN
F 2 "" H 1600 6200 60  0000 C CNN
F 3 "" H 1600 6200 60  0000 C CNN
	1    1600 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 6200 1600 6100
$Comp
L R R1
U 1 1 55CA57A7
P 1100 6000
F 0 "R1" H 1100 6080 60  0000 C CNN
F 1 "100R" H 1100 6000 40  0000 C CNN
F 2 "0603_N" H 1100 5940 40  0001 C CNN
F 3 "" H 1100 6000 60  0000 C CNN
	1    1100 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 6000 1400 6000
$Comp
L +12V #PWR012
U 1 1 55CA5F31
P 4100 4100
F 0 "#PWR012" H 4100 3950 50  0001 C CNN
F 1 "+12V" H 4100 4240 50  0000 C CNN
F 2 "" H 4100 4100 60  0000 C CNN
F 3 "" H 4100 4100 60  0000 C CNN
	1    4100 4100
	1    0    0    -1  
$EndComp
Connection ~ 4100 4200
$Comp
L EDG-5.08mm-4 CON5
U 1 1 55CEFE85
P 2900 4400
F 0 "CON5" H 2900 4760 60  0000 C CNN
F 1 "BEC" H 2900 4140 60  0000 C CNN
F 2 "EDG-5.08mm-4_N" H 2900 4050 40  0001 C CNN
F 3 "" H 2900 4400 60  0000 C CNN
	1    2900 4400
	-1   0    0    -1  
$EndComp
$Comp
L EDG-5.08mm-2 CON3
U 1 1 55CEFF1C
P 2200 5600
F 0 "CON3" H 2200 5860 60  0000 C CNN
F 1 "Heater" H 2200 5440 60  0000 C CNN
F 2 "EDG-5.08mm-2_N" H 2200 5350 40  0001 C CNN
F 3 "" H 2200 5600 60  0000 C CNN
	1    2200 5600
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR013
U 1 1 55CF0406
P 1600 5300
F 0 "#PWR013" H 1600 5150 50  0001 C CNN
F 1 "+12V" H 1600 5440 50  0000 C CNN
F 2 "" H 1600 5300 60  0000 C CNN
F 3 "" H 1600 5300 60  0000 C CNN
	1    1600 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 5500 1600 5500
Wire Wire Line
	1600 5500 1600 5300
Wire Wire Line
	1400 5600 1800 5600
Wire Wire Line
	1600 5600 1600 5700
$Comp
L +12V #PWR014
U 1 1 55CF0C07
P 3400 4100
F 0 "#PWR014" H 3400 3950 50  0001 C CNN
F 1 "+12V" H 3400 4240 50  0000 C CNN
F 2 "" H 3400 4100 60  0000 C CNN
F 3 "" H 3400 4100 60  0000 C CNN
	1    3400 4100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3300 4200 3400 4200
Wire Wire Line
	3400 4200 3400 4100
$Comp
L +6V #PWR015
U 1 1 55CF0EB9
P 3600 4100
F 0 "#PWR015" H 3600 3950 50  0001 C CNN
F 1 "+6V" H 3600 4240 50  0000 C CNN
F 2 "" H 3600 4100 60  0000 C CNN
F 3 "" H 3600 4100 60  0000 C CNN
	1    3600 4100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3300 4400 3600 4400
Wire Wire Line
	3600 4400 3600 4100
Wire Wire Line
	3300 4300 3400 4300
Wire Wire Line
	3400 4300 3400 4600
Wire Wire Line
	3300 4500 3400 4500
Connection ~ 3400 4500
$Comp
L GND #PWR016
U 1 1 55CF104B
P 3400 4600
F 0 "#PWR016" H 3400 4350 50  0001 C CNN
F 1 "GND" H 3400 4450 50  0000 C CNN
F 2 "" H 3400 4600 60  0000 C CNN
F 3 "" H 3400 4600 60  0000 C CNN
	1    3400 4600
	-1   0    0    -1  
$EndComp
$Comp
L EDG-5.08mm-2 CON4
U 1 1 55CF1092
P 1100 4400
F 0 "CON4" H 1100 4660 60  0000 C CNN
F 1 "+12V" H 1100 4240 60  0000 C CNN
F 2 "EDG-5.08mm-2_N" H 1100 4150 40  0001 C CNN
F 3 "" H 1100 4400 60  0000 C CNN
	1    1100 4400
	-1   0    0    -1  
$EndComp
$Comp
L +12V #PWR017
U 1 1 55CF1178
P 1600 4100
F 0 "#PWR017" H 1600 3950 50  0001 C CNN
F 1 "+12V" H 1600 4240 50  0000 C CNN
F 2 "" H 1600 4100 60  0000 C CNN
F 3 "" H 1600 4100 60  0000 C CNN
	1    1600 4100
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR018
U 1 1 55CF11FC
P 1600 4500
F 0 "#PWR018" H 1600 4250 50  0001 C CNN
F 1 "GND" H 1600 4350 50  0000 C CNN
F 2 "" H 1600 4500 60  0000 C CNN
F 3 "" H 1600 4500 60  0000 C CNN
	1    1600 4500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1500 4400 1600 4400
Wire Wire Line
	1600 4400 1600 4500
Wire Wire Line
	1500 4300 1600 4300
Wire Wire Line
	1600 4300 1600 4100
$Comp
L GND #PWR019
U 1 1 55CF1711
P 3500 6200
F 0 "#PWR019" H 3500 5950 50  0001 C CNN
F 1 "GND" H 3500 6050 50  0000 C CNN
F 2 "" H 3500 6200 60  0000 C CNN
F 3 "" H 3500 6200 60  0000 C CNN
	1    3500 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 6200 3500 6100
$Comp
L R R2
U 1 1 55CF1718
P 3000 6000
F 0 "R2" H 3000 6080 60  0000 C CNN
F 1 "100R" H 3000 6000 40  0000 C CNN
F 2 "0603_N" H 3000 5940 40  0001 C CNN
F 3 "" H 3000 6000 60  0000 C CNN
	1    3000 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 6000 3300 6000
$Comp
L +12V #PWR020
U 1 1 55CF171F
P 4700 5500
F 0 "#PWR020" H 4700 5350 50  0001 C CNN
F 1 "+12V" H 4700 5640 50  0000 C CNN
F 2 "" H 4700 5500 60  0000 C CNN
F 3 "" H 4700 5500 60  0000 C CNN
	1    4700 5500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4500 5600 4700 5600
Wire Wire Line
	4700 5600 4700 5500
Wire Wire Line
	3700 5600 3500 5600
Wire Wire Line
	3500 5500 3500 5700
$Comp
L PIN-2x1_angled CON6
U 1 1 55D026B9
P 4100 5600
F 0 "CON6" H 4100 5760 60  0000 C CNN
F 1 "Motor" H 4100 5440 60  0000 C CNN
F 2 "PIN-2x1_angled_N" H 4100 5350 40  0001 C CNN
F 3 "" H 4100 5600 60  0000 C CNN
	1    4100 5600
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR021
U 1 1 55D06169
P 1600 7500
F 0 "#PWR021" H 1600 7250 50  0001 C CNN
F 1 "GND" H 1600 7350 50  0000 C CNN
F 2 "" H 1600 7500 60  0000 C CNN
F 3 "" H 1600 7500 60  0000 C CNN
	1    1600 7500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 7500 1600 7400
$Comp
L R R3
U 1 1 55D06170
P 1100 7300
F 0 "R3" H 1100 7380 60  0000 C CNN
F 1 "100R" H 1100 7300 40  0000 C CNN
F 2 "0603_N" H 1100 7240 40  0001 C CNN
F 3 "" H 1100 7300 60  0000 C CNN
	1    1100 7300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 7300 1400 7300
Wire Wire Line
	1400 6900 1800 6900
Wire Wire Line
	1600 6900 1600 7000
$Comp
L PIN-1x3 CON7
U 1 1 55D0619C
P 2200 6800
F 0 "CON7" H 2200 7060 60  0000 C CNN
F 1 "FAN1" H 2200 6540 60  0000 C CNN
F 2 "PIN-1x3_M" H 2200 6450 40  0001 C CNN
F 3 "" H 2200 6800 60  0000 C CNN
	1    2200 6800
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR022
U 1 1 55D0622F
P 1600 6600
F 0 "#PWR022" H 1600 6450 50  0001 C CNN
F 1 "+12V" H 1600 6740 50  0000 C CNN
F 2 "" H 1600 6600 60  0000 C CNN
F 3 "" H 1600 6600 60  0000 C CNN
	1    1600 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1800 6800 1600 6800
Wire Wire Line
	1600 6800 1600 6600
$Comp
L GND #PWR023
U 1 1 55D0642F
P 3500 7500
F 0 "#PWR023" H 3500 7250 50  0001 C CNN
F 1 "GND" H 3500 7350 50  0000 C CNN
F 2 "" H 3500 7500 60  0000 C CNN
F 3 "" H 3500 7500 60  0000 C CNN
	1    3500 7500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 7500 3500 7400
$Comp
L R R4
U 1 1 55D06436
P 3000 7300
F 0 "R4" H 3000 7380 60  0000 C CNN
F 1 "100R" H 3000 7300 40  0000 C CNN
F 2 "0603_N" H 3000 7240 40  0001 C CNN
F 3 "" H 3000 7300 60  0000 C CNN
	1    3000 7300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 7300 3300 7300
Wire Wire Line
	3300 6900 3700 6900
Wire Wire Line
	3500 6900 3500 7000
$Comp
L PIN-1x3 CON8
U 1 1 55D06445
P 4100 6800
F 0 "CON8" H 4100 7060 60  0000 C CNN
F 1 "FAN2" H 4100 6540 60  0000 C CNN
F 2 "PIN-1x3_M" H 4100 6450 40  0001 C CNN
F 3 "" H 4100 6800 60  0000 C CNN
	1    4100 6800
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR024
U 1 1 55D0644B
P 3500 6600
F 0 "#PWR024" H 3500 6450 50  0001 C CNN
F 1 "+12V" H 3500 6740 50  0000 C CNN
F 2 "" H 3500 6600 60  0000 C CNN
F 3 "" H 3500 6600 60  0000 C CNN
	1    3500 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 6800 3500 6800
Wire Wire Line
	3500 6800 3500 6600
Wire Wire Line
	900  6000 600  6000
Text Label 600  6000 0    60   ~ 0
Heater
Wire Wire Line
	900  7300 600  7300
Text Label 600  7300 0    60   ~ 0
FAN1
Wire Wire Line
	2800 6000 2500 6000
Text Label 2500 6000 0    60   ~ 0
Motor
Wire Wire Line
	2800 7300 2500 7300
Text Label 2500 7300 0    60   ~ 0
FAN2
$Comp
L AMS1117-3.3 U4
U 1 1 55D09C1B
P 6600 4300
F 0 "U4" H 6600 4650 60  0000 C CNN
F 1 "AMS1117-3.3" H 6600 4560 60  0000 C CNN
F 2 "SOT223_N" H 6600 4470 40  0001 C CNN
F 3 "" H 6600 4300 60  0000 C CNN
	1    6600 4300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR025
U 1 1 55D09CDE
P 6600 4600
F 0 "#PWR025" H 6600 4350 50  0001 C CNN
F 1 "GND" H 6600 4450 50  0000 C CNN
F 2 "" H 6600 4600 60  0000 C CNN
F 3 "" H 6600 4600 60  0000 C CNN
	1    6600 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 4600 6600 4500
$Comp
L C C8
U 1 1 55D09D66
P 7200 4400
F 0 "C8" H 7220 4500 60  0000 L CNN
F 1 "100n" H 7220 4300 60  0000 L CNN
F 2 "0603_N" H 7220 4210 40  0001 C CNN
F 3 "" H 7200 4400 60  0000 C CNN
	1    7200 4400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR026
U 1 1 55D09D6C
P 7200 4600
F 0 "#PWR026" H 7200 4350 50  0001 C CNN
F 1 "GND" H 7200 4450 50  0000 C CNN
F 2 "" H 7200 4600 60  0000 C CNN
F 3 "" H 7200 4600 60  0000 C CNN
	1    7200 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 4600 7200 4500
Wire Wire Line
	7100 4200 7200 4200
Wire Wire Line
	7200 4100 7200 4300
$Comp
L +5V #PWR027
U 1 1 55D09D75
P 6000 4100
F 0 "#PWR027" H 6000 3950 50  0001 C CNN
F 1 "+5V" H 6000 4240 50  0000 C CNN
F 2 "" H 6000 4100 60  0000 C CNN
F 3 "" H 6000 4100 60  0000 C CNN
	1    6000 4100
	1    0    0    -1  
$EndComp
Connection ~ 7200 4200
$Comp
L C C7
U 1 1 55D09E0B
P 6000 4400
F 0 "C7" H 6020 4500 60  0000 L CNN
F 1 "100n" H 6020 4300 60  0000 L CNN
F 2 "0603_N" H 6020 4210 40  0001 C CNN
F 3 "" H 6000 4400 60  0000 C CNN
	1    6000 4400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR028
U 1 1 55D09E11
P 6000 4600
F 0 "#PWR028" H 6000 4350 50  0001 C CNN
F 1 "GND" H 6000 4450 50  0000 C CNN
F 2 "" H 6000 4600 60  0000 C CNN
F 3 "" H 6000 4600 60  0000 C CNN
	1    6000 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 4600 6000 4500
Wire Wire Line
	6100 4200 6000 4200
Wire Wire Line
	6000 4100 6000 4300
Connection ~ 6000 4200
$Comp
L +3.3V #PWR029
U 1 1 55D0A050
P 7200 4100
F 0 "#PWR029" H 7200 3950 50  0001 C CNN
F 1 "+3.3V" H 7200 4240 50  0000 C CNN
F 2 "" H 7200 4100 60  0000 C CNN
F 3 "" H 7200 4100 60  0000 C CNN
	1    7200 4100
	1    0    0    -1  
$EndComp
$Comp
L MicroswitchSmt-4.3 SW1
U 1 1 55D0B7DC
P 8200 4300
F 0 "SW1" H 8200 4420 60  0000 C CNN
F 1 "RESET" H 8200 4220 60  0000 C CNN
F 2 "MicroswitchSmd-4.3_N" H 8200 4130 40  0001 C CNN
F 3 "" H 8200 4300 60  0000 C CNN
	1    8200 4300
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR030
U 1 1 55D0BCCA
P 8200 4600
F 0 "#PWR030" H 8200 4350 50  0001 C CNN
F 1 "GND" H 8200 4450 50  0000 C CNN
F 2 "" H 8200 4600 60  0000 C CNN
F 3 "" H 8200 4600 60  0000 C CNN
	1    8200 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 4600 8200 4500
Wire Wire Line
	8200 4100 8200 4000
Wire Wire Line
	8200 4000 8500 4000
Text Label 8200 4000 0    60   ~ 0
RESET
Text Label 2400 900  0    60   ~ 0
RESET
Wire Wire Line
	2700 900  2400 900 
Wire Wire Line
	2700 1100 1700 1100
Wire Wire Line
	1700 1100 1700 1400
Wire Wire Line
	1700 1400 1800 1400
Wire Wire Line
	2200 1400 2300 1400
Wire Wire Line
	2300 1400 2300 1200
Wire Wire Line
	2300 1200 2700 1200
$Comp
L GND #PWR031
U 1 1 55D2CBB7
P 2000 1700
F 0 "#PWR031" H 2000 1450 50  0001 C CNN
F 1 "GND" H 2000 1550 50  0000 C CNN
F 2 "" H 2000 1700 60  0000 C CNN
F 3 "" H 2000 1700 60  0000 C CNN
	1    2000 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 1700 2000 1600
$Comp
L Ceramic_3.7x3.1_16MHz Q1
U 1 1 55D2C616
P 2000 1400
F 0 "Q1" H 2000 1630 60  0000 C CNN
F 1 "16MHz" H 2000 1550 60  0000 C CNN
F 2 "3.7x3.1_N" H 2000 1460 40  0001 C CNN
F 3 "" H 2000 1400 60  0000 C CNN
	1    2000 1400
	1    0    0    -1  
$EndComp
$Comp
L ESP-01-RESCUE-drOctopus U3
U 1 1 55CF328A
P 8600 5800
F 0 "U3" H 8600 6260 60  0000 C CNN
F 1 "ESP-01" H 8600 5440 60  0000 C CNN
F 2 "ESP-01_N_socket" H 8600 5350 40  0001 C CNN
F 3 "" H 8600 5800 60  0000 C CNN
	1    8600 5800
	1    0    0    -1  
$EndComp
$Comp
L PESD5V2S2UT D1
U 1 1 55DCBD43
P 7000 1500
F 0 "D1" H 7175 1535 60  0000 L CNN
F 1 "PESD5V2S2UT" V 6800 1200 40  0000 L CNN
F 2 "SOT23-3_N" H 7175 1325 40  0001 L CNN
F 3 "" H 7000 1500 60  0000 C CNN
	1    7000 1500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR032
U 1 1 55DCBFCB
P 7000 1800
F 0 "#PWR032" H 7000 1550 50  0001 C CNN
F 1 "GND" H 7000 1650 50  0000 C CNN
F 2 "" H 7000 1800 60  0000 C CNN
F 3 "" H 7000 1800 60  0000 C CNN
	1    7000 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 1800 7000 1700
Wire Wire Line
	7100 1100 7100 1400
Connection ~ 7100 1100
Wire Wire Line
	6900 1400 6900 1000
Connection ~ 6900 1000
$Comp
L PESD5V2S2UT D3
U 1 1 55DCC87D
P 7600 1500
F 0 "D3" H 7775 1535 60  0000 L CNN
F 1 "PESD5V2S2UT" V 7400 1200 40  0000 L CNN
F 2 "SOT23-3_N" H 7775 1325 40  0001 L CNN
F 3 "" H 7600 1500 60  0000 C CNN
	1    7600 1500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR033
U 1 1 55DCC883
P 7600 1800
F 0 "#PWR033" H 7600 1550 50  0001 C CNN
F 1 "GND" H 7600 1650 50  0000 C CNN
F 2 "" H 7600 1800 60  0000 C CNN
F 3 "" H 7600 1800 60  0000 C CNN
	1    7600 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 1800 7600 1700
$Comp
L PESD5V2S2UT D2
U 1 1 55DCCADE
P 7000 2800
F 0 "D2" H 7175 2835 60  0000 L CNN
F 1 "PESD5V2S2UT" V 6800 2500 40  0000 L CNN
F 2 "SOT23-3_N" H 7175 2625 40  0001 L CNN
F 3 "" H 7000 2800 60  0000 C CNN
	1    7000 2800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR034
U 1 1 55DCCAE4
P 7000 3100
F 0 "#PWR034" H 7000 2850 50  0001 C CNN
F 1 "GND" H 7000 2950 50  0000 C CNN
F 2 "" H 7000 3100 60  0000 C CNN
F 3 "" H 7000 3100 60  0000 C CNN
	1    7000 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7000 3100 7000 3000
$Comp
L PESD5V2S2UT D4
U 1 1 55DCCAEB
P 7600 2800
F 0 "D4" H 7775 2835 60  0000 L CNN
F 1 "PESD5V2S2UT" V 7400 2500 40  0000 L CNN
F 2 "SOT23-3_N" H 7775 2625 40  0001 L CNN
F 3 "" H 7600 2800 60  0000 C CNN
	1    7600 2800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR035
U 1 1 55DCCAF1
P 7600 3100
F 0 "#PWR035" H 7600 2850 50  0001 C CNN
F 1 "GND" H 7600 2950 50  0000 C CNN
F 2 "" H 7600 3100 60  0000 C CNN
F 3 "" H 7600 3100 60  0000 C CNN
	1    7600 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7600 3100 7600 3000
Wire Wire Line
	6900 2700 6900 2300
Connection ~ 6900 2300
Wire Wire Line
	7100 2700 7100 2400
Connection ~ 7100 2400
Wire Wire Line
	7500 2700 7500 2500
Connection ~ 7500 2500
Wire Wire Line
	7700 2700 7700 2600
Connection ~ 7700 2600
Wire Wire Line
	7500 1400 7500 1200
Connection ~ 7500 1200
Wire Wire Line
	7700 1400 7700 1300
Connection ~ 7700 1300
$Comp
L +6V #PWR036
U 1 1 55DCF24A
P 10400 2400
F 0 "#PWR036" H 10400 2250 50  0001 C CNN
F 1 "+6V" H 10400 2540 50  0000 C CNN
F 2 "" H 10400 2400 60  0000 C CNN
F 3 "" H 10400 2400 60  0000 C CNN
	1    10400 2400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR037
U 1 1 55DCF250
P 10400 2800
F 0 "#PWR037" H 10400 2550 50  0001 C CNN
F 1 "GND" H 10400 2650 50  0000 C CNN
F 2 "" H 10400 2800 60  0000 C CNN
F 3 "" H 10400 2800 60  0000 C CNN
	1    10400 2800
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 2400 10400 2500
Wire Wire Line
	10400 2700 10400 2800
$Comp
L C C9
U 1 1 55DD0444
P 10400 1300
F 0 "C9" H 10420 1400 60  0000 L CNN
F 1 "10u/16V" H 10420 1200 60  0000 L CNN
F 2 "0805_N" H 10420 1110 40  0001 C CNN
F 3 "" H 10400 1300 60  0000 C CNN
	1    10400 1300
	1    0    0    -1  
$EndComp
$Comp
L +6V #PWR038
U 1 1 55DD044A
P 10400 1100
F 0 "#PWR038" H 10400 950 50  0001 C CNN
F 1 "+6V" H 10400 1240 50  0000 C CNN
F 2 "" H 10400 1100 60  0000 C CNN
F 3 "" H 10400 1100 60  0000 C CNN
	1    10400 1100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR039
U 1 1 55DD0450
P 10400 1500
F 0 "#PWR039" H 10400 1250 50  0001 C CNN
F 1 "GND" H 10400 1350 50  0000 C CNN
F 2 "" H 10400 1500 60  0000 C CNN
F 3 "" H 10400 1500 60  0000 C CNN
	1    10400 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 1100 10400 1200
Wire Wire Line
	10400 1400 10400 1500
$Comp
L IRLML6244TRPBF T2
U 1 1 55DD22AE
P 3500 5900
F 0 "T2" H 3625 5960 60  0000 L CNN
F 1 "IRLML6244TRPBF" H 3625 5840 60  0000 L CNN
F 2 "SOT23-3_N" H 3625 5750 40  0001 L CNN
F 3 "" H 3500 5900 60  0000 C CNN
	1    3500 5900
	1    0    0    -1  
$EndComp
$Comp
L IRLML6244TRPBF T3
U 1 1 55DD24BA
P 1600 7200
F 0 "T3" H 1725 7260 60  0000 L CNN
F 1 "IRLML6244TRPBF" H 1725 7140 60  0000 L CNN
F 2 "SOT23-3_N" H 1725 7050 40  0001 L CNN
F 3 "" H 1600 7200 60  0000 C CNN
	1    1600 7200
	1    0    0    -1  
$EndComp
$Comp
L IRLML6244TRPBF T4
U 1 1 55DD2577
P 3500 7200
F 0 "T4" H 3625 7260 60  0000 L CNN
F 1 "IRLML6244TRPBF" H 3625 7140 60  0000 L CNN
F 2 "SOT23-3_N" H 3625 7050 40  0001 L CNN
F 3 "" H 3500 7200 60  0000 C CNN
	1    3500 7200
	1    0    0    -1  
$EndComp
$Comp
L C C10
U 1 1 55DDD50D
P 10400 2600
F 0 "C10" H 10420 2700 60  0000 L CNN
F 1 "10u/16V" H 10420 2500 60  0000 L CNN
F 2 "0805_N" H 10420 2410 40  0001 C CNN
F 3 "" H 10400 2600 60  0000 C CNN
	1    10400 2600
	1    0    0    -1  
$EndComp
$Comp
L Cpol C11
U 1 1 55DD4DF2
P 1900 4300
F 0 "C11" H 2000 4350 60  0000 L CNN
F 1 "470u/16V" H 2000 4250 60  0000 L CNN
F 2 "Cpol_8.0_12.0_M" H 1920 4110 40  0001 L CNN
F 3 "ED1C471MNN0812" H 2000 4175 30  0000 L CNN
	1    1900 4300
	1    0    0    -1  
$EndComp
$Comp
L +12V #PWR040
U 1 1 55DE163D
P 1900 4100
F 0 "#PWR040" H 1900 3950 50  0001 C CNN
F 1 "+12V" H 1900 4240 50  0000 C CNN
F 2 "" H 1900 4100 60  0000 C CNN
F 3 "" H 1900 4100 60  0000 C CNN
	1    1900 4100
	-1   0    0    -1  
$EndComp
$Comp
L GND #PWR041
U 1 1 55DE16C9
P 1900 4500
F 0 "#PWR041" H 1900 4250 50  0001 C CNN
F 1 "GND" H 1900 4350 50  0000 C CNN
F 2 "" H 1900 4500 60  0000 C CNN
F 3 "" H 1900 4500 60  0000 C CNN
	1    1900 4500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1900 4100 1900 4200
Wire Wire Line
	1900 4400 1900 4500
$Comp
L SS14 D6
U 1 1 55DE2928
P 3500 5400
F 0 "D6" H 3575 5460 60  0000 L CNN
F 1 "SS14" H 3575 5340 60  0000 L CNN
F 2 "SMA_N" H 3575 5250 40  0001 L CNN
F 3 "" H 3500 5400 60  0000 C CNN
	1    3500 5400
	-1   0    0    1   
$EndComp
$Comp
L SS14 D5
U 1 1 55DE2EEC
P 1400 5400
F 0 "D5" H 1475 5460 60  0000 L CNN
F 1 "SS14" H 1475 5340 60  0000 L CNN
F 2 "SMA_N" H 1475 5250 40  0001 L CNN
F 3 "" H 1400 5400 60  0000 C CNN
	1    1400 5400
	-1   0    0    1   
$EndComp
Wire Wire Line
	1400 5300 1400 5300
Wire Wire Line
	1400 5600 1400 5500
Connection ~ 1600 5600
Connection ~ 3500 5600
$Comp
L +12V #PWR042
U 1 1 55DE3B5A
P 1400 5300
F 0 "#PWR042" H 1400 5150 50  0001 C CNN
F 1 "+12V" H 1400 5440 50  0000 C CNN
F 2 "" H 1400 5300 60  0000 C CNN
F 3 "" H 1400 5300 60  0000 C CNN
	1    1400 5300
	1    0    0    -1  
$EndComp
$Comp
L SS14 D7
U 1 1 55DE40E7
P 1400 6700
F 0 "D7" H 1475 6760 60  0000 L CNN
F 1 "SS14" H 1475 6640 60  0000 L CNN
F 2 "SMA_N" H 1475 6550 40  0001 L CNN
F 3 "" H 1400 6700 60  0000 C CNN
	1    1400 6700
	-1   0    0    1   
$EndComp
Wire Wire Line
	1400 6600 1400 6600
Wire Wire Line
	1400 6900 1400 6800
$Comp
L +12V #PWR043
U 1 1 55DE40EF
P 1400 6600
F 0 "#PWR043" H 1400 6450 50  0001 C CNN
F 1 "+12V" H 1400 6740 50  0000 C CNN
F 2 "" H 1400 6600 60  0000 C CNN
F 3 "" H 1400 6600 60  0000 C CNN
	1    1400 6600
	1    0    0    -1  
$EndComp
Connection ~ 1600 6900
$Comp
L SS14 D8
U 1 1 55DE466E
P 3300 6700
F 0 "D8" H 3375 6760 60  0000 L CNN
F 1 "SS14" H 3375 6640 60  0000 L CNN
F 2 "SMA_N" H 3375 6550 40  0001 L CNN
F 3 "" H 3300 6700 60  0000 C CNN
	1    3300 6700
	-1   0    0    1   
$EndComp
Wire Wire Line
	3300 6600 3300 6600
Wire Wire Line
	3300 6900 3300 6800
$Comp
L +12V #PWR044
U 1 1 55DE4676
P 3300 6600
F 0 "#PWR044" H 3300 6450 50  0001 C CNN
F 1 "+12V" H 3300 6740 50  0000 C CNN
F 2 "" H 3300 6600 60  0000 C CNN
F 3 "" H 3300 6600 60  0000 C CNN
	1    3300 6600
	1    0    0    -1  
$EndComp
Connection ~ 3500 6900
$Comp
L +12V #PWR045
U 1 1 55DE49E1
P 3500 5300
F 0 "#PWR045" H 3500 5150 50  0001 C CNN
F 1 "+12V" H 3500 5440 50  0000 C CNN
F 2 "" H 3500 5300 60  0000 C CNN
F 3 "" H 3500 5300 60  0000 C CNN
	1    3500 5300
	1    0    0    -1  
$EndComp
$Comp
L mounting_hole_plated MH4
U 1 1 55DEA268
P 10700 6200
F 0 "MH4" H 10700 6320 60  0000 C CNN
F 1 "mounting_hole_plated" H 10700 6200 60  0001 C CNN
F 2 "mounting_hole_3.2_7.5_plated_vias" H 10700 6110 40  0001 C CNN
F 3 "" H 10700 6200 60  0000 C CNN
	1    10700 6200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR046
U 1 1 55DEB000
P 10700 6300
F 0 "#PWR046" H 10700 6050 50  0001 C CNN
F 1 "GND" H 10700 6150 50  0000 C CNN
F 2 "" H 10700 6300 60  0000 C CNN
F 3 "" H 10700 6300 60  0000 C CNN
	1    10700 6300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR047
U 1 1 55DEB0B2
P 10700 5700
F 0 "#PWR047" H 10700 5450 50  0001 C CNN
F 1 "GND" H 10700 5550 50  0000 C CNN
F 2 "" H 10700 5700 60  0000 C CNN
F 3 "" H 10700 5700 60  0000 C CNN
	1    10700 5700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR048
U 1 1 55DEB1F5
P 10700 5100
F 0 "#PWR048" H 10700 4850 50  0001 C CNN
F 1 "GND" H 10700 4950 50  0000 C CNN
F 2 "" H 10700 5100 60  0000 C CNN
F 3 "" H 10700 5100 60  0000 C CNN
	1    10700 5100
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR049
U 1 1 55DEB27A
P 10700 4500
F 0 "#PWR049" H 10700 4250 50  0001 C CNN
F 1 "GND" H 10700 4350 50  0000 C CNN
F 2 "" H 10700 4500 60  0000 C CNN
F 3 "" H 10700 4500 60  0000 C CNN
	1    10700 4500
	1    0    0    -1  
$EndComp
$Comp
L mounting_hole_plated MH3
U 1 1 55DEB471
P 10700 5600
F 0 "MH3" H 10700 5720 60  0000 C CNN
F 1 "mounting_hole_plated" H 10700 5600 60  0001 C CNN
F 2 "mounting_hole_3.2_7.5_plated_vias" H 10700 5510 40  0001 C CNN
F 3 "" H 10700 5600 60  0000 C CNN
	1    10700 5600
	1    0    0    -1  
$EndComp
$Comp
L mounting_hole_plated MH2
U 1 1 55DEB51C
P 10700 5000
F 0 "MH2" H 10700 5120 60  0000 C CNN
F 1 "mounting_hole_plated" H 10700 5000 60  0001 C CNN
F 2 "mounting_hole_3.2_7.5_plated_vias" H 10700 4910 40  0001 C CNN
F 3 "" H 10700 5000 60  0000 C CNN
	1    10700 5000
	1    0    0    -1  
$EndComp
$Comp
L mounting_hole_plated MH1
U 1 1 55DEB5CA
P 10700 4400
F 0 "MH1" H 10700 4520 60  0000 C CNN
F 1 "mounting_hole_plated" H 10700 4400 60  0001 C CNN
F 2 "mounting_hole_3.2_7.5_plated_vias" H 10700 4310 40  0001 C CNN
F 3 "" H 10700 4400 60  0000 C CNN
	1    10700 4400
	1    0    0    -1  
$EndComp
$EndSCHEMATC