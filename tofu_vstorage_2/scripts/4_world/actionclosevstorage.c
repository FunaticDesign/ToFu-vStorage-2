class ActionCloseVStorage: ActionInteractBase
{
	void ActionCloseVStorage()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}
		
	override string GetText()
	{
		return "Close and save content";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object target_object = target.GetObject();
		if ( target_object.IsItemBase() )
		{
			tofu_vstorage_barrel ntarget = tofu_vstorage_barrel.Cast( target_object );
			if( ntarget )
			{
				if ( !ntarget.IsLocked() && ntarget.IsOpen() )
				{
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
					
					
					return true;
				}
			}
		}
		return false;
	}
	
	override void OnExecuteServer( ActionData action_data )
	{
		Object target_object = action_data.m_Target.GetObject();
		tofu_vstorage_barrel thebarrel = tofu_vstorage_barrel.Cast( target_object );

		if(!thebarrel) return;
		
		if(thebarrel.GetType() == "tofu_vstorage_q_barrel_express")
		{
		
			string steamid = action_data.m_Player.GetIdentity().GetPlainId();
			thebarrel.vclose(steamid);
		}
		else
		{
			thebarrel.vclose();
		}

		
	}
	
	override void OnEndServer( ActionData action_data )
	{
		Object target_object = action_data.m_Target.GetObject();
		Barrel_ColorBase ntarget = Barrel_ColorBase.Cast( target_object );
		if( ntarget )
		{
			ntarget.SoundSynchRemoteReset();
		}
	}
}
