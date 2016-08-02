#!/bin/bash
mkdir $1
$PACER_SCRIPT_PATH/clean-data.sh "desired_robot_q "  out-*.log $1/qdes.mat
$PACER_SCRIPT_PATH/clean-data.sh " robot_q "  out-*.log $1/q.mat
$PACER_SCRIPT_PATH/clean-data.sh " generalized_qd "  out-*.log $1/qd.mat
$PACER_SCRIPT_PATH/clean-data.sh "desired_robot_qd "  out-*.log $1/qddes.mat

$PACER_SCRIPT_PATH/clean-data.sh "finger_force_moby_FINGER0"  out-*.log $1/m0.mat
$PACER_SCRIPT_PATH/clean-data.sh "finger_force_moby_FINGER1"  out-*.log $1/m1.mat
$PACER_SCRIPT_PATH/clean-data.sh "finger_force_moby_FINGER2"  out-*.log $1/m2.mat
$PACER_SCRIPT_PATH/clean-data.sh "finger_force_moby_FINGER3"  out-*.log $1/m3.mat

$PACER_SCRIPT_PATH/clean-data.sh "finger_force_idyn_FINGER0"  out-*.log $1/i0.mat
$PACER_SCRIPT_PATH/clean-data.sh "finger_force_idyn_FINGER1"  out-*.log $1/i1.mat
$PACER_SCRIPT_PATH/clean-data.sh "finger_force_idyn_FINGER2"  out-*.log $1/i2.mat
$PACER_SCRIPT_PATH/clean-data.sh "finger_force_idyn_FINGER3"  out-*.log $1/i3.mat

$PACER_SCRIPT_PATH/clean-data.sh "final_control_force"  out-*.log $1/u.mat
$PACER_SCRIPT_PATH/clean-data.sh " feedback_force "  out-*.log $1/ufb.mat
$PACER_SCRIPT_PATH/clean-data.sh " idyn_force "  out-*.log $1/uff.mat
$PACER_SCRIPT_PATH/clean-data.sh " alpha "  out-*.log $1/a.mat
