/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mw.sqlitetool;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;

/**
 *
 * @author Maple
 */
public class SqliteHelper {
    private static SqliteHelper _instance;
    
    public static SqliteHelper getInstance() {
        if (_instance == null) {
            _instance = new SqliteHelper();
        }
        return _instance;
    }
    
    private SqliteHelper() {
        try {
            Class.forName("org.sqlite.JDBC");
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
    
    public void openDb(String filePath) throws SQLException {
        _conn = DriverManager.getConnection("jdbc:sqlite:" + filePath);
    }
    
    public void closeDb() throws SQLException {
        if (_conn != null) {
            _conn.close();
        }
    }
    
    public void executeSql(String sql) throws SQLException {
        if (_conn == null) {
            throw new RuntimeException("No db is loaded.");
        }
        Statement stat = _conn.createStatement();
        stat.executeUpdate(sql);
    }
    
    Connection _conn;
}
