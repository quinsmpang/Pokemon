/******************************
 Description: XML printer.
 Author: M.Wan
 Date: 01/11/2015
 ******************************/

#ifndef __XML_XMLPRINTER__
#define __XML_XMLPRINTER__

#include "../base/Macros.h"

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
        virtual const char *visitBegin(XmlNode *node) = 0;
        /**
         * Provide a visit way when ending.
         *
         * @param node Node to visit
         */
        virtual const char *visitEnd(XmlNode *node) = 0;
    };
    
    class XmlPrinter : public XmlVisitor
    {
        SINGLETON(XmlPrinter);
    public:
        /**
         * XmlVisitor overrides.
         */
        virtual const char *visitBegin(XmlNode *node);
        virtual const char *visitEnd(XmlNode *node);
        
        /**
         * Print xml node recursively.
         *
         * @param node The node to print.
         *
         * @return Xml string.
         */
        virtual const char *print(XmlNode *node, bool needVersion = false);
    };
    
    class XmlPrettyPrinter : public XmlPrinter
    {
        SINGLETON(XmlPrettyPrinter);
    public:
        /**
         * XmlVisitor overrides.
         */
        const char *visitBegin(XmlNode *node) override;
        const char *visitEnd(XmlNode *node) override;
        
    private:
        const char *printTabs(int tabNum);
        
        int _counter;
    };
}

#endif /* defined(__XML_XMLPRINTER__) */
