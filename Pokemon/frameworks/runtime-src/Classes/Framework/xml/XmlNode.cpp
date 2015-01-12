#include "XmlNode.h"
#include "XmlElement.h"
#include "XmlParser.h"
#include "XmlPrinter.h"
#include "../base/RefString.h"
#include <new>

using namespace cocos2d;
using namespace std;

namespace framework {
    XmlNode::XmlNode(const std::string &name)
        : _nodeName("")
        , _nodeValue("")
        , _attributes(new Map())
        , _childNodes(new Vector())
        , _parent(nullptr)
    {
        this->setName(name);
    }
    
    XmlNode::~XmlNode()
    {
        CC_SAFE_RELEASE(_attributes);
        CC_SAFE_RELEASE(_childNodes);
    }
    
    XmlNode *XmlNode::create(const std::string &name)
    {
        auto pNode = new (nothrow) XmlNode(name);
        if (pNode) {
            pNode->autorelease();
            return pNode;
        }
        return nullptr;
    }
    
    XmlNode *XmlNode::createWithString(const std::string &xmlStr)
    {
        return XmlParser::getInstance()->parseString(xmlStr);
    }
    
    XmlNode *XmlNode::createWithFile(const std::string &xmlPath)
    {
        return XmlParser::getInstance()->parseFile(xmlPath);
    }
    
    void XmlNode::setName(const std::string &name)
    {
        CCASSERT(name.size() > 0 && (name.at(0) == '_' || (name.at(0) >= 'a' && name.at(0) <= 'z') || (name.at(0) >= 'A' && name.at(0) <= 'Z')), "Invalid xml node name. The first character must be letters or underline.");
        _nodeName = name;
    }
    
    void XmlNode::setValue(const std::string &value)
    {
        CCASSERT(value.find('<') < 0, "Invalid '<' character.");
        _nodeValue = value;
    }
    
    void XmlNode::putAttribute(const std::string &name, bool value)
    {
        CCASSERT(name.size() > 0, "Name can't be empty.");
        auto pBool = XmlBoolean::create(value);
        _attributes->setObjectForKey(pBool, name);
    }
    
    void XmlNode::putAttribute(const std::string &name, double value)
    {
        CCASSERT(name.size() > 0, "Name can't be empty.");
        auto pNumber = XmlNumber::create(value);
        _attributes->setObjectForKey(pNumber, name);
    }
    
    void XmlNode::putAttribute(const std::string &name, const std::string &value)
    {
        CCASSERT(name.size() > 0 && value.size() > 0, "Name and value can't be empty.");
        CCASSERT(value.find('"') < 0, "Value can't include illegal characters.");
        auto pStr = XmlString::create(value);
        _attributes->setObjectForKey(pStr, name);
    }
    
    bool XmlNode::getBooleanAttribute(const std::string &name)
    {
        auto val = _attributes->objectForKey(name);
        CCASSERT(val, "Invalid attribute name.");
        XmlElement *pVal = dynamic_cast<XmlElement*>(val);
        return pVal->boolValue();
    }
    
    double XmlNode::getNumberAttribute(const std::string &name)
    {
        auto val = _attributes->objectForKey(name);
        CCASSERT(val, "Invalid attribute name.");
        XmlElement *pVal = dynamic_cast<XmlElement*>(val);
        return pVal->numberValue();
    }
    
    const char *XmlNode::getStringAttribute(const std::string &name)
    {
        auto val = _attributes->objectForKey(name);
        CCASSERT(val, "Invalid attribute name.");
        XmlElement *pVal = dynamic_cast<XmlElement*>(val);
        return pVal->stringValue();
    }
    
    void XmlNode::setAttributes(framework::Map *attributes)
    {
        CCASSERT(attributes, "Param can't be null.");
        CC_SAFE_RELEASE(_attributes);
        _attributes = attributes;
        CC_SAFE_RETAIN(_attributes);
    }
    
    void XmlNode::removeAttribute(const std::string &name)
    {
        _attributes->removeObjectForKey(name);
    }
    
    void XmlNode::clearAttributes()
    {
        _attributes->clear();
    }
    
    void XmlNode::appendChildNode(framework::XmlNode *node)
    {
        CCASSERT(node, "Param can't be null.");
        CCASSERT(!node->_parent, "The node is already added.");
        _childNodes->addObject(node);
        node->_parent = this;
    }
    
    void XmlNode::insertChildNode(framework::XmlNode *node, int index)
    {
        CCASSERT(node, "Param can't be null.");
        CCASSERT(!node->_parent, "The node is already added.");
        _childNodes->setObjectAt(node, index);
        node->_parent = this;
    }
    
    void XmlNode::removeChildNode(framework::XmlNode *node)
    {
        CCASSERT(node, "Param can't be null.");
        if (node->_parent != this) {
            return;
        }
        _childNodes->removeObject(node);
        node->_parent = nullptr;
    }
    
    void XmlNode::removeChildNodeAt(int index)
    {
        XmlNode *pChild = (XmlNode*)_childNodes->objectAt(index);
        if (pChild) {
            this->removeChildNode(pChild);
        }
    }
    
    void XmlNode::clearChildNodes()
    {
        XmlNode *pChild = nullptr;
        for (int i = 0; i < _childNodes->getLength(); ++i) {
            pChild = (XmlNode*)_childNodes->objectAt(i);
            pChild->_parent = nullptr;
        }
        _childNodes->clear();
    }
    
    XmlNode *XmlNode::findFirstNode(const std::string &attributeName, const std::string &attributeValue, bool isRecursive)
    {
        XmlNode *pResult = nullptr;
        XmlNode *pChild = nullptr;
        for (int i = 0; i < _childNodes->getLength(); ++i) {
            pChild = (XmlNode*)_childNodes->objectAt(i);
            if (pChild->getStringAttribute(attributeName) == attributeValue) {
                pResult = pChild;
                break;
            } else {
                if (isRecursive) {
                    pResult = pChild->findFirstNode(attributeName, attributeValue, isRecursive);
                    if (pResult) {
                        break;
                    }
                }
            }
        }
        return pResult;
    }
    
    XmlNode *XmlNode::findFirstNode(framework::Map *attributePairs, bool isRecursive)
    {
        XmlNode *pResult = nullptr;
        XmlNode *pChild = nullptr;
        for (int i = 0; i < _childNodes->getLength(); ++i) {
            pChild = (XmlNode*)_childNodes->objectAt(i);
            bool satisfy = this->satisfyAttributeConditions(pChild, attributePairs);
            if (satisfy) {
                pResult = pChild;
                break;
            } else {
                if (isRecursive) {
                    pResult = pChild->findFirstNode(attributePairs, isRecursive);
                    if (pResult) {
                        break;
                    }
                }
            }
        }
        return pResult;
    }
    
    XmlNode *XmlNode::findFirstNode(const std::string &xpath)
    {
		CCASSERT(false, "xpath not implemented yet.");
        // todo
        return nullptr;
    }
    
    Vector *XmlNode::findNodes(const std::string &attributeName, const std::string &attributeValue, bool isRecursive)
    {
        auto nodes = Vector::create();
        XmlNode *pChild = nullptr;
        for (int i = 0; i < _childNodes->getLength(); ++i) {
            pChild = (XmlNode*)_childNodes->objectAt(i);
            if (pChild->getStringAttribute(attributeName) == attributeValue) {
                nodes->addObject(pChild);
            } else {
                if (isRecursive) {
                    auto childResultNodes = pChild->findNodes(attributeName, attributeValue, isRecursive);
                    for (int j = 0; j < childResultNodes->getLength(); ++j) {
                        nodes->addObject(childResultNodes->objectAt(j));
                    }
                }
            }
        }
        return nodes;
    }
    
    Vector *XmlNode::findNodes(framework::Map *attributePairs, bool isRecursive)
    {
        auto nodes = Vector::create();
        XmlNode *pChild = nullptr;
        for (int i = 0; i < _childNodes->getLength(); ++i) {
            pChild = (XmlNode*)_childNodes->objectAt(i);
            bool satisfy = this->satisfyAttributeConditions(pChild, attributePairs);
            if (satisfy) {
                nodes->addObject(pChild);
            } else {
                if (isRecursive) {
                    auto childResultNodes = pChild->findNodes(attributePairs, isRecursive);
                    for (int j = 0; j < childResultNodes->getLength(); ++j) {
                        nodes->addObject(childResultNodes->objectAt(j));
                    }
                }
            }
        }
        return nodes;
    }
    
    Vector *XmlNode::findNodes(const std::string &xpath)
	{
		CCASSERT(false, "xpath not implemented yet.");
        // todo
        return nullptr;
    }
    
    bool XmlNode::satisfyAttributeConditions(framework::XmlNode *node, framework::Map *conditions)
    {
        bool satisfy = true;
        Vector *allKeys = conditions->allKeys();
        for (int j = 0; j < allKeys->getLength(); ++j) {
            std::string key = dynamic_cast<RefString*>(allKeys->objectAt(j))->getCString();
            std::string val = dynamic_cast<RefString*>(conditions->objectForKey(key))->getCString();
            std::string nodeVal = node->getStringAttribute(key);
            if (nodeVal != val) {
                satisfy = false;
                break;
            }
        }
        
        return satisfy;
    }
    
    XmlNode *XmlNode::nextSibling()
    {
        if (!_parent) {
            return nullptr;
        }
        Vector *pBrothers = _parent->_childNodes;
        XmlNode *pChild = nullptr;
        int idx = -1;
        for (int i = 0; i < pBrothers->getLength(); ++i) {
            pChild = (XmlNode*)pBrothers->objectAt(i);
            if (pChild == this) {
                idx = i;
                break;
            }
        }
        return (XmlNode*)pBrothers->objectAt(++idx);
    }
    
    XmlNode *XmlNode::prevSibling()
    {
        if (!_parent) {
            return nullptr;
        }
        Vector *pBrothers = _parent->_childNodes;
        XmlNode *pChild = nullptr;
        int idx = -1;
        for (int i = 0; i < pBrothers->getLength(); ++i) {
            pChild = (XmlNode*)pBrothers->objectAt(i);
            if (pChild == this) {
                idx = i;
                break;
            }
        }
        return (XmlNode*)pBrothers->objectAt(--idx);
    }
    
    const char *XmlNode::toString(bool needXmlHead)
    {
        return XmlPrinter::getInstance()->print(this, needXmlHead);
    }
    
    const char *XmlNode::toPrettyString(bool needXmlHead)
    {
        return XmlPrettyPrinter::getInstance()->print(this, needXmlHead);
    }
}