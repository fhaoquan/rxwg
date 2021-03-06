﻿#pragma once

// 人物属性相关地址
extern DWORD UserBaseAddress; // 人物属性基址
extern DWORD UserNameOffset; // 名称偏移
extern DWORD UserCareerOffset; // 人物职业偏移
extern DWORD UserLevelOffset; // 等级偏移
extern DWORD UserHPOffset; // 血量偏移
extern DWORD UserMPOffset; // 蓝量偏移
extern DWORD UserMaxHPOffset; // 血量最大值偏移
extern DWORD UserMaxMPOffset; // 蓝量最大值偏移

extern DWORD CordinateBaseAddress; // 坐标基址
extern DWORD CordinateXOffset; // X坐标偏移
extern DWORD CordinateYOffset; // Y坐标偏移

extern DWORD MapBaseAddress; // 地图基址
extern DWORD MapNameOffset; // 当前地图名称偏移

// 背包相关地址
extern DWORD GoodsBaseAddress;//背包的基址
extern DWORD GoodsBaseOffestAddress;     //背包基本的偏移
extern DWORD GoodsNameOffset; // 物品名称偏移
extern DWORD GoodsNumberOffset; // 物品数量偏移
//石头分类(比如金刚石里的武功，追加。。。)：[物品基址] + 0xD1C
// 1:攻击力，2:防御力，3:生命力，4:内功，5:命中率，6:回避率，7:武功攻击力，8:全部气功等级，9:物品升级成功率1%
//石头属性值：[物品基址] + 0xD24
extern DWORD GoodsIDOffset;
extern DWORD GoodsPropOffset;

extern DWORD GoodsUseCallAddress;// 使用背包物品call，参数为物品在背包中的索引下标(0-35)

// NPC商店
extern DWORD ShopBaseAddress; // 商店基址
extern DWORD ShopBaseOffset; // 商店基本偏移值
extern DWORD ShopItemIDOffset; // 商店物品ID偏移
extern DWORD ShopItemNameOffset; // 商店物品名称偏移
extern DWORD ShopCallAddress; // 商店购买call

// 选中的怪物相关地址
extern DWORD EntityBaseAddress;// 选中怪物ID基址
extern DWORD EntitySelOffset; // 选中怪物ID偏移值
extern DWORD EntityXOffset; // x坐标偏移
extern DWORD EntityYOffset; // y坐标偏移
// 怪物属性相关
extern DWORD EntityPropAddress;// 怪物属性基址
extern DWORD EntityTypeOffset; // 类型偏移
extern DWORD EntityIdOffset; // ID偏移
extern DWORD EntityNameOffset; // 名称偏移
extern DWORD EntityDistOffset; // 距离偏移
extern DWORD EntityLevelOffset; // 等级偏移
extern DWORD EntityHalfOffset; // 血量偏移
extern DWORD EntityDeadOffset; // 是否死亡偏移
extern DWORD EntityKillOffset; // 是否可以施展绝命技的偏移，为1是可以
extern DWORD EntityCordinateXOffset; // 怪物X坐标偏移
extern DWORD EntityCordinateYOffset; // 怪物Y坐标偏移
// 怪物类型 物品：0x33，玩家：0x31, 怪物/NPC：0x2E(NPC等级为0，血量为32000)
extern DWORD EntityType_Monster; // 野怪
extern DWORD EntityType_NPC; // NPC
extern DWORD EntityType_Player; // 其他玩家
extern DWORD EntityType_Goods; // 物品

// 选中物品时，名称偏移
extern DWORD EntityGoodsIDOffset; // 物品ID偏移
extern DWORD EntityGoodsNameOffset; // 物品名称偏移


// 快捷键相关地址
extern DWORD F1_F10_BaseAddress;//快捷键基址
extern DWORD F1_F10_BaseOffestAddress;     //快捷键基本偏移
extern DWORD F1_F10_CallAddress;//快捷键call地址

// 人物动作相关地址
extern DWORD ActionBaseAddress; // 动作基址
extern DWORD ActionCallAddress; // 动作call地址




