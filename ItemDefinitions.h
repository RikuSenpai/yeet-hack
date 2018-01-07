#pragma once

#include <unordered_map>

struct Item_t {
	Item_t(const char* model) {
		this->model = model;
	}

	const char* model = nullptr;
};

const std::unordered_map<size_t, Item_t> ItemDefinitionIndex = {
	{ 1,{ "models/weapons/v_pist_deagle.mdl" } },
	{ 2,{ "models/weapons/v_pist_elite.mdl" } },
	{ 3,{ "models/weapons/v_pist_fiveseven.mdl" } },
	{ 4,{ "models/weapons/v_pist_glock18.mdl" } },
	{ 7,{ "models/weapons/v_rif_ak47.mdl" } },
	{ 8,{ "models/weapons/v_rif_aug.mdl" } },
	{ 9,{ "models/weapons/v_snip_awp.mdl" } },
	{ 10,{ "models/weapons/v_rif_famas.mdl" } },
	{ 11,{ "models/weapons/v_snip_g3sg1.mdl" } },
	{ 13,{ "models/weapons/v_rif_galilar.mdl" } },
	{ 14,{ "models/weapons/v_mach_m249para.mdl" } },
	{ 16,{ "models/weapons/v_rif_m4a1.mdl" } },
	{ 17,{ "models/weapons/v_smg_mac10.mdl" } },
	{ 19,{ "models/weapons/v_smg_p90.mdl" } },
	{ 24,{ "models/weapons/v_smg_ump45.mdl" } },
	{ 25,{ "models/weapons/v_shot_xm1014.mdl" } },
	{ 26,{ "models/weapons/v_smg_bizon.mdl" } },
	{ 27,{ "models/weapons/v_shot_mag7.mdl" } },
	{ 28,{ "models/weapons/v_mach_negev.mdl" } },
	{ 29,{ "models/weapons/v_shot_sawedoff.mdl" } },
	{ 30,{ "models/weapons/v_pist_tec9.mdl" } },
	{ 31,{ "models/weapons/v_eq_taser.mdl" } },
	{ 32,{ "models/weapons/v_pist_hkp2000.mdl" } },
	{ 33,{ "models/weapons/v_smg_mp7.mdl" } },
	{ 34,{ "models/weapons/v_smg_mp9.mdl" } },
	{ 35,{ "models/weapons/v_shot_nova.mdl" } },
	{ 36,{ "models/weapons/v_pist_p250.mdl" } },
	{ 38,{ "models/weapons/v_snip_scar20.mdl" } },
	{ 39,{ "models/weapons/v_rif_sg556.mdl" } },
	{ 40,{ "models/weapons/v_snip_ssg08.mdl" } },
	{ 42,{ "models/weapons/v_knife_default_ct.mdl" } },
	{ 43,{ "models/weapons/v_eq_flashbang.mdl" } },
	{ 44,{ "models/weapons/v_eq_fraggrenade.mdl" } },
	{ 45,{ "models/weapons/v_eq_smokegrenade.mdl" } },
	{ 46,{ "models/weapons/v_eq_molotov.mdl" } },
	{ 47,{ "models/weapons/v_eq_decoy.mdl" } },
	{ 48,{ "models/weapons/v_eq_incendiarygrenade.mdl" } },
	{ 49,{ "models/weapons/v_ied.mdl" } },
	{ 59,{ "models/weapons/v_knife_default_t.mdl" } },
	{ 60,{ "models/weapons/v_rif_m4a1_s.mdl" } },
	{ 61,{ "models/weapons/v_pist_223.mdl" } },
	{ 63,{ "models/weapons/v_pist_cz_75.mdl" } },
	{ 64,{ "models/weapons/v_pist_revolver.mdl" } },
	{ 500,{ "models/weapons/v_knife_bayonet.mdl" } },
	{ 505,{ "models/weapons/v_knife_flip.mdl" } },
	{ 506,{ "models/weapons/v_knife_gut.mdl" } },
	{ 507,{ "models/weapons/v_knife_karam.mdl" } },
	{ 508,{ "models/weapons/v_knife_m9_bay.mdl" } },
	{ 509,{ "models/weapons/v_knife_tactical.mdl" } },
	{ 512,{ "models/weapons/v_knife_falchion_advanced.mdl" } },
	{ 514,{ "models/weapons/v_knife_survival_bowie.mdl" } },
	{ 515,{ "models/weapons/v_knife_butterfly.mdl" } },
	{ 516,{ "models/weapons/v_knife_push.mdl" } }
};