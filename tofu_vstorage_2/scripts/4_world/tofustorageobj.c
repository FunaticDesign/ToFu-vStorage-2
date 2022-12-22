class tofuvStorageObj 
{
	string itemName = "";
	string itemType = "";
	int itemRow = 0;
	int itemCol = 0;
	bool itemFliped = false;
	int itemQuantity = 0;
	int itemAmmoQuantity = 0;
	float itemHealth = 0;
	int itemLiquidType = 0;
	int itemFoodstage = 0;
	float itemTemp = 0;
	float itemWetness = 0;
	int itemInventoryType = 0;
	int itemIdx = 0;
	int itemSlotId = 0;
	int itemTimeStored = 0;
	string itemID = "";
	string itemWpnBarrelInfo = "";
	string itemWpnInternalMagInfo = "";
	string itemMagInfo = "";
	
	autoptr array<string> itemMagInhalt = {};
	
	string itemUnusedString1 = "";
	string itemUnusedString2 = "";
	string itemUnusedString3 = "";
	string itemUnusedString4 = "";
	string itemUnusedString5 = "";
	string itemUnusedString6 = "";
	
	int itemEnergy = 0;
	int itemUnusedInt2 = 0;
	int itemUnusedInt3 = 0;
	int itemUnusedInt4 = 0;
	int itemUnusedInt5 = 0;
	int itemUnusedInt6 = 0;
	
	bool itemHasEnergy = false;
	bool itemUnusedBool2 = false;
	bool itemUnusedBool3 = false;
	bool itemUnusedBool4 = false;
	bool itemUnusedBool5 = false;
	bool itemUnusedBool6 = false;
	
	ref array<ref tofuvStorageObj> itemChildren = {};
};


class tofuvStorageContainer 
{
	string persistentId = "";
	ref array<ref tofuvStorageObj> storedItems = {};
};