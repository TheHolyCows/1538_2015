#include "CowRobot.h"
#include "CowBase.h"

// TODO: a lot of the older functions in this file are clunky.  clean them up.

//TODO: initializer list
/// Constructor for CowRobot
CowRobot::CowRobot()
{	
	m_DSUpdateCount = 0;
		
	m_Controller = NULL;
	// Set up drive motors
	m_RightDrive = new CANTalon(1);
	m_LeftDrive = new CANTalon(2);
	m_Roller = new Talon(0);

	//m_SolenoidA = new Solenoid(0);

	m_Gyro = new CowLib::CowGyro(ANALOG_GYRO);
	m_Gyro->SetSensitivity(GYRO_SENSITIVITY);
	m_Gyro->Reset();

	m_DriveEncoder = new Encoder(0, 1, true, Encoder::k1X);
	m_DriveEncoder->SetDistancePerPulse(0.03490658503); // 4*pi/360
	//m_DriveEncoder->Start();
	
	m_LeftDriveValue = 0;
	m_RightDriveValue = 0;
	
	m_PreviousGyroError = 0;
	m_PreviousDriveError = 0;
}

void CowRobot::Reset()
{
	m_DriveEncoder->Reset();
	m_PreviousGyroError = 0;
	m_PreviousDriveError = 0;

}

void CowRobot::SetController(GenericController* controller)
{
	m_Controller = controller;
}

void CowRobot::PrintToDS()
{
	if(m_DSUpdateCount % 10 == 0)
	{
		m_DSUpdateCount = 0;

//		CowLib::PrintToLCD("K:%s\nA:%s\nP:%f\nG:%f\nE:%f\nI:F%f_R%f",
//						   kinectArms,
//						   AutoModes::GetInstance()->GetName(),
//						   m_Winch->GetAverageVoltage(),
//						   m_Gyro->GetAngle(),
//						   m_DriveEncoder->GetDistance(),
//						   m_FrontIR->GetVoltage(), m_RearIR->GetVoltage());
	}
}

/// Used to handle the recurring logic funtions inside the robot.
/// Please call this once per update cycle.
void CowRobot::handle()
{	
	if(m_Controller == NULL)
	{
		printf("No controller for CowRobot!!\n");
		return;
	}
	//printf("Handling...\n");
	m_Controller->handle(this);
	
	// Default drive
	float tmpLeftMotor = m_LeftDriveValue;
	float tmpRightMotor = m_RightDriveValue;
	
	SetLeftMotors(tmpLeftMotor);
	SetRightMotors(tmpRightMotor);
	if(m_DSUpdateCount % 10 == 0)
	{
		printf("Gyro: %f, Encoder: %f\r\n",  m_Gyro->GetAngle(), m_DriveEncoder->GetDistance());
	}

	if(m_DSUpdateCount % 100 == 0)
	{
		//m_SolenoidA->Set(!m_SolenoidA->Get());
	}
	m_DSUpdateCount++;

}

double CowRobot::GetDriveDistance()
{
	return m_DriveEncoder->GetDistance();
}

bool CowRobot::DriveDistanceWithHeading(double heading, double distance)
{
	double PID_P = CONSTANT("DRIVE_P");
	double PID_D = CONSTANT("DRIVE_D");
	double error = distance - m_DriveEncoder->GetDistance();
	double dError = error - m_PreviousDriveError;
	double output = PID_P*error + PID_D*dError;
	
	bool headingResult = DriveWithHeading(heading, CowLib::LimitMix(output, CONSTANT("DRIVE_MAX_SPEED")));
	
	m_PreviousDriveError = error;
	
	return (fabs(error) < 4 && CowLib::UnitsPerSecond(fabs(dError)) < 1 && headingResult);
}

bool CowRobot::DriveWithHeading(double heading, double speed)
{
	speed *= -1;
	double PID_P = CONSTANT("TURN_P");
	double PID_D = CONSTANT("TURN_D");
	//double error = heading - m_Gyro->GetAngle();
	double error = 0;
	double dError = error - m_PreviousGyroError;
	double output = PID_P*error + PID_D*dError;
				
	DriveLeftRight(speed-output, speed+output);
	
	m_PreviousGyroError = error;
	
	return (fabs(error) < 1 && CowLib::UnitsPerSecond(fabs(dError)) < 0.5);
}

/// Allows skid steer robot to be driven using tank drive style inputs
/// @param leftDriveValue
/// @param rightDriveValue
///
void CowRobot::DriveLeftRight(float leftDriveValue, float rightDriveValue)
{
	m_LeftDriveValue = leftDriveValue;
	m_RightDriveValue = rightDriveValue;
}

void CowRobot::DriveSpeedTurn(float speed, float turn, bool quickTurn)
{
	//Linear degredation of steeering based off of velocity
	//	velocity *= 0.003;
	float temp_vel = speed;
	float sensitivity = 0;
	float unscaled_turn = 0;

	if (temp_vel < 0)
		temp_vel = -temp_vel;

	//printf("Velocity: %f, stick: %f\r\n", velocity, temp_vel);
	
	if(speed < 0.10 && speed > -0.10)
		speed = 0;
	if (turn < 0.10 && turn > -0.10 || (speed == 0 && !quickTurn))
		turn = 0;

	unscaled_turn = turn;

	if(quickTurn)
		sensitivity = 1;
	else
		sensitivity = 0.4;

	turn *= sensitivity;
	turn = -turn;
	

	float left_power = CowLib::LimitMix(speed + turn);
	float right_power = CowLib::LimitMix(speed - turn);

	DriveLeftRight(left_power, right_power);
}

/// Allows robot to spin in place
/// @param turnRate
///
void CowRobot::QuickTurn(float turnRate)
{
	//when provided with + turn, quick turn right

	float left = -1 * turnRate;
	float right = turnRate;

	DriveLeftRight(left, right);
}

/// Returns the value of the drive's left side encoder
//Encoder * CowRobot::GetEncoder()
//{
//	return m_Encoder;
//}
//
//Gyro * CowRobot::GetGyro()
//{
//	return m_Gyro;
//}

/// sets the left side motors
void CowRobot::SetLeftMotors(float val)
{
	if (val > 1.0)
		val = 1.0;
	if (val < -1.0)
		val = -1.0;

	m_LeftDrive->Set(-val);
}

/// sets the left side motors
void CowRobot::SetRightMotors(float val)
{
	if (val > 1.0)
		val = 1.0;
	if (val < -1.0)
		val = -1.0;

	m_RightDrive->Set(val);
}

void CowRobot::SetRollerSpeed(float val)
{
	m_Roller->Set(val);
}

void CowRobot::GyroHandleCalibration()
{
	m_Gyro->HandleCalibration();
}

void CowRobot::GyroFinalizeCalibration()
{
	m_Gyro->FinalizeCalibration();
}
