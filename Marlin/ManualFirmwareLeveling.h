#ifndef MANUALFIRMWARELEVELING_H
#define MANUALFIRMWARELEVELING_H

struct s_manual_bed_values {
	float z_origin, z_right_front, z_left_back;
};

extern struct s_manual_bed_values manual_bed_values;

void g31_manual_firmware_leveling();
void g32_clear_manual_firmware_leveling();
void g33_position_extruder_to_measure_bed();
void set_bed_level_equation(float z_at_xLeft_yFront, float z_at_xRight_yFront, float z_at_xLeft_yBack);

#endif
