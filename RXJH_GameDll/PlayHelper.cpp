﻿#include "stdafx.h"
#include "PlayHelper.h"
#include "EntifyMonster.h"


PlayHelper::PlayHelper()
{
	m_protectHP = 150;
	m_protectMP = 100;
	m_workRange = 150;
	m_attackIndex = 0;
	m_minMonsterID = 1;
	m_maxMonsterID = 0x2710;
	m_bNearest = true;
}


PlayHelper::~PlayHelper()
{
}

// 开始/停止挂机
void PlayHelper::Start()
{
	// 初始化挂机范围
	m_rcRange.left = m_workPt.x - m_workRange;
	m_rcRange.right = m_workPt.x + m_workRange;
	m_rcRange.top = m_workPt.y - m_workRange;
	m_rcRange.bottom = m_workPt.y + m_workRange;
	// 初始话周围怪物的ID范围(最大，最小值)
	InitMonterIDRange();
}
void PlayHelper::Stop()
{

}

void outstr(const char* log)
{
	::OutputDebugString(log);
}

// 定时调用，自动选怪/攻击
void PlayHelper::Work()
{
	DWORD dwSelID = GetCurSelID();
	if (EntityBase::ID_NULL == dwSelID)
	{
		dwSelID = CheckMonster();
	}
	else
	{
		// 类型不是野怪，则重新选怪(可能用户自己手动点了其他玩家或者物品之类的)
		if (ET_Monster != EntityBase::GetTypeWithID(dwSelID))
		{
			dwSelID = CheckMonster();
		}
	}
	if (EntityBase::ID_NULL != dwSelID)
	{
		// 类型为野怪
		if (ET_Monster == EntityBase::GetTypeWithID(dwSelID))
		{
			// 判断是否可以使用必杀技
			EntifyMonster monster(dwSelID);
			if (monster.IsKillStatus())
			{
				// 必杀技快捷键
				m_role.UseShortcutF1_F10(EntityRole::FC_F8);
			}
			else
			{
				// 普攻或技能
				if (0 == m_attackIndex)
				{
					m_role.DoAction(EntityRole::Attack);
				}
				else
				{
					EntityRole::ShortCut sc = static_cast<EntityRole::ShortCut>(m_attackIndex - 1);
					m_role.UseShortcutF1_F10(sc);
				}
			}
		}
	}
}
// 保护功能，自动加血/蓝
void PlayHelper::Protect()
{
	DWORD dwCurrentHP= m_role.GetCurrentHP();
	if (dwCurrentHP <= m_protectHP)
	{
		// 吃红药
		m_role.UseShortcutF1_F10(EntityRole::FC_F2);
	}

	DWORD dwCurrentMP = m_role.GetCurrentMP();
	if (dwCurrentMP <= m_protectMP)
	{
		// 吃蓝药
		m_role.UseShortcutF1_F10(EntityRole::FC_F3);
	}
}

POINT PlayHelper::GetCurPoint()
{
	POINT pt = { 0 };
	pt.x = Read_RD(Read_RD(CordinateBaseAddress) + CordinateXOffset);
	pt.y = Read_RD(Read_RD(CordinateBaseAddress) + CordinateYOffset);
	pt.y = 0 - pt.y;
	return pt;
}
CString PlayHelper::GetCurMap()
{
	char* pMapName = Read_RS(Read_RD(MapBaseAddress) + MapNameOffset);
	return pMapName ? pMapName : "";
}

// 设置挂机点
void PlayHelper::SetWorkPoint(POINT a_pt)
{
	m_workPt = a_pt;
}

void PlayHelper::SetWorkRange(DWORD a_range)
{
	m_workRange = a_range;
}

void PlayHelper::SetAttackIndex(int a_index)
{
	m_attackIndex = a_index;
}

void PlayHelper::SetNearestPrior(bool a_nearest)
{
	m_bNearest = a_nearest;
}

// 设置HP/MP保护百分比，低于这个值则自动加血/蓝
void PlayHelper::SetProtectHP(DWORD a_protectHP)
{
	m_protectHP = a_protectHP;
}
void PlayHelper::SetProtectMP(DWORD a_protectMP)
{
	m_protectMP = a_protectMP;
}

void PlayHelper::SetPriorHPDrug(const CString& a_drugName)
{
	m_szPriorHPDrug = a_drugName;
}
void PlayHelper::SetPriorMPDrug(const CString& a_drugName)
{
	m_szPriorMPDrug = a_drugName;
}

void PlayHelper::InitMonterIDRange()
{
	m_minMonsterID = 0x2710;
	m_maxMonsterID = 0;
	for (DWORD dwID = 0x1; dwID < 0x2710; dwID++)
	{
		// 类型为野怪
		if (ET_Monster == EntityBase::GetTypeWithID(dwID))
		{
			if (m_minMonsterID > dwID)
			{
				m_minMonsterID = dwID;
			}
			if (m_maxMonsterID < dwID)
			{
				m_maxMonsterID = dwID;
			}
		}
	}
}

// 获取当前选中的ID
DWORD PlayHelper::GetCurSelID()
{
	return Read_RD(Read_RD(EntityBaseAddress) + EntitySelOffset);
}

DWORD PlayHelper::CheckMonster()
{
	DWORD dwSelID = EntityBase::ID_NULL;
	float dwDistion = 0.0f;
	EntifyMonster monster;
	for (DWORD dwID = m_minMonsterID; dwID <= m_maxMonsterID; dwID++)
	{
		// 类型为野怪
		if (ET_Monster == EntityBase::GetTypeWithID(dwID))
		{
			monster.SetID(dwID);
			// 未死亡
			if (!monster.IsDead())
			{
				// 怪物是否在挂机范围内
				POINT pt = monster.GetPoint();
				if (::PtInRect(&m_rcRange, pt))
				{
					float dist = monster.GetDistance();
					// 最近优先还是最远优先
					if (m_bNearest)
					{
						if (dwDistion == 0.0f || dwDistion > dist)
						{
							dwDistion = dist;
							dwSelID = dwID;
						}
					}
					else
					{
						if (dwDistion == 0.0f || dwDistion < dist)
						{
							dwDistion = dist;
							dwSelID = dwID;
						}
					}
				}
			}
		}
	}
	// 选中怪物
	if (EntityBase::ID_NULL != dwSelID)
	{
		monster.SetID(dwSelID);
		monster.Select();
	}

	return dwSelID;
}
