/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package controller;
import deepspace.GameUniverse;
import View.GUI.ExamView;
import deepspace.GameUniverseToUI;
import java.util.ArrayList;
import java.util.Collections;
import deepspace.SpaceFighterToUI;
/**
 *
 * @author leandrofdez
 */
public class ExamController {
    
    private static final ExamController instance = new ExamController();
 
    private GameUniverse game;
    private ExamView view;
    
    
    private ExamController () {}
    
    public static ExamController getInstance () {
      return instance;
    }
    
    public void setModelView (GameUniverse aGame, ExamView aView) {
      game = aGame;
      view = aView;
    }
    
    public void start() {
        
        view.updateView();
        view.showView();
    }
    
    
     public GameUniverseToUI getUIversion() {
      return game.getUIversion();
    }
    
    private void invertArray (ArrayList<Integer> array) {
      int i, n;
      
      n = array.size();
      for (i = 0; i < n/2; i++)
        Collections.swap(array, i, n-i-1);
    }
    
    public void addFighter(){
        game.addFighter();
    }
    
    public void deleteFighters(ArrayList<Integer> indexes){
        
        invertArray(indexes);
        for(Integer i: indexes) game.deleteFighter(i);
    }
    
    
    public ArrayList<SpaceFighterToUI> getUIFighters(){
        return game.getUIFighters();
    }
    
}
