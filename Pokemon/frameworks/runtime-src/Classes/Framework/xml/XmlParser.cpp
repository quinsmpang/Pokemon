#include "XmlParser.h"
#include "XmlElement.h"
#include "XmlNode.h"
#include "../containers/Map.h"
#include "../containers/Vector.h"

using namespace cocos2d;
using namespace tinyxml2;

namespace framework {
    XmlParser::XmlParser()
    {
    }
    
    XmlNode *XmlParser::parseString(const std::string &xmlStr)
    {
        tinyxml2::XMLDocument doc;
        doc.Parse(xmlStr.c_str());
        if (doc.ErrorID()) {
            CCLOG("Invalid XML content.");
            return nullptr;
        }
        XMLElement *root = doc.RootElement();
        XmlNode *pNode = this->parseToXmlNode(root);
        
        return pNode;
    }
    
    XmlNode *XmlParser::parseFile(const std::string &xmlPath)
    {
        std::string buffer;
        Data data = FileUtils::getInstance()->getDataFromFile(xmlPath.c_str());
        unsigned char *lpFileData = data.getBytes();
        unsigned long fileSize = data.getSize();
        if (lpFileData) {
            for (unsigned long i = 0; i < fileSize; ++i) {
                buffer.push_back(lpFileData[i]);
            }
            delete[] lpFileData;
        }
        return this->parseString(buffer);
    }
    
    XmlNode *XmlParser::parseToXmlNode(tinyxml2::XMLElement *elem)
    {
        auto pNode = XmlNode::create(elem->Name());
        // value
        pNode->setValue(elem->Value());
        // attributes
        auto rootAttrs = Map::create();
        for (auto attr = elem->FirstAttribute(); attr->Next(); attr = attr->Next()) {
            rootAttrs->setStringForKey(attr->Value(), attr->Name());
        }
        pNode->setAttributes(rootAttrs);
        // add child nodes recursively.
        for (auto child = elem->FirstChildElement(); child->NextSiblingElement(); child = child->NextSiblingElement()) {
            XmlNode *pChild = this->parseToXmlNode(child);
            pNode->appendChildNode(pChild);
        }
        
        return pNode;
    }
}