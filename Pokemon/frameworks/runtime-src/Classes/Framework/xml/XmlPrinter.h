/******************************
 Description: XML printer.
 Author: M.Wan
 Date: 01/11/2015
 ******************************/

#ifndef __XML_XMLPRINTER__
#define __XML_XMLPRINTER__

#include "../base/Macros.h"
#include "../base/Uninheritable.h"
#include <string>

namespace framework {
    class XmlNode;
    
    class XmlVisitor
    {
    public:
        virtual ~XmlVisitor() {}
        
        /**
         * Provide a visit way when starting.
         *
         * @param node Node to visit
         */
        virtual std::string visitBegin(XmlNode *node) = 0;
        /**
         * Provide a visit way when ending.
         *
         * @param node Node to visit
         */
		virtual std::string visitEnd(XmlNode *node) = 0;
    };
    
    class XmlPrinter : public XmlVisitor
    {
        SINGLETON(XmlPrinter);
    public:
        /**
         * XmlVisitor overrides.
         */
		virtual std::string visitBegin(XmlNode *node);
		virtual std::string visitEnd(XmlNode *node);
        
        /**
         * Print xml node recursively. Ignore encoding.
         *
         * @param node The node to print.
         *
         * @return Xml string.
         */
		virtual std::string print(XmlNode *node, bool needVersion = false);
    };
    
    class XmlPrettyPrinter : public XmlPrinter, public Uninheritable<XmlPrettyPrinter>
    {
        SINGLETON(XmlPrettyPrinter);
    public:
        /**
         * XmlVisitor overrides.
         */
		std::string visitBegin(XmlNode *node) override;
		std::string visitEnd(XmlNode *node) override;

		virtual std::string print(XmlNode *node, bool needVersion = false) override;
        
    private:
		std::string printTabs(int tabNum);
        
        int _counter;
    };
}

#endif /* defined(__XML_XMLPRINTER__) */
