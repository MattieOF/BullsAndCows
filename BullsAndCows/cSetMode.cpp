#include "cSetMode.h"
#include <wx/statline.h>

cSetMode::cSetMode(cMain* main)
	: wxFrame(nullptr, wxID_ANY, "Set Mode", wxPoint(10, 10), wxSize(300, 400),
		wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN)
{
	m_Main = main;

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	mainSizer->AddSpacer(5);
	mainSizer->Add(new wxStaticText(this, wxID_ANY, "Set Mode", wxDefaultPosition, wxDefaultSize),
		0, wxLEFT, 10);

	wxArrayString items;
	items.Add("Number");
	items.Add("Word");
	m_ModeComboBox = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(200, 30), items);

	mainSizer->Add(m_ModeComboBox, 0, wxALL, 10);
	mainSizer->Add(new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxSize(200, 1), wxLI_HORIZONTAL), 
		0, wxLEFT, 10);

	mainSizer->AddSpacer(5);
	m_SetButton = new wxButton(this, wxID_ANY, "Set Mode", wxDefaultPosition, wxSize(80, 25));
	m_SetButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cSetMode::OnSetModeButtonClicked, this);
	mainSizer->AddSpacer(5);
	mainSizer->Add(m_SetButton, wxSizerFlags(0).Align(wxALIGN_RIGHT).Border(wxRIGHT, 10));
	mainSizer->AddSpacer(5);

	// Final setup for frame
	SetSizerAndFit(mainSizer);
	SetAutoLayout(true);
	Layout();
	SetBackgroundColour(wxColour("lightgrey"));
	CenterOnScreen();
}

cSetMode::~cSetMode()
{
}

void cSetMode::OnSetModeButtonClicked(wxCommandEvent& evt)
{
	if (m_ModeComboBox->GetSelection() == wxNOT_FOUND)
	{
		wxMessageBox("You must select a mode!", "Error setting mode", wxICON_ERROR | wxOK);
		evt.Skip();
		return;
	}

	m_Main->SetGameMode(GetGameModeFromIndex(m_ModeComboBox->GetSelection()));
	evt.Skip();
	Close();
}

GameMode cSetMode::GetGameModeFromIndex(int index)
{
	switch (index)
	{
	case 0:
		return GameMode::GAMEMODE_NUMBER;
	case 1:
		return GameMode::GAMEMODE_WORD;
	default:
		return GameMode::GAMEMODE_NUMBER;
	}
}
