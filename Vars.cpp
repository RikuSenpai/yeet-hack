#include "Vars.h"

// TODO: Remove this
void CVars::Load()
{
	bhop_active = false;
	nohands_active = false;
	esp_active = false;
	esp_name = false;
	esp_hp = false;
	namespam = false;

	asus = 1.f;
	nightmode = false;
	nosky = false;

	tab_visuals = true;
	tab_misc = false;

	esp_color[0] = 1.f;
	esp_color[1] = 0.f;
	esp_color[2] = 0.f;
}

CVars* Vars = new CVars;