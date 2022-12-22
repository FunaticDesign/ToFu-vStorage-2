modded class ActionConstructor
{
    override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);
		actions.Insert(ActionOpenVStorage);
		actions.Insert(ActionCloseVStorage);
		actions.Insert(ActionUnclaimVStorage);
	}
}