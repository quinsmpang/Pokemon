/******************************
 Description: XML parser.
 Author: M.Wan
 Date: 01/11/2015
 ******************************/

#ifndef __XML_XMLPARSER__
#define __XML_XMLPARSER__

#include "cocos2d.h"
#include "../base/Macros.h"
#include "tinyxml2/tinyxml2.h"
#include <string>

namespace framework {
    class XmlNode;
    
    class XmlParser
    {
        /**
         * XmlParser is a singleton.
         */
        SINGLETON(XmlParser);
    public:
        /**
         * Parse the xml to XmlNode.
         *
         * @param xmlStr XML string.
         *
         * @return Return xml node.
         */
        XmlNode *parseString(const std::string &xmlStr);
        
        /**
         * Parse the xml file to XmlNode.
         *
         * @param xmlPath XML file path.
         *
         * @return Return xml node.
         */
        XmlNode *parseFile(const std::string &xmlPath);
        
    private:
        XmlNode *parseToXmlNode(tinyxml2::XMLElement *elem);
    };
}

#endif /* defined(__XML_XMLPARSER__) */
