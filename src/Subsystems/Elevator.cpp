#include "Elevator.h"
#include "Hook.h"
#include "../RobotMap.h"
#include "Commands/MoveElevator.h"

Elevator::Elevator() :
		Subsystem("Elevator"), s1Screw(new Jaguar(SCREW_1)), s2Screw(new Jaguar(SCREW_2)),
		s1Encoder(new Encoder(SCREW_1_ENCODER_1, SCREW_1_ENCODER_2)),
		s2Encoder(new Encoder(SCREW_2_ENCODER_1, SCREW_2_ENCODER_2)), clawControl(false)
{
	s1Encoder->SetDistancePerPulse(1.0);
	s2Encoder->SetDistancePerPulse(1.0);
}

double Elevator::getS2Distance(){
	return s2Encoder->GetDistance() / 28534.0;
}

void Elevator::resetS2Distance()
{
	s2Encoder->Reset();
}

void Elevator::clawOn()
{
	clawControl = true;
}

void Elevator::clawOff()
{
	clawControl = false;
}

void Elevator::bothOn()
{
	both = true;
}

void Elevator::bothOff()
{
	both = false;
}

void Elevator::moveElevator(float speed){
	//printf("Claw: %f; Hooks: %f\n", s1Encoder->GetDistance(), s2Encoder->GetDistance());
	if(!CommandBase::hook->isActive()){
		/*CLAW+HOOKS ENABLED: */if(clawControl)
			s1Screw->Set(speed);
		else if(both){
			s1Screw->Set(speed);
			s2Screw->Set(speed);
		}
		else
			s2Screw->Set(speed);
		/* HOOKS ONLY ENABLED: s2Screw->Set(speed);*/
	}
}

void Elevator::hardStop(){
	s1Screw->Set(0);
	s2Screw->Set(0);
}

void Elevator::InitDefaultCommand()
{
	SetDefaultCommand(new MoveElevator());
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

