#include "stepper.h"
#include "planner.h"
#include "Marlin.h"
#include "ManualFirmwareLeveling.h"
#include "gcode.h"

#ifdef ENABLE_AUTO_BED_LEVELING

struct s_manual_bed_values manual_bed_values = {0,0,0};

void g31_manual_firmware_leveling()
{
	float z_origin, z_right_front, z_left_back, z_offset;
	bool ok = true;
	if (code_seen('O')) {
		z_origin = code_value();
	} else {
		ok = false;
	}

	if (code_seen('R')) {
		z_right_front = code_value();
	} else {
		ok = false;
	}

	if (code_seen('B')) {
		z_left_back = code_value();
	} else {
		ok = false;
	}
	
	if (code_seen('Z')) {
		z_offset = code_value();
	} else {
		ok = false;
	}
	
	if (ok) {
		manual_bed_values.z_origin = z_origin;
		manual_bed_values.z_right_front = z_right_front;
		manual_bed_values.z_left_back = z_left_back;
		zprobe_zoffset = z_offset;
		set_bed_level_equation(-manual_bed_values.z_origin, -manual_bed_values.z_right_front, -manual_bed_values.z_left_back);
	} else {
		SERIAL_PROTOCOLLN("G31 needs O(rigin) R(ight) B(back) and Z(origin real offset) offsets");
	}
}

void g32_clear_manual_firmware_leveling()
{
	st_synchronize();
    manual_bed_values.z_origin = 0; 
    manual_bed_values.z_right_front = 0; 
    manual_bed_values.z_left_back = 0;
    zprobe_zoffset = 0;
	plan_bed_level_matrix.set_to_identity();
	SERIAL_PROTOCOLLN("Bed leveling matrix cleared");
}

void g33_position_extruder_to_measure_bed()
{
	plan_bed_level_matrix.set_to_identity();
	if (code_seen('O')) {
		do_blocking_move_to(LEFT_PROBE_BED_POSITION, FRONT_PROBE_BED_POSITION, current_position[Z_AXIS]);
	} else if (code_seen('R')) {
		do_blocking_move_to(RIGHT_PROBE_BED_POSITION, FRONT_PROBE_BED_POSITION, current_position[Z_AXIS]);
	} else if (code_seen('B')) {
		do_blocking_move_to(LEFT_PROBE_BED_POSITION, BACK_PROBE_BED_POSITION, current_position[Z_AXIS]);
	} else {
		SERIAL_PROTOCOLLN("G33 needs O(rigin) R(ight) or B(back)");
	}
	st_synchronize();
}


#endif /* ENABLE_AUTO_BED_LEVELING */
/* vim: set ts=4 sw=4 autoindent nocindent:  */
