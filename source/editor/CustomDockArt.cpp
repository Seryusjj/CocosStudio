#include "stdafx.h"

#include "CustomDockArt.h"





int ParseColor(std::string color) {
	//the compisition is not RGB is BGR
	//blue 16711680 (11111111,00000000,00000000) (FF,00,00)
	//green 65280 (00000000,11111111,00000000) (00,FF,00)
	//red 255 (00000000,00000000,11111111) (00,00,FF)
	return 65280;
}

CustomDockArt::CustomDockArt():wxAuiDefaultDockArt()
{
	wxColourDatabase colorDatabase;
	colorDatabase.Find("DARK GREY");
	//auto color = wxColor(ParseColor("#0000FF"));
	//m_baseColour = colorDatabase.Find("DARK GREY");

	m_activeCaptionColour = colorDatabase.Find("GREY");//wxSystemSettings::GetColour(wxSYS_COLOUR_ACTIVECAPTION);
	m_activeCaptionGradientColour = colorDatabase.Find("GREY");//wxSystemSettings::GetColour(wxSYS_COLOUR_GRADIENTACTIVECAPTION);

	m_inactiveCaptionColour = colorDatabase.Find("DARK GREY");//wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTION);
	m_inactiveCaptionGradientColour = colorDatabase.Find("DARK GREY");//wxSystemSettings::GetColour(wxSYS_COLOUR_GRADIENTINACTIVECAPTION);


	m_activeCaptionTextColour = colorDatabase.Find("DARK GREY");//wxSystemSettings::GetColour(wxSYS_COLOUR_CAPTIONTEXT);	
	m_inactiveCaptionTextColour = colorDatabase.Find("GREY");//wxSystemSettings::GetColour(wxSYS_COLOUR_INACTIVECAPTIONTEXT);
}

CustomDockArt::~CustomDockArt()
{
}
