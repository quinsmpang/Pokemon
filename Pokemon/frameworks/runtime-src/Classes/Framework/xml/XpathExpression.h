/******************************
 Description: Simple xml expression(limited features).
 Author: M.Wan
 Date: 01/20/2015
 ******************************/

#ifndef __XML_XPATHEXPRESSION__
#define __XML_XPATHEXPRESSION__

#include <string>
#include <map>

namespace framework {
    class XpathExpression
    {
    public:
        enum class ExpressionType
        {
            ROOT = 0,
            ANCESTOR,
            DESCENDANT,
            PARENT,
            SELF,
            ATTRIBUTE,
            INDEX,
        };
    public:
        explicit XpathExpression(const std::string &xpath);
        ~XpathExpression();
        
    protected:
        std::string _xpath;
        std::map<ExpressionType, std::string> _expressions;
    };
}

#endif /* defined(__XML_XPATHEXPRESSION__) */
