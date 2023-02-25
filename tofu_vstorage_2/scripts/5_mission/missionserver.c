modded class MissionServer
{
	ref VST_Config m_VST_Config;
	
	void MissionServer()
	{
		GetRPCManager().AddRPC("ToFuVStorage", "GetVSTServerConfig", this, SingeplayerExecutionType.Server);
	}
	
	override void OnInit()
    {
        super.OnInit();
               
        m_VST_Config = new VST_Config;
        g_Game.SetVSTConfig(m_VST_Config);
    }
	
	void GetVSTServerConfig(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
    {
        if (type == CallType.Server && sender != null)                    
            GetRPCManager().SendRPC("ToFuVStorage", "ClientStoreVSTConfig", new Param1<ref VST_Config>( m_VST_Config ), true, sender);
    }
	
}