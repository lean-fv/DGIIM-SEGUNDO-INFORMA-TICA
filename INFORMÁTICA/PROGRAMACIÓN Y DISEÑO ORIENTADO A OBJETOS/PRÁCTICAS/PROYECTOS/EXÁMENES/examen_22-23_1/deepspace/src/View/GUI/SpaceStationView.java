/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/GUIForms/JPanel.java to edit this template
 */
package View.GUI;

import controller.Controller;
import deepspace.SpaceStationToUI;
import java.awt.Component;
import java.util.ArrayList;
import javax.swing.JOptionPane;
import deepspace.WeaponToUI;
import deepspace.ShieldToUI;
import deepspace.GameState;


/**
 *
 * @author leandrofdez
 */
public class SpaceStationView extends javax.swing.JPanel {

    private HangarView hangarView;
    private DamageView damageView;
    
    /**
     * Creates new form SpaceStationView
     */
    //************************************************************************//
    //Creamos una instancia de HangarView y de DamageView y las inicializamos
    //Porque en tiempo de diseño sabemos que la vista contenedora(SpaceStation)
    //siempre va a contener a UN solo hangar y UN solo damage.
    //En cambio en HangarView no creamos una instancia de WeaponView o de 
    //ShieldBoosterView porque no sabemos cuantos va a haber(usaremos un JScrollPanel).
    //************************************************************************//
    public SpaceStationView() {
        initComponents();
        
        repaint();
        revalidate();
        
    }
    
    ArrayList<Integer> getSelectedWeaponsMounted () {
        ArrayList<Integer> selectedWeapons = new ArrayList<>();
        int i = 0;
        for (Component c : jPMountedWeapons.getComponents()) {
            if (((WeaponView) c).isSelected()) {
                selectedWeapons.add(i);
            }
            i++;
        }
        return selectedWeapons;
    }
    
    ArrayList<Integer> getSelectedShieldsMounted () {
        ArrayList<Integer> selectedShields = new ArrayList<>();
        int i = 0;
        for (Component c : jPMountedShields.getComponents()) {
            if (((ShieldBoosterView) c).isSelected()) {
                selectedShields.add(i);
            }
            i++;
        }
        return selectedShields;
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        stationName = new javax.swing.JLabel();
        stationFire = new javax.swing.JLabel();
        jLSpaceStationName = new javax.swing.JLabel();
        jLPower = new javax.swing.JLabel();
        jLShield = new javax.swing.JLabel();
        jLFuel = new javax.swing.JLabel();
        jLMedals = new javax.swing.JLabel();
        jScrollPane1 = new javax.swing.JScrollPane();
        jPMountedWeapons = new javax.swing.JPanel();
        jScrollPane2 = new javax.swing.JScrollPane();
        jPMountedShields = new javax.swing.JPanel();
        jPHangar = new javax.swing.JPanel();
        jBMount = new javax.swing.JButton();
        jBDiscard = new javax.swing.JButton();
        jBDiscardHangar = new javax.swing.JButton();
        jPDamage = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        jLabel2 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();
        jLabel5 = new javax.swing.JLabel();

        setBackground(new java.awt.Color(204, 204, 204));
        setBorder(javax.swing.BorderFactory.createLineBorder(new java.awt.Color(0, 0, 0)));

        jLSpaceStationName.setBackground(new java.awt.Color(153, 153, 153));
        jLSpaceStationName.setFont(new java.awt.Font("Liberation Sans", 1, 18)); // NOI18N
        jLSpaceStationName.setText("jLabel1");

        jLPower.setText("jLabel2");

        jLShield.setText("jLabel3");

        jLFuel.setText("jLabel4");

        jLMedals.setText("jLabel5");

        jPMountedWeapons.setBorder(javax.swing.BorderFactory.createTitledBorder("Mounted Weapons"));
        jScrollPane1.setViewportView(jPMountedWeapons);

        jPMountedShields.setBorder(javax.swing.BorderFactory.createTitledBorder("Mounted Shields"));
        jScrollPane2.setViewportView(jPMountedShields);

        jBMount.setText("Mount");
        jBMount.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jBMountActionPerformed(evt);
            }
        });

        jBDiscard.setText("Discard");
        jBDiscard.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jBDiscardActionPerformed(evt);
            }
        });

        jBDiscardHangar.setText("Discard Whole Hangar");
        jBDiscardHangar.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jBDiscardHangarActionPerformed(evt);
            }
        });

        jPDamage.setBorder(javax.swing.BorderFactory.createTitledBorder("Pending Punishment"));

        jLabel1.setText("Name: ");

        jLabel2.setText("Ammo Power: ");

        jLabel3.setText("Shield Power: ");

        jLabel4.setText("Fuel Units");

        jLabel5.setText("Medals: ");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(17, 17, 17)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(jScrollPane2)
                            .addComponent(jScrollPane1, javax.swing.GroupLayout.DEFAULT_SIZE, 930, Short.MAX_VALUE)
                            .addComponent(jPHangar, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addGroup(layout.createSequentialGroup()
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addComponent(stationName)
                                    .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                                        .addComponent(stationFire)
                                        .addComponent(jLabel2, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                        .addComponent(jLabel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                                    .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.TRAILING, false)
                                        .addComponent(jLabel5, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                        .addComponent(jLabel3, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                        .addComponent(jLabel4, javax.swing.GroupLayout.Alignment.LEADING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)))
                                .addGap(18, 18, 18)
                                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                                    .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                                        .addComponent(jLPower, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                        .addComponent(jLShield, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                        .addComponent(jLFuel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                                        .addComponent(jLMedals, javax.swing.GroupLayout.PREFERRED_SIZE, 96, javax.swing.GroupLayout.PREFERRED_SIZE))
                                    .addComponent(jLSpaceStationName, javax.swing.GroupLayout.PREFERRED_SIZE, 326, javax.swing.GroupLayout.PREFERRED_SIZE))
                                .addGap(18, 18, 18)
                                .addComponent(jPDamage, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(26, 26, 26)
                        .addComponent(jBMount)
                        .addGap(18, 18, 18)
                        .addComponent(jBDiscard)
                        .addGap(18, 18, 18)
                        .addComponent(jBDiscardHangar)))
                .addContainerGap(28, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(stationName)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(48, 48, 48)
                        .addComponent(jLabel3)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jLabel4)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jLabel5))
                    .addComponent(stationFire)
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jLabel1)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jLabel2))
                    .addGroup(layout.createSequentialGroup()
                        .addComponent(jLSpaceStationName)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jLPower)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jLShield)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jLFuel)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                        .addComponent(jLMedals))
                    .addComponent(jPDamage, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(jScrollPane1, javax.swing.GroupLayout.PREFERRED_SIZE, 135, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(jScrollPane2, javax.swing.GroupLayout.PREFERRED_SIZE, 141, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jPHangar, javax.swing.GroupLayout.PREFERRED_SIZE, 328, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jBMount)
                    .addComponent(jBDiscard)
                    .addComponent(jBDiscardHangar))
                .addContainerGap(22, Short.MAX_VALUE))
        );
    }// </editor-fold>//GEN-END:initComponents

    private void jBMountActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jBMountActionPerformed
        // TODO add your handling code here:
        Controller.getInstance().mount(hangarView.getSelectedWeapons(), hangarView.getSelectedShields());
        
        MainWindow.getInstance().updateView();
    }//GEN-LAST:event_jBMountActionPerformed

    private void jBDiscardHangarActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jBDiscardHangarActionPerformed
        // TODO add your handling code here:
        JOptionPane.showMessageDialog(this, "******* Hangar Completo Descartado *******", MainWindow.getInstance().getAppName(), JOptionPane.INFORMATION_MESSAGE);
        Controller.getInstance().discardHangar();
        
        MainWindow.getInstance().updateView();
    }//GEN-LAST:event_jBDiscardHangarActionPerformed

    private void jBDiscardActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jBDiscardActionPerformed
        // TODO add your handling code here:
        Controller.getInstance().discard(Controller.WEAPON, this.getSelectedWeaponsMounted(), this.getSelectedShieldsMounted());
        Controller.getInstance().discard(Controller.SHIELD, this.getSelectedWeaponsMounted(), this.getSelectedShieldsMounted());
        
        if(hangarView.isVisible()){
            Controller.getInstance().discard(Controller.HANGAR, hangarView.getSelectedWeapons(), hangarView.getSelectedShields());
        }
        
        MainWindow.getInstance().updateView();
    }//GEN-LAST:event_jBDiscardActionPerformed

    
    
    //Completar
    void setSpaceStation(SpaceStationToUI station){
        
        jLSpaceStationName.setText(station.getName());
        jLPower.setText(Float.toString(station.getAmmoPower()));
        jLShield.setText(Float.toString(station.getShieldPower()));
        jLFuel.setText(Float.toString(station.getFuelUnits()));
        jLMedals.setText(Integer.toString(station.getnMedals()));
        
        ArrayList<WeaponToUI> weapons = station.getWeapons();
        ArrayList<ShieldToUI> shieldBoosters = station.getShieldBoosters();
        
        jPMountedWeapons.removeAll();
        jPMountedShields.removeAll();
        jPHangar.removeAll();
        jPDamage.removeAll();
        
        WeaponView weaponView;
        for(WeaponToUI w : weapons){
            weaponView = new WeaponView();
            weaponView.setWeapon(w);
            jPMountedWeapons.add(weaponView);
        }
        
        ShieldBoosterView shieldView;
        for(ShieldToUI s : shieldBoosters){
            shieldView = new ShieldBoosterView();
            shieldView.setShield(s);
            jPMountedShields.add(shieldView);
        }
        
        damageView = new DamageView();
        damageView.setDamage(station.getPendingDamage());
        jPDamage.add(damageView);
             
        hangarView = new HangarView(); 
        hangarView.setHangar(station.getHangar());
        jPHangar.add(hangarView);
        
        enabledButtons(station);
        
        repaint();
        revalidate();
        
        
    }
    
    void enabledButtons(SpaceStationToUI station){
        boolean hangarAvailable = station.getHangar() != null;
        
        GameState gameState = Controller.getInstance().getState();
        boolean init = gameState == GameState.INIT;
        boolean aftercombat = gameState == GameState.AFTERCOMBAT;
        boolean available_state=(init || aftercombat);
        
        boolean shieldsInHangar = false;
        boolean weaponsInHangar = false;
        boolean elementsInHangar = false;
        
        if(hangarAvailable){
            weaponsInHangar = (station.getHangar().getWeapons().size() != 0);
            shieldsInHangar = (station.getHangar().getShieldBoosters().size() != 0);
            
            elementsInHangar = weaponsInHangar || shieldsInHangar;
            
        }
        
        boolean sth_in_hangar= weaponsInHangar || shieldsInHangar;
        
        boolean weaponsMounted = !station.getWeapons().isEmpty();
        boolean shieldsMounted = !station.getShieldBoosters().isEmpty();
        
        boolean sth_mounted = weaponsMounted || shieldsMounted;
        
        
        
        jBDiscardHangar.setEnabled(hangarAvailable && available_state);
        jBMount.setEnabled(hangarAvailable && sth_in_hangar && available_state);
        jBDiscard.setEnabled((elementsInHangar || sth_mounted) && available_state);
        
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton jBDiscard;
    private javax.swing.JButton jBDiscardHangar;
    private javax.swing.JButton jBMount;
    private javax.swing.JLabel jLFuel;
    private javax.swing.JLabel jLMedals;
    private javax.swing.JLabel jLPower;
    private javax.swing.JLabel jLShield;
    private javax.swing.JLabel jLSpaceStationName;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JPanel jPDamage;
    private javax.swing.JPanel jPHangar;
    private javax.swing.JPanel jPMountedShields;
    private javax.swing.JPanel jPMountedWeapons;
    private javax.swing.JScrollPane jScrollPane1;
    private javax.swing.JScrollPane jScrollPane2;
    private javax.swing.JLabel stationFire;
    private javax.swing.JLabel stationName;
    // End of variables declaration//GEN-END:variables
}
