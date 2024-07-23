/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package deepspace;
import java.util.ArrayList;

/**
 *
 * @author leandrofdez
 */
public class ExamenP4 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
        ArrayList<WeaponType> types = new ArrayList<>();
        
        types.add(WeaponType.LASER);
        types.add(WeaponType.MISSILE);
        types.add(WeaponType.MISSILE);
        types.add(WeaponType.PLASMA);
        types.add(WeaponType.PLASMA);
        types.add(WeaponType.PLASMA);
        
        SpecificDamage damage= new SpecificDamage(types,0);
        System.out.println(damage.getUIversion().toString());

        
        
        CardDealer dealer = CardDealer.getInstance();
        
        SpaceStation station = new SpaceStation("Leandro",dealer.nextSuppliesPackage());
        
        station.setLoot(new Loot (0,0,0,1,0));
        
        System.out.println(station.getUIversion().toString());
        
        final int NLASERS=3;
        final int NMISSILES=2;
        
        for (int i=0; i<NLASERS; i++){
            
            station.receiveWeapon(new Weapon("Weapon", WeaponType.LASER,1));
            station.mountWeapon(0);
        }
        
        for (int i=0; i<NMISSILES; i++){
            
            station.receiveWeapon(new Weapon("Weapon", WeaponType.MISSILE,1));
            station.mountWeapon(0);
            
        }
        
        station.receiveWeapon(new Weapon("Weapon", WeaponType.PLASMA,1));
        station.mountWeapon(0);
        
        System.out.println(station.getUIversion().toString());
        
        station.setPendingDamage(damage);
        
        System.out.println(station.getUIversion().toString());

        

        



    }
    
}
