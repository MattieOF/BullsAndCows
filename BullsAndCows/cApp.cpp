#include "cApp.h"

wxIMPLEMENT_APP(cApp); 

cApp::cApp()
{
	
}

cApp::~cApp()
{

}

bool cApp::OnInit()
{
	m_MainFrame = new cMain();
	m_MainFrame->Show();

	return true;
}
