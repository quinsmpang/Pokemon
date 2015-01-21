/******************************
 Description: XML nodes.
 Author: M.Wan
 Date: 01/11/2015
 ******************************/

#ifndef __XML_XMLNODE__
#define __XML_XMLNODE__

#include "cocos2d.h"
#include "../containers/Map.h"
#include "../containers/Vector.h"

namespace framework {
    class XmlNode : public cocos2d::Ref
    {
		friend class XmlParser;
    public:
        /**
         * XmlNode constructor.
         */
        XmlNode(const std::string &name);
        /**
         * XmlNode destructor.
         */
        virtual ~XmlNode();
        
        /**
         * Create xml node.
         *
         * @param name Node name.
         *
         * @return Return new XmlNode object.
         */
        static XmlNode *create(const std::string &name);
        /**
         * Create an xml node through string.
         *
         * @param xmlStr Xml string.
         *
         * @return Return a new xml node.
         */
        static XmlNode *createWithString(const std::string &xmlStr);
        /**
         * Create an xml node from xml file.
         *
         * @param xmlPath Xml file path.
         *
         * @return Return a new xml node.
         */
        static XmlNode *createWithFile(const std::string &xmlPath);
        
        /**
         * Get attribute collection.
         *
         * @return Return attribute map.
         */
        inline Map *getAttributes()
        {
            return _attributes;
        }
        /**
         * Get all xml child nodes.
         *
         * @return Return all child nodes.
         */
        inline Vector *getChildren()
        {
            return _childNodes;
        }
        /**
         * Get node name.
         *
         * @return Node name.
         */
        inline const std::string &getName()
        {
            return _nodeName;
        }
        /**
         * Set node name.
         *
         * @param name Node name.
         */
        inline void setName(const std::string &name);
        /**
         * Get node value.
         *
         * @return Node value.
         */
        inline const std::string &getValue()
        {
            return _nodeValue;
        }
        /**
         * Set node value.
         *
         * @param value Node value.
         */
        void setValue(const std::string &value);
        
        /**
         * Add new boolean attribute for the specified key.
         *
         * @param name Attribute name.
         * @param value Attribute value.
         */
        void putAttribute(const std::string &name, bool value);
        /**
         * Add new number attribute for the specified key.
         *
         * @param name Attribute name.
         * @param value Attribute value.
         */
        void putAttribute(const std::string &name, double value);
        /**
         * Add new string attribute for the specified key.
         *
         * @param name Attribute name.
         * @param value Attribute value.
         */
        void putAttribute(const std::string &name, const std::string &value);
        
        /**
         * Get boolean value of attribute for the specified name.
         *
         * @param name Attribute name.
         *
         * @return Boolean value of the attribute.
         */
        bool getBooleanAttribute(const std::string &name);
        /**
         * Get number value of attribute for the specified name.
         *
         * @param name Attribute name.
         *
         * @return Number value of the attribute.
         */
        double getNumberAttribute(const std::string &name);
        /**
         * Get string value of attribute for the specified name.
         *
         * @param name Attribute name.
         *
         * @return String value of the attribute.
         */
        const char *getStringAttribute(const std::string &name);
        
        /**
         * Replace all attributes with the new ones.
         *
         * @param attributes New attributes.
         */
        void setAttributes(Map *attributes);
        
        /**
         * Remove attribute of the specified name.
         *
         * @param name Attribute name to remove.
         */
        void removeAttribute(const std::string &name);
        /**
         * Clear all attributes.
         */
        void clearAttributes();
        
        /**
         * Add new xml child node to the tail.
         *
         * @param node New xml node to add.
         */
        void appendChildNode(XmlNode *node);
        /**
         * Insert new xml child node at the specified index.
         *
         * @param node New xml node to insert.
         * @param index The index to insert.
         */
        void insertChildNode(XmlNode *node, int index);
        /**
         * Remove the specified xml node.
         *
         * @param node Xml node to remove.
         */
        void removeChildNode(XmlNode *node);
        /**
         * Remove the xml node at specified index.
         *
         * @param index Index of xml node to remove.
         */
        void removeChildNodeAt(int index);
        /**
         * Remove all child nodes.
         */
        void clearChildNodes();
        
        /**
         * Find first child node with specified attribute name and value.
         *
         * @param attributeName Attribute name of condition.
         * @param attributeValue Attribute value of condition.
         * @param isRecursive Whether to find the node recursively.
         *
         * @return Return the first satisfied node if found, otherwise it will return null.
         */
        XmlNode *findFirstNode(const std::string &attributeName, const std::string &attributeValue, bool isRecursive = false);
        /**
         * Find first child node with specified node name.
         *
         * @param nodeName XML node name.
         * @param isRecursive Whether to find the node recursively.
         *
         * @return Return the first satisfied node if found, otherwise it will return null.
         */
        XmlNode *findFirstNode(const std::string &nodeName, bool isRecursive = false);
        /**
         * Find first child node with specified node name.
         *
         * @param nodeName XML node name.
         * @param attributeName Attribute name of condition.
         * @param attributeValue Attribute value of condition.
         * @param isRecursive Whether to find the node recursively.
         *
         * @return Return the first satisfied node if found, otherwise it will return null.
         */
        XmlNode *findFirstNode(const std::string &nodeName, const std::string &attributeName, const std::string &attributeValue, bool isRecursive = false);
        /**
         * Find first child node with multiple conditions of attribute.
         *
         * @param attributePairs Attribute conditions map.
         * @param isRecursive Whether to find the node recursively.
         *
         * @return Return the first satisfied node if found, otherwise it will return null.
         */
        XmlNode *findFirstNode(Map *attributePairs, bool isRecursive = false);
        /**
         * Find first child node with multiple conditions of attribute and specified node name.
         *
         * @param nodeName XML node name.
         * @param attributePairs Attribute conditions map.
         * @param isRecursive Whether to find the node recursively.
         *
         * @return Return the first satisfied node if found, otherwise it will return null.
         */
        XmlNode *findFirstNode(const std::string &nodeName, Map *attributePairs, bool isRecursive = false);
        /**
         * Find first child node with xpath.
         *
         * @param xpath Xpath expression.
         *
         * @return Return the first satisfied node if found, otherwise it will return null.
         */
        XmlNode *findFirstNode(const std::string &xpath);
        
        /**
         * Find all child nodes with specified attribute name and value.
         *
         * @param attributeName Attribute name of condition.
         * @param attributeValue Attribute value of condition.
         * @param isRecursive Whether to find the node recursively.
         *
         * @return Return all satisfied nodes if found, otherwise it will return null.
         */
        Vector *findNodes(const std::string &attributeName, const std::string &attributeValue, bool isRecursive = false);
        /**
         * Find all child nodes with specified attribute name and value.
         *
         * @param nodeName XML node name.
         * @param isRecursive Whether to find the node recursively.
         *
         * @return Return all satisfied nodes if found, otherwise it will return null.
         */
        Vector *findNodes(const std::string &nodeName, bool isRecursive = false);
        /**
         * Find all child nodes with specified node name, attribute name and value.
         *
         * @param nodeName XML node name.
         * @param attributeName Attribute name of condition.
         * @param attributeValue Attribute value of condition.
         * @param isRecursive Whether to find the node recursively.
         *
         * @return Return all satisfied nodes if found, otherwise it will return null.
         */
        Vector *findNodes(const std::string &nodeName, const std::string &attributeName, const std::string &attributeValue, bool isRecursive = false);
        /**
         * Find all child nodes with multiple conditions of attribute.
         *
         * @param attributePairs Attribute conditions map.
         * @param isRecursive Whether to find the node recursively.
         *
         * @return Return all satisfied nodes if found, otherwise it will return null.
         */
        Vector *findNodes(Map *attributePairs, bool isRecursive = false);
        /**
         * Find all child nodes with multiple conditions of attribute.
         *
         * @param nodeName XML node name.
         * @param attributePairs Attribute conditions map.
         * @param isRecursive Whether to find the node recursively.
         *
         * @return Return all satisfied nodes if found, otherwise it will return null.
         */
        Vector *findNodes(const std::string &nodeName, Map *attributePairs, bool isRecursive = false);
        /**
         * Find all child nodes with xpath.
         *
         * @param xpath Xpath expression.
         *
         * @return Return all satisfied nodes if found, otherwise it will return null.
         */
        Vector *findNodes(const std::string &xpath);
        
        /**
         * Get parent node.
         *
         * @return Return parent node, or null if non-exist.
         */
        inline XmlNode *getParent()
        {
            return _parent;
        }
        
        /**
         * Get next sibling node.
         *
         * @return Return next sibling node, or null if non-exist.
         */
        XmlNode *nextSibling();
        /**
         * Get previous sibling node.
         *
         * @return Return previous sibling node, or null if non-exist.
         */
        XmlNode *prevSibling();
        
        /**
         * Get the root node.
         *
         * @return Return root node.
         */
        XmlNode *root();
        
        /**
         * Format to xml string.
         *
         * @return Return xml.
         */
		std::string toString(bool needXmlHead = false);
        /**
         * Format to xml string in a pretty format.
         *
         * @return Return formatted xml.
         */
		std::string toPrettyString(bool needXmlHead = false);
        
        /**
         * Write generated xml to the specified file.
         *
         * @param path File path to write.
         *
         * @return Return xml.
         */
        bool writeToFile(const std::string &path);
        
    protected:
        bool satisfyAttributeConditions(XmlNode *node, Map *conditions);
        
        std::string _nodeName;
        std::string _nodeValue;
        Map *_attributes;
        Vector *_childNodes;
        XmlNode *_parent;
    };
}

#endif /* defined(__XML_XMLNODE__) */
