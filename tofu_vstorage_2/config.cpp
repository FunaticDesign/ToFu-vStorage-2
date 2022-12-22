class CfgPatches
{
	class ToFuVStorage
	{
		units[] = {
			"tofu_vstorage_barrel_ammo",
			"tofu_vstorage_barrel_food",
			"tofu_vstorage_barrel_base",
			"tofu_vstorage_barrel_clothing",
			"tofu_vstorage_barrel_other",
			"tofu_vstorage_barrel_transport",
			"tofu_vstorage_barrel_medic",
			"tofu_vstorage_barrel_important",
			"tofu_vstorage_barrel_event",
			"tofu_vstorage_barrel_tools",
			"tofu_vstorage_barrel_weapons",
			"tofu_vstorage_q_barrel_express"
		};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {
			"DZ_Data",
			"DZ_Scripts",
			"JM_CF_Scripts"
		};
	};
};
class CfgMods
{
	class ToFuVStorage
	{
		dir = "tofu_vstorage_2";
		picture = "";
		action = "";
		hideName = 0;
		hidePicture = 0;
		name = "ToFuVirtualStorage2";
		credits = "Funatic / inkihh";
		author = "";
		authorID = "0";
		version = "2.0";
		extra = 0;
		type = "mod";
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"tofu_vstorage_2/scripts/3_Game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"tofu_vstorage_2/Scripts/4_World"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"tofu_vstorage_2/Scripts/5_Mission"};
			};
		};
	};
};
class CfgVehicles
{	
	class Barrel_ColorBase;
	class tofu_vstorage_barrel: Barrel_ColorBase
	{
		scope=0;
		displayName="vStorage2 Barrel";
		descriptionShort="An experimental barrel that stores content in a new way.";
		class Cargo
		{
			itemsCargoSize[]={10,50};
		};
		inventorySlot[]={};
		
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=10000000;
				};
			};
		};
		
	};
	
			
	class tofu_vstorage_q_barrel_express: tofu_vstorage_barrel
	{
		scope=2;
		displayName="Express vStorage v2 Barrel";
		/*
		hiddenSelectionsTextures[] = 
		{
			"tofu_vstorage_2\Data\your_texture.paa"
		};
		*/
		
	};
	
	class tofu_vstorage_barrel_ammo: tofu_vstorage_barrel
	{
		scope=2;
		displayName="Ammo vStorage v2 Barrel";
		/*
		hiddenSelectionsTextures[] = 
		{
			"tofu_vstorage_2\Data\your_texture.paa"
		};
		*/
		
	};
			
	class tofu_vstorage_barrel_food: tofu_vstorage_barrel
	{
		scope=2;				
		displayName="Food vStorage v2 Barrel";
		/*
		hiddenSelectionsTextures[] = 
		{
			"tofu_vstorage_2\Data\your_texture.paa"
		};
		*/
		
	};
	
	class tofu_vstorage_barrel_base: tofu_vstorage_barrel
	{
		scope=2;			
		displayName="Base vStorage v2 Barrel";
		/*
		hiddenSelectionsTextures[] = 
		{
			"tofu_vstorage_2\Data\your_texture.paa"
		};
		*/
	};
	
	class tofu_vstorage_barrel_clothing: tofu_vstorage_barrel
	{
		scope=2;				
		displayName="Clothing vStorage v2 Barrel";
		/*
		hiddenSelectionsTextures[] = 
		{
			"tofu_vstorage_2\Data\your_texture.paa"
		};
		*/
		
	};
	
	class tofu_vstorage_barrel_other: tofu_vstorage_barrel
	{
		scope=2;				
		displayName="Other vStorage v2 Barrel";
		/*
		hiddenSelectionsTextures[] = 
		{
			"tofu_vstorage_2\Data\your_texture.paa"
		};
		*/
		
	};
	
	class tofu_vstorage_barrel_transport: tofu_vstorage_barrel
	{
		scope=2;				
		displayName="Transport vStorage v2 Barrel";
		/*
		hiddenSelectionsTextures[] = 
		{
			"tofu_vstorage_2\Data\your_texture.paa"
		};
		*/
		
	};
	
	class tofu_vstorage_barrel_medic: tofu_vstorage_barrel
	{
		scope=2;				
		displayName="Medic vStorage v2 Barrel";
		/*
		hiddenSelectionsTextures[] = 
		{
			"tofu_vstorage_2\Data\your_texture.paa"
		};
		*/
		
	};
	
	class tofu_vstorage_barrel_important: tofu_vstorage_barrel
	{
		scope=2;				
		displayName="Important vStorage v2 Barrel";
		/*
		hiddenSelectionsTextures[] = 
		{
			"tofu_vstorage_2\Data\your_texture.paa"
		};
		*/
		
	};
	
	class tofu_vstorage_barrel_event: tofu_vstorage_barrel
	{
		scope=2;				
		displayName="Event vStorage v2 Barrel";
		/*
		hiddenSelectionsTextures[] = 
		{
			"tofu_vstorage_2\Data\your_texture.paa"
		};
		*/
		
	};
	
	class tofu_vstorage_barrel_tools: tofu_vstorage_barrel
	{
		scope=2;			
		displayName="Tools vStorage v2 Barrel";
		/*
		hiddenSelectionsTextures[] = 
		{
			"tofu_vstorage_2\Data\your_texture.paa"
		};
		*/
	};
	
	class tofu_vstorage_barrel_weapons: tofu_vstorage_barrel
	{
		scope=2;
		displayName="Weapons vStorage v2 Barrel";
		/*
		hiddenSelectionsTextures[] = 
		{
			"tofu_vstorage_2\Data\your_texture.paa"
		};
		*/
	};
};
