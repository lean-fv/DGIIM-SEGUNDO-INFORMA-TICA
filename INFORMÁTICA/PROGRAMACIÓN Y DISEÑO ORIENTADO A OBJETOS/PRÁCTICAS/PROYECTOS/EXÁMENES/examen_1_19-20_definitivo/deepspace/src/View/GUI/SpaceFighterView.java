/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/GUIForms/JPanel.java to edit this template
 */
package View.GUI;
import deepspace.SpaceFighterToUI;
import java.awt.Color;

/**
 *
 * @author leandrofdez
 */
public class SpaceFighterView extends javax.swing.JPanel {
    
    private boolean selected=false;

    /**
     * Creates new form SpaceFighterView
     */
    public SpaceFighterView() {
        initComponents();
    }
    
    public void setSpaceFighter(SpaceFighterToUI f){
        
        jLFire.setText(Float.toString(f.getFire()));
    }
    
    public boolean isSelected(){
        return selected;
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jLabel1 = new javax.swing.JLabel();
        jLFire = new javax.swing.JLabel();

        addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                formMouseClicked(evt);
            }
        });

        jLabel1.setText("Fire: ");
        add(jLabel1);

        jLFire.setText("jLabel2");
        add(jLFire);
    }// </editor-fold>//GEN-END:initComponents

    private void formMouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_formMouseClicked
        // TODO add your handling code here:
        selected=!selected;
        setOpaque(selected);
        this.setBackground(Color.green);
        repaint();
        
        
    }//GEN-LAST:event_formMouseClicked


    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JLabel jLFire;
    private javax.swing.JLabel jLabel1;
    // End of variables declaration//GEN-END:variables
}
