/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mw.sqlitetool;

import java.io.File;
import java.io.IOException;
import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.JScrollBar;
import javax.swing.SwingUtilities;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.ss.usermodel.Cell;
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.xssf.usermodel.XSSFSheet;

/**
 *
 * @author Maple
 */
public class MainFrame extends javax.swing.JFrame {

    /**
     * Creates new form MainFrame
     */
    public MainFrame() {
        initComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        fcSelectDb = new javax.swing.JFileChooser();
        rbModeGroup = new javax.swing.ButtonGroup();
        lbl1 = new javax.swing.JLabel();
        txtDbPath = new javax.swing.JTextField();
        btnBrowseDb = new javax.swing.JButton();
        lbl2 = new javax.swing.JLabel();
        btnBrowseData = new javax.swing.JButton();
        txtDataPath = new javax.swing.JTextField();
        rbAll = new javax.swing.JRadioButton();
        rbExclude = new javax.swing.JRadioButton();
        rbOnly = new javax.swing.JRadioButton();
        txtModeContent = new javax.swing.JTextField();
        svLog = new javax.swing.JScrollPane();
        txtLog = new javax.swing.JTextArea();
        btnStart = new javax.swing.JButton();
        jLabel1 = new javax.swing.JLabel();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Sqlite Tool (By M.Wan)");
        setPreferredSize(new java.awt.Dimension(480, 410));
        setResizable(false);

        lbl1.setText("DBPath: ");

        btnBrowseDb.setText("Browse");
        btnBrowseDb.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnBrowseDbActionPerformed(evt);
            }
        });

        lbl2.setText("DataPath:");

        btnBrowseData.setText("Browse");
        btnBrowseData.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnBrowseDataActionPerformed(evt);
            }
        });

        rbModeGroup.add(rbAll);
        rbAll.setSelected(true);
        rbAll.setText("All");

        rbModeGroup.add(rbExclude);
        rbExclude.setText("Exclude");

        rbModeGroup.add(rbOnly);
        rbOnly.setText("Only");

        txtLog.setEditable(false);
        txtLog.setColumns(20);
        txtLog.setRows(5);
        txtLog.setDragEnabled(false);
        svLog.setViewportView(txtLog);

        btnStart.setText("Start");
        btnStart.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnStartActionPerformed(evt);
            }
        });

        jLabel1.setText("(Use ; to seperate.)");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(svLog)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                            .addComponent(btnStart)
                            .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                .addGroup(layout.createSequentialGroup()
                                    .addGap(12, 12, 12)
                                    .addComponent(lbl1)
                                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                    .addComponent(txtDbPath, javax.swing.GroupLayout.PREFERRED_SIZE, 303, javax.swing.GroupLayout.PREFERRED_SIZE)
                                    .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                    .addComponent(btnBrowseDb))
                                .addGroup(layout.createSequentialGroup()
                                    .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING)
                                        .addComponent(rbAll)
                                        .addComponent(lbl2))
                                    .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                                        .addGroup(layout.createSequentialGroup()
                                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                                            .addComponent(txtDataPath, javax.swing.GroupLayout.PREFERRED_SIZE, 301, javax.swing.GroupLayout.PREFERRED_SIZE)
                                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                            .addComponent(btnBrowseData))
                                        .addGroup(layout.createSequentialGroup()
                                            .addGap(36, 36, 36)
                                            .addComponent(rbExclude)
                                            .addGap(18, 18, 18)
                                            .addComponent(rbOnly)
                                            .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                            .addComponent(jLabel1)
                                            .addGap(39, 39, 39))))))
                        .addGap(0, 6, Short.MAX_VALUE))
                    .addComponent(txtModeContent, javax.swing.GroupLayout.Alignment.TRAILING))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(8, 8, 8)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(lbl1)
                    .addComponent(txtDbPath, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btnBrowseDb))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(lbl2)
                    .addComponent(btnBrowseData)
                    .addComponent(txtDataPath, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(rbExclude)
                    .addComponent(rbAll)
                    .addComponent(rbOnly)
                    .addComponent(jLabel1))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(txtModeContent, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(svLog, javax.swing.GroupLayout.DEFAULT_SIZE, 226, Short.MAX_VALUE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(btnStart)
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void btnBrowseDbActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnBrowseDbActionPerformed
        // TODO add your handling code here:
        fcSelectDb.setFileSelectionMode(JFileChooser.FILES_ONLY);
        int result = fcSelectDb.showOpenDialog(this);
        if (result == JFileChooser.APPROVE_OPTION) {
            txtDbPath.setText(fcSelectDb.getSelectedFile().getAbsolutePath());
        }
    }//GEN-LAST:event_btnBrowseDbActionPerformed

    private void btnBrowseDataActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnBrowseDataActionPerformed
        // TODO add your handling code here:
        fcSelectDb.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        int result = fcSelectDb.showOpenDialog(this);
        if (result == JFileChooser.APPROVE_OPTION) {
            txtDataPath.setText(fcSelectDb.getSelectedFile().getAbsolutePath());
        }
    }//GEN-LAST:event_btnBrowseDataActionPerformed

    private void btnStartActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnStartActionPerformed
        // TODO add your handling code here:
        if (txtDbPath.getText().trim().length() <= 0 || txtDataPath.getText().trim().length() <= 0) {
            JOptionPane.showMessageDialog(this, "The DB path or Data path is empty.");
            return;
        }
        File hDb = new File(txtDbPath.getText().trim());
        File hData = new File(txtDataPath.getText().trim());
        if (!hData.exists()) {
            JOptionPane.showMessageDialog(this, "The DB path or Data path doesn't exist.");
            return;
        }
        
        if (!hDb.exists()) {
            this.log("The db doesn't exist. Create a new one.");
        }
        try {
            // create db file.
            SqliteHelper.getInstance().openDb(txtDbPath.getText().trim());
        } catch (SQLException ex) {
            this.log("Error: " + ex.getMessage());
            return;
        }
        
        Thread worker = new Thread() {
            @Override
            public void run() {
                beginWork();
            }
        };
        worker.start();
    }//GEN-LAST:event_btnStartActionPerformed

    private void beginWork() {
        File hData = new File(txtDataPath.getText().trim());
        // foreach the data directory.
        try {
            if (txtModeContent.getText().trim().length() > 0) {
                _options = txtModeContent.getText().trim().split(";");
            } else {
                _options = null;
            }
            Action handler = new Action(this, "dealFile");
            this.doActionForEachFile(hData, handler);
            SqliteHelper.getInstance().closeDb();
            this.log("All complete.");
        } catch (Exception ex) {
            this.log("Error: " + ex.getMessage());
        }
    }
    
    private void doActionForEachFile(File dir, Action handler) {
        if (dir.isDirectory()) {
            File[] children = dir.listFiles();
            File hFile;
            for (int i = 0; i < children.length; i++) {
                hFile = children[i];
                if (hFile.isDirectory()) {
                    this.doActionForEachFile(hFile, handler);
                } else {
                    handler.invoke(hFile);
                }
            }
        }
    }
    
    private void dealFile(File file) {
        if (file.getName().lastIndexOf(".") > 0) {
            // exclude mode
            if (rbExclude.isSelected() && _options != null) {
                for (int i = 0; i < _options.length; i++) {
                    if (_options[i].equals(file.getName())) {
                        return;
                    }
                }
            }
            // include mode
            if (rbOnly.isSelected() && _options != null) {
                for (int i = 0; i < _options.length; i++) {
                    if (!_options[i].equals(file.getName())) {
                        return;
                    }
                }
            }
            String ext = file.getName().substring(file.getName().lastIndexOf(".") + 1);
            if (ext.equals("xlsx") || ext.equals("xls")) {
                this.log("Importing " + file.getAbsolutePath());
                _currentFile = file.getName().substring(0, file.getName().lastIndexOf("."));
                try {
                    // whether the table already exists?
                    String sql = "drop table if exists [" + _currentFile + "];";
                    this.log("Executing sql: " + sql);
                    SqliteHelper.getInstance().executeSql(sql);
                    ExcelHelper.getInstance().importExcel(file.getAbsolutePath(), ext.equals("xlsx"), null);
                    Action handler = new Action(this, "exportToDb");
                    ExcelHelper.getInstance().doActionForSheet(0, handler);
                } catch (IOException ex) {
                    Logger.getLogger(MainFrame.class.getName()).log(Level.SEVERE, null, ex);
                } catch (Exception ex) {
                    Logger.getLogger(MainFrame.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        }
    }
    
    private void exportToDb(XSSFSheet sheet) {
        this.innerExportToDb(sheet);
    }
    
    private void exportToDb(HSSFSheet sheet) {
        this.innerExportToDb(sheet);
    }
    
    private void innerExportToDb(Sheet sheet) {
        int rowNum = sheet.getLastRowNum();
        if (rowNum < 2) {
            throw new RuntimeException("Empty excel.");
        }
        // the first row is attribute names.
        Row firstRow = sheet.getRow(1);
        int colNum = firstRow.getLastCellNum();
        Cell cell = null;
        
        StringBuilder sb = new StringBuilder();
        sb.append("create table [");
        sb.append(_currentFile);
        sb.append("](");
        for (int i = 0; i < colNum; i++) {
            cell = firstRow.getCell(i);
            String attribute = ExcelHelper.getInstance().getCellValue(cell).toString();
            sb.append("[").append(attribute).append("] varchar(100)");
            if (i != colNum - 1) {
                sb.append(", ");
            }
        }
        sb.append(");");
        String sql = sb.toString();
        this.log("Executing sql: " + sql);
        try {
            SqliteHelper.getInstance().executeSql(sql);
        } catch (SQLException ex) {
            this.log("Error: " + ex.getMessage());
        }
        
        // import the data
        Row row = null;
        sql = "insert into [" + _currentFile + "] values(";
        for (int i = 2; i < rowNum; i++) {
            row = sheet.getRow(i);
            String tmpSql = sql;
            for (int j = 0; j < colNum; j++) {
                cell = row.getCell(j);
                String val = "\"" + ExcelHelper.getInstance().getCellValue(cell).toString().replace("\'", "\'\'") + "\"";
                tmpSql += val;
                if (j != colNum - 1) {
                    tmpSql += ", ";
                }
            }
            tmpSql += ");";
            this.log("Executing sql: " + tmpSql);
            try {
                SqliteHelper.getInstance().executeSql(tmpSql);
            } catch (SQLException ex) {
                this.log("Error: " + ex.getMessage());
            }
        }
    }
    
    private void log(String content) {
        _content = content;
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                txtLog.append(_content + "\n");
                JScrollBar scrollBar = svLog.getVerticalScrollBar();
                if (scrollBar != null) {
                    scrollBar.setValue(scrollBar.getMaximum());
                }
            }
        });
    }
    
    private String _currentFile;
    private String[] _options;
    private String _content;
    
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(MainFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(MainFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(MainFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(MainFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new MainFrame().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btnBrowseData;
    private javax.swing.JButton btnBrowseDb;
    private javax.swing.JButton btnStart;
    private javax.swing.JFileChooser fcSelectDb;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel lbl1;
    private javax.swing.JLabel lbl2;
    private javax.swing.JRadioButton rbAll;
    private javax.swing.JRadioButton rbExclude;
    private javax.swing.ButtonGroup rbModeGroup;
    private javax.swing.JRadioButton rbOnly;
    private javax.swing.JScrollPane svLog;
    private javax.swing.JTextField txtDataPath;
    private javax.swing.JTextField txtDbPath;
    private javax.swing.JTextArea txtLog;
    private javax.swing.JTextField txtModeContent;
    // End of variables declaration//GEN-END:variables
}
