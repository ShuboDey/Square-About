// Games Concept Assignment-1.cpp: A program using the TL-Engine

#include <TL-Engine.h>	// TL-Engine include file and namespace
using namespace tle;
// Declaring Constant floats 
const float kCameraX = 0.0f;
const float kCameraY = 200.0f; 
const float kCameraZ = -170.0f;
const float kRotationX = 45.0f;
const float kPlatformInitialX = 0.0f;
const float kPlatformInitialY = -5.0f;
const float kPlatformInitialZ = 0.0f;
const float kSphereInitialX = -85.0f;
const float kSphereInitialY = 10.0f;
const float kSphereInitialZ = -85.0f;
const float kSphere2InitialX = 85.0f;
const float kSphere2InitialY = 10.0f;
const float kSphere2InitialZ = 85.0f;
const float kSphere3InitialX = -85.0f;
const float kSphere3InitialY = 10.0f;
const float kSphere3InitialZ = 85.0f;
const float kSphere4InitialX = 85.0f;
const float kSphere4InitialY = 10.0f;
const float kSphere4InitialZ = -85.0f;
const float kCubeInitialX = 0.0f;
const float kCubeInitialY = 5.0f;
const float kCubeInitialZ = 0.0f;
const float kBulletInitialX = 0.0f;
const float kBulletInitialY = 5.0f;
const float kBulletInitialZ = 0.0f;
const float kMaxCoordinate = 85.0f;
const int kSpeedUpdater = -1.0f;
const EKeyCode kReverseMovement = EKeyCode::Key_R;
const EKeyCode kPause = EKeyCode::Key_P;
const EKeyCode kQuitProgram = EKeyCode::Key_Escape;

void main()
{
	// Create a 3D engine (using TLX engine here) and open a window for it
	I3DEngine* myEngine = New3DEngine(kTLX);
	myEngine->StartWindowed();

	// Add default folder for meshes and other media
	myEngine->AddMediaFolder("C:\\ProgramData\\TL-Engine\\Media");

	/**** Set up your scene here ****/
	// Camera Set Up
	ICamera* mycamera = myEngine->CreateCamera(kManual, kCameraX, kCameraY, kCameraZ);
	mycamera->RotateLocalX(kRotationX);

	//Creating Models
	IMesh* platformmesh = myEngine->LoadMesh("Platform.x");
	IModel* platformmodel = platformmesh->CreateModel(kPlatformInitialX, kPlatformInitialY, kPlatformInitialZ);

	IMesh* Spheremesh = myEngine->LoadMesh("Sphere.x");
	IModel* Spheremodel = Spheremesh->CreateModel(kSphereInitialX, kSphereInitialY, kSphereInitialZ);
	Spheremodel->SetSkin("Sun.jpg");

	IMesh* Spheremesh2 = myEngine->LoadMesh("Sphere.x");
	IModel* Spheremodel2 = Spheremesh2->CreateModel(kSphere2InitialX, kSphere2InitialY, kSphere2InitialZ);
	Spheremodel2->SetSkin("Sun.jpg");

	IMesh* Spheremesh3 = myEngine->LoadMesh("Sphere.x");
	IModel* Spheremodel3 = Spheremesh3->CreateModel(kSphere3InitialX, kSphere3InitialY, kSphere3InitialZ);
	Spheremodel3->SetSkin("Super.jpg");

	IMesh* Spheremesh4 = myEngine->LoadMesh("Sphere.x");
	IModel* Spheremodel4 = Spheremesh4->CreateModel(kSphere4InitialX, kSphere4InitialY, kSphere4InitialZ);
	Spheremodel4->SetSkin("Super.jpg");

	IMesh* cubemesh = myEngine->LoadMesh("Cube.x");
	IModel* cubemodel = cubemesh->CreateModel(kCubeInitialX, kCubeInitialY, kCubeInitialZ);
	cubemodel->SetSkin("Cube.jpg");

	IMesh* Bulletmesh = myEngine->LoadMesh("Bullet.x");
	IModel* Bulletmodel = Bulletmesh->CreateModel(kBulletInitialX, kBulletInitialY, kBulletInitialZ);
	Bulletmodel->SetSkin("bullet.jpg");

	// Creating Font
	IFont* myfont = myEngine->LoadFont("Comic sans MS", 30);

	//Declaring Float Variable.
	float XCoordinate;
	float ZCoordinate;
	float sphereMovementSpeed = 0.05f;
	float sphereRotationSpeed = 0.05f;
	float sphereincreasedSpeed = 0.055f;
	float spheredecreasedSpeed = 0.045f;
	float bulletMovementSpeed = 0.25f;
	bool isPaused = false;
	bool bulletfired = false;
	float vectorX = Bulletmodel->GetX() - cubemodel->GetX();
	float vectorZ = Bulletmodel->GetZ() - cubemodel->GetZ();
	float squaredVectorX = vectorX * vectorX;
	float squaredVectorZ = vectorZ * vectorZ;
	float distance = sqrt(squaredVectorX + squaredVectorZ);
	bool clockwise = true;
	int score = 0;
	int points = 10;

	// The main game loop, repeat until engine is stopped
	while (myEngine->IsRunning())
	{
		// Draw the scene
		myEngine->DrawScene();

		/**** Update your scene each frame here ****/
		// Quit game 
		if (myEngine->KeyHit(kQuitProgram)) {
			myEngine->Stop();
		}
		// Pause game
		if (myEngine->KeyHit(kPause)) {
			isPaused = !isPaused;
		}
		else if (isPaused == true)
		{
			myfont->Draw("Paused, Press P to resume", myEngine->GetWidth() / 2, myEngine->GetHeight() / 2, kBlack, kCentre);
		}
		//Firing Bullet
		if (myEngine->KeyHit(Key_Up) && !bulletfired) {
			bulletfired = !bulletfired;
		}
		else if (bulletfired == true) {
			Bulletmodel->MoveZ(bulletMovementSpeed);
		}
		// Calculation of the distance between bullet and the cube
		if (distance >= 200.0f) {
			bulletfired = false;
			Bulletmodel->SetPosition(kBulletInitialX, kBulletInitialY, kBulletInitialZ);
		}
		// Calculation of the distance between bullet and spheremodel
		vectorX = Bulletmodel->GetX() - Spheremodel->GetX();
		vectorZ = Bulletmodel->GetZ() - Spheremodel->GetZ();
		squaredVectorX = vectorX * vectorX;
		squaredVectorZ = vectorZ * vectorZ;
		distance = sqrt(squaredVectorX + squaredVectorZ);
		if (distance < 10) {
			bulletfired = false;
			Spheremodel->SetPosition(1000, -1000, -1000);
			Bulletmodel->SetPosition(kBulletInitialX, kBulletInitialY, kBulletInitialZ);
			score = score + points;
		}
		// Calculation of the distance between bullet and spheremode2
		vectorX = Bulletmodel->GetX() - Spheremodel2->GetX();
		vectorZ = Bulletmodel->GetZ() - Spheremodel2->GetZ();
		squaredVectorX = vectorX * vectorX;
		squaredVectorZ = vectorZ * vectorZ;
		distance = sqrt(squaredVectorX + squaredVectorZ);
		if (distance < 10) {
			bulletfired = false;
			Spheremodel2->SetPosition(1000, -1000, -1000);
			Bulletmodel->SetPosition(kBulletInitialX, kBulletInitialY, kBulletInitialZ);
			score = score + points;
		}
		// Calculation of the distance between bullet and spheremodel3
		vectorX = Bulletmodel->GetX() - Spheremodel3->GetX();
		vectorZ = Bulletmodel->GetZ() - Spheremodel3->GetZ();
		squaredVectorX = vectorX * vectorX;
		squaredVectorZ = vectorZ * vectorZ;
		distance = sqrt(squaredVectorX + squaredVectorZ);
		if (distance < 10) {
			bulletfired = false;
			Spheremodel3->SetPosition(1000, -1000, -1000);
			Bulletmodel->SetPosition(kBulletInitialX, kBulletInitialY, kBulletInitialZ);
			score = score + points;
		}
		// Calculation of the distance between bullet and spheremodel4
		vectorX = Bulletmodel->GetX() - Spheremodel4->GetX();
		vectorZ = Bulletmodel->GetZ() - Spheremodel4->GetZ();
		squaredVectorX = vectorX * vectorX;
		squaredVectorZ = vectorZ * vectorZ;
		distance = sqrt(squaredVectorX + squaredVectorZ);
		if (distance < 10) {
			bulletfired = false;
			Spheremodel4->SetPosition(1000, -1000, -1000);
			Bulletmodel->SetPosition(kBulletInitialX, kBulletInitialY, kBulletInitialZ);
			score = score + points;
		}
		// Reverse Movement of the spheres
		if (myEngine->KeyHit(kReverseMovement)) {
			clockwise = !clockwise;
			sphereMovementSpeed = sphereMovementSpeed * kSpeedUpdater;
			sphereRotationSpeed = sphereRotationSpeed * kSpeedUpdater;
		}
		// Increasing and Decreasing speeds of the spheres
		if (myEngine->KeyHit(Key_D) && sphereMovementSpeed <= 0.1) {
			sphereMovementSpeed += sphereincreasedSpeed;
			sphereRotationSpeed += sphereincreasedSpeed;
		}
		if (myEngine->KeyHit(Key_A) && sphereMovementSpeed >= 0.025) {
			sphereMovementSpeed -= spheredecreasedSpeed;
			sphereRotationSpeed -= spheredecreasedSpeed;
		}
		if (isPaused == false) {
			
			//Sphere Movements and Rotation
			ZCoordinate = Spheremodel->GetZ();
			XCoordinate = Spheremodel->GetX();
			if (XCoordinate <= -kMaxCoordinate && ZCoordinate < kMaxCoordinate) {
				Spheremodel->MoveZ(sphereMovementSpeed);
				Spheremodel->RotateX(sphereRotationSpeed);
			}
			else if (XCoordinate < kMaxCoordinate && ZCoordinate >= kMaxCoordinate) {
				Spheremodel->MoveX(sphereMovementSpeed);
				Spheremodel->RotateZ(-sphereRotationSpeed);
			}
			else if (XCoordinate >= kMaxCoordinate && ZCoordinate > -kMaxCoordinate) {
				Spheremodel->MoveZ(-sphereMovementSpeed);
				Spheremodel->RotateX(-sphereRotationSpeed);
			}
			else if (XCoordinate > -kMaxCoordinate && ZCoordinate <= -kMaxCoordinate) {
				Spheremodel->MoveX(-sphereMovementSpeed);
				Spheremodel->RotateZ(sphereRotationSpeed);
			}
			XCoordinate = Spheremodel2->GetX();
			ZCoordinate = Spheremodel2->GetZ();
			if (XCoordinate >= kMaxCoordinate && ZCoordinate > -kMaxCoordinate) {
				Spheremodel2->MoveZ(-sphereMovementSpeed);
				Spheremodel2->RotateX(-sphereRotationSpeed);
			}
			else if (XCoordinate > -kMaxCoordinate && ZCoordinate <= -kMaxCoordinate) {
				Spheremodel2->MoveX(-sphereMovementSpeed);
				Spheremodel2->RotateZ(sphereRotationSpeed);
			}
			else if (XCoordinate <= -kMaxCoordinate && ZCoordinate < kMaxCoordinate) {
				Spheremodel2->MoveZ(sphereMovementSpeed);
				Spheremodel2->RotateX(sphereRotationSpeed);
			}
			else if (XCoordinate < kMaxCoordinate && ZCoordinate >= kMaxCoordinate) {
				Spheremodel2->MoveX(sphereMovementSpeed);
				Spheremodel2->RotateZ(-sphereRotationSpeed);
			}
			XCoordinate = Spheremodel3->GetX();
			ZCoordinate = Spheremodel3->GetZ();

			if (XCoordinate < kMaxCoordinate && ZCoordinate >= kMaxCoordinate) {
				Spheremodel3->MoveX(sphereMovementSpeed);
				Spheremodel3->RotateZ(-sphereRotationSpeed);
			}
			else if (XCoordinate >= kMaxCoordinate && ZCoordinate > -kMaxCoordinate) {
				Spheremodel3->MoveZ(-sphereMovementSpeed);
				Spheremodel3->RotateX(-sphereRotationSpeed);
			}
			else if (XCoordinate > -kMaxCoordinate && ZCoordinate <= -kMaxCoordinate) {
				Spheremodel3->MoveX(-sphereMovementSpeed);
				Spheremodel3->RotateZ(sphereRotationSpeed);
			}
			else if (XCoordinate <= -kMaxCoordinate && ZCoordinate < kMaxCoordinate) {
				Spheremodel3->MoveZ(sphereMovementSpeed);
				Spheremodel3->RotateX(sphereRotationSpeed);
			}
			XCoordinate = Spheremodel4->GetX();
			ZCoordinate = Spheremodel4->GetZ();

			if (XCoordinate > -kMaxCoordinate && ZCoordinate <= -kMaxCoordinate) {
				Spheremodel4->MoveX(-sphereMovementSpeed);
				Spheremodel4->RotateZ(sphereRotationSpeed);
			}
			else if (XCoordinate <= -kMaxCoordinate && ZCoordinate < kMaxCoordinate) {
				Spheremodel4->MoveZ(sphereMovementSpeed);
				Spheremodel4->RotateX(sphereRotationSpeed);
			}
			else if (XCoordinate < kMaxCoordinate && ZCoordinate >= kMaxCoordinate) {
				Spheremodel4->MoveX(sphereMovementSpeed);
				Spheremodel4->RotateZ(-sphereRotationSpeed);
			}
			else if (XCoordinate >= kMaxCoordinate && ZCoordinate > -kMaxCoordinate) {
				Spheremodel4->MoveZ(-sphereMovementSpeed);
				Spheremodel4->RotateX(-sphereRotationSpeed);
			}
			// Displaying text in the game 
			myfont->Draw("CurrentSpeed: " + to_string(sphereMovementSpeed) , 920.0, 10.0, kBlue);
			myfont->Draw("Score: "+ to_string(score), 520.0, 10.0, kBlue);
			myfont->Draw("BulletsLeft: ", 20.0, 10.0, kBlue);
		}
	}
	// Delete the 3D engine now we are finished with it
	myEngine->Delete();
}