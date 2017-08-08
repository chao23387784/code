#include "crttreeitem.h"
#include "crtproject.h"
#include "crtcontroller.h"
#include "crtloop.h"
#include "crtbuilding.h"
#include "crtlayer.h"
#include "crtdevice.h"
#include "common.h"

CrtTreeItem::CrtTreeItem()
{

}

CrtTreeItem::~CrtTreeItem()
{
    parent = NULL;
    if(children.count()>0)
    {
        foreach(CrtTreeItem* item,children)
        {
            SAFE_DELETE(item)
        }
    }
}

void CrtTreeItem::addChild(CrtTreeItem *child)
{
    children.append(child);
}

CrtTreeItem *CrtTreeItem::childAt(int nIndex)
{
    if(children.count()<=0 || nIndex >= children.count() || nIndex < 0)
        return NULL;
    return children[nIndex];
}

void CrtTreeItem::removeChild(int nIndex)
{
    if(children.count()<=0 || nIndex >= children.count() || nIndex < 0)
        return;
    CrtTreeItem* item = children[nIndex];
    children.removeAt(nIndex);
    SAFE_DELETE(item)
}

int CrtTreeItem::indexOf(const CrtTreeItem *child)
{
    if(child != NULL)
    {
        return children.indexOf(const_cast<CrtTreeItem*>(child));
    }
    return -1;
}

void CrtTreeItem::load(CrtObject *obj, int type)
{
    if(obj != NULL)
    {
        if(type == 0)
        {
            if(!obj->Type().compare("project"))
            {
                CrtProject* root = (CrtProject*)obj;
                for(int i=0;i<root->m_lstController.count();i++)
                {
                    CrtTreeItem* item = new CrtTreeItem();
                    item->setParent(this);
                    item->setData(root->m_lstController[i]);
                    item->setRow(i);
                    item->setColumn(0);
                    addChild(item);
                    item->load(item->Data(),type);
                }
            }
            else if(!obj->Type().compare("controller"))
            {
                CrtController* root = (CrtController*)obj;
                for(int i=0;i<root->m_lstLoop.count();i++)
                {
                    CrtTreeItem* item = new CrtTreeItem();
                    item->setParent(this);
                    item->setData(root->m_lstLoop[i]);
                    item->setRow(i);
                    item->setColumn(0);
                    addChild(item);
                    item->load(item->Data(),type);
                }
            }
            else if(!obj->Type().compare("loop"))
            {
                CrtLoop* root = (CrtLoop*)obj;
                for(int i=0;i<root->m_lstDevice.count();i++)
                {
                    CrtTreeItem* item = new CrtTreeItem();
                    item->setParent(this);
                    item->setData(root->m_lstDevice[i]);
                    item->setRow(i);
                    item->setColumn(0);
                    addChild(item);
                }
            }
        }
        else if(type == 1)
        {
            if(!obj->Type().compare("project"))
            {
                CrtProject* root = (CrtProject*)obj;
                for(int i=0;i<root->m_lstBuilding.count();i++)
                {
                    CrtTreeItem* item = new CrtTreeItem();
                    item->setParent(this);
                    item->setData(root->m_lstBuilding[i]);
                    item->setRow(i);
                    item->setColumn(0);
                    addChild(item);
                    item->load(item->Data(),type);
                }
            }
            else if(!obj->Type().compare("building"))
            {
                CrtBuilding* root = (CrtBuilding*)obj;
                for(int i=0;i<root->m_lstLayer.count();i++)
                {
                    CrtTreeItem* item = new CrtTreeItem();
                    item->setParent(this);
                    item->setData(root->m_lstLayer[i]);
                    item->setRow(i);
                    item->setColumn(0);
                    addChild(item);
                }
            }
            else if(!obj->Type().compare("layer"))
            {
                CrtLayer* root = (CrtLayer*)obj;
                for(int i=0;i<root->m_lstDevice.count();i++)
                {
                    CrtTreeItem* item = new CrtTreeItem();
                    item->setParent(this);
                    item->setData(root->m_lstDevice[i]);
                    item->setRow(i);
                    item->setColumn(0);
                    addChild(item);
                }
            }
        }
    }
}

