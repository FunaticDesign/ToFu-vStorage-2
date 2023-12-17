class ActionOpenVStorage: ActionInteractBase
{
	void ActionOpenVStorage()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.OpenHood;
	}

	override string GetText()
	{
		return "Open and load content";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object target_object = target.GetObject();
		if ( !target_object.IsItemBase() ) return false;

		tofu_vstorage_barrel ntarget = tofu_vstorage_barrel.Cast( target_object );
		if( !ntarget ) return false;
		
		if(ntarget.GetType() == "tofu_vstorage_q_barrel_express")
		{
			string steamid;
			if(GetGame().IsServer())
			{
				steamid = player.GetIdentity().GetPlainId();
			}
			else
			{
				if (GetGame().GetUserManager() && GetGame().GetUserManager().GetTitleInitiator()){
					steamid = GetGame().GetUserManager().GetTitleInitiator().GetUid();
				}
			}
			
			if(!ntarget.canInteract(steamid))
				return false;
		}
		
		
		if( !ntarget.IsLocked() && !ntarget.IsOpen() ) return true;
			
		return false;
	}
	
	override void OnExecuteServer( ActionData action_data )
	{
		
		Object target_object = action_data.m_Target.GetObject();
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		

		tofu_vstorage_barrel vbarrel = tofu_vstorage_barrel.Cast( target_object );
		string steamid = action_data.m_Player.GetIdentity().GetPlainId();
		
		array<EntityAI> illegal_items = new array<EntityAI>;
		vbarrel.GetInventory().EnumerateInventory(InventoryTraversalType.LEVELORDER, illegal_items);

		int count = illegal_items.Count();
		for (int ii = 0; ii < count; ii++)
		{
			EntityAI item_in_storage = illegal_items.Get(ii);
			if (item_in_storage)
			{
				if(g_Game.GetVSTConfig().Get_script_logging() == 1)
					Print("[vStorage]-----> FOUND ILLEGAL ITEM "+item_in_storage.GetType()+" IN VSTORAGE BARREL AT "+vbarrel.GetPosition());
			}
		}
		
		
		if(!vbarrel.vopen(action_data.m_Player, steamid ))
		{
			if(player && player.GetIdentity())
			{
				g_Game.SendMessage(false,player.GetIdentity(),"WARNING","Some bugged items where deleted or dropped on ground.",5,2,false,false,"",0,0);
			}
		}
	}
		
	
	
	
	
	override void OnEndServer( ActionData action_data )
	{
		
		Object target_object = action_data.m_Target.GetObject();

		Barrel_ColorBase ntarget = Barrel_ColorBase.Cast( target_object );
		if( ntarget )
			ntarget.SoundSynchRemoteReset();
		
		tofu_vstorage_barrel vbarrel = tofu_vstorage_barrel.Cast( target_object );
		
	}
}