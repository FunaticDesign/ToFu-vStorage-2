class VST_Config
{	
		
	static const string CONFIG_ROOT = "$profile:ToFuVStorage/";
    static const string FULLPATH = "$profile:ToFuVStorage/VST_Config.json";
	
	private int auto_close_random_seconds_min = 120;
	private int auto_close_random_seconds_max = 240;

	private ref array<string> Blacklist;
	private ref array<string> Admins;
	
	void VST_Config()
	{
		if (!GetGame().IsServer()) return;
		
		if (!FileExist(CONFIG_ROOT))
        {
            MakeDirectory(CONFIG_ROOT);
        }

        if (!FileExist(FULLPATH))
        {
            Default();
            return; 
        }

        Load();
    }

	void Load()
    {
		JsonFileLoader<VST_Config>.JsonLoadFile(FULLPATH, this);
		Save();
    }

	
	protected void Save()
    {
        JsonFileLoader<VST_Config>.JsonSaveFile(FULLPATH, this);
    }

	protected void Default()
    {
		
        Blacklist = new array<string>;
		Blacklist.Insert("WrittenNote");
		Blacklist.Insert("VehicleKeyBase");
		Blacklist.Insert("MCK_CarKey_Base");
		Blacklist.Insert("ChickenBreastMeat");
		Blacklist.Insert("GoatSteakMeat");
		Blacklist.Insert("SheepSteakMeat");
		Blacklist.Insert("PigSteakMeat");
		Blacklist.Insert("WolfSteakMeat");
		Blacklist.Insert("BearSteakMeat");
		Blacklist.Insert("DeerSteakMeat");
		Blacklist.Insert("CowSteakMeat");
		Blacklist.Insert("Lard");
		Blacklist.Insert("Carp");
		Blacklist.Insert("Mackerel");
		
		Admins = new array<string>;
		Blacklist.Insert("76561198009118169");
		
		Save();
	}

	array<string> Get_Blacklist()
	{
		if(Blacklist.Count() < 1)
		{
			Blacklist = new array<string>;
			Blacklist.Insert("WrittenNote");
			Blacklist.Insert("VehicleKeyBase");
			Blacklist.Insert("MCK_CarKey_Base");
			Blacklist.Insert("ChickenBreastMeat");
			Blacklist.Insert("GoatSteakMeat");
			Blacklist.Insert("SheepSteakMeat");
			Blacklist.Insert("PigSteakMeat");
			Blacklist.Insert("WolfSteakMeat");
			Blacklist.Insert("BearSteakMeat");
			Blacklist.Insert("DeerSteakMeat");
			Blacklist.Insert("CowSteakMeat");
			Blacklist.Insert("Lard");
			Blacklist.Insert("Carp");
			Blacklist.Insert("Mackerel");
		}
		return Blacklist;
	}
	
	array<string> Get_Admins()
	{
		return Admins;
	}

	int Get_auto_close_random_seconds_min()
	{
		return auto_close_random_seconds_min;
	}

	int Get_auto_close_random_seconds_max()
	{
		return auto_close_random_seconds_max;
	}

	
};