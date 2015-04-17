/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mw.sqlitetool;

import java.lang.reflect.Method;

/**
 * Simple Action delegate.
 * @author Maple
 */
public class Action {
    public Action(Object obj, String methodName) {
        this._target = obj;
        this._methodName = methodName;
    }
    
    public void invoke(Object... params) {
        Class<?>[] classAry = new Class[params.length];
        Object[] paramAry = new Object[params.length];
        if (params.length > 0) {
            for (int i = 0; i < params.length; i++) {
                classAry[i] = params[i].getClass();
            }
            for (int i = 0; i < params.length; i++) {
                paramAry[i] = params[i];
            }
        }
        
        try {
            Method method = _target.getClass().getDeclaredMethod(_methodName, classAry);
            if (method != null) {
                method.setAccessible(true);
                method.invoke(_target, paramAry);
            }
        } catch (Exception ex) {
            throw new RuntimeException(ex);
        }
    }

    private Object _target;
    private String _methodName;
}
