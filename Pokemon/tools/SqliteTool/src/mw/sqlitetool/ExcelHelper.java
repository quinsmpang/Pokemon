/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mw.sqlitetool;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.CellValue;
import org.apache.poi.ss.usermodel.DateUtil;
import org.apache.poi.ss.usermodel.FormulaEvaluator;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.ss.usermodel.Workbook;
import org.apache.poi.xssf.usermodel.XSSFWorkbook;

/**
 * Helper class to handle excel io.
 * @author Maple
 */
public class ExcelHelper {
    private static ExcelHelper _instance;
    
    public static ExcelHelper getInstance() {
        if (_instance == null) {
            _instance = new ExcelHelper();
        }
        return _instance;
    }
    
    private ExcelHelper() {}
    
    // const
    private static final int EXCEL_MAX_SIZE = 60000;
    
    public void importExcel(String filePath, boolean isXlsx, Action callback) throws Exception {
        FileInputStream fis = null;
        try {
            fis = new FileInputStream(filePath);
            Workbook workbook = null;
            if (isXlsx) {
                workbook = new XSSFWorkbook(fis);
            } else {
                workbook = new HSSFWorkbook(fis);
            }
            
            if (callback != null) {
                callback.invoke(workbook);
            }
            this._workbook = workbook;
        } catch (Exception ex) {
            throw new RuntimeException(ex);
        } finally {
            if (fis != null) {
                fis.close();
            }
        }
    }
    
    public void doActionForSheet(int sheetIndex, Action handler) {
        if (_workbook == null) {
            throw new RuntimeException("You have to import excel file at first.");
        }
        
        Sheet sheet = _workbook.getSheetAt(sheetIndex);
        if (sheet == null) {
            throw new RuntimeException("The sheet index is non-exist.");
        }
        
        handler.invoke(sheet);
    }
    
    public Object getCellValue(Cell cell) {
        if (cell == null || cell.getCellType() == cell.CELL_TYPE_BLANK) {
            return "";
        } else if (cell.getCellType() == cell.CELL_TYPE_BOOLEAN) {
            return cell.getBooleanCellValue();
        } else if (cell.getCellType() == cell.CELL_TYPE_ERROR) {
            return cell.getErrorCellValue();
        } else if (cell.getCellType() == cell.CELL_TYPE_FORMULA) {
            FormulaEvaluator evaluator = _workbook.getCreationHelper().createFormulaEvaluator();
            CellValue val = evaluator.evaluate(cell);
            if (val.getCellType() == cell.CELL_TYPE_BOOLEAN) {
                return val.getBooleanValue();
            } else if (val.getCellType() == cell.CELL_TYPE_NUMERIC) {
                return val.getNumberValue();
            } else if (val.getCellType() == cell.CELL_TYPE_STRING) {
                return val.getStringValue();
            } else if (val.getCellType() == cell.CELL_TYPE_ERROR) {
                return val.getErrorValue();
            }
        } else if (cell.getCellType() == cell.CELL_TYPE_NUMERIC) {
            if (DateUtil.isCellDateFormatted(cell)) {
                return cell.getDateCellValue();
            } else {
                return cell.getNumericCellValue();
            }
        } else if (cell.getCellType() == cell.CELL_TYPE_STRING) {
            return cell.getStringCellValue();
        }
        return "";
    }
    
    private Workbook _workbook;
}
