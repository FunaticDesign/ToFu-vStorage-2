modded class DayZGame
{	
	private ref VST_Config m_VST_Config;
	
    ref VST_Config GetVSTConfig()
    {
        if (!m_VST_Config)
        {
            SetVSTConfig(new VST_Config);
        }
        
	    return m_VST_Config;
    }

    void SetVSTConfig(VST_Config config)
	{
		m_VST_Config = config;
	}
    
};
