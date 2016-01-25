#include "OI.h"
#include "Commands/DriveReverse.h"
#include "Commands/DriveForward.h"
#include "Commands/ToggleRotationCurve.h"
#include "NetworkTablesInterface.h"
#include "CommandBase.h"

OI::OI() :
 driveStick(new Joystick(DRIVESTICK)), operatorStick(new Joystick(OPERATORSTICK))
{
	Button* driveTrigger = new JoystickButton(driveStick, 1);
	//Vas and Itzel use WhenPressed() and WhenReleased() like below
	driveTrigger->WhenPressed(new DriveReverse());
	driveTrigger->WhenReleased(new DriveForward());
	Button* toggleRotationCurve = new JoystickButton(driveStick, 5);
	toggleRotationCurve->WhenPressed(new ToggleRotationCurve());
}

Joystick* OI::getDriveStick(){
	return driveStick;
}

Joystick* OI::getOperatorStick(){
	return operatorStick;
}

