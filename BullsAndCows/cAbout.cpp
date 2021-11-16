#include "cAbout.h"

cAbout::cAbout()
	: wxFrame(nullptr, wxID_ANY, "About", wxPoint(10, 10), wxSize(300, 400),
		wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	mainSizer->AddSpacer(5);
	mainSizer->Add(new wxStaticText(this, wxID_ANY, "Bulls and Cows", wxDefaultPosition, wxDefaultSize),
		0, wxLEFT, 10);

	mainSizer->AddSpacer(5);
	mainSizer->Add(new wxStaticText(this, wxID_ANY, "Version 1.0", wxDefaultPosition, wxDefaultSize),
		0, wxLEFT, 10);

	mainSizer->AddSpacer(5);
	mainSizer->Add(new wxStaticText(this, wxID_ANY, "Copyright 2021", wxDefaultPosition, wxDefaultSize),
		0, wxLEFT, 10);

	mainSizer->AddSpacer(5);
	mainSizer->Add(new wxStaticText(this, wxID_ANY, "Matt Ware", wxDefaultPosition, wxDefaultSize),
		0, wxLEFT, 10);

	mainSizer->AddSpacer(5);
	mainSizer->Add(new wxStaticText(this, wxID_ANY, "The classic code-breaking puzzle implemented in C++ with wxWidgets.      ", wxDefaultPosition, wxDefaultSize),
		0, wxLEFT, 10);

	wxButton* okButton = new wxButton(this, wxID_ANY, "OK");
	okButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cAbout::OnOkButtonClicked, this);
	mainSizer->Add(okButton, 0, wxALL, 10);

	mainSizer->AddSpacer(5);

	SetSizerAndFit(mainSizer);
	SetAutoLayout(true);
	Layout();
	SetBackgroundColour(wxColour("lightgrey"));
	CenterOnScreen();
}

cAbout::~cAbout()
{
}

void cAbout::OnOkButtonClicked(wxCommandEvent& evt)
{
	Close();
	evt.Skip();
}
