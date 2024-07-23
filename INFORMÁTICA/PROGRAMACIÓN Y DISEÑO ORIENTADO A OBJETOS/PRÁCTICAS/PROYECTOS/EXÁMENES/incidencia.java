/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package deepspace;
import java.util.ArrayList;

/**
 *
 * @author leandrofdez
 */
public class incidencia {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
        
        Damage dam_t1=new Damage(1,1);
        Damage dam_f1= new Damage(dam_t1);
        
        dam_f1.discardShieldBooster();
        dam_f1.discardWeapon(new Weapon("1",WeaponType.LASER,1));
        
   
        
        
        
        
        ArrayList<WeaponType> types= new ArrayList<WeaponType>();
        types.add(WeaponType.LASER);
        
        
        //Falso Segundo Contructor
        Damage dam_t2=new Damage(types,0);
    
        Damage dam_f2= new Damage(dam_t2);
        dam_f2.discardWeapon(new Weapon ("1",WeaponType.LASER,1));
        
        dam_t1.getUIVersion();
        dam_t2.getUIVersion();
        dam_f1.getUIVersion();
        dam_f2.getUIVersion();
        
        
        

        
        
        
        
    }
    
}
