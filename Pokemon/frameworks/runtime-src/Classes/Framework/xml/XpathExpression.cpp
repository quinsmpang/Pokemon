#include "XpathExpression.h"

using namespace std;

namespace framework {
    XpathExpression::XpathExpression(const string &xpath)
        : _xpath(xpath)
        , _expressions()
    {
    }
}