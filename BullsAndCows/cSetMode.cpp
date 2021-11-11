#include "cSetMode.h"

cSetMode::cSetMode(cMain* main)
	: wxFrame(nullptr, wxID_ANY, "Set Mode", wxPoint(10, 10), wxSize(300, 400),
		wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
	m_Main = main;

	// Final setup for frame
	SetAutoLayout(true);
	Layout();
	SetBackgroundColour(wxColour("lightgrey"));
	CenterOnScreen();
}

cSetMode::~cSetMode()
{
}
