#!/bin/bash
#this file just modifies the current vars.xml to contain the initial values for the next test window
#this is to ensure that the model begins the test in the same way that the first line it recieves looks, so it doesnt jerk into place
cd $BUILDER_XML_PATH

sed -i "16s/\(<q type=\"double\">\)\([^<]*\)\(<[^>]*\)/\1"$LF_X_1_q" "$LF_Y_2_q" "$LF_Y_3_q"  "$RF_X_1_q" "$RF_Y_2_q" "$RF_Y_3_q"  "$LH_X_1_q" "$LH_Y_2_q" "$LH_Y_3_q"  "$RH_X_1_q" "$RH_Y_2_q" "$RH_Y_3_q"\3/" vars.xml
sed -i "17s/\(<qd type=\"double\">\)\([^<]*\)\(<[^>]*\)/\1"$LF_X_1_qd" "$LF_Y_2_qd" "$LF_Y_3_qd"  "$RF_X_1_qd" "$RF_Y_2_qd" "$RF_Y_3_qd"  "$LH_X_1_qd" "$LH_Y_2_qd" "$LH_Y_3_qd"  "$RH_X_1_qd" "$RH_Y_2_qd" "$RH_Y_3_qd"\3/" vars.xml
sed -i "11s/\(<xd type=\"double\">\)\([^<]*\)\(<[^>]*\)/\1"$BODYx" "$BODYy" "$BODYz"  "$BODYr" "$BODYp" "$BODYt"\3/" vars.xml


