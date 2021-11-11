#pragma once

#include <wx/wx.h>
#include "cMain.h"

class cSetMode : public wxFrame
{
public:
	cSetMode(cMain* main);
	~cSetMode();

private:
	cMain* m_Main;
};
