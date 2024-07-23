
/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */

package deepspace;
import java.util.ArrayList;

/**
 *
 * @author jaime
 */
public class Examen2 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        
        ArrayList<WeaponType> weapons = new ArrayList<WeaponType>();
        
        weapons.add(WeaponType.LASER);
        weapons.add(WeaponType.LASER);
        weapons.add(WeaponType.PLASMA);
        weapons.add(WeaponType.PLASMA);
        weapons.add(WeaponType.PLASMA);
        weapons.add(WeaponType.PLASMA);
        weapons.add(WeaponType.PLASMA);
        weapons.add(WeaponType.PLASMA);
        weapons.add(WeaponType.PLASMA);
        weapons.add(WeaponType.MISSILE);
        
        int nShieldBoosters = 8;  //Usar constantes
        
        
        Damage damage = new Damage(weapons, nShieldBoosters);
        
        
        while(!(damage.hasNoEffect())){
            
            if(!damage.getWeapons().isEmpty()){
                damage.discardWeapon(new Weapon("1",damage.getWeapons().get(0),1));
                
            }
            else if(nShieldBoosters!=0){
                damage.discardShieldBooster();
            }
            
        }
        
        System.out.println("El resultado de hasNoEffect es: " 
                               + damage.hasNoEffect());
        
        
    }
    
}
