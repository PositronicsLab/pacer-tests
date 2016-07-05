#!/bin/bash
var1=0
var2=0
var3=0
var4=0
var5=0
var6=0
var7=0
var8=0
var9=0
var10=0
var11=0
var12=0
var13=0
var14=0
var15=0
zenity --question --title "Bot Builder" --text "Click next to select the base model file, or cancel to exit" --ok-label="Next" --cancel-label="Cancel"
case $? in
         0)
              FILE=`zenity --file-selection --title "Bot Builder" --file-filter=""*.xml" "*.sdf""`
		
		case $? in
        	0)
                	mv $FILE model-1.xml
		
			zenity --forms --title="Bot Builder" --text="Set Test Values:" \
   			--add-entry="Maximum Velocity" \
   			--add-entry="Test Time Interval" 
			
			case $? in
			0)
				stuff=$(zenity --list \
 				 --title="Choose the Bugs You Wish to View" \
				 --text="unit sizes:\nLeg Lengths: 0.01 m\nDensity: 10 kg/m^3 " --editable --print-column=2,4 \
 				 --column="Change this parameter?" --column="Parameter" --column="Jacobian" --column="amount to increase/decrease(unit size)" --column="Limits Activated" \
   				 0 Density $var1 $var2 $var3\
    				 0 LF $var4 $var5 $var6\
    				0 RF $var7 $var8 $var9\
				0 LH $var10 $var11 $var12\
    				0 RH $var13 $var14 $var15)
				
				zenity --info --title="My Title" --text="Your input was: $stuff"
				;;
			1)
				exit;;
		       -1)
				exit;;
			
		       esac;;
                       
         	1)
                	exit;;
               -1)
                	exit;;
		esac;;
		
         1)
                exit;;
	-1)
		exit;;  
esac      
