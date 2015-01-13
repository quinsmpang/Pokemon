#include "lua_decryption_loader.h"
#include "platform/CCFileUtils.h"
#include "../encryption/AesUtils.h"
#include <string>

using namespace cocos2d;

extern "C" {
    int framework_decipher_loader(lua_State *L)
    {
        std::string filename(luaL_checkstring(L, 1));
        size_t pos = filename.rfind(".lua");
        if (pos != std::string::npos)
        {
            filename = filename.substr(0, pos);
        }
        
        pos = filename.find_first_of(".");
        while (pos != std::string::npos)
        {
            filename.replace(pos, 1, "/");
            pos = filename.find_first_of(".");
        }
        filename.append(".lua");
        
        Data data = FileUtils::getInstance()->getDataFromFile(filename);
        
        if (!data.isNull())
        {
            char *bytes = (char*)data.getBytes();
            
            // decipher lua file.
            int outSize;
            bytes = (char*)framework::AesUtils::getInstance()->decipher(bytes, LUA_DECIPHER_KEY, &outSize);
            
            if (luaL_loadbuffer(L, bytes, outSize, filename.c_str()) != 0)
            {
                luaL_error(L, "error loading module %s from file %s :\n\t%s",
                           lua_tostring(L, 1), filename.c_str(), lua_tostring(L, -1));
            }
        }
        else
        {
            log("can not get file data of %s", filename.c_str());
        }
        
        return 1;
    }
}