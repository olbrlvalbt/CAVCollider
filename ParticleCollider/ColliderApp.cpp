#include "ColliderApp.h"


#include "ColliderConfiguration.h"
#include "ColliderFrame.h"
#include "CollisionSystem.h"
#include "FilteredCollisionSystem.h"

wxIMPLEMENT_APP(ColliderApp);


ColliderApp::ColliderApp() {
}

bool ColliderApp::OnInit() {
	m = new ColliderMenu();
	//m->SetAutoLayout(true);
	m->Show();

	return true;
}