/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mw.sqlitetool;

import java.io.Serializable;

/**
 *
 * @author Maple
 */
public class SaveData implements Serializable {
    private String _dbPath;
    private String _dataPath;
    private String _filters;
    
    public SaveData(String dbPath, String dataPath, String filters) {
        _dbPath = dbPath;
        _dataPath = dataPath;
        _filters = filters;
    }

    /**
     * @return the _dbPath
     */
    public String getDbPath() {
        return _dbPath;
    }

    /**
     * @param dbPath the _dbPath to set
     */
    public void setDbPath(String dbPath) {
        this._dbPath = dbPath;
    }

    /**
     * @return the _dataPath
     */
    public String getDataPath() {
        return _dataPath;
    }

    /**
     * @param dataPath the _dataPath to set
     */
    public void setDataPath(String dataPath) {
        this._dataPath = dataPath;
    }

    /**
     * @return the _filters
     */
    public String getFilters() {
        return _filters;
    }

    /**
     * @param filters the _filters to set
     */
    public void setFilters(String filters) {
        this._filters = filters;
    }
}
