/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mw.destool;

import java.io.Serializable;

/**
 *
 * @author Maple
 */
public class SaveData implements Serializable {
    private String _dataPath;
    private String _cipherKey;
    private String _skipItems;
    
    public SaveData(String dataPath, String cipherKey, String skipItems) {
        _dataPath = dataPath;
        _cipherKey = cipherKey;
        _skipItems = skipItems;
    }

    /**
     * @return the _dataPath
     */
    public String getDataPath() {
        return _dataPath;
    }

    /**
     * @param dataPath the dataPath to set
     */
    public void setDataPath(String dataPath) {
        this._dataPath = dataPath;
    }

    /**
     * @return the _cipherKey
     */
    public String getCipherKey() {
        return _cipherKey;
    }

    /**
     * @param cipherKey the cipherKey to set
     */
    public void setCipherKey(String cipherKey) {
        this._cipherKey = cipherKey;
    }

    /**
     * @return the skipItems
     */
    public String getSkipItems() {
        return _skipItems;
    }

    /**
     * @param skipItems the skipItems to set
     */
    public void setSkipItems(String skipItems) {
        this._skipItems = skipItems;
    }
}
