#include "EcaApp.h"

wxIMPLEMENT_APP(EcaApp);

bool EcaApp::OnInit() {
	mainFrame = new EcaMenu();
	mainFrame->SetAutoLayout(true);
	mainFrame->Show();

	return true;
}
