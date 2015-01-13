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
    
	std::string XmlPrinter::visitBegin(XmlNode *node)
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
		head.append(">").append(node->getValue());
        
        return head;
    }
    
	std::string XmlPrinter::visitEnd(XmlNode *node)
    {
        CCASSERT(node, "The node to visit can't be null.");
        string tail;
		tail.clear();
        tail.append("</").append(node->getName()).append(">");
        
        return tail;
    }
    
	std::string XmlPrinter::print(framework::XmlNode *node, bool needVersion)
    {
        if (!node) {
            return nullptr;
        }
        string xml;
		xml.clear();
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
        
        return xml;
    }
    
    XmlPrettyPrinter::XmlPrettyPrinter()
        : _counter(-1)
    {
    }
    
	std::string XmlPrettyPrinter::printTabs(int tabNum)
    {
        string tabs;
        for (int i = 0; i < tabNum; ++i) {
            tabs.append("\t");
        }
        return tabs;
    }
    
	std::string XmlPrettyPrinter::visitBegin(framework::XmlNode *node)
    {
		CCASSERT(node, "The node to visit can't be null.");
		++_counter;
		string head;
		head.append(this->printTabs(_counter)).append("<");
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
		head.append(">").append("\n").append(this->printTabs(_counter + 1)).append(node->getValue()).append("\n");

		return head;
    }
    
	std::string XmlPrettyPrinter::visitEnd(framework::XmlNode *node)
    {
		CCASSERT(node, "The node to visit can't be null.");
		string tail;
		tail.clear();
		tail.append(this->printTabs(_counter));
		tail.append("</").append(node->getName()).append(">\n");
		--_counter;

		return tail;
    }

	std::string XmlPrettyPrinter::print(framework::XmlNode *node, bool needVersion)
	{
		if (!node) {
			return nullptr;
		}
		string xml;
		xml.clear();
		if (needVersion) {
			xml.append("<?xml version=\"1.0\"?>\n");
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

		return xml;
	}
}