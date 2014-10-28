
-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    print("----------------------------------------")
    print("LUA ERROR: " .. tostring(msg) .. "\n")
    print(debug.traceback())
    print("----------------------------------------")
end

GameLauncher = {}

DEBUG = true

GameLauncher.publicResources = {
    "images/common.plist",
    "images/common.pvr.ccz",
    -- "images/pokemons1.plist",
    -- "images/pokemons1.pvr.ccz",
    -- "images/pokemons2.plist",
    -- "images/pokemons2.pvr.ccz",
    -- "images/pokemons3.plist",
    -- "images/pokemons3.pvr.ccz",
    -- "images/pokemons4.plist",
    -- "images/pokemons4.pvr.ccz",
    -- "images/pokemons5.plist",
    -- "images/pokemons5.pvr.ccz",
    -- "images/pokemons6.plist",
    -- "images/pokemons6.pvr.ccz",
    -- "images/pokemons7.plist",
    -- "images/pokemons7.pvr.ccz",
}

function GameLauncher:init()
    collectgarbage("collect")
    -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)
    cc.FileUtils:getInstance():addSearchResolutionsOrder("src");
    cc.FileUtils:getInstance():addSearchResolutionsOrder("res");
    
    self:loadLuaFramework()
    self:loadPublicModules()
    self:loadPublicResources()

    -- print current platform
    _G["TARGET_PLATFORM"] = cc.Application:getInstance():getTargetPlatform()
    log("Current Platform: ", TARGET_PLATFORM)

    -- enable keyboard extensions when at win32 platform
    if TARGET_PLATFORM == cc.PLATFORM_OS_WINDOWS then
        KeyboardHelper:getInstance():hookOn()
    end

    -- set random seed
    math.randomseed(tostring(os.time()):reverse():sub(1, 6))

    -- set record encryption key
    RecordHelper:getInstance():setEncryptionKey(213)

    -- load game settings
    GameSettings:loadSettings()

    -- print current version
    log(string.format("framework version string: %s, number: %.2f\n", PSFrameworkVersionStr, PSFrameworkVersionNumber))
end

function GameLauncher:loadLuaFramework()
    require "src/framework/Cocos2d"
    require "src/framework/Cocos2dConstants"
    require "src/framework/luaClass"
    require "src/framework/class"
    require "src/framework/FrameworkConstants"
    require "src/framework/SystemExtensions"
    require "src/framework/BaseExtensions"
    require "src/framework/commonLib"
    require "src/framework/Notifier"
    require "src/framework/SqliteLua"
    require "src/framework/psModel"
    require "src/framework/RecordHelperLua"
    require "src/framework/Containers"
end

function GameLauncher:loadPublicModules()
    -- models
    require "src/model/Dialog"
    require "src/model/MapInfo"
    require "src/model/PlayerData"
    require "src/model/Obstacle"
    require "src/model/Entrance"
    require "src/model/NpcInfo"
    require "src/model/NPC"
    require "src/model/ActionInfo"
    require "src/model/Trigger"
    require "src/model/Response"
    require "src/model/EventInfo"
    require "src/model/PetInfo"
    require "src/model/Pokemon"

    -- public data or utils
    require "src/utils/GameConfig"
    require "src/utils/Enumerations"
    require "src/utils/NotifyEvents"
    require "src/utils/GameSettings"
    require "src/utils/GameVolumeHelper"
    require "src/utils/GameDBHelper"
    require "src/utils/DataCenter"
    require "src/utils/DialogPopHelper"
end

function GameLauncher:loadPublicResources()
    LoadSpriteFrames(self.publicResources)
end

function GameLauncher:startGame()
    require "src/view/maintitle/MainViewScene"

    local mainView = MainViewScene:create()

    cc.Director:getInstance():runWithScene(mainView)
end

function GameLauncher:launch()
    GameLauncher:init()

    GameLauncher:startGame()
end

xpcall(function() GameLauncher:launch() end, __G__TRACKBACK__)
