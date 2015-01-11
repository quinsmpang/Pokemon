#include "XmlPrinter.h"
#include "XmlElement.h"
#include "XmlNode.h"
#include "../base/RefString.h"
#include <string>

using namespace std;

namespace framework {
    XmlPrinter::XmlPrinter()
    {
    }
    
    const char *XmlPrinter::visitBegin(XmlNode *node)
    {
        CCASSERT(node, "The node to visit can't be null.");
        string head("<");
        head.append(node->getName());
        Map *pAttrs = node->getAttributes();
        if (pAttrs->getLength() > 0) {
            Vector *pAttrKeys = pAttrs->allKeys();
            int len = pAttrKeys->getLength();
            for (int i = 0; i < len; ++i) {
                string key = ((RefString*)pAttrKeys->objectAt(i))->getCString();
                string value = ((XmlElement*)pAttrs->objectForKey(key))->stringValue();
                head.append(" ").append(key).append("=").append("\"").append(value).append("\"");
            }
        }
        head.append(">");
        
        return head.c_str();
    }
    
    const char *XmlPrinter::visitEnd(XmlNode *node)
    {
        CCASSERT(node, "The node to visit can't be null.");
        string tail;
        tail.append(node->getValue()).append("</").append(node->getName()).append(">");
        
        return tail.c_str();
    }
    
    const char *XmlPrinter::print(framework::XmlNode *node, bool needVersion)
    {
        if (!node) {
            return nullptr;
        }
        string xml;
        if (needVersion) {
            xml.append("<?xml version=\"1.0\"?>");
        }
        xml.append(this->visitBegin(node));
        Vector *pChildren = node->getChildren();
        int len = pChildren->getLength();
        XmlNode *pChild = nullptr;
        for (int i = 0; i < len; ++i) {
            pChild = (XmlNode*)pChildren->objectAt(i);
            xml.append(this->print(pChild));
        }
        xml.append(this->visitEnd(node));
        
        return xml.c_str();
    }
    
    XmlPrettyPrinter::XmlPrettyPrinter()
        : _counter(0)
    {
    }
    
    const char *XmlPrettyPrinter::printTabs(int tabNum)
    {
        string tabs;
        for (int i = 0; i < tabNum; ++i) {
            tabs.append("\t");
        }
        return tabs.c_str();
    }
    
    const char *XmlPrettyPrinter::visitBegin(framework::XmlNode *node)
    {
        CCASSERT(node, "The node to visit can't be null.");
        string head;
        head.append(this->printTabs(_counter));
        head.append(XmlPrinter::visitBegin(node));
        head.append("\n");
        ++_counter;
        
        return head.c_str();
    }
    
    const char *XmlPrettyPrinter::visitEnd(framework::XmlNode *node)
    {
        CCASSERT(node, "The node to visit can't be null.");
        string tail;
        if (node->getValue().size() > 0) {
            tail.append(this->printTabs(_counter + 1));
            tail.append(node->getValue()).append("\n");
        }
        tail.append(this->printTabs(_counter));
        tail.append("</").append(node->getName()).append(">");
        --_counter;
        
        return tail.c_str();
    }
}