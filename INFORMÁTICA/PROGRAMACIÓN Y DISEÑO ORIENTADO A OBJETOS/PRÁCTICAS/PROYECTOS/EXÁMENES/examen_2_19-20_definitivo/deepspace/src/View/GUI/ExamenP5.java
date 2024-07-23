/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/GUIForms/JFrame.java to edit this template
 */
package View.GUI;
import View.ExamenP5View;
import controller.ExamenP5Controller;
import deepspace.EnemyToUI;

/**
 *
 * @author leandrofdez
 */
public class ExamenP5 extends javax.swing.JFrame implements ExamenP5View{

     private static ExamenP5 instance = null;
     
     private static EnemyStarShipView enemyView;
    /**
     * Creates new form ExamenP5
     */
     
    public static ExamenP5 getInstance() {
        if (instance == null) {
          instance = new ExamenP5();
        }
        return instance;
    }
    
    
    public ExamenP5() {
        initComponents();
        
        enemyView= new EnemyStarShipView();
        repaint();
        
        
    }
    
    public void showView(){
        this.setVisible(true);
    }
    
    public void updateView(){
        
        EnemyToUI enemy= ExamenP5Controller.getInstance().nextEnemy();
        
        enemyView.setEnemy(enemy);
        jPEnemy.add(enemyView);
        
        repaint();
        revalidate();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPEnemy = new javax.swing.JPanel();
        jBNextEnemy = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);

        jBNextEnemy.setText("NEXT ENEMY");
        jBNextEnemy.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jBNextEnemyActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(15, 15, 15)
                        .addComponent(jPEnemy, javax.swing.GroupLayout.PREFERRED_SIZE, 1014, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(453, 453, 453)
                        .addComponent(jBNextEnemy)))
                .addContainerGap(57, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(46, 46, 46)
                .addComponent(jPEnemy, javax.swing.GroupLayout.DEFAULT_SIZE, 694, Short.MAX_VALUE)
                .addGap(18, 18, 18)
                .addComponent(jBNextEnemy, javax.swing.GroupLayout.PREFERRED_SIZE, 62, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(62, 62, 62))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void jBNextEnemyActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jBNextEnemyActionPerformed
        // TODO add your handling code here:
        updateView();
    }//GEN-LAST:event_jBNextEnemyActionPerformed


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jBNextEnemy;
    private javax.swing.JPanel jPEnemy;
    // End of variables declaration//GEN-END:variables
}
