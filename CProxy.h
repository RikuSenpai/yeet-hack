#pragma once

#define SEQUENCE_DEFAULT_DRAW 0
#define SEQUENCE_DEFAULT_IDLE1 1
#define SEQUENCE_DEFAULT_IDLE2 2
#define SEQUENCE_DEFAULT_LIGHT_MISS1 3
#define SEQUENCE_DEFAULT_LIGHT_MISS2 4
#define SEQUENCE_DEFAULT_HEAVY_MISS1 9
#define SEQUENCE_DEFAULT_HEAVY_HIT1 10
#define SEQUENCE_DEFAULT_HEAVY_BACKSTAB 11
#define SEQUENCE_DEFAULT_LOOKAT01 12

#define SEQUENCE_BUTTERFLY_DRAW 0
#define SEQUENCE_BUTTERFLY_DRAW2 1
#define SEQUENCE_BUTTERFLY_LOOKAT01 13
#define SEQUENCE_BUTTERFLY_LOOKAT03 15

#define SEQUENCE_FALCHION_IDLE1 1
#define SEQUENCE_FALCHION_HEAVY_MISS1 8
#define SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP 9
#define SEQUENCE_FALCHION_LOOKAT01 12
#define SEQUENCE_FALCHION_LOOKAT02 13

#define SEQUENCE_DAGGERS_IDLE1 1
#define SEQUENCE_DAGGERS_LIGHT_MISS1 2
#define SEQUENCE_DAGGERS_LIGHT_MISS5 6
#define SEQUENCE_DAGGERS_HEAVY_MISS2 11
#define SEQUENCE_DAGGERS_HEAVY_MISS1 12

#define SEQUENCE_BOWIE_IDLE1 1

namespace CProxy
{
	inline const int RandomSequence(int low, int high) {
		return (rand() % (high - low + 1) + low);
	}

	void _cdecl Sequence(const CRecvProxyData *pDataConst, void *pStruct, void *pOut)
	{
		CRecvProxyData* pData = const_cast<CRecvProxyData*>(pDataConst);
		IClientEntity* pViewModel = (IClientEntity*)pStruct;

		if (pViewModel) {
			IClientEntity* pOwner = Interface.EntityList->GetClientEntityFromHandle(*(DWORD*)((DWORD)pViewModel + 0x29BC));

			if (pOwner && pOwner->GetIndex() == Interface.Engine->GetLocalPlayer()) {
				void* pModel = Interface.ModelInfo->GetModel(pViewModel->GetModelIndex());
				const char* szModel = Interface.ModelInfo->GetModelName((model_t*)pModel);

				int m_nSequence = pData->m_Value.m_Int;

				if (!strcmp(szModel, "models/weapons/v_knife_butterfly.mdl")) {
					// Fix animations for the Butterfly Knife.
					switch (m_nSequence) {
					case SEQUENCE_DEFAULT_DRAW:
						m_nSequence = RandomSequence(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2); break;
					case SEQUENCE_DEFAULT_LOOKAT01:
						m_nSequence = RandomSequence(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03); break;
					default:
						m_nSequence++;
					}
				}
				else if (!strcmp(szModel, "models/weapons/v_knife_falchion_advanced.mdl")) {
					// Fix animations for the Falchion Knife.
					switch (m_nSequence) {
					case SEQUENCE_DEFAULT_IDLE2:
						m_nSequence = SEQUENCE_FALCHION_IDLE1; break;
					case SEQUENCE_DEFAULT_HEAVY_MISS1:
						m_nSequence = RandomSequence(SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP); break;
					case SEQUENCE_DEFAULT_LOOKAT01:
						m_nSequence = RandomSequence(SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02); break;
					case SEQUENCE_DEFAULT_DRAW:
					case SEQUENCE_DEFAULT_IDLE1:
						break;
					default:
						m_nSequence--;
					}
				}
				else if (!strcmp(szModel, "models/weapons/v_knife_push.mdl")) {
					// Fix animations for the Shadow Daggers.
					switch (m_nSequence) {
					case SEQUENCE_DEFAULT_IDLE2:
						m_nSequence = SEQUENCE_DAGGERS_IDLE1; break;
					case SEQUENCE_DEFAULT_LIGHT_MISS1:
					case SEQUENCE_DEFAULT_LIGHT_MISS2:
						m_nSequence = RandomSequence(SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5); break;
					case SEQUENCE_DEFAULT_HEAVY_MISS1:
						m_nSequence = RandomSequence(SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1); break;
					case SEQUENCE_DEFAULT_HEAVY_HIT1:
					case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
					case SEQUENCE_DEFAULT_LOOKAT01:
						m_nSequence += 3; break;
					case SEQUENCE_DEFAULT_DRAW:
					case SEQUENCE_DEFAULT_IDLE1:
						break;
					default:
						m_nSequence += 2;
					}
				}
				else if (!strcmp(szModel, "models/weapons/v_knife_survival_bowie.mdl")) {
					// Fix animations for the Bowie Knife.
					switch (m_nSequence) {
					case SEQUENCE_DEFAULT_DRAW:
					case SEQUENCE_DEFAULT_IDLE1:
						break;
					case SEQUENCE_DEFAULT_IDLE2:
						m_nSequence = SEQUENCE_BOWIE_IDLE1; break;
					default:
						m_nSequence--;
					}
				}

				// Set the fixed sequence.
				pData->m_Value.m_Int = m_nSequence;
			}
		}

		H::Sequence->GetOriginalFunction()(pData, pStruct, pOut);
	}
};