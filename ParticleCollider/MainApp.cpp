#include "MainApp.h"

#include <wx/progdlg.h>

wxIMPLEMENT_APP(MainApp);

MainApp::MainApp() {
}


bool MainApp::OnInit() {
	m = new SimulatorMenu();
	m->Show();

	return true;
}