#include "cHelp.h"

cHelp::cHelp()
	: wxFrame(nullptr, wxID_ANY, "How to Play", wxPoint(10, 10), wxSize(300, 400),
		wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	mainSizer->AddSpacer(5);
	mainSizer->Add(new wxStaticText(this, wxID_ANY, "How to Play", wxDefaultPosition, wxDefaultSize),
		0, wxLEFT, 10);

	mainSizer->AddSpacer(5);
	mainSizer->Add(new wxStaticText(this, wxID_ANY, "In number mode, you guess a 4 digit number with no duplicate digits.", wxDefaultPosition, wxDefaultSize),
		0, wxLEFT, 10);
	mainSizer->Add(new wxStaticText(this, wxID_ANY, "In word mode, you guess a 4 letter word. It can have duplicate characters.       ", wxDefaultPosition, wxDefaultSize),
		0, wxLEFT, 10);

	mainSizer->AddSpacer(10);

	mainSizer->Add(new wxStaticText(this, wxID_ANY, "A bull is a character/digit in the correct place.", wxDefaultPosition, wxDefaultSize),
		0, wxLEFT, 10);
	mainSizer->Add(new wxStaticText(this, wxID_ANY, "A cow is a character/digit in the number/word, but in the wrong place.      ", wxDefaultPosition, wxDefaultSize),
		0, wxLEFT, 10);

	mainSizer->AddSpacer(10);

	wxButton* okButton = new wxButton(this, wxID_ANY, "OK");
	okButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cHelp::OnOkButtonClicked, this);
	mainSizer->Add(okButton, 0, wxALL, 10);

	mainSizer->AddSpacer(5);

	SetSizerAndFit(mainSizer);
	SetAutoLayout(true);
	Layout();
	SetBackgroundColour(wxColour("lightgrey"));
	CenterOnScreen();
}

void cHelp::OnOkButtonClicked(wxCommandEvent& evt)
{
	Close();
	evt.Skip();
}
