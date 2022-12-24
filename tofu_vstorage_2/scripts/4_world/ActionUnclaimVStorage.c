class ActionUnclaimVStorage: ActionInteractBase
{
		
	void ActionUnclaimVStorage()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.OpenHood;
	}

	override string GetText()
	{
		return "Unclaim Barrel";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object target_object = target.GetObject();
		if ( target_object.IsItemBase() )
		{
			Barrel_ColorBase ntarget = Barrel_ColorBase.Cast( target_object );
			if( ntarget )
			{
				
				if(ntarget.GetType()=="tofu_vstorage_q_barrel_express")
				{
				
					string steamid;
					
					tofu_vstorage_barrel qbarrel = tofu_vstorage_barrel.Cast( target_object );
					
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
					
					if(qbarrel.canInteractAdmin(steamid))
					{
						return true;
					}
					
					if( !ntarget.IsLocked() && ntarget.IsOpen() )
					{
						
						if(qbarrel.canInteract(steamid))
						{
							return true;
						}
						else
						{
							return false;
						}
					}
				}
			}
		}
		return false;
	}

		
	
	override void OnExecuteServer( ActionData action_data )
	{
		Object target_object = action_data.m_Target.GetObject();
		tofu_vstorage_barrel qbarrel = tofu_vstorage_barrel.Cast( target_object );
		qbarrel.Unclaim();
	}
	
	
}