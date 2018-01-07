#pragma once

namespace CChams
{
	void __fastcall Render(void* thisptr, int edx, IMatRenderContext* matctx, DrawModelState_t& state, ModelRenderInfo_t& pInfo, matrix3x4* pCustomBoneToWorld)
	{
		static HColor handsColor = HColor();

		if (pInfo.pModel)
		{
			std::string szModelName = Interface.ModelInfo->GetModelName(pInfo.pModel);

			if (Options::Visuals::Chams::Enabled && szModelName.find("player") != std::string::npos)
			{
				CPlayer* pBaseEntity = Interface.EntityList->GetClientEntity<CPlayer>(pInfo.entity_index);
				if (pBaseEntity)
				{

					CPlayer* pLocalEntity = Interface.EntityList->GetClientEntity<CPlayer>(Interface.Engine->GetLocalPlayer());
					bool valid = true;
					if (Options::Visuals::Chams::EnemyOnly &&
						pLocalEntity->GetTeam() == pBaseEntity->GetTeam())
						valid = false;

					if (valid)
						valid = pBaseEntity->IsValid();


					if (valid)
					{
						static RColor copyrightColor = RColor();

						if (Options::Visuals::Chams::Stylez == 0 ||
							Options::Visuals::Chams::Stylez == 1)
						{
							if (!Options::Visuals::Chams::VisibleOnly)
							{
								U::ForceMaterial(Options::Visuals::Chams::Stylez == 1 ? G::ignoreFlatMaterial : G::ignoreNormalMaterial, Options::Visuals::Chams::coloriz);
								O::DrawModelExecute(thisptr, matctx, state, pInfo, pCustomBoneToWorld);
							}
							U::ForceMaterial(Options::Visuals::Chams::Stylez == 1 ? G::chamsFlatMaterial : G::chamsNormalMaterial, Options::Visuals::Chams::color);


							if (Options::Visuals::Chams::RainBow)
							{
								if (Options::Visuals::Chams::VisibleRainBow)
								{
									U::ForceMaterial(Options::Visuals::Chams::Stylez == 2 ? G::fMaterial : G::fMaterial, copyrightColor.GetColor().base());
								}
								if (Options::Visuals::Chams::InVisibleRainBow)
								{
									U::ForceMaterial(Options::Visuals::Chams::Stylez == 1 ? G::ignoreFlatMaterial : G::ignoreNormalMaterial, copyrightColor.GetColor().base());
								}
							}
						}

						else
						{
							IMaterial *mats[32];
							studiohdr_t* hdr = Interface.ModelInfo->GetStudiomodel(pInfo.pModel);
							Interface.ModelInfo->GetModelMaterials(pInfo.pModel, hdr->numtextures, mats);
							for (int m = 0; m < 2; m++)
							{
								bool ignore = m == 0;
								if (ignore && Options::Visuals::Chams::VisibleOnly)
									continue;

								for (int i = 0; i < hdr->numtextures; i++)
								{
									IMaterial* mat = mats[i];
									if (!mat)
										break;

									mat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, ignore);

									/*static KeyValues* visibleMat = 0;
									static KeyValues* invisibleMat = 0;
									if (!visibleMat)
									visibleMat = U::CreateKeyValue("temp_1", false, false);
									if (!invisibleMat)
									invisibleMat = U::CreateKeyValue("temp_2", false, true);

									if (mat->GetShaderName() != "VertexLitGeneric")
									mat->SetShaderAndParams(ignore ? invisibleMat : visibleMat);

									if (ignore) mat->ColorModulate(0, 0, 0); else mat->ColorModulate(0, 1, 0);*/
								}
								O::DrawModelExecute(thisptr, matctx, state, pInfo, pCustomBoneToWorld);
							}
						}

					}

				}
			}
			else if (szModelName.find(XorStr("arms")) != std::string::npos)
			{
				if (Options::Visuals::Hands::Enabled)
				{

					IMaterial* Hands = Interface.MatSystem->FindMaterial(szModelName.c_str(), XorStr("Model textures"));
					bool forceMaterial = true;

					Hands->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);
					Hands->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);
					Hands->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);

					if (Options::Visuals::Hands::Style == 0)
					{
						Hands->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
					}
					if (Options::Visuals::Hands::Style == 2 || Options::Visuals::Hands::Style == 3 ||
						Options::Visuals::Hands::Style == 4 || Options::Visuals::Hands::Style == 5)
					{
						U::ForceMaterial(G::chamsNormalMaterial,
							Options::Visuals::Hands::Style == 4 || Options::Visuals::Hands::Style == 5 ? handsColor.GetColor().base() : Options::Visuals::Hands::color);
						forceMaterial = false;
						if (Options::Visuals::Hands::Style == 3 || Options::Visuals::Hands::Style == 5)
						{
							O::DrawModelExecute(thisptr, matctx, state, pInfo, pCustomBoneToWorld);
							forceMaterial = true;
						}
					}
					if (Options::Visuals::Hands::Style == 1 || Options::Visuals::Hands::Style == 3 ||
						Options::Visuals::Hands::Style == 5)
					{
						Hands->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, true);
						//if (Options::Visuals::Hands::Style == 5)
						//Hands->ColorModulate(255, 255, 255);
						//if (Options::Visuals::Hands::Style == 3) 
						//Hands->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
					}
					else
					{
						Hands->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, false);
					}


					if (forceMaterial) Interface.ModelRender->ForcedMaterialOverride(Hands);
				}
			}

			O::DrawModelExecute(thisptr, matctx, state, pInfo, pCustomBoneToWorld);
			Interface.ModelRender->ForcedMaterialOverride(NULL);
		}
	}
}