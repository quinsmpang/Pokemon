#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__

#include "base/RefString.h"
#include "base/RefInteger.h"
#include "base/RefDouble.h"
#include "base/RefBoolean.h"

#include "containers/Queue.h"
#include "containers/Stack.h"
#include "containers/Vector.h"
#include "containers/Map.h"

#include "lua/LuaUtils.h"

#include "encryption/DesUtils.h"
#include "encryption/FileEncryptor.h"

#include "sqlite/SqliteDb.h"

#include "scene/ViewController.h"
#include "scene/GameScene.h"

#include "ui/GameLayer.h"
#include "ui/CoreLayer.h"
#include "ui/MaskLayer.h"
#include "ui/ModalLayer.h"

#include "controls/TableViewEx.h"
#include "controls/EncryptedTMXLayer.h"
#include "controls/EncryptedTMXTiledMap.h"

#include "utils/ScriptCCBReader.h"
#include "utils/IOUtils.h"
#include "utils/RecordHelper.h"
//#include "utils/UUIDGenerator.h"

#endif