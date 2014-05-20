require "Cocos2d"
require "Cocos2dConstants"

-- for CCLuaEngine traceback
function __G__TRACKBACK__(msg)
    print("----------------------------------------")
    print("LUA ERROR: " .. tostring(msg) .. "\n")
    print(debug.traceback())
    print("----------------------------------------")
end

GameLauncher = {}

DEBUG = true

function GameLauncher:init()
    collectgarbage("collect")
    -- avoid memory leak
    collectgarbage("setpause", 100)
    collectgarbage("setstepmul", 5000)
    cc.FileUtils:getInstance():addSearchResolutionsOrder("src");
    cc.FileUtils:getInstance():addSearchResolutionsOrder("res");
    
    self:loadLuaFramework()
    self:loadPublicModules()

    -- set random seed
    math.randomseed(tostring(os.time()):reverse():sub(1, 6))

    -- set record encryption key
    RecordHelper:getInstance():setEncryptionKey(213)

    -- load game settings
    GameSettings:loadSettings()

    -- print current version
    log("framework version string: %s, number: %.2f\n", PSFrameworkVersionStr, PSFrameworkVersionNumber)
end

function GameLauncher:loadAudioResources()
    log("GameLauncher:loadAudioResources begin")
    -- effects
    for i = 1, 649 do
        local str = "audio/pm/"
        if i < 10 then
            str = str .. "00"
        elseif i < 100 then
            str = str .. "0"
        end
        cc.SimpleAudioEngine:getInstance():preloadEffect(str .. i .. ".wav")
    end
    log("GameLauncher:loadAudioResources end")
end

function GameLauncher:loadLuaFramework()
    require "src/framework/luaClass"
    require "src/framework/class"
    require "src/framework/SystemExtensions"
    require "src/framework/BaseExtensions"
    require "src/framework/commonLib"
    require "src/framework/Notifier"
    require "src/framework/SqliteLua"
    require "src/framework/psModel"
    require "src/framework/RecordHelperLua"
end

function GameLauncher:loadPublicModules()
    require "src/utils/GameConst"
    require "src/utils/GameSettings"
    require "src/utils/GameVolumeHelper"
end

function GameLauncher:startGame()
    require "src/view/maintitle/MainViewScene"

    local mainView = MainViewScene:create()

    cc.Director:getInstance():runWithScene(mainView)
end

function GameLauncher:launch()
    GameLauncher:init()

    --GameLauncher:demo()

    GameLauncher:startGame()
end

function GameLauncher:demo()
    log("framework version string: %s, number: %.2f", PSFrameworkVersionStr, PSFrameworkVersionNumber)
    
    local screenSize = cc.Director:getInstance():getWinSize()

    local mainScene = psGameScene:create()

    mainScene.onEnter = function(self)
        print("onEnter")
    end

    local coreLayer = psCoreLayer:create()
    local background = cc.Sprite:create("farm.jpg")
    background:setAnchorPoint(0, 0)
    coreLayer:addChild(background)

    local dogTexture = cc.Director:getInstance():getTextureCache():addImage("dog.png")
    local rect = cc.rect(0, 0, 105, 95)
    local frame0 = cc.SpriteFrame:createWithTexture(dogTexture, rect)
    rect = cc.rect(105, 0, 105, 95)
    local frame1 = cc.SpriteFrame:createWithTexture(dogTexture, rect)

    local dog = cc.Sprite:createWithSpriteFrame(frame0)
    dog.isPaused = false
    dog:setPosition(screenSize.width * 0.5, screenSize.height * 0.5)

    local animation = cc.Animation:createWithSpriteFrames({ frame0, frame1 }, 0.5)
    local animate = cc.Animate:create(animation)
    local moveAction = cc.Sequence:create({
            cc.MoveBy:create(1, ccp(0, 100)),
            cc.MoveBy:create(1, ccp(0, -100))
        })
    dog:runAction(cc.RepeatForever:create(cc.Spawn:create({
            animate,
            moveAction
        })))

    coreLayer:addChild(dog)

    mainScene:setCoreLayer(coreLayer)

    local function onClick()
        print("onClick")
    end

    local menuLayer = cc.Layer:create()

    local btn = cc.MenuItemImage:create("btn1.png", "btn2.png")
    btn:registerScriptTapHandler(onClick)
    local menu = cc.Menu:create(btn)
    menu:setPosition(screenSize.width * 0.9, screenSize.height * 0.9)
    menuLayer:addChild(menu)

    coreLayer:addChild(menuLayer)

    cc.Director:getInstance():runWithScene(mainScene)

    local maskLayer = psMaskLayer:create(cc.rect(200, 200, 100, 100))
    maskLayer:setOpacity(100)
    maskLayer:forceInterceptAllEvents(false)

    maskLayer.onEventIntercepted = function(self, x, y)
        log("onEventIntercepted at %.2f, %.2f", x, y)
    end

    maskLayer.onEventPenetrated = function(self, x, y)
        log("onEventPenetrated at %.2f, %.2f", x, y)
    end

    coreLayer:addChild(maskLayer)

    local topLayer = psGameLayer:createWithTransitions(
        cc.EaseOut:create(cc.MoveBy:create(0.5, ccp(-screenSize.width, 0)), 2), 
        cc.EaseOut:create(cc.MoveBy:create(0.5, ccp(screenSize.width, 0)), 2),
        cc.EaseIn:create(cc.MoveBy:create(0.5, ccp(-screenSize.width, 0)), 2),
        cc.EaseIn:create(cc.MoveBy:create(0.5, ccp(screenSize.width, 0)), 2)
        )
    topLayer:setPosition(screenSize.width, 0)
    local land = cc.Sprite:create("land.png")
    land:setPosition(screenSize.width * 0.25, screenSize.height * 0.25)
    topLayer:addChild(land)

    local function onTouchScreen(touch, event)
        local pos = touch:getLocation()
        log("onTouchScreen: %.2f, %.2f", pos.x, pos.y)
        local copyLayer = psGameLayer:createWithTransitions(
            cc.EaseOut:create(cc.MoveBy:create(0.5, ccp(-screenSize.width, 0)), 2), 
            cc.EaseOut:create(cc.MoveBy:create(0.5, ccp(screenSize.width, 0)), 2),
            cc.EaseIn:create(cc.MoveBy:create(0.5, ccp(-screenSize.width, 0)), 2),
            cc.EaseIn:create(cc.MoveBy:create(0.5, ccp(screenSize.width, 0)), 2)
            )
        copyLayer:setPosition(screenSize.width, 0)
        local land = cc.Sprite:create("land.png")
        land:setPosition(screenSize.width * 0.75, screenSize.height * 0.75)
        copyLayer:addChild(land)

        local function tmpTouchScreen(touch, event)
            coreLayer:popLayer()
        end

        local listener = cc.EventListenerTouchOneByOne:create()
        listener:setSwallowTouches(true)
        listener:registerScriptHandler(tmpTouchScreen, cc.Handler.EVENT_TOUCH_BEGAN)
        copyLayer:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, copyLayer)

        coreLayer:pushLayer(copyLayer)
        --coreLayer:popLayer()

        return true
    end

    local listener = cc.EventListenerTouchOneByOne:create()
    listener:setSwallowTouches(true)
    listener:registerScriptHandler(onTouchScreen, cc.Handler.EVENT_TOUCH_BEGAN)
    topLayer:getEventDispatcher():addEventListenerWithSceneGraphPriority(listener, topLayer)

    coreLayer:pushLayer(topLayer)

    local modalLayer = psModalLayer:create()
    modalLayer:ignoreAnchorPointForPosition(false)
    modalLayer:setAnchorPoint(0.5, 0.5)
    modalLayer:setPosition(screenSize.width * 0.5, screenSize.height * 0.5)
    modalLayer:setScale(0)
    modalLayer:setOpacity(100)
    modalLayer:setColor(ccc3(0, 0, 0))

    modalLayer.onComeIn = function(self)
        local comeInAction = cc.ScaleTo:create(0.5, 1)
        self:runAction(comeInAction)
    end

    modalLayer.cleanUp = function(self)
        self:removeFromParent()
        log("modalLayer is cleaned up.")
    end

    modalLayer.onModalTouchBegan = function(self, x, y)
        log("Modal layer touched at: %.2f, %.2f", x, y)
        local goOutAction = cc.Sequence:create(
            cc.ScaleTo:create(0.5, 0),
            cc.CallFunc:create(MakeScriptHandler(self, self.cleanUp))
            )
        self:runAction(goOutAction)
    end

    topLayer:addChild(modalLayer)

    --[[
    local visibleSize = cc.Director:getInstance():getVisibleSize()
    local origin = cc.Director:getInstance():getVisibleOrigin()

    -- add the moving dog
    local function creatDog()
        local frameWidth = 105
        local frameHeight = 95

        -- create dog animate
        local textureDog = cc.Director:getInstance():getTextureCache():addImage("dog.png")
        local rect = cc.rect(0, 0, frameWidth, frameHeight)
        local frame0 = cc.SpriteFrame:createWithTexture(textureDog, rect)
        rect = cc.rect(frameWidth, 0, frameWidth, frameHeight)
        local frame1 = cc.SpriteFrame:createWithTexture(textureDog, rect)

        local spriteDog = cc.Sprite:createWithSpriteFrame(frame0)
        spriteDog.isPaused = false
        spriteDog:setPosition(origin.x, origin.y + visibleSize.height / 4 * 3)

        local animation = cc.Animation:createWithSpriteFrames({frame0,frame1}, 0.5)
        local animate = cc.Animate:create(animation);
        spriteDog:runAction(cc.RepeatForever:create(animate))

        -- moving dog at every frame
        local function tick()
            if spriteDog.isPaused then return end
            local x, y = spriteDog:getPosition()
            if x > origin.x + visibleSize.width then
                x = origin.x
            else
                x = x + 1
            end

            spriteDog:setPositionX(x)
        end

        schedulerID = cc.Director:getInstance():getScheduler():scheduleScriptFunc(tick, 0, false)

        return spriteDog
    end

    -- create farm
    local function createLayerFarm()
        local layerFarm = cc.Layer:create()

        -- add in farm background
        local bg = cc.Sprite:create("farm.jpg")
        bg:setPosition(origin.x + visibleSize.width / 2 + 80, origin.y + visibleSize.height / 2)
        layerFarm:addChild(bg)

        -- add land sprite
        for i = 0, 3 do
            for j = 0, 1 do
                local spriteLand = cc.Sprite:create("land.png")
                spriteLand:setPosition(200 + j * 180 - i % 2 * 90, 10 + i * 95 / 2)
                layerFarm:addChild(spriteLand)
            end
        end

        -- add crop
        local frameCrop = cc.SpriteFrame:create("crop.png", cc.rect(0, 0, 105, 95))
        for i = 0, 3 do
            for j = 0, 1 do
                local spriteCrop = cc.Sprite:createWithSpriteFrame(frameCrop);
                spriteCrop:setPosition(10 + 200 + j * 180 - i % 2 * 90, 30 + 10 + i * 95 / 2)
                layerFarm:addChild(spriteCrop)
            end
        end

        -- add moving dog
        local spriteDog = creatDog()
        layerFarm:addChild(spriteDog)

        -- handing touch events
        local touchBeginPoint = nil
        local function onTouchBegan(touch, event)
            local location = touch:getLocation()
            cclog("onTouchBegan: %0.2f, %0.2f", location.x, location.y)
            touchBeginPoint = {x = location.x, y = location.y}
            spriteDog.isPaused = true
            -- CCTOUCHBEGAN event must return true
            return true
        end

        local function onTouchMoved(touch, event)
            local location = touch:getLocation()
            cclog("onTouchMoved: %0.2f, %0.2f", location.x, location.y)
            if touchBeginPoint then
                local cx, cy = layerFarm:getPosition()
                layerFarm:setPosition(cx + location.x - touchBeginPoint.x,
                                      cy + location.y - touchBeginPoint.y)
                touchBeginPoint = {x = location.x, y = location.y}
            end
        end

        local function onTouchEnded(touch, event)
            local location = touch:getLocation()
            cclog("onTouchEnded: %0.2f, %0.2f", location.x, location.y)
            touchBeginPoint = nil
            spriteDog.isPaused = false
        end

        local listener = cc.EventListenerTouchOneByOne:create()
        listener:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCH_BEGAN )
        listener:registerScriptHandler(onTouchMoved,cc.Handler.EVENT_TOUCH_MOVED )
        listener:registerScriptHandler(onTouchEnded,cc.Handler.EVENT_TOUCH_ENDED )
        local eventDispatcher = layerFarm:getEventDispatcher()
        eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layerFarm)
        
        local function onNodeEvent(event)
           if "exit" == event then
               cc.Director:getInstance():getScheduler():unscheduleScriptEntry(schedulerID)
           end
        end
        layerFarm:registerScriptHandler(onNodeEvent)

        return layerFarm
    end


    -- create menu
    local function createLayerMenu()
        local layerMenu = cc.Layer:create()

        local menuPopup, menuTools, effectID

        local function menuCallbackClosePopup()
            -- stop test sound effect
            cc.SimpleAudioEngine:getInstance():stopEffect(effectID)
            menuPopup:setVisible(false)
        end

        local function menuCallbackOpenPopup()
            -- loop test sound effect
            local effectPath = cc.FileUtils:getInstance():fullPathForFilename("effect1.wav")
            effectID = cc.SimpleAudioEngine:getInstance():playEffect(effectPath)
            menuPopup:setVisible(true)
        end

        -- add a popup menu
        local menuPopupItem = cc.MenuItemImage:create("menu2.png", "menu2.png")
        menuPopupItem:setPosition(0, 0)
        menuPopupItem:registerScriptTapHandler(menuCallbackClosePopup)
        menuPopup = cc.Menu:create(menuPopupItem)
        menuPopup:setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2)
        menuPopup:setVisible(false)
        layerMenu:addChild(menuPopup)
        
        -- add the left-bottom "tools" menu to invoke menuPopup
        local menuToolsItem = cc.MenuItemImage:create("menu1.png", "menu1.png")
        menuToolsItem:setPosition(0, 0)
        menuToolsItem:registerScriptTapHandler(menuCallbackOpenPopup)
        menuTools = cc.Menu:create(menuToolsItem)
        local itemWidth = menuToolsItem:getContentSize().width
        local itemHeight = menuToolsItem:getContentSize().height
        menuTools:setPosition(origin.x + itemWidth/2, origin.y + itemHeight/2)
        layerMenu:addChild(menuTools)

        return layerMenu
    end

    -- play background music, preload effect

    -- uncomment below for the BlackBerry version
    local bgMusicPath = nil 
    if (cc.PLATFORM_OS_IPHONE == targetPlatform) or (cc.PLATFORM_OS_IPAD == targetPlatform) then
        bgMusicPath = cc.FileUtils:getInstance():fullPathForFilename("res/background.caf")
    else
        bgMusicPath = cc.FileUtils:getInstance():fullPathForFilename("res/background.mp3")
    end
    cc.SimpleAudioEngine:getInstance():playMusic(bgMusicPath, true)
    local effectPath = cc.FileUtils:getInstance():fullPathForFilename("effect1.wav")
    cc.SimpleAudioEngine:getInstance():preloadEffect(effectPath)

    -- run
    local sceneGame = cc.Scene:create()
    sceneGame:addChild(createLayerFarm())
    sceneGame:addChild(createLayerMenu())
    
    if cc.Director:getInstance():getRunningScene() then
        cc.Director:getInstance():replaceScene(sceneGame)
    else
        cc.Director:getInstance():runWithScene(sceneGame)
    end
]]
end

xpcall(GameLauncher.launch, __G__TRACKBACK__)
