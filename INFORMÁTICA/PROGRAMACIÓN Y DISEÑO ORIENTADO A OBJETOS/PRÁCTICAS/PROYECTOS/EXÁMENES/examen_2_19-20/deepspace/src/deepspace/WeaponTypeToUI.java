/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package deepspace;

/**
 *
 * @author leandrofdez
 */
public class WeaponTypeToUI {
    
    private float power;
    private String type;
    
    WeaponTypeToUI(WeaponType t){
        
        power=t.getPower();
        
        if (power==WeaponType.LASER.getPower()) type="LASER";
        else if (power == WeaponType.MISSILE.getPower()) type="MISSILE";
        else type="PLASMA";
    }
    
    public float getPower(){
        return power;
    }
    
    public String getType(){
        return type;
    }
    
}
