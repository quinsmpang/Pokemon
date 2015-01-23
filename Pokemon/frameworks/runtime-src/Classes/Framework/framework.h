#ifndef __FRAMEWORK_H__
#define __FRAMEWORK_H__

#include "base/Macros.h"
#include "base/RefString.h"
#include "base/RefInteger.h"
#include "base/RefDouble.h"
#include "base/RefBoolean.h"
#include "base/BinaryData.h"

#include "containers/Queue.h"
#include "containers/Stack.h"
#include "containers/Vector.h"
#include "containers/Map.h"

#include "lua/LuaUtils.h"
#include "lua/LuaEngineEx.h"

#include "encryption/DesUtils.h"
#include "encryption/FileEncryptor.h"

#include "sqlite/SqliteDb.h"

#include "scene/ViewController.h"
#include "scene/GameScene.h"

#include "ui/GameLayer.h"
#include "ui/CoreLayer.h"
#include "ui/MaskLayer.h"
#include "ui/ModalLayer.h"

#include "controls/EncryptedTMXLayer.h"
#include "controls/EncryptedTMXTiledMap.h"
#include "controls/ListMenuItem.h"
#include "controls/ListMenu.h"
#include "controls/TitleSwitch.h"
#include "controls/DirectionController.h"
#include "controls/CheckedButton.h"

#include "editor/ScriptCCBReader.h"

#include "utils/IOUtils.h"
#include "utils/RecordHelper.h"
#include "utils/ImageUtils.h"
#include "utils/ZipHelper.h"

#include "format/SaveData.h"

//#include "threading/Thread.h"
#include "threading/Mutex.h"

#include "json/JsonElement.h"
#include "json/JsonStructure.h"
#include "json/JsonParser.h"
#include "json/JsonFormatter.h"

#include "xml/XmlElement.h"
#include "xml/XmlNode.h"
#include "xml/XmlParser.h"
#include "xml/XmlPrinter.h"
#include "xml/XpathExpression.h"

#include "net/NetRequest.h"
#include "net/NetResponse.h"
#include "net/NetService.h"
#include "net/NetHandler.h"
#include "net/NetFilter.h"
#include "net/NetProtocol.h"
#include "net/NetCenter.h"

#include "http/HttpTransferStrategy.h"
#include "http/HttpForm.h"
#include "http/HttpDownloader.h"
#include "http/HttpService.h"

#include "win32/Win32EventArgs.h"
#include "win32/Win32EventListener.h"
#include "win32/Win32EventListenerKeyboard.h"
#include "win32/Win32Notifier.h"
#include "win32/KeyboardHelper.h"

#endif