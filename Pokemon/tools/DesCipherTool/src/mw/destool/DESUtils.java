/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mw.destool;

import java.io.File;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Maple
 */
public class DESUtils {
    // Singleton
    private static DESUtils _instance;
    
    public static DESUtils getInstance() {
        if (_instance == null) {
            _instance = new DESUtils();
        }
        return _instance;
    }
    
    private DESUtils() {
    }
    
    static {
        try {
            File root = new File(".");
            String rootPath = root.getCanonicalPath();
            System.load(rootPath + File.separator + "des.so");
        } catch (IOException ex) {
            Logger.getLogger(DESUtils.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public native byte[] encipher(byte[] content, byte[] cipherKey);
    
    public native byte[] decipher(byte[] content, byte[] cipherKey);
}
