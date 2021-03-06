/*
*	Created:			25.02.10
*	Author:				009
*	Last Modifed:		-
*	Description:		���������
*/

#if defined _items_handcuffs_included
	#endinput
#endif

#define _items_handcuffs_included
#pragma library items_handcuffs

// --------------------------------------------------
// includes
// --------------------------------------------------

// --------------------------------------------------
// statics
// --------------------------------------------------
static tmp;

// --------------------------------------------------
// Obligatory functions
// --------------------------------------------------
Handcuffs_BuildTypeListItems(ownerid,ownertype,type,var0[],dest[],size)
{
	Debug(DEBUG_START,"Handcuffs_BuildTypeListItems(%d,%d,%d,'%s')",ownerid,ownertype,type,var0);
	Debug(DEBUG_END,"Handcuffs_BuildTypeListItems(reason: complete)");
	return 1;
}

Handcuffs_BuildItemActionsString(playerid,ownerid,ownertype,itemid,type,dest[],size)
{
	Debug(DEBUG_START,"Handcuffs_BuildItemActionsString(%d,%d,%d,%d,%d)",playerid,ownerid,ownertype,itemid,type);
	
	switch(ownertype)
	{
		case ITEM_OWNER_CHARACTER: 
		{
			if(!strcmp(GetItemOwnerId(itemid),oGetCharacterName(playerid),true)) 
			{
				if(((tmp = GetPlayerClosestPlayer(playerid)) != INVALID_PLAYER_ID) && (IsPlayerInRangeOfPlayer(playerid,2.0,tmp)) && (GetCharacterVarInt(tmp,"HandcuffsItemId") != INVALID_ITEM_ID))) format(dest,size,"������������\n��������");
				else format(dest,size,"��������");
			}
			else format(dest,size,"�������");
		}
		default: format(dest,size,"�����");
	}	
	Debug(DEBUG_END,"Handcuffs_BuildItemActionsString(reason: complete)");
}

Handcuffs_OnPlayerUseItem(playerid,ownerid,ownertype,itemid,type,itemdialogid,action[])
{
	Debug(DEBUG_START,"Handcuffs_OnPlayerUseItem(%d,%d,%d,%d,%d,%d,'%s')",playerid,ownerid,ownertype,itemid,type,itemdialogid,action);
	if(!strcmp(action,"������������"))
	{
		Debug(DEBUG_ACTION,"������������");
		if(((tmp = GetPlayerClosestPlayer(playerid)) == INVALID_PLAYER_ID) || (!IsPlayerInRangeOfPlayer(playerid,2.0,tmp)) || (GetCharacterVarInt(tmp,"HandcuffsItemId") == INVALID_ITEM_ID)) {Debug(DEBUG_END,"Handcuffs_OnPlayerUseItem(reason: complete)");return 0;}
		SetPlayerAction(tmp,ACTION_HANDCUFFS);
		new keyid = CreateItem(ITEM_TYPE_KEY);
		SetItemVarString(keyid,0,"�� ����������");
		SetItemOwner(keyid,ITEM_OWNER_CHARACTER,playerid);
		ItemOwnerRemove(itemid);
		SetItemVarInt(itemid,0,GetItemVarInt(keyid,1));
		SetCharacterVarInt(tmp,"HandcuffsItemId",itemid);
		Debug(DEBUG_END,"Handcuffs_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"��������"))
	{
		Debug(DEBUG_ACTION,"��������");
		ItemOwnerRemove(itemid);
		new Float:pos[4];
		GetPlayerPos(playerid,pos[0],pos[1],pos[2]);
		GetPlayerFacingAngle(playerid,pos[3]);
		MoveCoordsOnAngleByDistance(pos[0],pos[1],pos[3],1.0);
		SetItemPos(itemid,pos[0],pos[1],pos[2]);
		SetItemPremise(itemid,GetPlayerPremise(playerid));
		Debug(DEBUG_END,"Handcuffs_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"�������"))
	{
		Debug(DEBUG_ACTION,"�������");
		SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
		Debug(DEBUG_END,"Handcuffs_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	if(!strcmp(action,"�����"))
	{
		Debug(DEBUG_ACTION,"�����");
		SetItemOwner(itemid,ITEM_OWNER_CHARACTER,playerid);
		Debug(DEBUG_END,"Handcuffs_OnPlayerUseItem(reason: complete)");
		return 1;
	}
	Debug(DEBUG_END,"Handcuffs_OnPlayerUseItem(reason: complete)");
	return 0;
}