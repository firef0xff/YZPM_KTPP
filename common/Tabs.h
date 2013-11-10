

#ifndef TabsH
#define TabsH

#include "BomTree.h"
#include "technology.h"
#include "TechnologyView.h"
#include "SearchModule.h"
#include "Izd_Unroll.h"
#include "Orders.h"
#include "manufacture.h"
class Tab
    {
    public:
    Tab(void);
    Tab(const Tab &);
    virtual ~Tab(void);
    virtual bool CanClose(void){return true;};
    virtual String TrueClassName (void)const{return "Tab";};
    bool ItTrueClassName (void)const{return TrueClassName()=="Tab"?true:false;}

    TTabSheet     *tab;
    bool         last_tab;
    };
class TreeTab:public Tab
    {
    public:
    TreeTab(void);
    TreeTab(const TreeTab &);
    ~TreeTab(void);
    bool CanClose(void){return true;};
    String TrueClassName (void)const{return "TreeTab";};
    bool ItTrueClassName (void)const{return TrueClassName()=="TreeTab"?true:false;}

    TSpTree        *module;
    };
class TechTab:public Tab
    {
    public:
    TechTab(void);
    TechTab(const TechTab &);
    ~TechTab(void);
    bool CanClose(void){return module->Close_teh();};
    String TrueClassName (void)const{return "TechTab";};
    bool ItTrueClassName (void)const{return TrueClassName()=="TechTab"?true:false;}

    TTechWnd    *module;
    };
class TechViewTab:public Tab
    {
    public:
    TechViewTab(void);
    TechViewTab(const TechViewTab &);
    ~TechViewTab(void);
    bool CanClose(void){return true;};
    String TrueClassName (void)const{return "TechViewTab";};
    bool ItTrueClassName (void)const{return TrueClassName()=="TechViewTab"?true:false;}

    TTechView   *module;
    };
class SearchTab:public Tab
    {
    public:
    SearchTab(void);
    SearchTab(const SearchTab &);
    ~SearchTab(void);
    bool CanClose(void){return true;};
    String TrueClassName (void)const{return "SearchTab";};
    bool ItTrueClassName (void)const{return TrueClassName()=="SearchTab"?true:false;}

    TSearch   *module;
    };
class ProcessingTab:public Tab
    {
    public:
    ProcessingTab(void);
    ProcessingTab(const ProcessingTab &);
    ~ProcessingTab(void);
    bool CanClose(void){return true;};
    String TrueClassName (void)const{return "ProcessingTab";};
    bool ItTrueClassName (void)const{return TrueClassName()=="ProcessingTab"?true:false;}

    TList_Editor   *module;
    };
class OrdersTab:public Tab
    {
    public:
    OrdersTab(void);
    OrdersTab(const OrdersTab &);
    ~OrdersTab(void);
    bool CanClose(void){return true;};
    String TrueClassName (void)const{return "OrdersTab";};
    bool ItTrueClassName (void)const{return TrueClassName()=="OrdersTab"?true:false;}

    TOrders_editor   *module;
    };
class ManufactureTab:public Tab
    {
    public:
    ManufactureTab(void);
    ManufactureTab(const ManufactureTab &);
    ~ManufactureTab(void);
    bool CanClose(void){return true;};
    String TrueClassName (void)const{return "ManufactureTab";};
    bool ItTrueClassName (void)const{return TrueClassName()=="ManufactureTab"?true:false;}

    TManufactureControl   *module;
    };

#endif
