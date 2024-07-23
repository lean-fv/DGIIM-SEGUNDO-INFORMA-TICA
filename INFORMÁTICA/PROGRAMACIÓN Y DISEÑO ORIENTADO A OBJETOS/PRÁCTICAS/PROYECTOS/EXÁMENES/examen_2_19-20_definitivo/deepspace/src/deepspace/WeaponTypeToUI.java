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
        type=t.toString();
        
    }
    
    public float getPower(){
        return power;
    }
    
    public String getType(){
        return type;
    }
}
