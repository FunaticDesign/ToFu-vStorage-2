modded class MissionGameplay
{
	void MissionGameplay()
	{
		GetRPCManager().AddRPC("ToFuVStorage", "ClientStoreVSTConfig", this, SingeplayerExecutionType.Client);
		GetRPCManager().SendRPC("ToFuVStorage", "GetVSTServerConfig", null, true, null);
	}

	void ClientStoreVSTConfig(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        ref Param1<ref VST_Config> data;
        if (type == CallType.Client)
		{
			if (!ctx.Read(data)) return;
			g_Game.SetVSTConfig( data.param1 );			
		}
    }
};