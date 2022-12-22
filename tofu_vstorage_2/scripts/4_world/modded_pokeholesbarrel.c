modded class PokeHolesBarrel
{	
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
    {
        ItemBase parent = ingredients[0];

        if (!parent.IsEmpty())
			return false;

		if(parent.IsKindOf("tofu_vstorage_barrel"))
			return false;

		return true;
    }
};
