class tofu_vstorage_barrel: Barrel_Red {
	
	protected bool m_vst_hasitems;
	protected int m_vst_steamid1;
	protected int m_vst_steamid2;
	protected int m_vst_steamid3;
	protected bool m_vst_wasplaced;
	
	protected int m_didVStorage;	
	
	protected int m_auto_close_random_seconds_min;
	protected int m_auto_close_random_seconds_max;

	//protected ref array<string> m_BlackListItems;

	

	void tofu_vstorage_barrel()
	{
		m_vst_steamid1 	= 0;
		m_vst_steamid2 	= 0;
		m_vst_steamid3 	= 0;
		m_vst_wasplaced = false;
		
		m_didVStorage = false;	
				
		RegisterNetSyncVariableBool( "m_vst_hasitems" );
		RegisterNetSyncVariableInt( "m_vst_steamid1" );
		RegisterNetSyncVariableInt( "m_vst_steamid2" );
		RegisterNetSyncVariableInt( "m_vst_steamid3" );
		RegisterNetSyncVariableBool( "m_vst_wasplaced" );

		m_auto_close_random_seconds_min = g_Game.GetVSTConfig().Get_auto_close_random_seconds_min();
		m_auto_close_random_seconds_max = g_Game.GetVSTConfig().Get_auto_close_random_seconds_max();

		if(GetGame().IsDedicatedServer())
		{
			
			string vstoreClassName = GetType();
			
			if(vstoreClassName != "tofu_vstorage_q_barrel_express")
			{
				if(g_Game.GetVSTConfig().Get_script_logging() == 1)
					Print("[vStorage] scheduling open/close check in 60 sec.");
				
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(vst_timer_start, 60000, false, false);
				if(vstoreClassName.Contains("_1000"))
				{
					GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(vstorageLifeRefresh, 30000, false, this);
				}
					
			}
			
		}
			
	}
	
	void vstorageLifeRefresh(EntityAI ent)
	{
		if(g_Game.GetVSTConfig().Get_script_logging() == 1)
			Print("[vStorage] Auto set Lifetime of "+ent.GetType()+" at pos "+ent.GetPosition());
		SetLifetime(3888000);
	}
	
	/*
	void ladeConfig()
	{
		m_BlackListItems = g_Game.GetVSTConfig().Get_Blacklist();
	}
	*/
	
	
	override void OnPlacementComplete( Man player, vector position = "0 0 0", vector orientation = "0 0 0" )
	{
		super.OnPlacementComplete( player, position, orientation );
		if(GetGame().IsServer())
		{
			string steamid = player.GetIdentity().GetPlainId();
			if(g_Game.GetVSTConfig().Get_script_logging() == 1)
				Print("[vStorage] player "+steamid+ "placed barrel "+GetType()+" at pos "+GetPosition());
			
			//string steamid_part1 = "999999";
			string steamid_part1 = steamid.Substring(0,6);
			string steamid_part2 = steamid.Substring(6,6);
			string steamid_part3 = steamid.Substring(12,5);
			saveSteamid(steamid_part1,steamid_part2,steamid_part3);
		}
	}
	
	
	void saveSteamid(string a, string b, string c) {
				
		
		//Print("[vStorage] a "+a);
		//Print("[vStorage] b "+b);
		//Print("[vStorage] c "+c);
		
		string mod1 = "9"+a; 
		string mod2 = "9"+b;
		string mod3 = "9"+c;
		
		//Print("[vStorage] mod1 "+mod1);
		//Print("[vStorage] mod2 "+mod2);
		//Print("[vStorage] mod3 "+mod3);
		
		m_vst_steamid1 = mod1.ToInt();
		m_vst_steamid2 = mod2.ToInt();
		m_vst_steamid3 = mod3.ToInt();
		
		//Print("[vStorage] m_vst_steamid1 "+m_vst_steamid1);
		//Print("[vStorage] m_vst_steamid2 "+m_vst_steamid2);
		//Print("[vStorage] m_vst_steamid3 "+m_vst_steamid3);
				
		m_vst_wasplaced = true;
		SetSynchDirty();
	}
	
	bool canInteract(string steamid)
	{
		//Print(steamid);
		
		string steamid_part1 = steamid.Substring(0,6);
		string steamid_part2 = steamid.Substring(6,6);
		string steamid_part3 = steamid.Substring(12,5);
		
		string mod1 = "9"+steamid_part1; 
		string mod2 = "9"+steamid_part2;
		string mod3 = "9"+steamid_part3;
		
		int steamid1 = mod1.ToInt();
		int steamid2 = mod2.ToInt();
		int steamid3 = mod3.ToInt();
		
		/*
		Print(m_vst_wasplaced);
		Print(m_vst_steamid1);
		Print(m_vst_steamid2);
		Print(m_vst_steamid3);
		Print(steamid1);
		Print(steamid2);
		Print(steamid3);
		*/
		
		if(m_vst_wasplaced == false) {
			return true;
		}
				
		if(m_vst_steamid1 == steamid1 && m_vst_steamid2 == steamid2 && m_vst_steamid3 == steamid3)
			return true;
				
		
		return false;
	}
	
	bool canInteractAdmin(string steamid)
	{
		//Print(steamid);
		
		string steamid_part1 = steamid.Substring(0,6);
		string steamid_part2 = steamid.Substring(6,6);
		string steamid_part3 = steamid.Substring(12,5);
		
		string mod1 = "9"+steamid_part1; 
		string mod2 = "9"+steamid_part2;
		string mod3 = "9"+steamid_part3;
		
		int steamid1 = mod1.ToInt();
		int steamid2 = mod2.ToInt();
		int steamid3 = mod3.ToInt();
		
		/*
		Print(m_vst_wasplaced);
		Print(m_vst_steamid1);
		Print(m_vst_steamid2);
		Print(m_vst_steamid3);
		Print(steamid1);
		Print(steamid2);
		Print(steamid3);
		*/
				
		
		array<string> Admins_List = g_Game.GetVSTConfig().Get_Admins();
		
		for (int i = 0; i < Admins_List.Count(); i++)
        {
			if(steamid == Admins_List.Get(i))
				return true;
		}
		
		return false;
	}
	
		
	void Unclaim() {
		m_vst_wasplaced = false;
		m_vst_steamid1 = 0;
		m_vst_steamid2 = 0;
		m_vst_steamid3 = 0;
		SetSynchDirty();
	}

	void vst_timer_start(bool express = false)
	{
		if(!(m_auto_close_random_seconds_min > 0 && m_auto_close_random_seconds_max > 0 && m_auto_close_random_seconds_min < m_auto_close_random_seconds_max))
			return;

		if(IsOpen())
		{
			int autoclose_timer;
			if(express)
			{
				autoclose_timer = 20*1000;
			}
			else
			{
				autoclose_timer = Math.RandomInt(m_auto_close_random_seconds_min, m_auto_close_random_seconds_max)*1000;
			}
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(vst_timer_end, autoclose_timer, false);
			if(g_Game.GetVSTConfig().Get_script_logging() == 1)
				Print("[vStorage] Starting " + autoclose_timer +" ms autoclose timer for " + GetType() + " at Position " +GetPosition() );
		}
		
	}

	void vst_timer_end()
	{
		if(!IsOpen()) return;

		array<Object> items_in_vicinity = new array<Object>;
        
        GetGame().GetObjectsAtPosition(GetPosition(), 10.0, items_in_vicinity, NULL);

		bool PlayerIsAround = false;

		for (int i = 0; i < items_in_vicinity.Count(); i++)
		{
			EntityAI item_in_vicinity = EntityAI.Cast(items_in_vicinity.Get(i));
			if (item_in_vicinity && item_in_vicinity.IsKindOf("SurvivorBase"))
			{
				PlayerIsAround = true;
				break;
			}
		};

		if(!PlayerIsAround)
		{
			if(g_Game.GetVSTConfig().Get_script_logging() == 1)
				Print("[vStorage] No player(s) around, autoclosing "+GetType()+" at pos "+GetPosition());
			
			vclose();
		} else
		{
			if(g_Game.GetVSTConfig().Get_script_logging() == 1)
				Print("[vStorage] Player(s) around near "+GetType()+" at pos "+GetPosition()+", not closing, restarting timer");
			
			vst_timer_start(false);
		}
	}

	void setItems(bool items)
	{
		m_vst_hasitems = items;
		SetSynchDirty();
	}
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{   
		
		super.OnStoreSave(ctx);
		
		ctx.Write(m_vst_hasitems);
		ctx.Write(m_vst_steamid1);
		ctx.Write(m_vst_steamid2);
		ctx.Write(m_vst_steamid3);
		ctx.Write(m_vst_wasplaced);
		
		//Print("[vStorage] saving m_vst_wasplaced "+m_vst_wasplaced);
		//Print("[vStorage] saving m_vst_steamid1 "+m_vst_steamid1);
		//Print("[vStorage] saving m_vst_steamid2 "+m_vst_steamid2);
		//Print("[vStorage] saving m_vst_steamid3 "+m_vst_steamid3);
		//Print("[vStorage] saving m_vst_hasitems "+m_vst_hasitems);
		
		
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{   
		if ( !super.OnStoreLoad(ctx, version) )
			return false;
		
		/*
		if (ctx.Read(m_vst_hasitems)) { Print("[vStorage] reading m_vst_hasitems "+m_vst_hasitems); }
		if (ctx.Read(m_vst_steamid1)) { Print("[vStorage] reading m_vst_steamid1 "+m_vst_steamid1); }
		if (ctx.Read(m_vst_steamid2)) { Print("[vStorage] reading m_vst_steamid2 "+m_vst_steamid2); }
		if (ctx.Read(m_vst_steamid3)) { Print("[vStorage] reading m_vst_steamid3 "+m_vst_steamid3); }
		if (ctx.Read(m_vst_wasplaced)) { Print("[vStorage] reading m_vst_wasplaced "+m_vst_wasplaced); }
		*/
		
		if (ctx.Read(m_vst_hasitems)) {  }
		if (ctx.Read(m_vst_steamid1)) {  }
		if (ctx.Read(m_vst_steamid2)) {  }
		if (ctx.Read(m_vst_steamid3)) {  }
		if (ctx.Read(m_vst_wasplaced)) {  }
			
		
		SetSynchDirty();
		return true;
	}
	
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionOpenVStorage);
		AddAction(ActionCloseVStorage);
		RemoveAction(ActionOpenBarrel);
		RemoveAction(ActionCloseBarrel);
		RemoveAction(ActionTakeItem);
		RemoveAction(ActionTakeItemToHands);
		AddAction(ActionTakeItem);
		AddAction(ActionTakeItemToHands);
		AddAction(ActionUnclaimVStorage);
	}
	
	bool vst_IsOnBlacklist(EntityAI item)
	{
		
		/*
		if(!m_BlackListItems || m_BlackListItems.Count() == 0) {
			//Print("[vStorage] m_BlackListItems array nicht bekannt oder leer ");
			return false;
		}
		*/
			

		int i;
		string BlackListClass;

		for (i = 0; i < g_Game.GetVSTConfig().Get_Blacklist().Count(); i++)
		{
			BlackListClass = g_Game.GetVSTConfig().Get_Blacklist().Get(i);
			if(item.IsKindOf(BlackListClass)) 
			{
				//Print("[vStorage] Found Item "+BlackListClass+" IN blacklist");
				return true;
			}
			
		}

		array<EntityAI> items_in_storage = new array<EntityAI>;
		EntityAI item_in_storage;

		item.GetInventory().EnumerateInventory(InventoryTraversalType.LEVELORDER, items_in_storage);

		for (i = 0; i < items_in_storage.Count(); i++)
		{
			item_in_storage = items_in_storage.Get(i);
			if (item_in_storage && vst_IsOnBlacklist(item_in_storage))
			{
				//Print("[vStorage] Found Child Item "+BlackListClass+" IN blacklist");
				return true;
			}
		};

		//Print("[vStorage] ITEM "+item+" IS NOT ON BLACKLIST");
		return false;
	}

	override bool CanReceiveItemIntoCargo (EntityAI item)
    {
		return !vst_IsOnBlacklist(item);
    }
	
	override bool CanPutInCargo( EntityAI parent )
	{
		string steamid;
		
		if(IsOpen() || m_vst_hasitems)
			return false;
		
		
		if(GetType().Contains("_1000"))
		{
			if(GetGame().IsServer())
			{
				steamid = PlayerBase.Cast(parent).GetIdentity().GetPlainId();
			}
			else
			{
				if (GetGame().GetUserManager() && GetGame().GetUserManager().GetTitleInitiator()){
					steamid = GetGame().GetUserManager().GetTitleInitiator().GetUid();
				}
			}
			
			return canInteractAdmin(steamid);
		}
		
		if(GetType() == "tofu_vstorage_q_barrel_express")
		{
		
			
			if(GetGame().IsServer())
			{
				steamid = PlayerBase.Cast(parent).GetIdentity().GetPlainId();
			}
			else
			{
				if (GetGame().GetUserManager() && GetGame().GetUserManager().GetTitleInitiator()){
					steamid = GetGame().GetUserManager().GetTitleInitiator().GetUid();
				}
			}
			
			if(!canInteract(steamid) || m_vst_hasitems || IsOpen())
			{
				return false;
			}
		}
		
		if ( !m_vst_hasitems )
			return true;
		
		if ( !super.CanPutInCargo( parent ))
			return false;
				
		return false;
	}
	
	override bool CanPutIntoHands( EntityAI parent )
	{
		
		string steamid;
		
		if(IsOpen()) 
			return false;
		
		if(GetType().Contains("_1000"))
		{
			if(GetGame().IsServer())
			{
				steamid = PlayerBase.Cast(parent).GetIdentity().GetPlainId();
			}
			else
			{
				if (GetGame().GetUserManager() && GetGame().GetUserManager().GetTitleInitiator()){
					steamid = GetGame().GetUserManager().GetTitleInitiator().GetUid();
				}
			}
			
			return canInteractAdmin(steamid);
		}
			
		
		// If Base nearby and barrel is closed allow take to hands
		array<Object> items_in_vicinity = new array<Object>;
        GetGame().GetObjectsAtPosition(GetPosition(), 60.0, items_in_vicinity, NULL);
		
		bool FlagNearby = false;

		for (int i = 0; i < items_in_vicinity.Count(); i++)
		{
			EntityAI item_in_vicinity = EntityAI.Cast(items_in_vicinity.Get(i));
			if (item_in_vicinity && item_in_vicinity.IsKindOf("TerritoryFlag"))
			{
				FlagNearby = true;
				break;
			}
		};
		
		if(FlagNearby && GetType() != "tofu_vstorage_q_barrel_express")
			return true;
		// --
		
		
		if(GetType() == "tofu_vstorage_q_barrel_express")
		{
						
			if(GetGame().IsServer())
			{
				steamid = PlayerBase.Cast(parent).GetIdentity().GetPlainId();
			}
			else
			{
				if (GetGame().GetUserManager() && GetGame().GetUserManager().GetTitleInitiator()){
					steamid = GetGame().GetUserManager().GetTitleInitiator().GetUid();
				}
			}
			
			if(!canInteract(steamid))
				return false;
			
			if(canInteract(steamid))
				return true;
			
		}
		
		if ( !m_vst_hasitems )
			return true;
						
		
		if ( !super.CanPutIntoHands( parent ))
			return false;		

		return false;
	}

	bool vopen(PlayerBase player, string steamid = "")
	{
		
		
		bool failedItems = false;
		
		int b1;
		int b2;
		int b3;
		int b4;
		string filename;
		GetPersistentID(b1, b2, b3, b4);
		
		if(this.GetType() != "tofu_vstorage_q_barrel_express")
		{
			filename = "container_"+b1+"_"+b2+"_"+b3+"_"+b4+".save";
		}
		else
		{
			filename = steamid+".save";
		}
		
		FileSerializer openfile = new FileSerializer();
		tofuvStorageContainer loadedContainerObj = new tofuvStorageContainer() ;
		
		if (openfile.Open("$profile:ToFuVStorage/" + filename, FileMode.READ)) {
			if(openfile.Read(loadedContainerObj)) {
				foreach(tofuvStorageObj item : loadedContainerObj.storedItems) {
					if(!vrestore(item, this, player))
						failedItems = true;
				}
			}
			openfile.Close();
			
			if(this.GetType() == "tofu_vstorage_q_barrel_express" || this.GetType() == "tofu_vstorage_q_barrel_travel")
			{
				if (FileExist("$profile:ToFuVStorage/"+filename)) {
					DeleteFile("$profile:ToFuVStorage/"+filename);
					//Print("[vStorage] DELETED FILE "+filename_q);
				}
			}
			
		}
				
		m_Openable.Open();
		m_RainProcurement.InitRainProcurement();
		SoundSynchRemote();
		SetTakeable(false);

		//SetSynchDirty(); //! called also in SoundSynchRemote - TODO

		UpdateVisualState();
		
		if(GetGame().IsDedicatedServer())
		{
			if(this.GetType() != "tofu_vstorage_q_barrel_express")
			{
				vst_timer_start(false);
				
				if(g_Game.GetVSTConfig().Get_script_logging() == 1)
					Print("[vStorage] Player "+steamid+" opened Barrel "+GetType()+" at position "+GetPosition());
			}
			
			//SoundSynchRemoteReset();
		}
		
		if(failedItems) 
		{
			SetSynchDirty();
			return false;
		}
		
		
		SetSynchDirty();
		return true;
		
	}

	void vclose(string steamid = "")
	{
		//Print("[vStorage] vclose() called, IsOpen() for " + GetType() + ": " + IsOpen());
		if(!IsOpen()) return;

		autoptr tofuvStorageContainer containerObj = new tofuvStorageContainer();
		
		int b1;
		int b2;
		int b3;
		int b4;
		string filename;
		GetPersistentID(b1, b2, b3, b4);
		string persistentIdToSave = "container_" + b1 + "_" + b2 + "_" + b3 + "_" + b4;
		
		if(this.GetType() != "tofu_vstorage_q_barrel_express")
		{
			filename = persistentIdToSave + ".save";
		}
		else
		{
			filename = steamid+".save";
		}
		
		
		containerObj.persistentId = persistentIdToSave;
		containerObj.storedItems = new ref array<ref tofuvStorageObj>;
		
		array<EntityAI> items = new array<EntityAI>;
		GetInventory().EnumerateInventory(InventoryTraversalType.LEVELORDER, items);

		int count = items.Count();
		for (int i = 0; i < count; i++)
		{
			EntityAI item_in_storage = items.Get(i);
			if (item_in_storage)
				containerObj.storedItems.Insert(vstore(item_in_storage));
		}
		
		if(count==1)
			setItems(false);
		else 
			setItems(true);

		//Print("[vStorage] vclose() ");
		
		FileSerializer file = new FileSerializer();
		if (file.Open("$profile:ToFuVStorage/" + filename, FileMode.WRITE))
		{
			if(file.Write(containerObj))
			{
				array<EntityAI> items_to_store = new array<EntityAI>;
				GetInventory().EnumerateInventory(InventoryTraversalType.LEVELORDER, items_to_store);
				count = items_to_store.Count();
				for (int j= 0; j < count; j++)
				{
					EntityAI item_in_storage_to_delete = items_to_store.Get(j);
					if (item_in_storage_to_delete) {
						item_in_storage_to_delete.Delete();
					}
				}
			}
			file.Close();
			//Print("Content Serialized and saved");
		}

		//Print("[vStorage] vclose() end");

		m_Openable.Close();
		if (m_RainProcurement.IsRunning())
			m_RainProcurement.StopRainProcurement();
		SoundSynchRemote();
		SetTakeable(true);

		//SetSynchDirty(); //! called also in SoundSynchRemote - TODO
		
		SetSynchDirty();
		UpdateVisualState();
	}

	tofuvStorageObj vstore(EntityAI item_in_storage)
	{
		autoptr tofuvStorageObj itemObj = new tofuvStorageObj();
		InventoryLocation item_in_storage_location = new InventoryLocation;
		item_in_storage.GetInventory().GetCurrentInventoryLocation( item_in_storage_location );
		ItemBase item_to_check = ItemBase.Cast(item_in_storage);
		
		itemObj.itemName = item_in_storage.GetType();
		itemObj.itemRow = item_in_storage_location.GetRow();
		itemObj.itemCol = item_in_storage_location.GetCol();
		itemObj.itemFliped = item_in_storage_location.GetFlip();
		itemObj.itemIdx = item_in_storage_location.GetIdx();
		itemObj.itemSlotId = item_in_storage_location.GetSlot();
		itemObj.itemInventoryType = item_in_storage_location.GetType();
		
		if(item_to_check.HasQuantity())
		{
			itemObj.itemQuantity = item_to_check.GetQuantity();
			if(item_to_check.IsLiquidContainer())
				itemObj.itemLiquidType = item_to_check.GetLiquidType();
		} else
		{
			itemObj.itemQuantity = 0;
			itemObj.itemLiquidType = 0;
		}
		
		if(item_in_storage.m_EM)
		{
			itemObj.itemEnergy =  Math.Ceil(item_in_storage.m_EM.GetEnergy());
			itemObj.itemHasEnergy = true;
		}
		
		Magazine magazine_check = Magazine.Cast(item_in_storage);
		Ammunition_Base ammo_check = Ammunition_Base.Cast(item_in_storage);

		if(item_in_storage.IsMagazine() && !(ammo_check && ammo_check.IsAmmoPile()))
		{
			itemObj.itemType = "magazine";
			itemObj.itemAmmoQuantity = magazine_check.GetAmmoCount();
			
			for (int f = 0; f < magazine_check.GetAmmoCount(); f++)
			{
				float dmg;
				string class_name;
				magazine_check.GetCartridgeAtIndex(f, dmg, class_name);
				string ma_temp = f.ToString() + "," + class_name;
				
				itemObj.itemMagInhalt.Insert(ma_temp);
			}
			//Print("MAGAZINE AMMO: "+magazine_check.GetAmmoCount());
		}
		
		array<string> a_itemWpnBarrelInfo = new array<string>;
		array<string> a_itemWpnInternalMagInfo = new array<string>;
				
		if(item_in_storage.IsWeapon())
		{
			Weapon_Base wpn = Weapon_Base.Cast(item_in_storage);
			float damage = 0.0;
			string type;
			string itemWpnBarrelInfo;
			string itemWpnInternalMagInfo;
			
			for (int mi = 0; mi < wpn.GetMuzzleCount(); ++mi)
			{
				if (!wpn.IsChamberEmpty(mi))
				{
					if (wpn.GetCartridgeInfo(mi, damage, type))
					{
						//Print ("[Im Lauf] " +mi+" "+damage+" "+type);
						string bi_temp = ""+mi+","+type;
						a_itemWpnBarrelInfo.Insert(bi_temp);
						//PushCartridgeToChamber(mi, damage, type);
					}
				}
				
				for (int ci = 0; ci < wpn.GetInternalMagazineCartridgeCount(mi); ++ci)
				{
					if (wpn.GetInternalMagazineCartridgeInfo(mi, ci, damage, type))
					{
						//Print ("[In internen Mag] " +mi+" "+ci+" "+damage+" "+type);
						string ci_temp = ""+mi+","+type;
						a_itemWpnInternalMagInfo.Insert(ci_temp);
						//PushCartridgeToInternalMagazine(mi, damage, type);
					}
				}
			}
			
			if(a_itemWpnBarrelInfo.Count() > 0)
			{
				for (int bi = 0; bi < a_itemWpnBarrelInfo.Count(); bi++)
				{
					itemWpnBarrelInfo += a_itemWpnBarrelInfo.Get(bi)+"|";
				}
				itemObj.itemWpnBarrelInfo = itemWpnBarrelInfo;
				//Print(itemWpnBarrelInfo);
			}
			
			if(a_itemWpnInternalMagInfo.Count() > 0)
			{
				for (int im = 0; im < a_itemWpnInternalMagInfo.Count(); im++)
				{
					itemWpnInternalMagInfo += a_itemWpnInternalMagInfo.Get(im)+"|";
				}
				itemObj.itemWpnInternalMagInfo = itemWpnInternalMagInfo;
				//Print(itemWpnInternalMagInfo);
			}
		}
		
		if(ammo_check && ammo_check.IsAmmoPile())
		{
			itemObj.itemAmmoQuantity = ammo_check.GetAmmoCount();
		}
		
		itemObj.itemHealth = item_in_storage.GetHealth();
						
		if(item_in_storage.IsFood())
		{
			Edible_Base item_to_check_food = Edible_Base.Cast(item_in_storage);
			if(item_to_check_food)
			{
				itemObj.itemFoodstage = item_to_check_food.GetFoodStageType();
			}
		}
		
		itemObj.itemTemp = item_to_check.GetTemperature();
		itemObj.itemWetness = item_to_check.GetWet();
		
		
		array<EntityAI> items = new array<EntityAI>;
		item_in_storage.GetInventory().EnumerateInventory(InventoryTraversalType.LEVELORDER, items);
		int count = items.Count();
		for (int i = 0; i < count; i++)
		{
			EntityAI item_in_storage_child = items.Get(i);
			if (item_in_storage_child) {
				itemObj.itemChildren.Insert(vstore(item_in_storage_child));
				m_didVStorage = true;
			}
		};
		
		
		/*
		Print("------- NEW ITEM ---------");
		Print(itemObj.itemName);
		Print(itemObj.itemType);
		Print(itemObj.itemRow);
		Print(itemObj.itemCol);
		Print(itemObj.itemFliped);
		Print(itemObj.itemQuantity);
		Print(itemObj.itemAmmoQuantity);
		Print(itemObj.itemHealth);
		Print(itemObj.itemLiquidType);
		Print(itemObj.itemFoodstage);
		Print(itemObj.itemTemp);
		Print(itemObj.itemWetness);
		Print(itemObj.itemInventoryType);
		Print(itemObj.itemIdx);
		Print(itemObj.itemSlotId);
		Print(itemObj.itemChildren);
		Print("----------------");
		*/
		
		return itemObj;
	}
	
	bool vrestore(tofuvStorageObj item, Object target_object, PlayerBase player)
	{
		
		
		bool itemFailed = false;
		bool indexError = false;
		
		EntityAI ntarget = EntityAI.Cast( target_object );
		ItemBase new_item;
	
		if(item.itemSlotId == -1) {
			
			if(g_Game.GetVSTConfig().Get_script_logging() == 1)
			{
				Print("[vStorage] Try Creating " + item.itemName + " in Parent " + ntarget.GetType());
				Print("[vStorage] Try " + item.itemIdx + " item.itemIdx ");
				Print("[vStorage] Try " + item.itemRow + " item.itemRow ");
				Print("[vStorage] Try " + item.itemCol + " item.itemCol ");
				Print("[vStorage] Try " + item.itemFliped + " item.itemFliped ");
			}
			
				
			GameInventory safty_iventory = GameInventory.Cast(ntarget.GetInventory());
			if(safty_iventory)
			{
				if(g_Game.GetVSTConfig().Get_script_logging() == 1)
					Print("[vStorage] safty_iventory okay");
				
				
				if(item.itemIdx == -1)
				{
					if(g_Game.GetVSTConfig().Get_script_logging() == 1)
						Print("[vStorage] !!!!!!!!!!!!!!item.itemIdx -1, Abort");
					
					indexError = true;
				}
				
				if(item.itemRow == -1)
				{
					if(g_Game.GetVSTConfig().Get_script_logging() == 1)
						Print("[vStorage] !!!!!!!!!!!!item.itemRow -1, Abort");
					
					indexError = true;
				}
				
				if(item.itemCol == -1)
				{
					if(g_Game.GetVSTConfig().Get_script_logging() == 1)
						Print("[vStorage] !!!!!!!!!!!!item.itemCol -1, Abort");
					
					indexError = true;
				}
				
				if(!indexError)				
				{	
					new_item = ItemBase.Cast(safty_iventory.CreateEntityInCargoEx(item.itemName,item.itemIdx,item.itemRow,item.itemCol,item.itemFliped));
				}
				else
				{
					new_item = ItemBase.Cast(GetGame().CreateObject(item.itemName, ntarget.GetPosition(),false,false,true));
					if(!new_item)
					{
						Print("[vStorage] !!!!!!!!Failed creating Item "+item.itemName+" "+new_item+" on ground.");
						return false;
					}
					else
					{
						if(g_Game.GetVSTConfig().Get_script_logging() == 1)
							Print("[vStorage] Item "+item.itemName+" "+new_item+" created on ground.");
					}
				}
			}
			else
			{
				if(g_Game.GetVSTConfig().Get_script_logging() == 1)
					Print("[vStorage] !!!!!!!!!!!!!! Failed casting Inventory");
				
				return false;
			}
			
			
			
						
			
			
			if(new_item) {
				if(g_Game.GetVSTConfig().Get_script_logging() == 1)
					Print("[vStorage] Item "+item.itemName+" "+new_item+" Created, preparing to set properties.");
			} else {
				if(g_Game.GetVSTConfig().Get_script_logging() == 1)
					Print("[vStorage] Item "+item.itemName+" "+new_item+" NOT created, try alternative way");
				
				
				GameInventory testinv = ntarget.GetInventory();
				if(!testinv) {
					if(g_Game.GetVSTConfig().Get_script_logging() == 1)
						Print("[vStorage] No Inventory found for Item "+item.itemName+" "+new_item+"");
				} else {
					testinv.UnlockInventory(HIDE_INV_FROM_SCRIPT);   
					new_item = ItemBase.Cast(testinv.CreateEntityInCargoEx(item.itemName,item.itemIdx,item.itemRow,item.itemCol,item.itemFliped));
					if(new_item) {
						if(g_Game.GetVSTConfig().Get_script_logging() == 1)
							Print("[vStorage] Item "+item.itemName+" "+new_item+" created in retry");
					} else {
						if(g_Game.GetVSTConfig().Get_script_logging() == 1)
							Print("[vStorage] Item "+item.itemName+" "+new_item+" NOT created in retry");
						
						new_item = ItemBase.Cast(GetGame().CreateObject(item.itemName, ntarget.GetPosition(),false,false,true));
						if(!new_item)
						{
							Print("[vStorage] !!!!!!!!Failed creating Item "+item.itemName+" "+new_item+" on ground.");
							return false;
						}
						else
						{
							if(g_Game.GetVSTConfig().Get_script_logging() == 1)
								Print("[vStorage] Item "+item.itemName+" "+new_item+" created on ground.");
						}
						
					}
				}
			}
		} else {
			if(ntarget.IsWeapon() && item.itemType == "magazine") {
				
				if(g_Game.GetVSTConfig().Get_script_logging() == 1)
					Print("[vStorage] Item "+item.itemName+" "+new_item+" is Magazine, parent is weapon.");
				
				Weapon_Base weapon = Weapon_Base.Cast(ntarget);
				
				
				weapon.SpawnAmmo( item.itemName, 0 );
				
				array<EntityAI> items = new array<EntityAI>;
				weapon.GetInventory().EnumerateInventory(InventoryTraversalType.LEVELORDER, items);
				int count = items.Count();
				for (int i = 0; i < count; i++)
				{
					ItemBase item_in_storage = ItemBase.Cast(items.Get(i));
					if (item_in_storage)
					{
						Magazine magazine_check = Magazine.Cast(item_in_storage);
						Ammunition_Base ammo_check = Ammunition_Base.Cast(item_in_storage);
						if(item_in_storage.IsMagazine() && !(ammo_check && ammo_check.IsAmmoPile())) {
							magazine_check.ServerSetAmmoCount(0);
							
							array<string> itemMagInhalt3 = item.itemMagInhalt;
					
							for (int ae = 0; ae < itemMagInhalt3.Count(); ae++)
							{
								string part_itemMagInfo3 = itemMagInhalt3.Get(ae);
								if(part_itemMagInfo3 != "")
								{
									TStringArray a_part_itemMagInfo3 = new TStringArray;
									part_itemMagInfo3.Split(",", a_part_itemMagInfo3);
															
									if ( magazine_check.ServerStoreCartridge(0.0, a_part_itemMagInfo3[1]))
									{
										//Print("Stored Ammo in Mag");
									}
								}
							}
							magazine_check.SetSynchDirty();
							
							ItemBase mag_stats = ItemBase.Cast(item_in_storage);
							
							mag_stats.SetHealth(item.itemHealth);
							
							mag_stats.SetTemperature(item.itemTemp);
							
							
							mag_stats.SetWet(item.itemWetness);
						}
					}
				}
			} else {
				if(item.itemType == "magazine") {
					new_item = ItemBase.Cast(ntarget.GetInventory().CreateAttachmentEx(item.itemName,item.itemSlotId));
					Magazine magazine_check3 = Magazine.Cast(new_item);
					Ammunition_Base ammo_check2 = Ammunition_Base.Cast(new_item);
					if(new_item && new_item.IsMagazine() && !(ammo_check2 && ammo_check2.IsAmmoPile())) {
						magazine_check3.ServerSetAmmoCount(0);
						
						array<string> itemMagInhalt2 = item.itemMagInhalt;
					
						for (int ad = 0; ad < itemMagInhalt2.Count(); ad++)
						{
							string part_itemMagInfo2 = itemMagInhalt2.Get(ad);
							if(part_itemMagInfo2 != "")
							{
								TStringArray a_part_itemMagInfo2 = new TStringArray;
								part_itemMagInfo2.Split(",", a_part_itemMagInfo2);
														
								if ( magazine_check3.ServerStoreCartridge(0.0, a_part_itemMagInfo2[1]))
								{
									//Print("Stored Ammo in Mag");
								}
							}
						}
						magazine_check3.SetSynchDirty();
						
						ItemBase mag_stats2 = ItemBase.Cast(new_item);
						
						
						mag_stats2.SetHealth(item.itemHealth);
						
						
						mag_stats2.SetTemperature(item.itemTemp);
						
						
						mag_stats2.SetWet(item.itemWetness);
					}
					
				} else {
					new_item = ItemBase.Cast(ntarget.GetInventory().CreateAttachmentEx(item.itemName,item.itemSlotId));
				}
			}
		}
		
		if(new_item)
		{
			if(g_Game.GetVSTConfig().Get_script_logging() == 1)
				Print("[vStorage] Item "+item.itemName+" "+new_item+" setting properties.");
			
			if(new_item.IsWeapon())
			{
				if(g_Game.GetVSTConfig().Get_script_logging() == 1)
					Print("[vStorage] Item  "+item.itemName+" "+new_item+" is weapon.");
				
				//Print("Item is Weapon");
				bool didChamberAction = false;
				Weapon_Base wpn = Weapon_Base.Cast(new_item);
				
				string itemWpnBarrelInfo = item.itemWpnBarrelInfo;
				
				TStringArray a_itemWpnBarrelInfo = new TStringArray;
				itemWpnBarrelInfo.Split("|", a_itemWpnBarrelInfo);
				for (int ab = 0; ab < a_itemWpnBarrelInfo.Count(); ab++)
				{
					string part_itemWpnBarrelInfo = a_itemWpnBarrelInfo.Get(ab);
					if(part_itemWpnBarrelInfo != "")
					{
						TStringArray a_part_itemWpnBarrelInfo = new TStringArray;
						part_itemWpnBarrelInfo.Split(",", a_part_itemWpnBarrelInfo);
						if(wpn.PushCartridgeToChamber(a_part_itemWpnBarrelInfo[0].ToInt(), 0.0, a_part_itemWpnBarrelInfo[1]))
						{
							//Print("Loaded Ammo to Chamber");
							didChamberAction = true;
						}
						else
						{
							//Print("NOT Loaded Ammo to Chamber");
						}
					}
				}
				
				string itemWpnInternalMagInfo = item.itemWpnInternalMagInfo;
				
				TStringArray a_itemWpnInternalMagInfo = new TStringArray;
				itemWpnInternalMagInfo.Split("|", a_itemWpnInternalMagInfo);
				for (int ib = 0; ib < a_itemWpnInternalMagInfo.Count(); ib++)
				{
					string part_itemWpnInternalMagInfo = a_itemWpnInternalMagInfo.Get(ib);
					if(part_itemWpnInternalMagInfo != "")
					{
						TStringArray a_part_itemWpnInternalMagInfo = new TStringArray;
						part_itemWpnInternalMagInfo.Split(",", a_part_itemWpnInternalMagInfo);
						if(wpn.PushCartridgeToInternalMagazine(a_part_itemWpnInternalMagInfo[0].ToInt(), 0.0, a_part_itemWpnInternalMagInfo[1]))
						{
							//Print("Loaded Ammo to intenal Mag");
							didChamberAction = true;
						}
						else
						{
							//Print("NOT Loaded Ammo to intenal Mag");
						}
					}
				}
				
				if(didChamberAction)
				{
					if (g_Game.IsServer())
						wpn.RandomizeFSMState();
						
					wpn.Synchronize();
					
					/*
					RandomizeFSMState();
					Synchronize();
					*/
				}
				
				
				
				//PushCartridgeToChamber(int muzzleIndex, float ammoDamage, string ammoTypeName);
			} else {
				//Print("Item is NOT Weapon");
			}
			
			if(new_item.HasQuantity()) {
				new_item.SetQuantity( item.itemQuantity );
			}
			new_item.SetLiquidType(item.itemLiquidType);
			
			if(item.itemLiquidType >= 1 && item.itemLiquidType <= 128) {
				BloodContainerBase bloodBag = BloodContainerBase.Cast(new_item);
				bloodBag.SetBloodTypeVisible(true);
			}
			
			if(item.itemHasEnergy)
			{
				new_item.m_EM.SetEnergy(item.itemEnergy);
			}
			
			if(new_item.IsAmmoPile()) {
				Magazine mgzn = Magazine.Cast(new_item);
				mgzn.ServerSetAmmoCount(item.itemAmmoQuantity);
			}
			
			if(item.itemType == "magazine") {
				bool is_single_or_server = !GetGame().IsMultiplayer() || GetGame().IsServer();
				if (is_single_or_server)
				{
					Magazine magazine_check2 = Magazine.Cast(new_item);
					magazine_check2.ServerSetAmmoCount(0);
					
					
					array<string> itemMagInhalt = item.itemMagInhalt;
					
					for (int ac = 0; ac < itemMagInhalt.Count(); ac++)
					{
						string part_itemMagInfo = itemMagInhalt.Get(ac);
						if(part_itemMagInfo != "")
						{
							TStringArray a_part_itemMagInfo = new TStringArray;
							part_itemMagInfo.Split(",", a_part_itemMagInfo);
													
							if ( magazine_check2.ServerStoreCartridge(0.0, a_part_itemMagInfo[1]))
							{
								//Print("Stored Ammo in Mag");
							}
						}
					}
					magazine_check2.SetSynchDirty();
				}
			}
						
			if(new_item.IsFood()) {
				Edible_Base new_item_food = Edible_Base.Cast(new_item);
				new_item_food.ChangeFoodStage(item.itemFoodstage);
			}

			new_item.SetHealth(item.itemHealth);
			
			
			new_item.SetTemperature(item.itemTemp);
			
			
			new_item.SetWet(item.itemWetness);
			
			foreach(tofuvStorageObj childitem : item.itemChildren) {
				vrestore(childitem, new_item, player);
			}
		}
		else
		{
			
			if(!(ntarget.IsWeapon() && item.itemType == "magazine"))
			{
				Print("[vStorage] !!!!!!!!!!!!!! Failed creating item "+item.itemName+" :");
				Print("[vStorage] DEBUG " + item.itemName + " in Parent " + ntarget.GetType());
				Print("[vStorage] DEBUG " + item.itemIdx + " item.itemIdx ");
				Print("[vStorage] DEBUG " + item.itemRow + " item.itemRow ");
				Print("[vStorage] DEBUG " + item.itemCol + " item.itemCol ");
				Print("[vStorage] DEBUG " + item.itemFliped + " item.itemFliped ");
				itemFailed = true;
				
				if(player && player.GetIdentity())
					g_Game.SendMessage(false,player.GetIdentity(),"WARNING", item.itemName+ " MIGHT NOT BE CREATED!",5,2,false,false,"",0,0);
				
				return false;
			}
		}
		
		return true;
		
	}
	
	void vrestore_drugexchange(tofuvStorageObj item, Object target_object)
	{
		
		EntityAI ntarget = EntityAI.Cast( target_object );
		ItemBase new_item;
		vector position;
		
		auto objects = new array<Object>;
		GetGame().GetObjectsAtPosition3D( target_object.GetPosition(), 2, objects, NULL );
		foreach ( Object obj: objects ) {
			if(obj.IsMan()) {
				position = obj.GetPosition();
				break;
			}
		}
		
		switch(item.itemName)
		{
			case "CP_CannabisSeedsPackSkunk":
				new_item = ItemBase.Cast(GetGame().CreateObject("CP_CannabisBrickSkunk", position));
			break;
			
			case "CP_CannabisSeedsPackBlue":
				new_item = ItemBase.Cast(GetGame().CreateObject("CP_CannabisBrickBlue", position));
			break;
			
			case "CP_CannabisSeedsPackKush":
				new_item = ItemBase.Cast(GetGame().CreateObject("CP_CannabisBrickKush", position));
			break;
			
			case "CP_CannabisSeedsPackStardawg":
				new_item = ItemBase.Cast(GetGame().CreateObject("CP_CannabisBrickStardawg", position));
			break;
			
			case "CP_CannabisSeedsPackFuture":
				new_item = ItemBase.Cast(GetGame().CreateObject("CP_CannabisBrickFuture", position));
			break;
			
			case "CP_CannabisSeedsPackS1":
				new_item = ItemBase.Cast(GetGame().CreateObject("CP_CannabisBrickS1", position));
			break;
			
			case "CP_CannabisSeedsPackNomad":
				new_item = ItemBase.Cast(GetGame().CreateObject("CP_CannabisBrickNomad", position));
			break;
			
			case "CP_CannabisSeedsPackBlackFrost":
				new_item = ItemBase.Cast(GetGame().CreateObject("CP_CannabisBrickBlackFrost", position));
			break;
			
			case "DP_CocaSeedsPack":
				new_item = ItemBase.Cast(GetGame().CreateObject("DP_CocaBrick", position));
			break;
			
		}
	}
	
};
