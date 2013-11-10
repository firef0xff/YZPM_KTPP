#pragma hdrstop

#include "Tabs.h"
#pragma package(smart_init)

		Tab::Tab	(void)
{
tab=0;
last_tab=false;
}
		Tab::Tab	(const Tab &r)
{
tab=r.tab;
last_tab=r.last_tab;
}
		Tab::~Tab	(void)
{
if (tab)
	{
	tab->Tag=-1;
	delete tab;
	}
}

		TreeTab::TreeTab	(void):Tab(),module(0)
{
}
		TreeTab::TreeTab	(const TreeTab &r):Tab(r)
{
module=r.module;
}
		TreeTab::~TreeTab	(void)
{
if (module)
	{
	module->Parent=0;
	delete module;
	}
}

		TechTab::TechTab	(void):Tab(),module(0)
{
}
		TechTab::TechTab	(const TechTab &r):Tab(r)
{
module=r.module;
}
		TechTab::~TechTab	(void)
{
if (module)
	{
	module->Parent=0;
	delete module;
	}
}

		TechViewTab::TechViewTab	(void):Tab(),module(0)
{}
		TechViewTab::TechViewTab	(const TechViewTab &r):Tab(r)
{
module=r.module;
}
		TechViewTab::~TechViewTab	(void)
{
if (module)
	{
	module->Parent=0;
	delete module;
	}
}

		SearchTab::SearchTab	(void):Tab(),module(0)
{}
		SearchTab::SearchTab	(const SearchTab &r):Tab(r)
{
module=r.module;
}
		SearchTab::~SearchTab	(void)
{
if (module)
	{
	module->Parent=0;
	delete module;
	}
}

		ProcessingTab::ProcessingTab	(void):Tab(),module(0)
{}
		ProcessingTab::ProcessingTab	(const ProcessingTab &r):Tab(r)
{
	module=r.module;
}
		ProcessingTab::~ProcessingTab	(void)
{
if (module)
	{
	module->Parent=0;
	delete module;
	}
}

		OrdersTab::OrdersTab	(void):Tab(),module(0)
{}
		OrdersTab::OrdersTab	(const OrdersTab &r):Tab(r)
{
	module=r.module;
}
		OrdersTab::~OrdersTab	(void)
{
if (module)
	{
	module->Parent=0;
	delete module;
	}
}

		ManufactureTab::ManufactureTab	(void):Tab(),module(0)
{}
		ManufactureTab::ManufactureTab	(const ManufactureTab &r):Tab(r)
{
	module=r.module;
}
		ManufactureTab::~ManufactureTab	(void)
{
	if (module)
	{
		module->Parent=0;
		delete module;
	}
}
